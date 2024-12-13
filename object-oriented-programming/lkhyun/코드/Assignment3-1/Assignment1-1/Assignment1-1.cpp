#include<iostream>
using namespace std;
class Person 
{
   friend ostream& operator << (ostream&, const Person&);
   friend istream& operator>>(istream&, Person&);
private:
   string name;
   int age;
   string area;
};

ostream& operator <<(ostream& output, const Person & data) 
{
	output << "�̸�: " << data.name << endl << "����:  " << data.age << endl<< "������: " << data.area;
   return output;
}
istream& operator>>(istream& input, Person& data)
{
   input >> data.name >> data.age >> data.area;
   return input;
}
int main() 
{
   Person P;
   cin >> P;
   cout << P;
   return 0;
}