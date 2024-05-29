#include <iostream>
using namespace std;

bool translate(int dec,int bin[5]) {
	//参数为十进制的数和存放转换后二进制的数组
	if (dec >31)
		return false;//当十进制数大于2^5-1时，对应二进制数超过5位，与题目对应命题变量不符
	int i = 4;//用以标记数组下标进行存放
	while (dec / 2 > 0) {
		bin[i--] = dec % 2;
		dec = dec / 2;
	}
	dec = bin[i];//最后一位数必为1，存入数组
	return true;
}

int main()
{
	int bin[5] = { 0 };
	/*
	bin[0]对应营业员A偷了手表
	bin[1]对应营业员B偷了手表
	bin[2]作案不在营业时间
	bin[3]B提供的证据正确
	bin[4]货柜未上锁
	*/
	for (int all_cases = 0; all_cases < 32; all_cases++) {//达到2^5-1后结束循环
		translate(all_cases, bin);
		if ((bin[0] || bin[1]) && (!bin[0] || bin[2]) && (!bin[3] || bin[4]) && (bin[3] || !bin[2]) && !bin[4]) {
			//A||B：A或B作案
			//!A || C：A没有作案或作案不在营业时间
			//!D || E：B提供的证据不正确或货柜未上锁
			//D || !C：B提供的证据正确或作案在营业时间
			//！E：货柜上锁了
			cout << "A=" << bin[0] << ",B=" << bin[1] << endl;
			cout << "So " << (bin[0] ? 'A' : 'B') << " is the thief who stole the watch." << endl;
			return 0;
		}
	}
	return 0;
}

