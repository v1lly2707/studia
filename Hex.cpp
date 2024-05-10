//Hex 24%
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


int BoardSize(int size)
{
    return sqrt(size);
    //cout << "\n";
}

int PawnsNumber(int red, int blue)
{
    return red + blue;
    //cout << "\n";
}

bool BoardCorrect(int red, int blue)
{
    if (red == blue || red - blue == 1)
        return true;
    else return false;

}
int main()
{


    string line;
    int cntB = 0;
    int cntR = 0;
    int sizeCnt = 0;
    int BSize = 0;
    while (getline(cin, line))
    {

        for (char a : line)
        {
            if (a == 'b')
                cntB++;
            else if (a == 'r')
                cntR++;
            else if (a == '<')
                sizeCnt++;

        }

        BSize = BoardSize(sizeCnt);



        if (line == "BOARD_SIZE")
        {

            cout << BSize;
            cout << '\n';
            sizeCnt = 0;
            cntR = cntB = 0;


        }
        else if (line == "PAWNS_NUMBER")
        {
            cout << PawnsNumber(cntR, cntB);
            cout << '\n';
            cntB = cntR = 0;
            sizeCnt = 0;

        }
        else if (line == "IS_BOARD_CORRECT")
        {
            if (BoardCorrect(cntR, cntB))
                cout << "YES\n";
            else cout << "NO\n";
            sizeCnt = cntB = cntR = 0;
        }
        
    }
    return 0;
}
