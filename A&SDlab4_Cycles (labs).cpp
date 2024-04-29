#include <iostream>
#include <vector>

using namespace std;

struct graph
{
	bool ifVisited;
	vector < int > con;

}*w;

void DFS(int n)
{
	
	w[n].ifVisited = 1;
	for (int i = 0; i < w[n].con.size(); i++)
	{
		if (!w[w[n].con[i]].ifVisited)
			DFS(w[n].con[i]);
		
	}

}

int matrix[1005][1005] = {};
int EdgeArr[1005] = {};
bool ok = true;
int main()
{
	ios_base::sync_with_stdio;
	cin.tie(NULL);

	int n,t;
	cin >> n;
	char a;
	int EdgeCnt = 0;
	int VisitedCnt = 0;
	while (n--)
	{
		cin >> t;
		
		w = new graph[t + 5];

		for (int i = 0; i <= t; i++)
		{
			w[i].con.clear();
			w[i].ifVisited = 0;
		}

		for (int i = 0; i < t; i++)
		{
			for (int j = 0; j < t; j++)
			{
				cin >> a;
				if (a == '1')
					EdgeCnt++;

				matrix[i][j] = a - '0';
			}
		}
		
		for (int i = 0; i < t; i++)
		{
			for (int j = 0; j < t; j++)
			{
				if (matrix[i][j] == 1)
				{
					w[i].con.push_back(j);
					EdgeArr[i]++;
				}
					


			}
				
		}

		DFS(0);

		for (int i = 0; i < t; i++)
		{
			if (w[i].ifVisited == true)
				VisitedCnt++;

			if (EdgeArr[i] != 2)
				ok = false;
		}

		if (VisitedCnt == t && EdgeCnt / 2 == t && ok == true)
			cout << 1 << '\n';
		else cout << 0 << '\n';

		EdgeCnt = VisitedCnt = 0;
		ok = true;
		for (int i = 0; i < t; i++)
			EdgeArr[i] = 0;

	}
	return 0;
}
