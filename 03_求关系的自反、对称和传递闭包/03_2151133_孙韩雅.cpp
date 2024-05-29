/*2151133 孙韩雅*/
#include <iostream>
using namespace std;

#define ROW 100//宏定义矩阵的行数最大值
#define COLUMN 100//宏定义矩阵的列数最大值

bool Matrix[ROW][COLUMN] = { 0 };
int row = 0;//方阵的行数（列数）

void output(bool Matrix[][COLUMN]) {//输出关系矩阵
	cout << "所求关系矩阵为:" << endl;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < row; j++)
			cout << Matrix[i][j] << ' ';
		cout << endl;
	}
}
void reflexive(bool Matrix[][COLUMN]) {//求自反闭包
	//将对角线元素置为1
	for (int i = 0; i < row; i++)
		Matrix[i][i] = true;
	output(Matrix);
}
void symmetric(bool Matrix[][COLUMN]) {//求对称闭包
	for (int i = 0; i < row; i++) {//原矩阵和对称矩阵相加
		for (int j = 0; j < row; j++)//逻辑加
			Matrix[i][j] = Matrix[i][j] || Matrix[j][i];
	}
	output(Matrix);
}
void transitive(bool Matrix[][COLUMN]) {//求传递闭包
	int i = 0, j = 0, k = 0;//循环控制变量
		for (i = 0; i < row; i++) {
			for (j = 0; j < row; j++) {
				if (Matrix[i][j]) {//若<i, j>属于关系，进入语句
					for (k = 0; k < row; k++) {
						if (Matrix[j][k])//若<j,k>也属于关系，进入语句
							Matrix[i][k] = true;//令<i,k>也属于关系
					}
				}
			}
		}
	output(Matrix);
}
void solution(bool Matrix[][COLUMN]) {
PART1:
	cout << "请输入矩阵的行(列)数（正整数且不超过100）:";
	cin >> row;
	if (cin.fail() || row < 0 || row>100) {
		cout << "输入错误，请重新输入！" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
		goto PART1;
	}
	int i = 0, j = 0;//循环控制变量
	for (i = 0; i < row; i++){
		PART2:
		cout << endl;
		cout << "请输入关系矩阵的第" << i + 1 << "行元素(0或1，元素以空格分隔) :";
		for (j = 0; j < row; j++) {
			cin >> Matrix[i][j];
			if (cin.fail()) {
				cout << "输入错误，请重新输入该行元素！" << endl;
				cin.clear();
				cin.ignore(100, '\n');//清空缓冲区
				goto PART2;//重新输入该行元素
			}
		}
	}
	cout << endl;
	cout << "l:自反闭包" << endl;
	cout << "2:对称闭包" << endl;
	cout << "3:传递闭包" << endl;
	cout << "4:退出" << endl;
	int choice = 0;//用于存储用户键盘输入的操作选项
	while (choice != 4) {
		cout <<endl<< "输入对应序号选择算法：" << endl;
		cin >> choice;
		if (cin.fail() || choice > 4 || choice < 1) {
			cout << "输入错误，请重新输入！" << endl;
			cin.clear();
			cin.ignore(100, '\n');//清空缓冲区
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
	cout << "程序已退出！" << endl;
}

int main(){
	solution(Matrix);
	return 0;
}
