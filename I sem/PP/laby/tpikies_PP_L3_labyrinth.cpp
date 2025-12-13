//60% solution
#include <iostream>

using namespace std;

char GameMap[1005][1005]={};

void fillTheMap()
{
        for(int i=0;i<=10;i++)
                for(int j=0;j<=10;j++)
                        GameMap[i][j]='.';
}
int main()
{
        
        fillTheMap();
        int p,x,y;
        int a,b,dist;
        cin >> p;
        for(int i=0;i<p;i++) // players coordinates
        {
                cin >> x >> y;
                GameMap[x][y]=((char)i)+48;
        }
        int m;
        cin >> m;
        for(int i=0;i<m;i++) // mines coordinates
        {
                cin >> x >> y;
                GameMap[x][y]='^';
        }
        
        int w;
        cin >> w;
        for(int i=0;i<w;i++)
        {
                cin >> x >> y;
                GameMap[x][y]='#';
        }
        int mode;
        cin >> mode;
        if(mode == 0)
        {
                for(int i=0;i<10;i++)
                {
                        for(int j=0;j<10;j++)
                                cout << GameMap[i][j];
                                
                        cout << endl;
                }
        }
        else if(mode == 1)
        {
                cin >> a >> b >> dist;
                for(int i=a-dist;i<=a+dist;i++)
                {
                        
                        //cout << i << "fjief\n";
                        
                        for(int j=b-dist;j<=b+dist;j++)
                        {
                                
                                if(j<0 || j>9 || i<0 || i>9)
                                        cout << '_';
                                else
                                cout << GameMap[i][j];
                        }
                        
                        
                                
                        
                        cout << endl;
                }
                        

        }
        return 0;
}
