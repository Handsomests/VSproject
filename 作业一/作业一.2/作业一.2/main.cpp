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
//		cout << "ʣ��:" << a.front() << endl;
//		return 0;
//	}
//	else if (a.size() >= 2)
//	{
//		while (!a.empty()) {
//		cout << "����:" <<a.front()  << endl;
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
	cout << "�����˿��Ƶ�����:";
	cin >> n;
	for ( i = 1; i<=n; i++)
		a.push(i);
	cout << "������Ԫ��: ";
	for (i = 0; i < n - 1; i++)
	{
		cout << a.front() << " ";
		a.pop();
		a.push(a.front());
		a.pop();
	}
	cout << endl;
	cout << "����Ԫ��: ";
	cout << a.front() << endl;
	return 0;
}