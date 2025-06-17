#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Globalna zmienna do zliczania liczby dodawań
int addition_count = 0;
pthread_mutex_t lock;

// Funkcja do obliczania n-tego wyrazu ciągu Fibonacciego
long fibonacci(int n) {
    if (n <= 1) return n;
    pthread_mutex_lock(&lock);
    addition_count++;
    pthread_mutex_unlock(&lock);
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Funkcja dla wątku
void* thread_function(void* arg) {
    int n = *(int*)arg;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    printf("Watek: Obliczam %d-ty wyraz ciagu Fibonacciego...\n", n);
    long result = fibonacci(n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Wynik: %ld\n", result);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Watek: Wynik = %ld, czas trwania = %.6f s\n", result, elapsed_time);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uzycie: %s <liczba_procesow> <liczba_wątkow>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int fib = 30; 
    struct timespec total_start, total_end;
    double final_time = 2^30 * (num_processes * num_threads); 

    pthread_mutex_init(&lock, NULL);
    clock_gettime(CLOCK_MONOTONIC, &total_start);

    for (int p = 0; p < num_processes; p++) {
        int pid = fork();
        if (pid == 0) {
            pthread_t threads[num_threads];
            for (int t = 0; t < num_threads; t++) {
                pthread_create(&threads[t], NULL, thread_function, &fib);
            }
            for (int t = 0; t < num_threads; t++) {
                pthread_join(threads[t], NULL);
            }
            exit(0);
        }
    }

    for (int p = 0; p < num_processes; p++) {
        wait(NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &total_end);
    double total_elapsed_time = (total_end.tv_sec - total_start.tv_sec) +
                                (total_end.tv_nsec - total_start.tv_nsec) / 1e9;

    printf("Laczny czas obliczen: %e \n", final_time/total_elapsed_time);
    

    pthread_mutex_destroy(&lock);
    return 0;
}