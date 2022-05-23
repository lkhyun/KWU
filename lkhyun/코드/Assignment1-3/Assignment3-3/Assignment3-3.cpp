#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int i = 0;
	int p = 0;
	int temp = 0;
	char word[100][20] = { 0 };
	char length[21][100]={ 0 };
	ifstream assignment;
	assignment.open("Assignment.txt");
	if (assignment.is_open() == 0)
		cout << "파일 안 열림";
	for (i = 0;; i++)
	{
		p = 0;
		assignment.get(word[i][p]);
		if (word[i][p] == NULL)
			break;

		for (p = 1;; p++)
		{
			assignment.get(word[i][p]);
			if (word[i][p] == ' ')
				break;
		}
		
	}
	assignment.close();

	for (i = 0;; i++)
	{
		if (word[i][0] == 0)
			break;
		for (p = 0;; p++)
		{
			if (word[i][p] == NULL)
			{
				if (length[p][0] != NULL)
				{
					for (int s = 0;; s++)
					{
						if (length[p][s] == 0)
						{
							temp = s;
							break;
						}
					}
					for (int s = 0; s < p; s++)
					{
						length[p][temp++] = word[i][s];
					}
					break;
						
				}
				else
				{
					for (int s = 0; s < p; s++)
					{
						length[p][s] = word[i][s];
					}
					break;
				}
				
			}
				
		}
	}

	for (i = 0;i<20; i++)
	{
		if (length[i][0] != NULL)
		{
			cout << "length" << i-1 << ": ";
			for (p = 0;; p++)
			{
				if (length[i][p] == NULL)
				{
					cout << endl;
					break;
				}
				cout << length[i][p];
			}
		}
		
	}
	return 0;

}