#include <iostream>
using namespace std;

class item
{
private:
	int price;
	int stock;
	int discount;
public:
	item(int price, int stock) { this->price = price; this->stock = stock; discount = 0; }
	int getprice() { return price; }
	int getstock() { return stock; }
	int getdiscount() { return discount; }
	void addstock(int num) { this->stock += num; }
	void sell_item(int num) { this->stock -= num; }
	void setdiscount(int num) { discount = num; }
};
class Pen :public item
{
public:
	Pen(int price, int stock) :item(price, stock) { print(); }

	void print()
	{
		cout << "======================" << endl;
		cout << "----------Pen---------" << endl;
		cout << "Price : " << getprice() << endl;
		cout << "Stock : " << getstock() << endl;
		cout << "Discount : " << getdiscount()<<'%'<< endl;
		cout << "----------------------" << endl;
	}
};
class Pencil :public item
{
public:
	Pencil(int price, int stock) :item(price, stock) { print(); }

	void print()
	{
		cout << "--------Pencil--------" << endl;
		cout << "Price : " << getprice() << endl;
		cout << "Stock : " << getstock() << endl;
		cout << "Discount : " << getdiscount() << '%' << endl;
		cout << "----------------------" << endl;
	}
};
class Eraser :public item
{
public:
	Eraser(int price, int stock) :item(price, stock) { print(); }

	void print()
	{
		cout << "--------Eraser--------" << endl;
		cout << "Price : " << getprice() << endl;
		cout << "Stock : " << getstock() << endl;
		cout << "Discount : " << getdiscount() << '%' << endl;
		cout << "----------------------" << endl;
		cout << "======================" << endl;
	}
};

int main()
{
	class Pen pen(600, 100);
	class Pencil pencil(1200, 100);
	class Eraser eraser(500, 100);
	int command;
	string name;
	int num = 0;
	int sale = 0;
	while (1)
	{
		cout << "Enter Any Command(0 : Sell, 1 : AddStock, 2 : Discount, 3 : Print, 4 : Quit): ";
		cin >> command;
		if (command == 0)
		{
			cin >> name;
			if (name == "Pen")
			{
				cin >> num;
				if (pen.getstock() > num * 3)
				{
					pen.sell_item(num * 3);
					sale += 600 * num * (100 - pen.getdiscount()) / 100;
				}
			}
			else if (name == "Pencil")
			{
				cin >> num;
				if (pencil.getstock() > num * 12)
				{
					pencil.sell_item(num * 12);
					sale += 1200 * num * (100 - pencil.getdiscount()) / 100;
				}
			}
			else if (name == "Eraser")
			{
				cin >> num;
				if (eraser.getstock() > num)
				{
					eraser.sell_item(num);
					sale += 500 * num * (100 - eraser.getdiscount()) / 100;
				}
			}
			else
				continue;
		}
		else if (command == 1)
		{
			cin >> name;
			if (name == "Pen")
			{
				cin >> num;
				pen.addstock(num);
			}
			else if (name == "Pencil")
			{
				cin >> num;
				pencil.addstock(num);
			}
			else if (name == "Eraser")
			{
				cin >> num;
				eraser.addstock(num);
			}
			else
				continue;
		}
		else if (command == 2)
		{
			cin >> name;
			if (name == "Pen")
			{
				cin >> num;
				pen.setdiscount(num);
			}
			else if (name == "Pencil")
			{
				cin >> num;
				pencil.setdiscount(num);
			}
			else if (name == "Eraser")
			{
				cin >> num;
				eraser.setdiscount(num);
			}
			else
				continue;
		}
		else if (command == 3)
		{
			pen.print();
			pencil.print();
			eraser.print();
		}
		else if (command == 4)
		{
			break;
		}
		cout << "======================" << endl;
		cout << "Sales : " << sale << endl;
	}
	return 0;
}