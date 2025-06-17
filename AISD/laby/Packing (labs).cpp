#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector < int > wyplaty;
vector < int > wagi;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; // ilosc przedmiotow
    int t; // ladownosc wozu
    int pom;

    int output = 0;
    int k = 500;
    while (k--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> pom;
            wyplaty.push_back(pom);
        }

        for (int i = 0; i < n; i++)
        {
            cin >> pom;
            wagi.push_back(pom);
        }
        cin >> t;

        for (int i = 0; i < pow(2, n); i++)
        {
            int totalW = 0;
            int totalP = 0;

            for (int j = 0; j < n; j++)
            {
                if (i & (1 << j))
                {
                    totalW += wagi[j];
                    totalP += wyplaty[j];

                }
            }
            if (totalW <= t)
            {
                if (output < totalP)
                    output = totalP;
            }
        }
        cout << output << "\n";
        output = 0;
        wyplaty.clear();
        wagi.clear();
    }





    return 0;

}
