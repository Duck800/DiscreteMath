/*2151133 �ﺫ��*/
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define N 13//�궨�������
#define MAX_F 80//�궨��ʹ��Ƶ������Ĵ�С
struct tree {
	int value = 0;
	tree* Left =NULL;//��ڵ�
	tree* Right =NULL;//�ҽڵ�
}*fp[N];       //������ 
bool code[N];  //��ǰ׺��

void init_leaf(int f[], int n) {//����Ҷ�ӽڵ�
	tree* leaf;
	for (int i = 0; i < n; i++) {
		leaf = (tree*)malloc(sizeof(tree));  //����Ҷ�ӽڵ� 
		if (leaf == NULL) {//ȷ���ռ俪�ٳɹ�
			cout << "����Ҷ�ӽ��ʧ��" << endl;
			return;
		}
		leaf->value = f[i];
		leaf->Left = NULL;
		leaf->Right = NULL;
		fp[i] = leaf;		//�ռ俪�ٳɹ���node����fp[]��
	}
}
void sort(tree* array[], int n) {//����N-n�������뵽���ź����������
	tree* tmp;
	for (int i = N - n; i < N - 1; i++) {
		if (array[i]->value > array[i + 1]->value) {//���д�С�����������
			tmp = array[i + 1];
			array[i + 1] = array[i];
			array[i] = tmp;
		}
	}
}
tree* create_Huffman(int f[], int n) {//������ 
	tree* parent;
	for (int i = 1; i < N; i++) {
		parent = (tree*)malloc(sizeof(tree));  //���ɷ�Ҷ�ӽ�㣨����㣩 
		if (parent == NULL) {//��֤�ռ俪�ٳɹ�
			cout << "���ɷ�Ҷ�ӽ��ʧ��" << endl;
			return NULL;
		}
		parent->value = fp[i - 1]->value + fp[i]->value;//��С������������һ������㣬��ֵΪ����֮��
		parent->Left = fp[i - 1];
		parent->Right = fp[i];
		fp[i] = parent;  //wl+w2
		sort(fp, N - i);//����ʱ��i�����������
	}
	return fp[N - 1];
}
void preorder(tree* p, int k, bool judge/*�����б���������*/) {//�ݹ�ʽǰ����������������
	if (p != NULL) {
		code[k] = judge;//judgeΪtrueʱ��������������1������Ϊ����������0
		if (p->Left == NULL) {//P ָ��Ҷ�� 
			cout << setw(6) << setiosflags(ios::left) << p->value << ": ";
			for (int j = 1; j <= k; j++) //��j=1��ʼ��ӡ��code[0]Ϊ�����һλ��0��
				cout << code[j];
			cout << endl;
		}
		//�ݹ������
		preorder(p->Left, k + 1, false);
		preorder(p->Right, k + 1, true);
	}
}

int main() {
	int node_num = 0;
PART1:
	cout << "�����������(������������):";
	cin >> node_num;
	if (cin.fail() || node_num < 0) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "����������������룡" << endl << endl;
		goto PART1;
	}
	int frequency[MAX_F] = { 0 };
	cout << "�������㣨�Կո�ָ�����" << endl;
	for (int i = 0; i < node_num; i++) {
		cin >> frequency[i];
		if (cin.fail()) {
			cout << "��������������������нڵ㣺" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			i = 0;
		}
	}
	tree* head = new tree;//����ռ�
	init_leaf(frequency, N);  //��ʼ����� 
	head = create_Huffman(frequency, N);  //���������� 
	code[0] = 0;
	preorder(head, 0, false);  //������ 
	return 0;
}

//2 3 5 7 11 13 17 19 23 29 31 37 41