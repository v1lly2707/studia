#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <cstring>
#include <mutex>
#include <sstream>
#include <sys/stat.h>
#include <csignal>

using namespace std;

bool Prime(int n) {
    if(n <= 1) return false;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0)
            return false;
    }
    return true;
}

struct Data {
    int index;
    int size;
    sem_t mutex;
};

void thread_function(int* numbers, bool* results, Data* data) {
    while(1) {
        sem_wait(&data->mutex);
        if(data->index >= data->size) {
            sem_post(&data->mutex);
            break;
        }
        int idx = data->index++;
        sem_post(&data->mutex);
        results[idx] = Prime(numbers[idx]);
    }
}

void createNamedPipe(const string& name) {
    if (access(name.c_str(), F_OK) == -1) {
        mkfifo(name.c_str(), 0666);
    }
}

void cleanupNamedPipe(const string& name) {
    unlink(name.c_str());
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "Użycie: ./program <liczba_procesów> <liczba_wątków>\n";
        return 1;
    }

    int P = atoi(argv[1]);
    int W = atoi(argv[2]);

    string fifoName = "zadania.in";
    createNamedPipe(fifoName);

    vector<pid_t> children(P);
    int ptc[P][2], ctp[P][2];

    for(int i = 0; i < P; i++) {
        pipe(ptc[i]);
        pipe(ctp[i]);

        pid_t pid = fork();
        if(pid == 0) {
            // Dziecko
            close(ptc[i][1]);
            close(ctp[i][0]);

            while(true) {
                int size;
                if(read(ptc[i][0], &size, sizeof(int)) <= 0 || size == -1)
                    break;

                vector<int> nums(size);
                read(ptc[i][0], nums.data(), size * sizeof(int));

                int* numbers = new int[size];
                bool* results = new bool[size];
                memcpy(numbers, nums.data(), size * sizeof(int));

                Data* data = new Data{0, size};
                sem_init(&data->mutex, 0, 1);

                vector<thread> threads;
                for(int t = 0; t < W; t++)
                    threads.emplace_back(thread_function, numbers, results, data);

                for(auto& t : threads)
                    t.join();

                write(ctp[i][1], &size, sizeof(int));
                write(ctp[i][1], results, size * sizeof(bool));

                delete[] numbers;
                delete[] results;
                sem_destroy(&data->mutex);
                delete data;
            }

            exit(0);
        } else {
            // Rodzic
            children[i] = pid;
            close(ptc[i][0]);
            close(ctp[i][1]);
        }
    }

    int fifoFD = open(fifoName.c_str(), O_RDONLY);
    FILE* fifoFile = fdopen(fifoFD, "r");
    if (!fifoFile) {
        cerr << "Błąd otwierania potoku\n";
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fifoFile)) {
        string line(buffer);
        if(line.empty() || line == "\n") continue;

        istringstream iss(line);
        string tok;
        iss >> tok;

        if(tok == "EXIT") {
            int endSignal = -1;
            for(int i = 0; i < P; i++)
                write(ptc[i][1], &endSignal, sizeof(int));

            for(int i = 0; i < P; i++)
                waitpid(children[i], NULL, 0);

            break;
        }

        int start, end;
        string name;
        start = stoi(tok);
        iss >> end >> name;

        int Z = end - start + 1;
        vector<int> numbers(Z);
        for(int i = 0; i < Z; i++)
            numbers[i] = start + i;

        int perProcess = (Z + P - 1) / P;
        vector<bool> Final;

        for(int i = 0; i < P; i++) {
            int s = i * perProcess;
            if(s >= Z) break;

            int e = min(s + perProcess, Z);
            vector<int> subset(numbers.begin() + s, numbers.begin() + e);
            int size = subset.size();
            write(ptc[i][1], &size, sizeof(int));
            write(ptc[i][1], subset.data(), size * sizeof(int));
        }

        for(int i = 0; i < P; i++) {
            int s = i * perProcess;
            if(s >= Z) break;

            int size;
            read(ctp[i][0], &size, sizeof(int));
            vector<char> raw(size);
            read(ctp[i][0], raw.data(), size);
            for(int j = 0; j < size; ++j)
                Final.push_back(raw[j]);
        }

        ofstream out(name);
        for(int i = 0; i < Z; i++) {
            if(Final[i])
                out << numbers[i] << " jest pierwsza\n";
            else
                out << numbers[i] << " nie jest pierwsza\n";
        }
    }

    fclose(fifoFile);
    cleanupNamedPipe(fifoName);
    return 0;
}
