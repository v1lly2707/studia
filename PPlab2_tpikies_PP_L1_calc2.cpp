#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    vector < double > vec;
    char a;
    double base;
    double a1;
    int n, t;
    double last = 0;
    cin >> t;
    for (int j = 0; j < t; j++)
    {


        cin >> a;
        if (a == '+')
        {
            cin >> n >> base;
            for (int i = 0; i < n; i++)
            {
                cin >> a1;
                base += a1;
            }
            cout << base << endl;
            vec.push_back(base);
        }
        else if (a == '-')
        {
            cin >> n >> base;
            for (int i = 0; i < n; i++)
            {
                cin >> a1;
                base -= a1;
            }
            cout << base << endl;
            vec.push_back(base);
        }
        else if (a == '*')
        {
            cin >> n >> base;
            for (int i = 0; i < n; i++)
            {
                cin >> a1;
                base *= a1;
            }
            cout << base << endl;
            vec.push_back(base);
        }
        else if (a == '/')
        {
            cin >> n >> base;
            for (int i = 0; i < n; i++)
            {
                cin >> a1;
                base /= a1;
            }
            cout << base << endl;
            vec.push_back(base);
        }
        else if (a == 'M')
        {
            last = vec[vec.size() - 1];
        }
        else if (a == 'P')
        {
            cout << last << '\n';
        }
    }


    return 0;
}
