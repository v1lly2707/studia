#include <iostream>

using namespace std;

struct Vector
{
    int* data;
    int capacity;
    int size;

    Vector()
    {
        capacity = 10;
        size = 0;
        data = new int[capacity];
    }

    void push_back(int val)
    {
        if (size == capacity)
        {
            capacity *= 2;
            int* newData = new int[capacity];

            for (int i = 0; i < size; i++)
                newData[i] = data[i];

            delete[] data;
            data = newData;
        }
        data[size++] = val;
    }

    void clear()
    {
        delete[] data;
        capacity = 10;
        size = 0;
        data = new int[capacity];
    }

    ~Vector()
    {
        delete[] data; // deskruktor wektora
    }
};

struct Queue
{
    int* data;
    int front, rear, size, capacity;

    Queue(int cap)
    {
        capacity = cap;
        front = size = 0;
        rear = capacity - 1;
        data = new int[capacity];
    }

    bool isFull()
    {
        return (size == capacity);
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    void add(int item) // dodawanie elementu do kolejki
    {
        if (isFull())
            return;

        rear = (rear + 1) % capacity;
        data[rear] = item;
        size++;
    }

    int pop() // usuwanie elementu z kolejki
    {
        if (isEmpty())
            return -1;

        int item = data[front];
        front = (front + 1) % capacity;
        size--;
        return item;
    }

    ~Queue()
    {
        delete[] data; // deskruktor kolejki
    }
};

struct Graph // struktura grafu
{
    bool ifVisited;
    Vector vec; // przechowywanie polaczen w grafie
} *w;

void merge(int arr[], int left, int mid, int right) // do merge sort
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) // merge sort do sortowania ciagu stopniowego
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void dfs(int v) // dfs do przeszukiwania grafu
{
    w[v].ifVisited = true;
    for (int i = 0; i < w[v].vec.size; i++)
    {
        int u = w[v].vec.data[i];
        if (!w[u].ifVisited)
        {
            dfs(u);
        }
    }
}

bool isBipartite(int n) // algorytm do dwudzielnosci
{
    int* color = new int[n + 1];
    for (int i = 0; i <= n; i++) color[i] = -1;

    Queue q(n + 1);

    for (int i = 1; i <= n; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            q.add(i);

            while (!q.isEmpty())
            {
                int v = q.pop();

                for (int j = 0; j < w[v].vec.size; j++)
                {
                    int u = w[v].vec.data[j];

                    if (color[u] == -1)
                    {
                        color[u] = 1 - color[v];
                        q.add(u);
                    }
                    else if (color[u] == color[v])
                    {
                        delete[] color;
                        return false;
                    }
                }
            }
        }
    }

    delete[] color;
    return true;
}

int* greedyColoring(int n) // kolorowanie grafu metoda zachlanna
{
    int* result = new int[n + 1];
    for (int i = 0; i <= n; i++) result[i] = -1;

    bool* available = new bool[n + 1];
    for (int i = 0; i <= n; i++) available[i] = false;

    result[1] = 0;

    for (int u = 2; u <= n; u++)
    {
        for (int i = 0; i < w[u].vec.size; i++)
        {
            int v = w[u].vec.data[i];
            if (result[v] != -1)
                available[result[v]] = true;
        }

        int cr;
        for (cr = 0; cr < n; cr++)
        {
            if (!available[cr])
                break;
        }

        result[u] = cr;

        for (int i = 0; i < w[u].vec.size; i++)
        {
            int v = w[u].vec.data[i];
            if (result[v] != -1)
                available[result[v]] = false;
        }
    }

    for (int i = 1; i <= n; i++)
        result[i]++;

    delete[] available;
    return result;
}

void _clear(int n) // czyszczenie grafu
{
    for (int i = 0; i <= n; ++i)
    {
        w[i].ifVisited = false;
        w[i].vec.clear();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int k;
    cin >> k;

    while (k--)
    {
        int n;
        cin >> n;

        int* tab = new int[n];

        w = new Graph[n + 5];

        _clear(n);

        long long EdgeCounter = 0;

        for (int i = 0; i < n; i++)
        {
            int s;
            cin >> s;
            EdgeCounter += s;

            for (int j = 0; j < s; j++)
            {
                int a;
                cin >> a;
                w[i + 1].vec.push_back(a);
            }
            tab[i] = s;
        }

        int cnt = 0;

        for (int i = 1; i <= n; i++)
        {
            if (!w[i].ifVisited)
            {
                dfs(i);
                cnt++;
            }
        }

        mergeSort(tab, 0, n - 1);

        for (int i = n - 1; i >= 0; i--)
            cout << tab[i] << ' ';

        cout << "\n";

        cout << cnt << "\n";

        if (isBipartite(n))
            cout << "T\n";
        else
            cout << "F\n";

        cout << "?\n?\n";

        int* colors = greedyColoring(n);

        for (int i = 1; i <= n; i++)
            cout << colors[i] << ' ';

        cout << "\n";

        delete[] tab;
        delete[] colors;

        for (int i = 1; i <= 3; i++)
            cout << "?\n";

        long long out = ((long long)n * ((long long)n - 1) / 2) - (EdgeCounter / 2);
        cout << out << "\n";

        delete[] w;
    }

    return 0;
}
