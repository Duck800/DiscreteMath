/*2151133 孙韩雅*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

#define N 100//宏定义点的最大个数为100
#define INF 2147483647//宏定义一个INF表示无穷大infinity
int Graph[N][N], cost[N];//用Graph存放题目图，cost存放已选中点与未选中点之间的最小造价，同时也可显示已被处理的点

//工具函数
void init() {//进行初始化操作
	for (int i = 0; i < N; i++) {
		cost[i] = INF;//各邻接城市间道路造价置无穷大
		for (int j = 0; j < N; j++)
			Graph[i][j] = INF;//原图各道路造价置无穷大
	}
}
bool input_num(int &vertex_num,int &edge_num) {//用以输入顶点数和边数并进行错误判定和处理
PART1:
	cout << "请输入城市总数（输入0结束程序）：" << endl;//输入所求的顶点数
	cin >> vertex_num;
	if (cin.fail() || vertex_num < 0) {
		cout << "城市总数错误，请重新输入！" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
	else if (vertex_num == 0)
		return false;//程序结束
PART2:
	cout << "请输入城市间通信道路总数（输入0结束程序）：" << endl;//输入所求的边数
	cin >> edge_num;
	if (cin.fail() || edge_num < 0) {
		cout << "通信道路总数错误，请重新输入！" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}
	else if (edge_num > vertex_num * (vertex_num - 1) / 2) {//进行重边的特判
		//注意：两个顶点确定一条边，所以边数最大为点数*（点数-1）÷2
		cout << "出现重边，请重新输入！" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}
	else if (vertex_num == 0)
		return false;//程序结束
	return true;
}
void input_weight(int& vertex_num, int& edge_num) {
	int u = 1, v = 1, weight = INF;//边的两个端点u，v以及该边权值weight
	bool input_good = true;//定义输入正误的判断变量，以便更高效地完成输入错误判断与提示。

	for (int i = 1; i < edge_num + 1; i++) { //输入所有边的权值，所以用edge_num控制循环
		cout << "请输入第" << i  << "条道路的两个端点城市序号[1，" << vertex_num << "]以及该道路造价：";
		input_good = true;//每轮循环更新依次判断变量，以保证输入的正确
		cin >> u;
		if (cin.fail() || u<1 || u>vertex_num)
			input_good = false;

		cin >> v;
		if (cin.fail() || v<1 || v>vertex_num)
			input_good = false;

		cin >> weight;
		if (cin.fail() || weight < 0)
			input_good = false;
		if (!input_good) {//如果输入有误的情况出现
			cout << "输入错误，请重新输入！" << endl << endl;
			cin.clear();
			cin.ignore(100, '\n');
			i--;//重新开始本轮输入，相当于continue
		}
		Graph[u][v] = Graph[v][u] = weight;
	}
}
//Prim算法
void Prim(int& vertex_num){
	cout << "最小耗费所需的城市通信道路为：" << endl;
	int i = 0, j = 0;//循环控制变量
	int total_cost = 0;
	int min_cost = INF, vertex = 1;//最小造价与选中点的下标

	for (i = 1; i < vertex_num; i++) {//循环直到所有城市都覆盖到
		min_cost = INF;//每轮循环都要将最低造价初始化
		for (j = 1; j < vertex_num + 1; j++) {
			if (Graph[vertex][j] < cost[j])
				cost[j] = Graph[vertex][j];//用新加入的城市更新cost
			cost[vertex] = 0;//因为选中该点，所以到自身的造价为0
		}
		for (j = 1; j < vertex_num+1; j++) {
			if (cost[j] && (cost[j] < min_cost)) {//找出最低造价，注意寻找的顶点必须是未被标记过的
				vertex = j;//覆盖当前顶点，找到最终下一轮增加到树中的顶点
				min_cost = cost[j];//更新最低造价，最终得到最小值
			}
		}
		for (j = 1; j < vertex_num; j++) {
			if (Graph[vertex][j] == min_cost && !cost[j])//道路另一端是被选中的城市
				break;
		}
		cout << j << "->" << vertex << "：" << Graph[j][vertex] << "万元" << endl;
		total_cost += Graph[j][vertex];
	}
	cout << "最小耗费共计" << total_cost << "万元" << endl;
}

int main(){
	int vertex_num = 0, edge_num = 0;//顶点数和边数
	while (input_num(vertex_num, edge_num)) {
		init();//首先进行初始化
		input_weight(vertex_num, edge_num);//输入每条道路的端点及造价
		Prim(vertex_num);//用Prim算法构建最小生成树
	}
	cout << "程序已退出！" << endl;
	return 0;
}

/*
7
12
1 2 20
2 3 15
3 4 3
4 5 17
5 6 28
6 1 23
1 7 1
2 7 4
3 7 9
4 7 16
5 7 25
6 7 36
*/