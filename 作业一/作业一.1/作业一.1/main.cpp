#include <iostream>   
#include <stack>  
using namespace std;
char Type(const char c) {    //判断字符是左括号,右括号,还是其他的类型
	char *s = "{[()]}"; int i = 0;
	for ( i = 0; i < 6; ++i) {
		if (s[i] == c) break;
	}
	if (i < 3)
		return 'l';
	else if (i < 6)
		return 'r';
	else return 'eror';
}
bool Compare(char l, char r) {    //对左右括号进行配对
	if (l == '(')
		return r == ')' ? true : false;
	else if (l == '[')
		return r == ']' ? true : false;
	else if (l == '{')
		return r == '}' ? true : false;
}
bool Istrue(const char * s) {    //进行判断输入的括号正确与否
	stack<char>st;
	int i = 0; char p;
	for (i = 0; s[i] != '\0'; ++i)
	{	
		p = Type(s[i]);
	if (p == 'l')
		st.push(s[i]);
	else if (p == 'r')
	 {
		if (Compare(st.top(), s[i]))
			st.pop();
		else return false;
	  }	
    } 
	if (st.empty()) return true;
	else return false;
}
int main() {
	cout << "输入括号进行检测" <<endl;
	char s[20];
	cin >> s;
	bool b=Istrue(s);
	if (b)
		cout << "正确";
	else
		cout << "错误";
	cout << endl;
	return 0;
}