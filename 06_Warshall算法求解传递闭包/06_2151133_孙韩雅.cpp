#include <iostream>
#include<cstring>
using namespace std;

#define R_num 4//宏定义R中元素个数为4
bool get_matrix(int M[R_num][R_num])
{
    int i = 0, j = 0;
    for (i = 0; i < R_num; i++) {
        for (j = 0; j < R_num; j++) {
            cin >> M[i][j];
            if (M[i][j] != 0 && M[i][j] != 1)
                return false;//若输入非0或1的数，则输入错误，返回false
        }
    }
    return true;
}
void output_matrix(int M[R_num][R_num])
{
    int i = 0, j = 0;
    for (i = 0; i < R_num; i++) {
        for (j = 0; j < R_num; j++) {
            cout << M[i][j] << ' ';
        }
        cout << endl;
    }
}
void Warshall(int R[][4]) {
    /*(1)i＝1；
      (2)对所有j如果a[j，i]＝1，则对k＝0，1，…，n-1，a[j，k]＝a[j，k]∨a[i，k]；
      (3)i加1；
      (4)如果i<n，则转到步骤2，否则停止*/
	int i = 0, j = 0, k = 0;
	for (k = 0; k < R_num; k++) {//进行R_num-1次R矩阵的变换，得到R的R_num次方
		for (i = 0; i < R_num; i++) {
			for (j = 0; j < R_num; j++) {
				R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
			}
		}
	}
    output_matrix(R);//输出t(R)的关系矩阵
}

int main()
{
    int M[R_num][R_num] = { 0 };
PART:
    cout << "请输入一个" << R_num << "×" << R_num << "的关系矩阵M" << endl;
    if (!get_matrix(M)) {
        cout << "输入错误，矩阵元素只能为0或1！" << endl << "请重新输入：" << endl;
        goto PART;
    }
    cout << "利用Warshall算法得到的t(R)关系矩阵为：" << endl;
    Warshall(M);

    return 0;
}
