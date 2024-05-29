/*2151133 孙韩雅*/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define N 13//宏定义结点个数
#define MAX_F 80//宏定义使用频率数组的大小
struct tree {
	int value = 0;
	tree* Left =NULL;//左节点
	tree* Right =NULL;//右节点
}*fp[N];       //保存结点 
bool code[N];  //放前缀码

void init_leaf(int f[], int n) {//生成叶子节点
	tree* leaf;
	for (int i = 0; i < n; i++) {
		leaf = (tree*)malloc(sizeof(tree));  //生成叶子节点 
		if (leaf == NULL) {//确保空间开辟成功
			cout << "生成叶子结点失败" << endl;
			return;
		}
		leaf->value = f[i];
		leaf->Left = NULL;
		leaf->Right = NULL;
		fp[i] = leaf;		//空间开辟成功则将node存入fp[]中
	}
}
void sort(tree* array[], int n) {//将第N-n个结点插入到已排好序的序列中
	tree* tmp;
	for (int i = N - n; i < N - 1; i++) {
		if (array[i]->value > array[i + 1]->value) {//序列从小到大进行排序
			tmp = array[i + 1];
			array[i + 1] = array[i];
			array[i] = tmp;
		}
	}
}
tree* create_Huffman(int f[], int n) {//建立树 
	tree* parent;
	for (int i = 1; i < N; i++) {
		parent = (tree*)malloc(sizeof(tree));  //生成非叶子结点（父结点） 
		if (parent == NULL) {//保证空间开辟成功
			cout << "生成非叶子结点失败" << endl;
			return NULL;
		}
		parent->value = fp[i - 1]->value + fp[i]->value;//最小的两个数上添一个父结点，其值为两数之和
		parent->Left = fp[i - 1];
		parent->Right = fp[i];
		fp[i] = parent;  //wl+w2
		sort(fp, N - i);//将此时第i个点进行排序
	}
	return fp[N - 1];
}
void preorder(tree* p, int k, bool judge/*用以判别左右子树*/) {//递归式前序遍历求哈弗曼编码
	if (p != NULL) {
		code[k] = judge;//judge为true时，是右子树，标1；否则为左子树，标0
		if (p->Left == NULL) {//P 指向叶子 
			cout << setw(6) << setiosflags(ios::left) << p->value << ": ";
			for (int j = 1; j <= k; j++) //从j=1开始打印，code[0]为多出的一位‘0’
				cout << code[j];
			cout << endl;
		}
		//递归遍历树
		preorder(p->Left, k + 1, false);
		preorder(p->Right, k + 1, true);
	}
}

int main() {
	int node_num = 0;
PART1:
	cout << "请输入结点个数(必须是正整数):";
	cin >> node_num;
	if (cin.fail() || node_num < 0) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "输入错误，请重新输入！" << endl << endl;
		goto PART1;
	}
	int frequency[MAX_F] = { 0 };
	cout << "请输入结点（以空格分隔）：" << endl;
	for (int i = 0; i < node_num; i++) {
		cin >> frequency[i];
		if (cin.fail()) {
			cout << "输入错误，请重新输入所有节点：" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			i = 0;
		}
	}
	tree* head = new tree;//分配空间
	init_leaf(frequency, N);  //初始化结点 
	head = create_Huffman(frequency, N);  //生成最优树 
	code[0] = 0;
	preorder(head, 0, false);  //遍历树 
	return 0;
}

//2 3 5 7 11 13 17 19 23 29 31 37 41