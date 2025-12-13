#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(static_cast<unsigned>(time(0)));
	int inter[10] = {};
	int n = 10000;
	while(n--)
	{
		double a = static_cast<double>(rand()) / RAND_MAX;
		//cout << a << '\n';
		int zaok = ceil(100*a+50);
		cout << zaok << "\n";
		
		inter[zaok/10-5]++;
		
	}
	
	for(int i = 0; i < 10; i++)
	{
		cout << "[ " << inter[i] << " ] ";
	}
    
    
    
	return 0;
}
