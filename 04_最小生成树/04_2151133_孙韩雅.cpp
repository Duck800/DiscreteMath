/*2151133 �ﺫ��*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

#define N 100//�궨����������Ϊ100
#define INF 2147483647//�궨��һ��INF��ʾ�����infinity
int Graph[N][N], cost[N];//��Graph�����Ŀͼ��cost�����ѡ�е���δѡ�е�֮�����С��ۣ�ͬʱҲ����ʾ�ѱ�����ĵ�

//���ߺ���
void init() {//���г�ʼ������
	for (int i = 0; i < N; i++) {
		cost[i] = INF;//���ڽӳ��м��·����������
		for (int j = 0; j < N; j++)
			Graph[i][j] = INF;//ԭͼ����·����������
	}
}
bool input_num(int &vertex_num,int &edge_num) {//�������붥�����ͱ��������д����ж��ʹ���
PART1:
	cout << "�������������������0�������򣩣�" << endl;//��������Ķ�����
	cin >> vertex_num;
	if (cin.fail() || vertex_num < 0) {
		cout << "���������������������룡" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
	else if (vertex_num == 0)
		return false;//�������
PART2:
	cout << "��������м�ͨ�ŵ�·����������0�������򣩣�" << endl;//��������ı���
	cin >> edge_num;
	if (cin.fail() || edge_num < 0) {
		cout << "ͨ�ŵ�·�����������������룡" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}
	else if (edge_num > vertex_num * (vertex_num - 1) / 2) {//�����رߵ�����
		//ע�⣺��������ȷ��һ���ߣ����Ա������Ϊ����*������-1����2
		cout << "�����رߣ����������룡" << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART2;
	}
	else if (vertex_num == 0)
		return false;//�������
	return true;
}
void input_weight(int& vertex_num, int& edge_num) {
	int u = 1, v = 1, weight = INF;//�ߵ������˵�u��v�Լ��ñ�Ȩֵweight
	bool input_good = true;//��������������жϱ������Ա����Ч�������������ж�����ʾ��

	for (int i = 1; i < edge_num + 1; i++) { //�������бߵ�Ȩֵ��������edge_num����ѭ��
		cout << "�������" << i  << "����·�������˵�������[1��" << vertex_num << "]�Լ��õ�·��ۣ�";
		input_good = true;//ÿ��ѭ�����������жϱ������Ա�֤�������ȷ
		cin >> u;
		if (cin.fail() || u<1 || u>vertex_num)
			input_good = false;

		cin >> v;
		if (cin.fail() || v<1 || v>vertex_num)
			input_good = false;

		cin >> weight;
		if (cin.fail() || weight < 0)
			input_good = false;
		if (!input_good) {//�������������������
			cout << "����������������룡" << endl << endl;
			cin.clear();
			cin.ignore(100, '\n');
			i--;//���¿�ʼ�������룬�൱��continue
		}
		Graph[u][v] = Graph[v][u] = weight;
	}
}
//Prim�㷨
void Prim(int& vertex_num){
	cout << "��С�ķ�����ĳ���ͨ�ŵ�·Ϊ��" << endl;
	int i = 0, j = 0;//ѭ�����Ʊ���
	int total_cost = 0;
	int min_cost = INF, vertex = 1;//��С�����ѡ�е���±�

	for (i = 1; i < vertex_num; i++) {//ѭ��ֱ�����г��ж����ǵ�
		min_cost = INF;//ÿ��ѭ����Ҫ�������۳�ʼ��
		for (j = 1; j < vertex_num + 1; j++) {
			if (Graph[vertex][j] < cost[j])
				cost[j] = Graph[vertex][j];//���¼���ĳ��и���cost
			cost[vertex] = 0;//��Ϊѡ�иõ㣬���Ե���������Ϊ0
		}
		for (j = 1; j < vertex_num+1; j++) {
			if (cost[j] && (cost[j] < min_cost)) {//�ҳ������ۣ�ע��Ѱ�ҵĶ��������δ����ǹ���
				vertex = j;//���ǵ�ǰ���㣬�ҵ�������һ�����ӵ����еĶ���
				min_cost = cost[j];//���������ۣ����յõ���Сֵ
			}
		}
		for (j = 1; j < vertex_num; j++) {
			if (Graph[vertex][j] == min_cost && !cost[j])//��·��һ���Ǳ�ѡ�еĳ���
				break;
		}
		cout << j << "->" << vertex << "��" << Graph[j][vertex] << "��Ԫ" << endl;
		total_cost += Graph[j][vertex];
	}
	cout << "��С�ķѹ���" << total_cost << "��Ԫ" << endl;
}

int main(){
	int vertex_num = 0, edge_num = 0;//�������ͱ���
	while (input_num(vertex_num, edge_num)) {
		init();//���Ƚ��г�ʼ��
		input_weight(vertex_num, edge_num);//����ÿ����·�Ķ˵㼰���
		Prim(vertex_num);//��Prim�㷨������С������
	}
	cout << "�������˳���" << endl;
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