////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name	:201920202050_simple_ls.c									  //
// Date		:2023/03/25											  //
// Os		:Ubuntu 16.04 LTS 64bits									  //
// Author 	:Lee Kang Hyun											  //
// Student ID	:2019202050											  //
//----------------------------------------------------------------------------------------------------------------//
// Title	:System Programming Assignment #1-1								  //
// Description	:This file contains code that outputs the list excluding hidden files that exist in the directory.//
// The destination directory path is entered by the user. (If not entered, the current directory is defaulted.)   //
// The output method follows ascending order without distinguishing between uppercase and lowercase letters.      //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <dirent.h>
#include <string.h> //for strcmp()

int main(int argc, char *argv[]) //argc: parameter number, argv[]: parameter
{
	DIR* dirp; //directory pointer
	struct dirent *dir; //directory entry
	char list[100][256]; //file list
	int count = 0; //file count

	if(argc > 2)//parameter is only one!
	{
		printf("simple_ls: only one directory path can be processed\n");
		return -1;
	}
	
	else if(argc == 1)//If no path is entered
	{
		dirp = opendir("."); // current directory is path
	}
	
	else
	{
		dirp = opendir(argv[1]); //parameter is path
	}	
	
	if(dirp == NULL)//exception
	{
		printf("simple_ls: cannot access '%s' : No such directory\n",argv[1]);
		return -1;
	}

	while((dir = readdir(dirp))!= NULL)//until you read it all
	{
		strcpy(list[count],dir->d_name); //copy file list
		if(list[count][0] == '.') //Hidden files are not output targets
		{
			continue;
		}
		else
		{
			count++;
		}
	}

	//selection sort part
	for(int i = 0; i<(count-1); i++)
	{
		for(int j = i+1;j<count;j++)
		{
			if(strcasecmp(list[i],list[j])>0)
			{	
				char temp[256];
				strcpy(temp,list[i]);
				strcpy(list[i],list[j]);
				strcpy(list[j],temp);
			}
		}
	}
	
	for(int i = 0; i<count; i++)//print
	{
		printf("%s\n",list[i]);
	}
	return 0;
}
