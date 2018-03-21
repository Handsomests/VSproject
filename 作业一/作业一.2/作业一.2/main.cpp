#include<iostream>
#include<queue>
using namespace std;
//template<typename T>
//int  Play(queue<T>a) {
//	queue<int>s;
//	//cout << a.size();
//	int i = 0;
//	if (a.size() < 2)
//	{
//		cout << "剩下:" << a.front() << endl;
//		return 0;
//	}
//	else if (a.size() >= 2)
//	{
//		while (!a.empty()) {
//		cout << "弹出:" <<a.front()  << endl;
//		a.pop();
//		s.push(a.front());
//		a.pop();
//		}	
//	}
//	Play(s);
//	return 0;
//}
int main() {
	int n ,i;
	queue<int> a;
	cout << "输入扑克牌的数量:";
	cin >> n;
	for ( i = 1; i<=n; i++)
		a.push(i);
	cout << "弹出的元素: ";
	for (i = 0; i < n - 1; i++)
	{
		cout << a.front() << " ";
		a.pop();
		a.push(a.front());
		a.pop();
	}
	cout << endl;
	cout << "最后的元素: ";
	cout << a.front() << endl;
	return 0;
}