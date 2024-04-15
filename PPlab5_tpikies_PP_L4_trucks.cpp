//This code passes all of the tests, but was given 25% score due to using a vector:)

#include <iostream>
#include <vector>

using namespace std;

vector < int > Cities[10005];
vector < int > Trucks[10005];
int arr[10005];

void _clear()
{
    for (int i = 0; i < 10005; i++)
        Cities[i].clear();
}

int main()
{
    for (int i = 0; i < 10005; i++)
        arr[i] = 0;
    int n; // number of cities
    cin >> n;
    int m; // number of trucks
    cin >> m;
    int l;
    int id;
    for (int i = 0; i < m; i++)
    {
        cin >> l; // length of the route;
        for (int j = 0; j < l; j++)
        {
            cin >> id;
            Trucks[i].push_back(id);
        }

    }
    int d;
    cin >> d; // number of days to pass
    d++;
    int pom = d;
    while (d--)
    {
        cout << "TRUCKS:\n";
        for (int i = 0; i < m; i++)
        {
            cout << i << ": ";
            if (arr[i] + 1 <= Trucks[i].size())
            {
                cout << Trucks[i][arr[i]] << '\n';
                Cities[Trucks[i][arr[i]]].push_back(i);
                arr[i]++;
            }
            else
            {
                arr[i] = 0;

                cout << Trucks[i][arr[i]] << '\n';
                Cities[Trucks[i][arr[i]]].push_back(i);
                arr[i]++;
            }


        }
        cout << "CITIES:\n";
        for (int j = 0; j < n; j++)
        {
            cout << j << ": ";
            for (int k = 0; k < Cities[j].size(); k++)
            {
                cout << Cities[j][k] << ' ';
            }
            cout << endl;
        }
        _clear();
    }
}
