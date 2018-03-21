#include<iostream>
using namespace std;
class shape {           //�������
public:
	virtual double Area() = 0;
	virtual void Show() = 0;
};
class Triangle :public shape {            //������������
private:
	double height, bottom;
	virtual double Area() { return (bottom*height )/ 2; }
public:
	Triangle(double h,double b):height(h),bottom(b){}
	virtual void Show() { cout << "The area of the Triangle=" << Area() << endl; }
};
int main() {
	shape *s = new Triangle(3,4);
	s->Show();
}