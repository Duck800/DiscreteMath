#include <iostream>
#include<cstring>
using namespace std;

#define R_num 4//�궨��R��Ԫ�ظ���Ϊ4
bool get_matrix(int M[R_num][R_num])
{
    int i = 0, j = 0;
    for (i = 0; i < R_num; i++) {
        for (j = 0; j < R_num; j++) {
            cin >> M[i][j];
            if (M[i][j] != 0 && M[i][j] != 1)
                return false;//�������0��1��������������󣬷���false
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
    /*(1)i��1��
      (2)������j���a[j��i]��1�����k��0��1������n-1��a[j��k]��a[j��k]��a[i��k]��
      (3)i��1��
      (4)���i<n����ת������2������ֹͣ*/
	int i = 0, j = 0, k = 0;
	for (k = 0; k < R_num; k++) {//����R_num-1��R����ı任���õ�R��R_num�η�
		for (i = 0; i < R_num; i++) {
			for (j = 0; j < R_num; j++) {
				R[i][j] = R[i][j] || (R[i][k] && R[k][j]);
			}
		}
	}
    output_matrix(R);//���t(R)�Ĺ�ϵ����
}

int main()
{
    int M[R_num][R_num] = { 0 };
PART:
    cout << "������һ��" << R_num << "��" << R_num << "�Ĺ�ϵ����M" << endl;
    if (!get_matrix(M)) {
        cout << "������󣬾���Ԫ��ֻ��Ϊ0��1��" << endl << "���������룺" << endl;
        goto PART;
    }
    cout << "����Warshall�㷨�õ���t(R)��ϵ����Ϊ��" << endl;
    Warshall(M);

    return 0;
}
