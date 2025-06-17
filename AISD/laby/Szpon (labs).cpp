#include <iostream>
#include <vector>
using namespace std;

bool fun(vector < vector < bool > >& matrix, int size)
{
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                for (int l = 0; l < size; l++)
                {
                    if (i == j || i == k || i == l || j == k || j == l || k == l)
                        continue;

                    if (matrix[i][j] && matrix[i][k] && matrix[i][l])
                        if (!matrix[j][k] && !matrix[k][l] && !matrix[l][j])
                            return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    int n;
    int tmp, v;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> v;

        vector < vector < bool > > matrix(v);

        cin.get();

        for (int j = 0; j < v; j++)
        {
            for (int k = 0; k < v; k++)
            {
                tmp = cin.get() - '0';

                matrix[j].push_back(tmp);
            }
        }
        cout << fun(matrix, v) << '\n';
    }
    return 0;
}
