#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_SIZE = 500;
const long long INF = 2000000000ll * 100000;

long long C[MAX_SIZE][MAX_SIZE], F[MAX_SIZE][MAX_SIZE];
int  n, s, t;

vector<int> edge;
vector<int> time_v;

bool BFS()
{
	queue<int> vertex;

	time_v.assign(n, 0);

	vertex.push(s);
	time_v[s] = 1;

	while (vertex.empty() == false)
	{
		int v = vertex.front();
		vertex.pop();

		for (int i = 0; i < n; ++i)
		{
			if (time_v[i] == 0 && C[v][i] - F[v][i] > 0)
			{
				time_v[i] = time_v[v] + 1;
				vertex.push(i);
			}
		}
	}

	if (time_v[t] == 0)
		return false;
	return true;
}

long long DFS(int v, long long FLOW = INF)
{

	if (v == t)
		return FLOW;

	for (; edge[v] < n; ++edge[v])
	{
		int to = edge[v];
		if (time_v[to] == time_v[v] + 1 && C[v][to] - F[v][to] > 0)
		{
			long long flow = DFS(to, min(FLOW, C[v][to] - F[v][to]));
			if (flow == 0)
				continue;

			F[v][to] += flow;
			F[to][v] -= flow;
			return flow;
		}
	}

	return 0;
}

int main()
{
	int m;
	cin >> n >> m;

	s = 0;
	t = n - 1;

	for (int i = 0; i < m; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;
		C[a - 1][b - 1] = c;
	}

	long long result = 0;
	while (true)
	{
		if (!BFS())
			break;
		edge.assign(n, 0);
		while (true)
		{
			long long f = DFS(s);
			if (f == 0)
				break;
			result += f;
		}
	}

	cout << result << endl;
	return 0;
}
