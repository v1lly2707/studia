#include <iostream>
#include <cmath>
using namespace std;

struct t1
{
    int x, y;
};


int main()
{
    int t, n, a, b;
    cin >> t;
    double out = 0;
    while (t--)
    {
        t1 t2;
        cin >> n;
        cin >> a >> b;
        int pom1 = a;
        int pom2 = b;
        for (int i = 1; i < n / 2; i++)
        {

            cin >> t2.x >> t2.y;
            out += (a * t2.y - t2.x * b);
            a = t2.x;
            b = t2.y;
        }
        out += (a * pom2) - (pom1 * b);
        out /= 2;
        cout << abs(int(out)) << endl;
        out = 0;
    }

    return 0;
}
