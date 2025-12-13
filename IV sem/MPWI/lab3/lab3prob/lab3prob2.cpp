#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(static_cast<unsigned>(time(0)));
	
	int n = 10000;
	
	double sum = 0;
	int inter[5] = {};
	while(n--)
	{
		double a = static_cast<double>(rand()) / RAND_MAX; // (0,1)
		sum = 0;
		sum += 0.1;
		if(a <= sum)
		{
			inter[1]++;
		}
		else
		{
			sum+=0.4;
			if(a <= sum)
				inter[2]++;
			else
			{
				sum+=0.2;
				
				if(a <= sum)
					inter[3]++;
				else
				{
					sum+=0.3;
					if(a <= sum)
						inter[4]++;
				}
			}
		}
		
	}
	
	for(int i=1;i<=4;i++)
		cout << inter[i] << ' ';
	return 0;
}
