#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class person {
protected:
	char name[10];  //姓名
	char home[20];  //住址
	char tel[20];   //电话
	char postcode[10];//邮编
	person *mynext;   //下一个学生指针
public:
	person();
	person(char pname[], char phome[], char ptel[], char ppostcode[]);
	person(char pname[], char phome[], char ptel[], char ppostcode[], person *next);
	char *getname() { return name; }
	char *gethome() { return home; }
	char *gettel() { return tel; }
	char *getpostcode() { return postcode; }
	person *getnext() { return mynext; }
	void setnext(person *next) { mynext = next; }
	void output();
};
person::person()
{
	strcpy(name, "");
	strcpy(tel, "");
	strcpy(postcode, "");
	mynext = NULL;
}
person::person(char pname[], char phome[], char ptel[], char ppostcode[])
{
	strcpy(name, pname);
	strcpy(home, phome);
	strcpy(tel, ptel);
	strcpy(postcode, ppostcode);
}
person::person(char pname[], char phome[], char ptel[], char ppostcode[], person *next)
{
	strcpy(name, pname);
	strcpy(home, phome);
	strcpy(tel, ptel);
	strcpy(postcode, ppostcode);
	mynext = next;
}
void person::output()
{
	cout << "----------------------------------------------------------------------" << endl;
	cout << "姓名" << "\t" << "住址" << "\t" << "电话" << "\t" << "邮编" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << name << "\t" << home << "\t" << tel << "\t" << postcode << endl;
	cout << "----------------------------------------------------------------------" << endl;
}
class AddressBook {  //联系人类
private:
	person * myfirst;//指向联系人人员的指针
public:
	AddressBook();
	AddressBook(char npname[], char nhome[], char nptel[], char nppostcode[]);
	~AddressBook();
	void insert(char npname[], char nhome[], char nptel[], char nppostcode[]);
	void display();//显示记录
	void query();//根据名字查询
	void add();      //增加
	void update();    //修改
	void save();    //向文件保存记录
	void load();   //从文件内读取
};
AddressBook::AddressBook()
{
	myfirst = NULL;
}

AddressBook::AddressBook(char npname[], char nhome[], char nptel[], char nppostcode[])
{
	myfirst = new person(npname, nhome, nptel, nppostcode);
}
AddressBook::~AddressBook()
{
	person *next = myfirst, *temp;
	while (next != NULL)
	{
		temp = next;
		next = next->getnext();
		delete temp;
	}
	myfirst = NULL;
}
//添加人员
void AddressBook::add()
{
	char pname[10], phome[20], ptel[20], ppostcode[10];
	cout << "姓名:"; cin >> pname; cout << endl;
	cout << "住址:"; cin >> phome; cout << endl;
	cout << "电话:"; cin >> ptel; cout << endl;
	cout << "邮编:"; cin >> ppostcode; cout << endl;
	insert(pname, phome, ptel, ppostcode);
}
//成员链表插入新成员信息
void AddressBook::insert(char npname[], char nhome[], char nptel[], char nppostcode[])
{
	person *pers = myfirst;
	if (pers == NULL)
		myfirst = new person(npname, nhome, nptel, nppostcode);
	else
	{
		while (pers->getnext() != NULL)
			pers = pers->getnext();
		pers->setnext(new person(npname, nhome, nptel, nppostcode, pers->getnext()));
	}
}
//显示记录
void AddressBook::display()
{
	person *head = myfirst;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "姓名" << "\t" << "住址" << "\t" << "电话" << "\t" << "邮编" << endl;
	int i = 0;
	while (head != NULL)
	{
		i++;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << head->getname() << "\t" << head->gethome() << "\t" << head->gettel() << "\t" << head->getpostcode() << endl;
		head = head->getnext();
	}
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "目前总共有" << i << "个人员信息" << endl;
}
//修改记录
void AddressBook::update()
{
	char name[10];
	char flag[5];
	person *head = myfirst;
	cout << "请输入要修改人的姓名:";
	cin >> name;
	if (head == NULL)
	{
		cout << "通讯录不存在!" << endl; exit(1);
	}
	else
		while (head != NULL)
		{
			if (strcmp(head->getname(), name) == 0)
			{
				cout << "您要修改的人员信息如下:" << endl;
				head->output();
				head = head->getnext();
				while (1)
				{
					int i;
					char newtxt[60];
					cout << "请输入要修改的信息项";
					cout << "1.住址 2.电话 3.邮编 0.返回\n";
					cout << ".";
					cin >> i;
					switch (i)
					{
					case 1:
					{
						cout << "请输入住址:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->gethome(), newtxt);
					}
					break;
					case 2:
					{
						cout << "请输入电话:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->gettel(), newtxt);
					}
					break;
					case 3:
					{
						cout << "请输入邮编:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->getpostcode(), newtxt);
					}
					break;
					default:
						break;
					}
					cout << "是否继续修改(Y/N):";
					cin >> flag;
					if (strcmp(flag, "Y\0") == 0)
						continue;
					else
					{
						break;
					}
				}
			}
			else
			{
				head = head->getnext();
			}
		}
}
//读取记录
void AddressBook::load()
{

	char name[40], home[10], tel[20], postcode[10];
	ifstream fin("addressbook.txt");
	int i = 0;
	while (fin >> name >> home >> tel >> postcode)
	{
		insert(name, home, tel, postcode);
		i++;
	}
	if (i == 0)
	{
		cout << "加载失败,目前文档内没有数据!" << endl;
		fin.close();
	}
	else
	{
		fin.close();
		cout << "已成功加载" << i << "行数据" << endl;
		display();
		fin.clear();
	}
	fin.close();
}
void AddressBook::save()
{
	ofstream fout("addressbook.txt", ios::app);
	person *pe = myfirst;
	while (pe)
	{
		fout << pe->getname() << "\t" << pe->gethome() << "\t" << pe->gettel() << "\t" << pe->getpostcode() << "\n";
		pe = pe->getnext();
	}
	fout.close();
	cout << "数据保存完毕!\n";
}
void AddressBook::query()
{
	char name[10];
	person *head = myfirst;
	cout << "请输入姓名进行查询:";
	cin >> name;
	if (head == NULL)
	{
		cout << "通讯录不存在!" << endl;
		exit(1);
	}
	while (head != NULL)
	{
		if (strcmp(head->getname(), name) == 0)
		{
			cout << "您要查找的人员信息如下:" << endl;
			head->output(); head=head->getnext();
		}
		else
		{
			head = head->getnext();
		}
	}
}
