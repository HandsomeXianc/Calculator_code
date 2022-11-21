#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#define MAXN 1001
using namespace std;

int n, m, ex, ey;//分别记录迷宫的大小以及终点的坐标
int ans = 0;//记录总的路线数量
typedef long long LL;
typedef pair<int, int>PII;
int map[MAXN][MAXN];//存储创建的迷宫
int vis[MAXN][MAXN];//判断此时是否走相同的路径

//对八个方向的预处理
int dxy[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
void print() {
	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= m; j++)
			cout << vis[i][j] << " ";
}
void dfs(int x, int y){
	if (ex == x && ey == y) {
		ans++;
		print();
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		int tempx = x + dxy[i][0];
		int tempy = y + dxy[i][1];
		if (1 <= tempx && tempx <= n && 1 <= tempy && tempy <= m && !vis[tempx][tempy] && map[tempx][tempy] != 1)
		{
			vis[tempx][tempy] = true;
			dfs(tempx, tempy);
			vis[tempx][tempy] = false;
		}
	}
}

deque<PII>Q;
int d[MAXN][MAXN];
void bfs(int sx,int sy,int ex,int ey) {
	Q.push_back({ sx,sy });
	d[sx][sy] = 0;
	while (!Q.empty())
	{
		PII node = Q.front();
		Q.pop_front();
		for (int i = 0; i < 8; i++)
		{
			int tempx = node.first + dxy[i][0];
			int tempy = node.second + dxy[i][1];
			if (1 <= tempx && tempx <= n && 1 <= tempy && tempy <= m && !vis[tempx][tempy] && map[tempx][tempy] != 1)
			{
				Q.push_back({ tempx,tempy });
				vis[tempx][tempy] = true;
				d[tempx][tempy] = d[node.first][node.second] + 1;
			}
		}
	}
	cout <<"最短路径长度：" << d[ex][ey]-1 << endl;
}

void solve()
{
	cout << "请输入需要创建的迷宫大小：" << endl;
	cout << " 行数：" << " 列数：" << endl;

	cin >> n >> m;
	cout << "创建一个n行m列的地图(若该处无障碍 输入0 否则 输入1)" << endl;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> map[i][j];

	cout << "请输入终点的坐标：" << endl;
	cin >> ex >> ey;

	dfs(0,0);
	cout << "总的线路数量为：" << ans << endl;
	memset(vis, false, sizeof vis);
	bfs(0, 0, ex, ey);
}

signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	solve();
	system("pause");
	return 0;
}