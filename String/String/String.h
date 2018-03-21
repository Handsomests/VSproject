#pragma once
#include<iostream>
using namespace std;
#include<stdlib.h>
#include<string>
class String {
private:
	char * str;  //ָ��̬�����ָ��
	int size;
	void Error(const char * c)const;   //������Ϣ����
public:
	String(const char* c = "");    //ת�����캯��
	String(const String& s);   //  ���ƹ��캯��
	~String() { delete[]str; }  //��������

	String& operator=(const char *c);//ת����ֵ  �മ=C��
	String& operator=(const String & s);//�മ=�മ
	String& Insert(int id, const String& s);//�Ӵ�����
	String& Erase(int id, int num);//�Ӵ�ɾ��
	String& Substr(int id, int num)const;//���Ӵ�



//�������
	friend istream& operator >> (istream& itr, String& s);
	friend ostream& operator <<(ostream& otr, String& s);

};
inline void String::Error(const char * c) const
{
}
//Ĭ�Ϲ��캯����ʵ��
String::String(const char *c) {
	size = strlen(c);
	str = new char[size + 1];
	if (str==NULL)
		Error("String: overFlow!");
	strcpy_s(str,size+1,c);
}
//��ֵ���캯����ʵ��
String::String(const String& s) {
	size = s.size;
	str = new char[size + 1];
		if (str == NULL)
			Error("String: overflow!");
		strcpy_s(str, size + 1, s.str);

}
//ת����ֵ
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
//���Ƹ�ֵ
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
//�Ӵ�����
String& String::Insert(int id, const String& s) {
	char * p, *p1, *buf;
	int len = size;
	int len1 = s.size;
	int left = len - id;
	int i;
	if (id<0 || id>len)
		Error("id is illegal!");
	//����һ
	buf = str;
	str = new char[len + len1 + 1];
	if (str == NULL)
		Error("overflow!");
	strcpy_s(str, len + len1 + 1, buf);
	delete[]buf;
	//�����
	p = str + len;
	p1 = p + len1;
	for (i = 1; i <= left + 1;++i)
		*p1-- = *p--;
	//������
	p = str + id;
	p1 = s.str;
	while (*p1 != '\0')
		*p++ = *p1++;
	size = len + len1;
	return *this;
}
//�Ӵ�ɾ��
String& String::Erase(int id, int num) {
	char*p, *q, *buf;
	int len = size;
	int left = len - id;
	if (id < 0 || id>size)
		Error("id is illegal!");
	if (num <= 0 || num > left)
		Error("num is illegal!");
	//����һ
	p = str + id;
	q = str + id + num;
	while (*q != '\0')
		*p++ = *q++;
	*p = '\0';
	//�����
	buf = str;
	//������
	len = strlen(buf);
	str = new char[len + 1];
	if (str == NULL)
		Error("overflow");
	strcpy_s(str, len + 1, buf);
	size = len;
	delete[]buf;
	return * this;
}
//�������
istream& operator >> (istream & istr, String& s) {
	char buf[256];   //256�����뻺�����ĳ���
	istr >> buf;
	s = buf;
	return istr;
}
ostream& operator<<(ostream& ostr, String &s) {
	ostr << s.str;
	return ostr;
}