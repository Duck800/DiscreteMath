#include <iostream>
using namespace std;

bool translate(int dec,int bin[5]) {
	//����Ϊʮ���Ƶ����ʹ��ת��������Ƶ�����
	if (dec >31)
		return false;//��ʮ����������2^5-1ʱ����Ӧ������������5λ������Ŀ��Ӧ�����������
	int i = 4;//���Ա�������±���д��
	while (dec / 2 > 0) {
		bin[i--] = dec % 2;
		dec = dec / 2;
	}
	dec = bin[i];//���һλ����Ϊ1����������
	return true;
}

int main()
{
	int bin[5] = { 0 };
	/*
	bin[0]��ӦӪҵԱA͵���ֱ�
	bin[1]��ӦӪҵԱB͵���ֱ�
	bin[2]��������Ӫҵʱ��
	bin[3]B�ṩ��֤����ȷ
	bin[4]����δ����
	*/
	for (int all_cases = 0; all_cases < 32; all_cases++) {//�ﵽ2^5-1�����ѭ��
		translate(all_cases, bin);
		if ((bin[0] || bin[1]) && (!bin[0] || bin[2]) && (!bin[3] || bin[4]) && (bin[3] || !bin[2]) && !bin[4]) {
			//A||B��A��B����
			//!A || C��Aû����������������Ӫҵʱ��
			//!D || E��B�ṩ��֤�ݲ���ȷ�����δ����
			//D || !C��B�ṩ��֤����ȷ��������Ӫҵʱ��
			//��E������������
			cout << "A=" << bin[0] << ",B=" << bin[1] << endl;
			cout << "So " << (bin[0] ? 'A' : 'B') << " is the thief who stole the watch." << endl;
			return 0;
		}
	}
	return 0;
}

