#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class person {
protected:
	char name[10];  //����
	char home[20];  //סַ
	char tel[20];   //�绰
	char postcode[10];//�ʱ�
	person *mynext;   //��һ��ѧ��ָ��
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
	cout << "����" << "\t" << "סַ" << "\t" << "�绰" << "\t" << "�ʱ�" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << name << "\t" << home << "\t" << tel << "\t" << postcode << endl;
	cout << "----------------------------------------------------------------------" << endl;
}
class AddressBook {  //��ϵ����
private:
	person * myfirst;//ָ����ϵ����Ա��ָ��
public:
	AddressBook();
	AddressBook(char npname[], char nhome[], char nptel[], char nppostcode[]);
	~AddressBook();
	void insert(char npname[], char nhome[], char nptel[], char nppostcode[]);
	void display();//��ʾ��¼
	void query();//�������ֲ�ѯ
	void add();      //����
	void update();    //�޸�
	void save();    //���ļ������¼
	void load();   //���ļ��ڶ�ȡ
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
//�����Ա
void AddressBook::add()
{
	char pname[10], phome[20], ptel[20], ppostcode[10];
	cout << "����:"; cin >> pname; cout << endl;
	cout << "סַ:"; cin >> phome; cout << endl;
	cout << "�绰:"; cin >> ptel; cout << endl;
	cout << "�ʱ�:"; cin >> ppostcode; cout << endl;
	insert(pname, phome, ptel, ppostcode);
}
//��Ա��������³�Ա��Ϣ
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
//��ʾ��¼
void AddressBook::display()
{
	person *head = myfirst;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "����" << "\t" << "סַ" << "\t" << "�绰" << "\t" << "�ʱ�" << endl;
	int i = 0;
	while (head != NULL)
	{
		i++;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << head->getname() << "\t" << head->gethome() << "\t" << head->gettel() << "\t" << head->getpostcode() << endl;
		head = head->getnext();
	}
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "Ŀǰ�ܹ���" << i << "����Ա��Ϣ" << endl;
}
//�޸ļ�¼
void AddressBook::update()
{
	char name[10];
	char flag[5];
	person *head = myfirst;
	cout << "������Ҫ�޸��˵�����:";
	cin >> name;
	if (head == NULL)
	{
		cout << "ͨѶ¼������!" << endl; exit(1);
	}
	else
		while (head != NULL)
		{
			if (strcmp(head->getname(), name) == 0)
			{
				cout << "��Ҫ�޸ĵ���Ա��Ϣ����:" << endl;
				head->output();
				head = head->getnext();
				while (1)
				{
					int i;
					char newtxt[60];
					cout << "������Ҫ�޸ĵ���Ϣ��";
					cout << "1.סַ 2.�绰 3.�ʱ� 0.����\n";
					cout << ".";
					cin >> i;
					switch (i)
					{
					case 1:
					{
						cout << "������סַ:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->gethome(), newtxt);
					}
					break;
					case 2:
					{
						cout << "������绰:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->gettel(), newtxt);
					}
					break;
					case 3:
					{
						cout << "�������ʱ�:\n";
						cout << ".";
						cin >> newtxt;
						strcpy(head->getpostcode(), newtxt);
					}
					break;
					default:
						break;
					}
					cout << "�Ƿ�����޸�(Y/N):";
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
//��ȡ��¼
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
		cout << "����ʧ��,Ŀǰ�ĵ���û������!" << endl;
		fin.close();
	}
	else
	{
		fin.close();
		cout << "�ѳɹ�����" << i << "������" << endl;
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
	cout << "���ݱ������!\n";
}
void AddressBook::query()
{
	char name[10];
	person *head = myfirst;
	cout << "�������������в�ѯ:";
	cin >> name;
	if (head == NULL)
	{
		cout << "ͨѶ¼������!" << endl;
		exit(1);
	}
	while (head != NULL)
	{
		if (strcmp(head->getname(), name) == 0)
		{
			cout << "��Ҫ���ҵ���Ա��Ϣ����:" << endl;
			head->output(); head=head->getnext();
		}
		else
		{
			head = head->getnext();
		}
	}
}
