#pragma once
#include<iostream>
using namespace std;
#include<stdlib.h>
#include<string>
class String {
private:
	char * str;  //指向动态数组的指针
	int size;
	void Error(const char * c)const;   //错误信息报告
public:
	String(const char* c = "");    //转换构造函数
	String(const String& s);   //  复制构造函数
	~String() { delete[]str; }  //析构函数

	String& operator=(const char *c);//转换赋值  类串=C串
	String& operator=(const String & s);//类串=类串
	String& Insert(int id, const String& s);//子串插入
	String& Erase(int id, int num);//子串删除
	String& Substr(int id, int num)const;//求子串



//输入输出
	friend istream& operator >> (istream& itr, String& s);
	friend ostream& operator <<(ostream& otr, String& s);

};
inline void String::Error(const char * c) const
{
}
//默认构造函数的实现
String::String(const char *c) {
	size = strlen(c);
	str = new char[size + 1];
	if (str==NULL)
		Error("String: overFlow!");
	strcpy_s(str,size+1,c);
}
//赋值构造函数的实现
String::String(const String& s) {
	size = s.size;
	str = new char[size + 1];
		if (str == NULL)
			Error("String: overflow!");
		strcpy_s(str, size + 1, s.str);

}
//转换赋值
String&String::operator=(const char * c) {
	int len = strlen(c);
	if (size != len) {
		delete[]str;
		str = new char[len + 1];
		if (str == NULL)
			Error("overFlow!");
		size = len;
	}
	strcpy_s(str, size + 1, c);
	return *this;
}
//复制赋值
String&String::operator=(const String&s) {
	if (size != s.size) {
		delete[]str;
		str = new char[s.size + 1];
		if (str == NULL)
			Error("overFlow");
		size = s.size;
	      }
		strcpy_s(str, size + 1, s.str);
		return *this;
}
//子串插入
String& String::Insert(int id, const String& s) {
	char * p, *p1, *buf;
	int len = size;
	int len1 = s.size;
	int left = len - id;
	int i;
	if (id<0 || id>len)
		Error("id is illegal!");
	//步骤一
	buf = str;
	str = new char[len + len1 + 1];
	if (str == NULL)
		Error("overflow!");
	strcpy_s(str, len + len1 + 1, buf);
	delete[]buf;
	//步骤二
	p = str + len;
	p1 = p + len1;
	for (i = 1; i <= left + 1;++i)
		*p1-- = *p--;
	//步骤三
	p = str + id;
	p1 = s.str;
	while (*p1 != '\0')
		*p++ = *p1++;
	size = len + len1;
	return *this;
}
//子串删除
String& String::Erase(int id, int num) {
	char*p, *q, *buf;
	int len = size;
	int left = len - id;
	if (id < 0 || id>size)
		Error("id is illegal!");
	if (num <= 0 || num > left)
		Error("num is illegal!");
	//步骤一
	p = str + id;
	q = str + id + num;
	while (*q != '\0')
		*p++ = *q++;
	*p = '\0';
	//步骤二
	buf = str;
	//步骤三
	len = strlen(buf);
	str = new char[len + 1];
	if (str == NULL)
		Error("overflow");
	strcpy_s(str, len + 1, buf);
	size = len;
	delete[]buf;
	return * this;
}
//输入输出
istream& operator >> (istream & istr, String& s) {
	char buf[256];   //256是输入缓冲区的长度
	istr >> buf;
	s = buf;
	return istr;
}
ostream& operator<<(ostream& ostr, String &s) {
	ostr << s.str;
	return ostr;
}