/*2151133 �ﺫ��*/
#include <iostream>
using namespace std;

#define ROW 100//�궨�������������ֵ
#define COLUMN 100//�궨�������������ֵ

bool Matrix[ROW][COLUMN] = { 0 };
int row = 0;//�����������������

void output(bool Matrix[][COLUMN]) {//�����ϵ����
	cout << "�����ϵ����Ϊ:" << endl;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++)
			cout << Matrix[i][j] << ' ';
		cout << endl;
	}
}
void reflexive(bool Matrix[][COLUMN]) {//���Է��հ�
	//���Խ���Ԫ����Ϊ1
	for (int i = 0; i < row; i++)
		Matrix[i][i] = true;
	output(Matrix);
}
void symmetric(bool Matrix[][COLUMN]) {//��ԳƱհ�
	for (int i = 0; i < row; i++) {//ԭ����ͶԳƾ������
		for (int j = 0; j < row; j++)//�߼���
			Matrix[i][j] = Matrix[i][j] || Matrix[j][i];
	}
	output(Matrix);
}
void transitive(bool Matrix[][COLUMN]) {//�󴫵ݱհ�
	int i = 0, j = 0, k = 0;//ѭ�����Ʊ���
		for (i = 0; i < row; i++) {
			for (j = 0; j < row; j++) {
				if (Matrix[i][j]) {//��<i, j>���ڹ�ϵ���������
					for (k = 0; k < row; k++) {
						if (Matrix[j][k])//��<j,k>Ҳ���ڹ�ϵ���������
							Matrix[i][k] = true;//��<i,k>Ҳ���ڹ�ϵ
					}
				}
			}
		}
	output(Matrix);
}
void solution(bool Matrix[][COLUMN]) {
PART1:
	cout << "������������(��)�����������Ҳ�����100��:";
	cin >> row;
	if (cin.fail() || row < 0 || row>100) {
		cout << "����������������룡" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
	int i = 0, j = 0;//ѭ�����Ʊ���
	for (i = 0; i < row; i++){
		PART2:
		cout << endl;
		cout << "�������ϵ����ĵ�" << i + 1 << "��Ԫ��(0��1��Ԫ���Կո�ָ�) :";
		for (j = 0; j < row; j++) {
			cin >> Matrix[i][j];
			if (cin.fail()) {
				cout << "��������������������Ԫ�أ�" << endl;
				cin.clear();
				cin.ignore(100, '\n');//��ջ�����
				goto PART2;//�����������Ԫ��
			}
		}
	}
	cout << endl;
	cout << "l:�Է��հ�" << endl;
	cout << "2:�ԳƱհ�" << endl;
	cout << "3:���ݱհ�" << endl;
	cout << "4:�˳�" << endl;
	int choice = 0;//���ڴ洢�û���������Ĳ���ѡ��
	while (choice != 4) {
		cout <<endl<< "�����Ӧ���ѡ���㷨��" << endl;
		cin >> choice;
		if (cin.fail() || choice > 4 || choice < 1) {
			cout << "����������������룡" << endl;
			cin.clear();
			cin.ignore(100, '\n');//��ջ�����
			continue;
		}
		switch (choice) {
		case 1:
			reflexive(Matrix);
			break;
		case 2:
			symmetric(Matrix);
			break;
		case 3:
			transitive(Matrix);
			break;
		}
	}
	cout << "�������˳���" << endl;
}

int main(){
	solution(Matrix);
	return 0;
}
