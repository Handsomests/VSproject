#include<queue>
#include<iostream>
using namespace std;
template<class container>
void card(container& C);
int main()
{
	queue<int> Q;
	int N, i;
	char c;
	do
	{
		cout << "please input N:" << endl;
		cin >> N;
		for (i = 1; i <= N; ++i)
			Q.push(i);
		card(Q);
		cout << "go on？(Y/N):";
		cin >> c;
		cin.ignore();
	} while (c == 'y' || c == 'Y');
	return 0;
}

//桌上有一叠牌，从第一张牌开始从上往下依次编号1~n。
//当至少还剩两张牌时进行如下操作：
//把第一张牌扔掉，然后把新的第一张牌放到整叠牌的最后。
//输入n，输出每次扔掉的牌，以及最后剩下的牌。
template<class container>
void card(container& C)
{
	cout << "扔掉的次序:";
	while (C.size()>2)
	{
		cout << C.front() << "  "; C.pop();
		C.push(C.front()); C.pop();
	}
	if (C.size() ==1)
		cout << C.front();
	else {
		cout << C.front() << "  "; C.pop();
		cout << C.front() << endl; C.pop();
	}
	
}
