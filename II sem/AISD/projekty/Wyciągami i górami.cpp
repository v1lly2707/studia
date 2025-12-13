#include <iostream>

using namespace std;

const int MAX = 10000;

struct Lift 
{
    int columnStart, rowStart;
    int columnEnd, rowEnd;
    int time;  
    int minutes;  
};

struct Node 
{
    int time;
    int row, col;
};

struct PriorityQueue 
{
    Node heap[MAX];
    int size = 0;

    void swap(Node& a, Node& b) 
    {
        Node tmp = a;
        a = b;
        b = tmp;
    }

    void push(Node val) 
    {
        int i = size++;
        heap[i] = val;
        while (i > 0) 
        {
            int p = (i - 1) / 2;
            if (heap[p].time <= heap[i].time)
                break;
            swap(heap[i], heap[p]);
            i = p;
        }
    }

    Node pop() 
    {
        Node res = heap[0];
        heap[0] = heap[--size];
        int i = 0;
        while (true) 
        {
            int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
            if (l < size && heap[l].time < heap[smallest].time) 
                smallest = l;
            if (r < size && heap[r].time < heap[smallest].time)
                smallest = r;
            if (smallest == i)
                break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
        return res;
    }

    bool empty() 
    {
        return size == 0;
    }
};

void readInput(int& width, int& height, int& columnStart, int& rowStart, int& columnEnd, int& rowEnd, int& n, Lift*& lifts, int**& map)
{
    cin >> width >> height >> columnStart >> rowStart >> columnEnd >> rowEnd >> n;

    lifts = new Lift[n];
    for (int i = 0; i < n; i++) 
        cin >> lifts[i].columnStart >> lifts[i].rowStart >> lifts[i].columnEnd >> lifts[i].rowEnd >> lifts[i].time >> lifts[i].minutes;

    map = new int*[height];
    for (int i = 0; i < height; i++) 
    {
        map[i] = new int[width];
        for (int j = 0; j < width; j++)
            cin >> map[i][j];
    }
}

void _Clear(Lift* lifts, int** map, int** dist, int height)
{
    delete[] lifts;
    for (int i = 0; i < height; i++) 
    {
        delete[] map[i];
        delete[] dist[i];
    }
    delete[] map;
    delete[] dist;
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int width, height;
    int columnStart, rowStart;
    int columnEnd, rowEnd;
    int n;

    Lift* lifts = nullptr;
    int** map = nullptr;

    readInput(width, height, columnStart, rowStart, columnEnd, rowEnd, n, lifts, map);

    int** dist = new int*[height];
    for (int i = 0; i < height; i++) 
    {
        dist[i] = new int[width];
        for (int j = 0; j < width; j++)
            dist[i][j] = INT_MAX;
    }

    PriorityQueue pq;
    dist[rowStart][columnStart] = 0;
    pq.push({0, rowStart, columnStart});

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!pq.empty()) 
    {
        Node cur = pq.pop();
        int t = cur.time;
        int r = cur.row;
        int c = cur.col;

        if (t > dist[r][c])
            continue;

        for (int d = 0; d < 4; d++) 
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= height || nc < 0 || nc >= width)
                continue;

            int cost = (map[nr][nc] > map[r][c]) ? (map[nr][nc] - map[r][c] + 1) : 1;
            if (t + cost < dist[nr][nc]) 
            {
                dist[nr][nc] = t + cost;
                pq.push({t + cost, nr, nc});
            }
        }

        for (int i = 0; i < n; i++) 
        {
            if (lifts[i].rowStart == r && lifts[i].columnStart == c) 
            {
                int wait = (lifts[i].minutes - (t % lifts[i].minutes)) % lifts[i].minutes;
                int arrival = t + wait + lifts[i].time;
                int rr = lifts[i].rowEnd;
                int cc = lifts[i].columnEnd;

                if (arrival < dist[rr][cc]) 
                {
                    dist[rr][cc] = arrival;
                    pq.push({arrival, rr, cc});
                }
            }
        }
    }

    cout << dist[rowEnd][columnEnd] << "\n";

    _Clear(lifts, map, dist, height);
    return 0;
}
