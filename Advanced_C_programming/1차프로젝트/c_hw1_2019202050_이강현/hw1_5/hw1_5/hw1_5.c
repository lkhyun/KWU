#include <stdio.h>//��� ���� ����

int main()//main �Լ� ����
{
	int arr1[3][3] = { 0 };//�迭 ���� �� �ʱ�ȭ
	int arr2[3][3] = { 0 };//�迭 ���� �� �ʱ�ȭ
	int arr3[3][3] = { 0 };//�迭 ���� �� �ʱ�ȭ
	int i = 0, j = 0;//���� ����
	int num1 = 0, num2 = 0;//���� ����
	int mul = 0;//���� ����
	int det = 0;//���� ����

	for (i = 0; i < 3; i++)//�Է¹޴� �ݺ���
	{
		for (j = 0; j < 3; j++)
		{
			printf("arr1�迭 �Է� �ޱ�: ");
			scanf("%d", &arr1[i][j]);
		}
	}

	for (i = 0; i < 3; i++)//�Է¹޴� �ݺ���
	{
		for (j = 0; j < 3; j++)
		{
			printf("arr2�迭 �Է� �ޱ�: ");
			scanf("%d", &arr2[i][j]);
		}
	}
	printf("\n");
	/*�� ����� ����*/
	printf("����\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", arr1[i][j] + arr2[i][j]);
		}
		printf("\n");//����
	}
	printf("\n");//����
	/*�� ����� ����*/
	printf("����\n");
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			printf("%d ", arr1[i][j] - arr2[i][j]);
		}
		printf("\n");//����
	}
	printf("\n");//����
	/*�� ����� ����*/
	printf("����\n");
	for (i = 0; i < 3; i++)
	{

		for (int k = 0; k < 3; k++)
		{
			mul = 0;
			for (j = 0; j < 3; j++)
				mul += arr1[i][j] * arr2[j][k];
			printf("%d ", mul);
		}
		printf("\n");//����
	}
	/*��Ľ� ���ϱ�*/
	for (i = 0; i < 3; i++) //3�� �ݺ� for��
		det += ((arr1[0][i] * arr1[1][(i + 1) % 3] * arr1[2][(i + 2) % 3]) - (arr1[0][i] * arr1[1][(i + 2) % 3] * arr1[2][(i + 1) % 3])); // ��Ľ� ���


	if (det == 0)// det=0 �� ���( ������� ���缺 ���� )
		printf("\n ����� �������� ���� \n"); // ���ڿ� ���
	else
	{ // det=0�� �ƴ� ���
		printf("\n ����� \n"); // ���ڿ� ���
		for (j = 0; j < 3; j++) // ���� �ݺ� for��
		{
			for (i = 0; i < 3; i++)
			{ // ���� �ݺ� for��
				printf("%g\t", ((arr1[(i + 1) % 3][(j + 1) % 3] * arr1[(i + 2) % 3][(j + 2) % 3]) - (arr1[(i + 2) % 3][(j + 1) % 3] * arr1[(i + 1) % 3][(j + 2) % 3]))/det); // ����� ���
			}
			printf(")\n"); // ���ڿ� ���
		}
		
	} // ����� ���

	return 0;//����
	


}