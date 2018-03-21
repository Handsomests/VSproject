//#include<conio.h>      //getch
//#include<stdlib.h>     //exit(1)
//#include<iostream>
//using namespace std;
//void Queen(int y = 0);       //�˻ʺ�ݹ��㷨
//void Display(const int *p, int n);   //����˻ʺ��㷨�Ľ�
//static int n;
//int main() {
//	Queen();
//	return 0;
//}
//void Queen(int y) {
//	static int A[22], B[22], C[22], Y[8];    
//	if (y < 0 || y>8) {
//		cout << "y is illeagal"; exit(1);
//	}
//	if (y == 8) {
//		Display(Y, 8);
//		return;
//	}
//	for(int x=0;x<8;x++)
//		if (!A[x + 7] && !B[x + y + 7] && !C[x - y + 7]) {     //!0 ��ֵΪ0�ǻ����ifѭ��
//			Y[y] = x;
//			A[x + 7] = B[x + y + 7] = C[x - y + 7] = 1;
//			Queen(y + 1);
//			A[x + 7] = B[x + y + 7] = C[x - y + 7] = 0;
//		}
//}
//void Display(const int * p, int n) {
//	static int total = 1;
//	for (int y = 0; y < n; y++) {
//		if (y % 8 == 0)
//			cout << total++ << endl;
//		for (int x = 0; x < 8; x++)
//			if (x != p[y])
//				cout << "#";
//			else
//			{
//				cout << "@";
//			}
//		cout << endl;
//	}
//	cout << "press any key to see" << endl;
//	_getch();
//}
//#include<conio.h>
//#include<stdlib.h>
//#include <iostream>
//using namespace std;
//void Queen(const int n, int y = 0);
//void Display(const int *p, int n);
//int main()
//{
//	int n;
//	cout << "������n\n";
//	cin>>n;
//	Queen(n);
//	return(0);
//}
//void Queen(const int n, int y)
//{
//	static int *A = new int[3 * n - 2](), *B = new int[3 * n - 2](), *C = new int[3 * n - 2](), *Y = new int[n]();
//	if (y<0 || y>n)
//	{
//		cout << "y illegal";
//		exit(1);
//	}
//	if (y == n)
//	{
//		Display(Y, n);
//		return;
//	}
//	for (int x = 0; x<n; x++)
//		if (!A[x + n - 1] && !B[x + y + n - 1] && !C[x - y + n - 1])
//		{
//			Y[y] = x;
//			A[x + n - 1] = B[x + y + n - 1] = C[x - y + n - 1] = 1;
//			Queen(n, y + 1);
//			A[x + n - 1] = B[x + y + n - 1] = C[x - y + n - 1] = 0;
//		}
//}
//void Display(const int *p, int n)
//{
//	static int total = 1;
//	for (int y = 0; y<n; y++)
//	{
//		if (y % n == 0)
//			cout << total++ << endl;
//		for (int x = 0; x<n; x++)
//			if (x != p[y])
//				cout << "#";
//			else
//				cout << "@";
//		cout << endl;
//	}
//	cout << "Press any key to see" << endl;
//	_getch();
//}

//�˻ʺ�ķǵݹ��㷨
#define t 8
#include<conio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
void Display(const int p[], int n)   //�������
{
	static int total = 1;
	for (int y = 0; y < n; y++)
	{
		if (y % 8 == 0)
			cout << total++ << endl;
		for (int x = 0; x < 8; x++)
			if (x != p[y])
				cout << "#";
			else
				cout << "@";
		cout << endl;
	}
	cout << "Press any key to see" << endl;
	_getch();
}
bool IsTrue(int queen[], int k) {    //��һ��������ʾ�˻ʺ����λ��,�ڶ�����ʾ��ǰҪ����İ˻ʺ������
	int i = 0;
	while (i < k) {
		if (queen[k] == queen[i] || abs(queen[i] - queen[k]) == abs(i - k)) {
			return false;
		}
		i++;
	}
	return true;
}
void Sim_Eight_Queen() {
	int queen[t] = { 0 };    //��ʼ���˻ʺ����.ÿһ�еİ˻ʺ����ڵ���
	int i = 0;      //�д�0��ʼ
	int s = 0;
	while (i >= 0) {
		queen[i]++;    //�д�1��ʼ
		while (!IsTrue(queen, i) && queen[i] <= t) {
           queen[i]++;
		}			
		if (queen[i] <= t) {
			if (queen[i] == t - 1) {    //�����һ��            
			  Display(queen,8); s++;
			}
			else
			{
				i++; queen[i] = 0;     //����һ��,��һ�п�ʼ��λ��
			}
		}
		else     //�����һ��û���ҵ����ʵ�λ��,�ͻص���һ��
		{
			i--;
		}
	}
	cout << s << endl;
}
int main() {
	Sim_Eight_Queen();
	return 0;
}

