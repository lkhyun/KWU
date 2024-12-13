#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class BST
{
public:
	char word[20] = { 0 };
	BST* left = NULL;
	BST* right = NULL;
};

class node
{
public:
	node() {}
	node(int a, int b, int c) { z = a; y = b; x = c; }
	int x;
	int y;
	int z;
	BST* head = NULL;
	node* pointer1D = NULL;//1차원에서 사용할 임시포인터
	node* xplus = NULL;
	node* xminus = NULL;
	node* yplus = NULL;
	node* yminus = NULL;
	node* zplus = NULL;
	node* zminus = NULL;
};


class cube
{
private:
	node* cubehead = NULL;
	node* center = NULL;
	node* cubetool = NULL;
public:
	cube()//cube를 만들기 전 리스트를 1차원으로 27개 만든다.
	{
		for (int i = 0; i < 3; i++)//z
		{
			for (int j = 0; j < 3; j++)//y
			{
				for (int k = 0; k < 3; k++)//x
				{
					node* temp = new node(i,j,k);
					if (i == 1 && j == 1 && k == 1)
						center = temp;
					if (i == 0 && j == 0 && k == 0)
					{
						cubehead = temp;
						cubetool = temp;
					}
					else
					{
						cubetool->pointer1D = temp;
						cubetool = temp;
					}
				}
			}
		}
	}
	int num = 0;//임시로 사용할 변수저장소
	node* search1D(int a, int b, int c);//1차원에서 좌표에 맞는 노드를 찾아 포인터를 반환하는 함수
	void createcube();//큐브형태로 구현
	node* search3D(int a, int b, int c);
	void insertword(node* insert, char* word);
	void nodeprint(BST* root);//노드에 있는 단어들을 모두 출력하는 함수
	void preorderprint(BST* root);
	void inorderprint(BST* root);
	void postorderprint(BST* root);
	bool locationprint(BST* root, char* word);//해당 좌표의 노드에 단어가 있는지 알아보는 함수
	void findword(node* block, char* word);//노드의 단어를 찾으면 좌표를 출력하는 함수
	void wordcount(BST* root);//노드 속 단어갯수 출력함수
	void deleteword(node* block, char* word);
	void nodeexchange(node* A, node* B);
	void cubeturn(int surface, int turn, int xyz);
	void memoryfree(node* block);
};
node* cube::search1D(int a, int b, int c)//1차원에서 좌표에 맞는 노드를 찾아 포인터를 반환하는 함수(처음 큐브 만들때만 사용)
{
	cubetool = cubehead;
	while (cubetool != NULL)
	{
		if (cubetool->z == a && cubetool->y == b && cubetool->x == c)
			return cubetool;
		cubetool = cubetool->pointer1D;
	}
	return NULL;
}
void cube::createcube()//1차원 링크드리스트에 반복문을 통해 모두 접근하여 3차원 큐브형태로 변환하는 함수(처음 큐브 만들때만 사용)
{
	for (int i = 0; i < 3; i++)//z
	{
		for (int j = 0; j < 3; j++)//y
		{
			for (int k = 0; k < 3; k++)//x
			{
				node* temp = search1D(i, j, k);
				if (i == 0)
				{
					temp->zplus = search1D(i + 1, j, k);
				}
				if (i == 1)
				{
					temp->zplus = search1D(i + 1, j, k);
					temp->zminus = search1D(i - 1, j, k);
				}
				if (i == 2)
				{
					temp->zminus = search1D(i - 1, j, k);
				}
				if (j == 0)
				{
					temp->yplus = search1D(i, j + 1, k);
				}
				if (j == 1)
				{
					temp->yplus = search1D(i, j + 1, k);
					temp->yminus = search1D(i, j - 1, k);
				}
				if (j == 2)
				{
					temp->yminus = search1D(i, j - 1, k);
				}
				if (k == 0)
				{
					temp->xplus = search1D(i, j, k + 1);
				}
				if (k == 1)
				{
					temp->xplus = search1D(i, j, k + 1);
					temp->xminus = search1D(i, j, k - 1);
				}
				if (k == 2)
				{
					temp->xminus = search1D(i, j, k - 1);
				}
			}
		}
	}
}
node* cube::search3D(int a, int b, int c)//큐브상태의 링크드 리스트의 좌표를 인자로 받아 해당 좌표의 포인터를 반환하는 함수
{
	cubetool = center;
	if (a < 0 || a>2)
		return NULL;
	if (b < 0 || b>2)
		return NULL;
	if (c < 0 || c>2)
		return NULL;
	if (a - cubetool->z > 0)
	{
		cubetool = cubetool->zplus;
	}
	else if (a - cubetool->z < 0)
	{
		cubetool = cubetool->zminus;
	}
	if (b - cubetool->y > 0)
	{
		cubetool = cubetool->yplus;
	}
	else if (b - cubetool->y < 0)
	{
		cubetool = cubetool->yminus;
	}
	if (c - cubetool->x > 0)
	{
		cubetool = cubetool->xplus;
	}
	else if (c - cubetool->x < 0)
	{
		cubetool = cubetool->xminus;
	}
	return cubetool;
}
void cube::insertword(node* insert, char* word)//word를 넣을 곳을 insert 노드포인터로 입력받은 후 해당 자리에 단어를 넣는 함수
{
	BST* n = insert->head;
	if (n == NULL)
	{
		insert->head = new BST;
		strcpy(insert->head->word, word);
		return;
	}
	while (n != NULL)
	{
		if (stricmp(n->word, word) < 0)
		{
			if (n->right == NULL)
			{
				n->right = new BST;
				strcpy(n->right->word, word);
				break;
			}
			n = n->right;
		}
		else if (stricmp(n->word, word) > 0)
		{
			if (n->left == NULL)
			{
				n->left = new BST;
				strcpy(n->left->word, word);
				break;
			}
			n = n->left;
		}
		else
			break;
	}
}
void cube::deleteword(node* block, char* word)
{
	BST* n = block->head;
	BST* a = block->head;
	while (n != NULL)
	{
		if (stricmp(n->word,word)<0)
		{
			a = n;
			n = n->right;
		}
		else if (stricmp(n->word, word) > 0)
		{
			a = n;
			n = n->left;
		}
		else if (stricmp(n->word, word) == 0)
		{
			if (a->left == n)
			{
				if (n->left != NULL && n->right == NULL)
				{
					a->left = n->left;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					BST* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->word,s->word);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->word,s->word);
					a->left = s->right;
					delete s;
					break;
				}
				a->left = n->right;
				break;
			}
			else if (a->right == n)
			{
				if (n->left != NULL && n->right == NULL)
				{
					a->right = n->left;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					BST* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->word,s->word);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->word,s->word);
					a->left = s->right;
					delete s;
					break;
				}
				a->right = n->right;
				break;
			}
			else if (n->word == block->head->word)
			{
				if (n->left == NULL && n->right == NULL)
				{
					block->head = NULL;
					break;
				}
				else if (n->left != NULL && n->right == NULL)
				{
					block->head = n->left;
					delete n;
					break;
				}
				else if (n->left == NULL && n->right != NULL)
				{
					block->head = n->right;
					delete n;
					break;
				}
				else if (n->left != NULL && n->right != NULL)
				{
					BST* s = n->right;
					a = n;
					while (s->left != NULL)
					{
						a = s;
						s = s->left;
					}
					if (n == a)
					{
						strcpy(n->word,s->word);
						n->right = s->right;
						delete s;
						break;
					}
					strcpy(n->word,s->word);
					a->left = s->right;
					delete s;
					break;
				}
			}
		}
	}
}
bool cube::locationprint(BST* root,char*word)
{
	BST* temp = root;
	while (temp != NULL)
	{
		if (stricmp(temp->word, word) == 0)
			return 1;
		else if (stricmp(temp->word, word) > 0)
			temp = temp->left;
		else if (stricmp(temp->word, word) < 0)
			temp = temp->right;
	}
	return 0;
}
void cube::findword(node* block, char* word)
{
	BST* search = block->head;
	bool temp = 0;
	temp = locationprint(search, word);
	if (temp==1)
	{
		cout << block->z << block->y << block->x << endl;
	}
}
void cube::nodeprint(BST* root)
{
	cout << "preorder : ";
	preorderprint(root);
	cout << endl;
	cout << "inorder : ";
	inorderprint(root);
	cout << endl;
	cout << "postorder : ";
	postorderprint(root);
	cout << endl;
}
void cube::preorderprint(BST* root)
{
	if (root != NULL)
	{
		cout << root->word << " ";
		preorderprint(root->left);
		preorderprint(root->right);
	}
}
void cube::inorderprint(BST* root)
{
	if (root != NULL)
	{
		inorderprint(root->left);
		cout << root->word << " ";
		inorderprint(root->right);
	}
}
void cube::postorderprint(BST* root)
{
	if (root != NULL)
	{
		postorderprint(root->left);
		postorderprint(root->right);
		cout << root->word << " ";
	}
}
void cube::wordcount(BST* root)
{
	if (root != NULL)
	{
		num++;
		wordcount(root->left);
		wordcount(root->right);
	}
}

void cube::nodeexchange(node* A, node* B)
{
	node* temp = new node(5,5,5);
	node* temp2 = new node(6,6,6);
	int num1 = 0;

	if (A->xplus == B)//인접했을 시 링크해제
	{
		temp2->xminus = search3D(A->z, A->y, A->x - 1);
		temp2->xplus = search3D(B->z, B->y, B->x + 1);
	}
	if (A->xminus == B)
	{
		temp2->xminus = search3D(B->z, B->y, B->x - 1);
		temp2->xplus = search3D(A->z, A->y, A->x + 1);
	}
	if (A->yplus == B)
	{
		temp2->yminus = search3D(A->z, A->y - 1, A->x);
		temp2->yplus = search3D(B->z, B->y + 1, B->x);
	}
	if (A->yminus == B)
	{
		temp2->yminus = search3D(B->z, B->y - 1, B->x);
		temp2->yplus = search3D(A->z, A->y + 1, A->x);
	}
	if (A->zplus == B)
	{
		temp2->zminus = search3D(A->z - 1, A->y, A->x);
		temp2->zplus = search3D(B->z + 1, B->y, B->x);
	}
	if (A->zminus == B)
	{
		temp2->zminus = search3D(B->z - 1, B->y, B->x);
		temp2->zplus = search3D(A->z + 1, A->y, A->x);
	}

	temp->zplus = A->zplus;//A와 B가 가리키는 포인터 바꾸기
	A->zplus = B->zplus;
	B->zplus = temp->zplus;

	temp->yplus = A->yplus;
	A->yplus = B->yplus;
	B->yplus = temp->yplus;

	temp->xplus = A->xplus;
	A->xplus = B->xplus;
	B->xplus = temp->xplus;

	temp->zminus = A->zminus;
	A->zminus = B->zminus;
	B->zminus = temp->zminus;

	temp->yminus = A->yminus;
	A->yminus = B->yminus;
	B->yminus = temp->yminus;

	temp->xminus = A->xminus;
	A->xminus = B->xminus;
	B->xminus = temp->xminus;

	if (A->zminus != NULL)//A와 인접한 노드들이 B를 가리키도록 포인터 수정
		A->zminus->zplus = A;
	if (A->zplus != NULL)
		A->zplus->zminus = A;
	if (A->yminus != NULL)
		A->yminus->yplus = A;
	if (A->yplus != NULL)
		A->yplus->yminus = A;
	if (A->xminus != NULL)
		A->xminus->xplus = A;
	if (A->xplus != NULL)
		A->xplus->xminus = A;

	if (B->zminus != NULL)//B와 인접한 노드들이 A를 가리키도록 포인터 수정
		B->zminus->zplus = B;
	if (B->zplus != NULL)
		B->zplus->zminus = B;
	if (B->yminus != NULL)
		B->yminus->yplus = B;
	if (B->yplus != NULL)
		B->yplus->yminus = B;
	if (B->xminus != NULL)
		B->xminus->xplus = B;
	if (B->xplus != NULL)
		B->xplus->xminus = B;

	num1 = A->x;//A와 B 좌표 바꾸기
	A->x = B->x;
	B->x = num1;
	num1 = A->y;
	A->y = B->y;
	B->y = num1;
	num1 = A->z;
	A->z = B->z;
	B->z = num1;

	if (A->xplus == A)
	{
		if (A->x == 0 && B->x == 1)
		{
			A->xminus = NULL;
			A->xplus = B;
			B->xminus = A;
			B->xplus = temp2->xplus;
			B->xplus->xminus = B;
			B->xplus->xplus = NULL;
		}
		else if (A->x == 1 && B->x == 2)
		{
			A->xminus = temp2->xminus;
			A->xplus = B;
			B->xminus = A;
			B->xplus = NULL;
			A->xminus->xplus = A;
			A->xminus->xminus = NULL;
		}
		else if (B->x == 0 && A->x == 1)
		{
			B->xminus = NULL;
			B->xplus = A;
			A->xminus = B;
			A->xplus = temp2->xplus;
			A->xplus->xminus = A;
			A->xplus->xplus = NULL;
		}
		else if (B->x == 1 && A->x == 2)
		{
			B->xminus = temp2->xminus;
			B->xplus = A;
			A->xminus = B;
			A->xplus = NULL;
			B->xminus->xplus = B;
			B->xminus->xminus = NULL;
		}
	}
	if (A->yplus == A)
	{
		if (A->y == 0 && B->y == 1)
		{
			A->yminus = NULL;
			A->yplus = B;
			B->yminus = A;
			B->yplus = temp2->yplus;
			B->yplus->yminus = B;
			B->yplus->yplus = NULL;
		}
		else if (A->y == 1 && B->y == 2)
		{
			A->yminus = temp2->yminus;
			A->yplus = B;
			B->yminus = A;
			B->yplus = NULL;
			A->yminus->yplus = A;
			A->yminus->yminus = NULL;
		}
		else if (B->y == 0 && A->y == 1)
		{
			B->yminus = NULL;
			B->yplus = A;
			A->yminus = B;
			A->yplus = temp2->yplus;
			A->yplus->yminus = A;
			A->yplus->yplus = NULL;
		}
		else if (B->y == 1 && A->y == 2)
		{
			B->yminus = temp2->yminus;
			B->yplus = A;
			A->yminus = B;
			A->yplus = NULL;
			B->yminus->yplus = B;
			B->yminus->yminus = NULL;
		}
	}
	if (A->zplus == A)
	{
		if (A->z == 0 && B->z == 1)
		{
			A->zminus = NULL;
			A->zplus = B;
			B->zminus = A;
			B->zplus = temp2->zplus;
			B->zplus->zminus = B;
			B->zplus->zplus = NULL;
		}
		else if (A->z == 1 && B->z == 2)
		{
			A->zminus = temp2->zminus;
			A->zplus = B;
			B->zminus = A;
			B->zplus = NULL;
			A->zminus->zplus = A;
			A->zminus->zminus = NULL;
		}
		else if (B->z == 0 && A->z == 1)
		{
			B->zminus = NULL;
			B->zplus = A;
			A->zminus = B;
			A->zplus = temp2->zplus;
			A->zplus->zminus = A;
			A->zplus->zplus = NULL;
		}
		else if (B->z == 1 && A->z == 2)
		{
			B->zminus = temp2->zminus;
			B->zplus = A;
			A->zminus = B;
			A->zplus = NULL;
			B->zminus->zplus = B;
			B->zminus->zminus = NULL;
		}
	}
	if (A->x == 1 && A->y == 1 && A->z == 1)
		center = A;
	if (B->x == 1 && B->y == 1 && B->z == 1)
		center = B;

	delete temp;
	delete temp2;
}
void cube::cubeturn(int surface,int turn,int xyz)
{
	if (surface == 0)//전면 y동일
	{
		if (turn == 0)
		{
			nodeexchange(search3D(0, xyz, 0), search3D(0, xyz, 2));
			nodeexchange(search3D(0, xyz, 0), search3D(2, xyz, 2));
			nodeexchange(search3D(0, xyz, 0), search3D(2, xyz, 0));
			nodeexchange(search3D(0, xyz, 1), search3D(1, xyz, 2));
			nodeexchange(search3D(0, xyz, 1), search3D(2, xyz, 1));
			nodeexchange(search3D(0, xyz, 1), search3D(1, xyz, 0));
		}
		else if(turn == 1)
		{
			nodeexchange(search3D(0, xyz, 0), search3D(2, xyz, 0));
			nodeexchange(search3D(0, xyz, 0), search3D(2, xyz, 2));
			nodeexchange(search3D(0, xyz, 0), search3D(0, xyz, 2));
			nodeexchange(search3D(0, xyz, 1), search3D(1, xyz, 0));
			nodeexchange(search3D(0, xyz, 1), search3D(2, xyz, 1));
			nodeexchange(search3D(0, xyz, 1), search3D(1, xyz, 2));
		}
	}
	else if (surface == 1)//윗면 z동일
	{
		if (turn == 0)
		{
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 2, 0));
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 2, 2));
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 0, 2));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 1, 0));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 2, 1));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 1, 2));
		}
		else if (turn == 1)
		{
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 0, 2));
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 2, 2));
			nodeexchange(search3D(xyz, 0, 0), search3D(xyz, 2, 0));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 1, 2));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 2, 1));
			nodeexchange(search3D(xyz, 0, 1), search3D(xyz, 1, 0));
		}
	}
	else if (surface == 2)//측면 x동일
	{
		if (turn == 0)
		{
			nodeexchange(search3D(0, 0, xyz), search3D(0, 2, xyz));
			nodeexchange(search3D(0, 0, xyz), search3D(2, 2, xyz));
			nodeexchange(search3D(0, 0, xyz), search3D(2, 0, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(1, 2, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(2, 1, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(1, 0, xyz));
		}
		else if (turn == 1)
		{
			nodeexchange(search3D(0, 0, xyz), search3D(2, 0, xyz));
			nodeexchange(search3D(0, 0, xyz), search3D(2, 2, xyz));
			nodeexchange(search3D(0, 0, xyz), search3D(0, 2, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(1, 0, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(2, 1, xyz));
			nodeexchange(search3D(0, 1, xyz), search3D(1, 2, xyz));
		}
	}
}
void cube::memoryfree(node*block)
{
	BST* n = block->head;
	BST* a = n;
	if (n == NULL)
		return;
	while (block->head->left != NULL || block->head->right != NULL)
	{
		while (1)
		{
			if (n->left != NULL)
			{
				a = n;
				n = n->left;
				if (n->left == NULL && n->right == NULL)
				{
					delete n;
					a->left = NULL;
					break;
				}
			}
			else if (n->right != NULL)
			{
				a = n;
				n = n->right;
				if (n->left == NULL && n->right == NULL)
				{
					delete n;
					a->right = NULL;
					break;
				}
			}
		}
		n = block->head;
	}
	delete block->head;
}
int main()
{
	cube wordcube;
	ifstream readtxt;
	int command = 0;
	int inputx = 0;
	int inputy = 0;
	int inputz = 0;
	int inputx1 = 0;
	int inputy1 = 0;
	int inputz1 = 0;
	char newword[20];
	wordcube.createcube();
	readtxt.open("WordBook.txt");
	if (!readtxt)
	{
		cout << "파일을 열 수 없습니다.";
		exit(0);
	}
	while (!readtxt.eof())
	{
		readtxt >> inputz >> inputy >> inputx >> newword;
		wordcube.insertword(wordcube.search3D(inputz,inputy,inputx), newword);
	}
	readtxt.close();

	while (1)
	{
		cout << "Enter Any Command(1 : insert, 2 : Delete, 3 : Find, 4 : Print, 5 : Print_All, 6 : Turn, 7 : Exchange, 8 : Exit) : ";
		cin >> command;
		if (command == 1)
		{
			cin >> inputz >> inputy >> inputx >> newword;
			wordcube.insertword(wordcube.search3D(inputz, inputy, inputx), newword);
		}
		else if (command == 2)
		{
			cin >> inputz >> inputy >> inputx >> newword;
			wordcube.deleteword(wordcube.search3D(inputz, inputy, inputx), newword);
		}
		else if (command == 3)
		{
			cin >> newword;
			for (int i = 0; i < 3; i++)//z
			{
				for (int j = 0; j < 3; j++)//y
				{
					for (int k = 0; k < 3; k++)//x
					{
						wordcube.findword(wordcube.search3D(i, j, k), newword);
					}
				}
			}
		}
		else if (command == 4)
		{
			cin >> inputz >> inputy >> inputx;
			wordcube.nodeprint(wordcube.search3D(inputz, inputy, inputx)->head);
		}
		else if (command == 5)
		{
			for (int i = 0; i < 3; i++)//y
			{
				for (int j = 0; j < 3; j++)//z
				{
					for (int k = 0; k < 3; k++)//x
					{
						wordcube.num = 0;
						wordcube.wordcount(wordcube.search3D(j, i, k)->head);
						cout << wordcube.num << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
		}
		else if (command == 6)
		{
			cin >> inputx >> inputy >> inputz;
			wordcube.cubeturn(inputx, inputy, inputz);
			for (int i = 0; i < 3; i++)//z
			{
				for (int j = 0; j < 3; j++)//y
				{
					for (int k = 0; k < 3; k++)//x
					{
						wordcube.num = 0;
						wordcube.wordcount(wordcube.search3D(j, i, k)->head);
						cout << wordcube.num << " ";
					}
					cout << endl;
				}
				cout << endl;
			}
		}
		else if (command == 7)
		{
			cin >> inputz >> inputy >> inputx >> inputz1 >> inputy1 >> inputx1;//앞에서부터 zplus, zminus, yplus, yminus, xplus, xminus이다.
			wordcube.nodeexchange(wordcube.search3D(inputz, inputy, inputx), wordcube.search3D(inputz1, inputy1, inputx1));
		}
		else if (command == 8)
		{
			for (int i = 0; i < 3; i++)//z
			{
				for (int j = 0; j < 3; j++)//y
				{
					for (int k = 0; k < 3; k++)//x
					{
						wordcube.memoryfree(wordcube.search3D(i, j, k));
					}
				}
			}
			delete wordcube.search3D(0, 0, 0);
			delete wordcube.search3D(0, 0, 2);
			delete wordcube.search3D(2, 0, 2);
			delete wordcube.search3D(2, 0, 0);
			delete wordcube.search3D(0, 2, 0);
			delete wordcube.search3D(0, 2, 2);
			delete wordcube.search3D(2, 2, 0);
			delete wordcube.search3D(2, 2, 2);
			delete wordcube.search3D(0, 1, 0);
			delete wordcube.search3D(0, 0, 1);
			delete wordcube.search3D(0, 2, 1);
			delete wordcube.search3D(0, 1, 2);
			delete wordcube.search3D(1, 2, 2);
			delete wordcube.search3D(1, 0, 2);
			delete wordcube.search3D(1, 0, 0);
			delete wordcube.search3D(1, 2, 0);
			delete wordcube.search3D(2, 1, 0);
			delete wordcube.search3D(2, 0, 1);
			delete wordcube.search3D(2, 2, 1);
			delete wordcube.search3D(2, 1, 2);
			delete wordcube.search3D(0, 1, 1);
			delete wordcube.search3D(1, 1, 0);
			delete wordcube.search3D(1, 2, 1);
			delete wordcube.search3D(1, 1, 2);
			delete wordcube.search3D(1, 0, 1);
			delete wordcube.search3D(2, 1, 1);
			delete wordcube.search3D(1, 1, 1);
			break;
		}
	}
	return 0;
}
