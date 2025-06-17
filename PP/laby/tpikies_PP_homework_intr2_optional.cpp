#include <iostream>

using namespace std;

char arr[1005][1005]={};

int main()
{
    int n,m;
    cin >> n >> m;
    
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            arr[i][j]='.';
            
    int mode {};
    cin >> mode;
    
    if(mode==0)
    {
        int r;
        cin >> r;
        for(int j=0;j<m;j++)
            arr[r][j]='*';
    }
    else if(mode==1)
    {
        int c;
        cin >> c;
        for(int i=0;i<n;i++)
            arr[i][c]='*';
            
    }
    else if(mode==2)
    {
        int r1,c1,r2,c2;
        cin >> r1 >> c1 >> r2 >> c2;
        for(int i=r1;i<=r2;i++)
            for(int j=c1;j<=c2;j++)
                arr[i][j]='*';
    }
    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout << arr[i][j];
        
        cout << "\n";
    }

        return 0;
}
