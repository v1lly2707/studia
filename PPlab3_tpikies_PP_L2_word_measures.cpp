#include <iostream>
using namespace std;

int main()
{
    int length;
    cin >> length;
    char ArrChar[1005] = {};
    char StringArr[1005][1005] = {};
    int cnt = 0;
    int mode;
    cin >> mode;
    int n, m;
    char SingleString[1005] = {};
    int cntEquals = 0;
    char phrase[1005] = {};
    char replace[1005] = {};
    bool found = false;
    if (mode == 0)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> ArrChar[i];

        cin >> m;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < length; j++)
                cin >> StringArr[i][j];


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int k = 0; k < length; k++)
                {
                    if (ArrChar[i] == StringArr[j][k])
                        cnt++;
                }
            }
            cout << ArrChar[i] << ' ' << cnt << endl;
            cnt = 0;
        }


    }
    else if (mode == 1)
    {
        for (int i = 0; i < length; i++)
            cin >> SingleString[i];

        cin >> m;

        for (int i = 0; i < m; i++)
            for (int j = 0; j < length; j++)
                cin >> StringArr[i][j];

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if (StringArr[i][j] == SingleString[j])
                    cntEquals++;
            }
            if (cntEquals == length)
            {
                for (int k = 0; k < length; k++)
                    cout << '*';

                cout << " ";
            }
            else
            {
                for (int j = 0; j < length; j++)
                    cout << StringArr[i][j];

                cout << " ";
            }
            cntEquals = 0;

        }
    }
    else if (mode == 2)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> phrase[i];

        for (int i = 0; i < length; i++)
            cin >> replace[i];

        cin >> m;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < length; j++)
                cin >> StringArr[i][j];


        for (int i = 0; i < m; i++)
        {
            found = false;
            for (int j = 0; j < length; j++)
            {
                if (StringArr[i][j] == phrase[0] && StringArr[i][j + 1] == phrase[1] && StringArr[i][j + 2] == phrase[2])
                {
                    found = true;

                }
            }
            if (found == true)
            {
                for (int j = 0; j < length; j++)
                    cout << replace[j];

                cout << ' ';
            }
            else
            {
                for (int j = 0; j < length; j++)
                    cout << StringArr[i][j];

                cout << ' ';
            }

        }
    }
    return 0;
}
