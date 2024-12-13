#include <iostream>
using namespace std;

class animal
{
private:
	char name[10] = { 0 };
	int year = 0;
	char species[100] = { 0 };
public:
	animal(char* name, int year, char* species)
	{
		this->year = year;
		for (int i = 0; name[i] != 0; i++)
			this->name[i] = name[i];
		for (int i = 0; species[i] != 0; i++)
			this->species[i] = species[i];
	}
	void print_all() const
	{
		cout << "Name : " << name << endl;
		cout << "Year : " << year << endl;
		cout << "Species : " << species << endl;
	}
	bool print_species(char* species) const
	{
		int i = 0;
		while (this->species[i] != 0 || species[i] != 0)
		{
			if (this->species[i] == species[i])
			{
				i++;
				continue;
			}
			else
				return 0;
		}
		return 1;
	}

};
class zoo
{
private:
	animal* animal_list[100];
	int size;
public:
	zoo() :size(0){}
	void newanimal(animal* ptr)
	{
		animal_list[size++] = ptr;
	}
	void printall() const
	{
		for (int i = 0; i < size; i++)
		{
			cout << "----------" << i << "----------" << endl;
			animal_list[i]->print_all();
			cout << "---------------------" << endl;
		}
			
	}
	void printspecies(char*species) const
	{
		int num = 0;
		for (int i = 0; i < size; i++)
		{
			if (animal_list[i]->print_species(species) == 1)
			{
				cout << "----------" << num << "----------" << endl;
				animal_list[i]->print_all();
				cout << "--------------------" << endl;
				num++;
			}
				
		}
		cout << "Number of Species is :" << num << endl;
		cout << "--------------------" << endl;
	}
	~zoo()
	{
		for (int i = 0; i < size; i++)
			delete animal_list[i];
	}

};

int main()
{
	string command;
	zoo control;
	char name[10] = { 0 };
	int year = 0;
	char species[100] = { 0 };

	while (1)
	{

		cout << "Please Enter Any Command(new_animal, print_all,print_species,exit) :";
		cin >> command;
		if (command == "new_animal")
		{
			cin >> name >> year >> species;
			control.newanimal(new animal(name, year, species));
		}
		else if (command == "print_all")
		{
			cout << "------print_all------" << endl;
			control.printall();
		}
		else if (command == "print_species")
		{
			cin >> species;
			cout << "------print_species------" << endl;
			control.printspecies(species);
		}
		else if (command == "exit")
			break;

	}
	return 0;
}
 