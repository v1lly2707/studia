#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector < string > vec;

int partition(vector < string >& arr, int low, int high) {
    string pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].size() < pivot.size() || (arr[j].size() == pivot.size() && arr[j] < pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; 
}

void quickSort(vector < string >& arr, int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string a;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        vec.push_back(a);
    }

    quickSort(vec, 0, n - 1);

    for (int i = 0; i < vec.size(); i++)
        cout << vec.at(i) << "\n";
    return 0;
}
