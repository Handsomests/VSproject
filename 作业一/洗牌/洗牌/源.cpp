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
		cout << "go on��(Y/N):";
		cin >> c;
		cin.ignore();
	} while (c == 'y' || c == 'Y');
	return 0;
}

//������һ���ƣ��ӵ�һ���ƿ�ʼ�����������α��1~n��
//�����ٻ�ʣ������ʱ�������²�����
//�ѵ�һ�����ӵ���Ȼ����µĵ�һ���Ʒŵ������Ƶ����
//����n�����ÿ���ӵ����ƣ��Լ����ʣ�µ��ơ�
template<class container>
void card(container& C)
{
	cout << "�ӵ��Ĵ���:";
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
