//#include<conio.h>      //getch
//#include<stdlib.h>     //exit(1)
//#include<iostream>
//using namespace std;
//void Queen(int y = 0);       //八皇后递归算法
//void Display(const int *p, int n);   //输出八皇后算法的解
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
//		if (!A[x + 7] && !B[x + y + 7] && !C[x - y + 7]) {     //!0 在值为0是会进入if循环
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
//	cout << "请输入n\n";
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

//八皇后的非递归算法
#define t 8
#include<conio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
void Display(const int p[], int n)   //输出函数
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
bool IsTrue(int queen[], int k) {    //第一个参数表示八皇后的列位置,第二个表示当前要插入的八皇后的行数
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
	int queen[t] = { 0 };    //初始化八皇后的列.每一行的八皇后所在的列
	int i = 0;      //行从0开始
	int s = 0;
	while (i >= 0) {
		queen[i]++;    //列从1开始
		while (!IsTrue(queen, i) && queen[i] <= t) {
           queen[i]++;
		}			
		if (queen[i] <= t) {
			if (queen[i] == t - 1) {    //到最后一行            
			  Display(queen,8); s++;
			}
			else
			{
				i++; queen[i] = 0;     //从下一行,第一列开始找位置
			}
		}
		else     //如果这一行没有找到合适的位置,就回到上一行
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

