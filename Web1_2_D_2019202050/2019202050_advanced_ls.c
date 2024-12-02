////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name	:2019202050_advanced_ls.c									  //
// Date		:2023/04/01											  //
// Os		:Ubuntu 16.04 LTS 64bits									  //
// Author 	:Lee Kang Hyun											  //
// Student ID	:2019202050											  //
//----------------------------------------------------------------------------------------------------------------//
// Title	:System Programming Assignment #1-2								  //
// Description	:This code directly implements the -a -l option of the ls command. Depending on the option and the//
// path of the file, information about the file the user wants is output to the shell.   			  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h> //malloc()
#include <dirent.h>
#include <string.h> //for strcmp()
#include <pwd.h> //for struct passwd
#include <grp.h> //for struct group
#include <sys/stat.h> //for struct stat
#include <time.h> //for struct tm
#include <unistd.h> //for getcwd and getopt
#include <sys/types.h>

/////////////////////////////////////////////////////
// selectionsort				   //
// ================================================//
// input: count -> how many files?		   //
//	  list -> file list			   //
//						   //
// output: void					   //
//						   //
//						   //
//						   //
// purpose: selection sorting			   //
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
// lsfunc				             //
// ==================================================//
// input: option -> 0: non-option 1: -a 2: -l 3: -al //
//	  path -> file or directory path	     //
//						     //
// output: void					     //
//						     //
//						     //
//						     //
// purpose: ls command algorithm		     //
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// filetype				                 //
// ======================================================//
// input: mode -> numbers of st_mode			 //
//	  str -> string of st_mode      		 //
//						         //
// output: void  				         //
//						         //
//						         //
//						         //
// purpose: Convert file type 				 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileaccess				                 //
// ======================================================//
// input: mode -> numbers of st_mode		         //
//	  str -> string of st_mode       		 //
//						         //
// output: void  				         //
//						         //
//						         //
//						         //
// purpose: Convert access rights from numbers to letters//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileinfo				                 //
// ======================================================//
// input:        		 //
//	  list -> file list			         //
//						         //
// output: void  				         //
//						         //
//						         //
//						         //
// purpose: printing file information			 //
///////////////////////////////////////////////////////////
void selectionsort(int count, char list[][256]); 

void lsfunc(int option, char* path); 

void filetype(int mode, char str[]); 

void fileaccess(int mode, char str[]);

void fileinfo(char* path, char list[]);

void selectionsort(int count, char list[][256])
{
	char hide1[256]; // To compare without excluding hidden files
	char hide2[256];
	for(int i = 0; i<(count-1); i++)
	{
		for(int j = i+1;j<count;j++)
		{
			if(list[i][0] == '.')//If you encounter a hidden file
			{
				for(int k = 0; k<strlen(list[i]);k++)
				{
					hide1[k] = list[i][k+1];
				}
			}
			else
			{
				strcpy(hide1,list[i]);
			}
			if(list[j][0] == '.')
			{
				for(int k = 0; k<strlen(list[j]);k++)
				{
					hide2[k] = list[j][k+1];
				}
			}
			else
			{
				strcpy(hide2,list[j]);
			}
			if(strcasecmp(hide1,hide2)>0)// Compare case insensitively
			{	
				char temp[256];
				strcpy(temp,list[i]);
				strcpy(list[i],list[j]);
				strcpy(list[j],temp);
			}
		}
	}
}

void filetype(int mode, char str[])
{
	if(S_ISDIR(mode)) str[0] = 'd';
}

void fileaccess(int mode, char str[])
{
	if(mode&S_IRUSR) str[1] = 'r';
	if(mode&S_IWUSR) str[2] = 'w';
	if(mode&S_IXUSR) str[3] = 'x';

	if(mode&S_IRGRP) str[4] = 'r';
	if(mode&S_IWGRP) str[5] = 'w';
	if(mode&S_IXGRP) str[6] = 'x';

	if(mode&S_IROTH) str[7] = 'r';
	if(mode&S_IWOTH) str[8] = 'w';
	if(mode&S_IXOTH) str[9] = 'x';
}
void fileinfo(char* path, char list[])
{
	char temp[4096];
	struct passwd* pas;
	struct group* gru;
	struct stat st;
	struct tm* ti;
	char str[11] = "----------";

	strcpy(temp,path);
	strcat(temp,"/");
	strcat(temp,list);
	if(stat(temp,&st) == -1)
	{
		perror("stat");
		printf("%s\n",list);
		printf("%s\n",temp);
			
	}
			
	filetype(st.st_mode, str);
	fileaccess(st.st_mode,str);
	pas = getpwuid(st.st_uid);
	gru = getgrgid(st.st_gid);
	ti = localtime(&st.st_mtime);
	char monthword[10];
	int monthnum = ti->tm_mon+1;
	int day = ti->tm_mday;
	int hour = ti->tm_hour;
	int minute = ti->tm_min;
	switch(monthnum)
	{
		case 1: strcpy(monthword,"Jan"); break;
		case 2: strcpy(monthword,"Feb"); break;
		case 3: strcpy(monthword,"Mar"); break;
		case 4: strcpy(monthword,"Apr"); break;
		case 5: strcpy(monthword,"May"); break;
		case 6: strcpy(monthword,"Jun"); break;
		case 7: strcpy(monthword,"Jul"); break;
		case 8: strcpy(monthword,"Arg"); break;
		case 9: strcpy(monthword,"Sep"); break;
		case 10: strcpy(monthword,"Oct"); break;
		case 11: strcpy(monthword,"Nov"); break;
		case 12: strcpy(monthword,"Dec"); break;
	}
	printf("%s\t %d\t %s\t %s\t %lld\t %s %d %d:%d %s\n",str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute, list);
}

void lsfunc(int option, char* path)//0:non-option 1: -a 2: -l 3: -al
{
	DIR* dirp; //directory pointer
	struct dirent *dir; //directory entry
	char list[2000][256]; //file list
	int count = 0; //file count
	char dirpath[4096];
	
	dirp = opendir(path);	
	realpath(path,dirpath);

	if(dirp == NULL)//path is not directory
	{
		struct passwd* pas;
		struct group* gru;
		struct stat st;
		struct tm* ti;

		if(option == 0 || option == 1)// not -l option
		{
			printf("%s\n",path);
		}

		else
		{
			stat(dirpath,&st);
			char str[11] = "----------";
			
			filetype(st.st_mode, str);//convert file type number
			fileaccess(st.st_mode,str);//convert file access number
			pas = getpwuid(st.st_uid); //get struct passwd
			gru = getgrgid(st.st_gid); //get struct group
			ti = localtime(&st.st_mtime); //convert time to struct tm
			char monthword[10];
			int monthnum = ti->tm_mon+1; // tm_mon's range 0~11
			int day = ti->tm_mday;
			int hour = ti->tm_hour;
			int minute = ti->tm_min;
			switch(monthnum) //convert month number
			{
				case 1: strcpy(monthword,"Jan"); break;
				case 2: strcpy(monthword,"Feb"); break;
				case 3: strcpy(monthword,"Mar"); break;
				case 4: strcpy(monthword,"Apr"); break;
				case 5: strcpy(monthword,"May"); break;
				case 6: strcpy(monthword,"Jun"); break;
				case 7: strcpy(monthword,"Jul"); break;
				case 8: strcpy(monthword,"Arg"); break;
				case 9: strcpy(monthword,"Sep"); break;
				case 10: strcpy(monthword,"Oct"); break;
				case 11: strcpy(monthword,"Nov"); break;
				case 12: strcpy(monthword,"Dec"); break;
			}
			printf("Directory path: %s\n",dirpath);
			printf("total: %d\n",(int)st.st_blocks/2); //number of 1k blocks allocated			
			
			printf("%s\t %d\t %s\t %s\t %lld\t %s %d %d:%d %s\n",str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute, path); //print file information	
		}
		closedir(dirp);
		return;
	}

	if(option == 0)//non-option
	{
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
	
		selectionsort(count, list);

		for(int i = 0; i<count; i++)//print
		{
			printf("%s\n",list[i]);
		}
	}

	else if(option == 1)// a option
	{
		while((dir = readdir(dirp))!= NULL)//until you read it all
		{
			strcpy(list[count],dir->d_name); //copy file list
			count++;
		}
	
		selectionsort(count, list);
	
		for(int i = 0; i<count; i++)//print
		{
			printf("%s\n",list[i]);
		}
	}

	else if(option == 2)// l option
	{
		struct stat st;
		int blocksize = 0;

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
	
		selectionsort(count, list);
		printf("Directory path: %s\n",dirpath);
		

		for(int i =0; i<count; i++)
		{
			char filepath[4096];
			strcpy(filepath,path);
			strcat(filepath,"/");
			strcat(filepath,list[i]);
			stat(filepath,&st);
			blocksize += st.st_blocks;
		}
		printf("total: %d\n",blocksize/2);
		for(int i = 0 ;i<count; i++)
		{
			fileinfo(path, list[i]);
		}
		
	}

	else if(option == 3)// al option
	{
		struct stat st;		
		int blocksize = 0;
		
		while((dir = readdir(dirp))!= NULL)//until you read it all
		{
			strcpy(list[count],dir->d_name); //copy file list
			count++;
		}
	
		selectionsort(count, list);

		printf("Directory path: %s\n",dirpath);
		

		for(int i =0; i<count; i++)
		{
			char filepath[4096];
			strcpy(filepath,path);
			strcat(filepath,"/");
			strcat(filepath,list[i]);
			stat(filepath,&st);
			blocksize += st.st_blocks;
		}
		printf("total: %d\n",blocksize/2);
		for(int i = 0 ;i<count; i++)
		{
			fileinfo(path, list[i]);
		}

		
	}
	
	closedir(dirp);
	
}


int main(int argc, char **argv) //argc: parameter number, argv[]: parameter
{
	int aflag = 0, lflag = 0;
	int c = 0;
	char** temp = NULL;
	temp = (char**)malloc(sizeof(char*)*argc); // no limit input file or directory count
	for(int i = 0; i<argc; i++)
	{
		temp[i] = (char*)malloc(sizeof(char)*256);
	}
	int num = 0;

	while((c = getopt(argc,argv,"al")) != -1) //parsing command
	{
      
      		switch(c)
      		{
         		case 'a': //option a
            			aflag++;
            			break;

         		case 'l': //option l
                                lflag++;
                                break;

         		case '?': //exception
                                printf("unknown option character\n");
                                break;

      		}
   	}
	
	
	if(argc == optind)// command has not nonoption
	{
		if(aflag && lflag) lsfunc(3,".");
		else if(lflag) lsfunc(2,".");
		else if(aflag) lsfunc(1,".");
		else lsfunc(0,".");
		return 0;
	}
	else // command has nonoptions
	{
		struct stat tempstat;
		for(int i = optind;i<argc;i++)
		{
			if(stat(argv[i],&tempstat) == -1)
			{
				printf("advance_ls: cannot access '%s' : No such directory or file\n",argv[i]);
				continue;
			}
			strcpy(temp[num++],argv[i]); //temp has only existed file list
		}
	}
	
	for(int i = 0;i<num;i++)
	{
		if(aflag && lflag) lsfunc(3,temp[i]);
		else if(lflag) lsfunc(2,temp[i]);
		else if(aflag) lsfunc(1,temp[i]);
		else lsfunc(0,temp[i]);
	}
	for(int i =0; i<argc ;i++)
	{
		free(temp[i]);
	}
	free(temp);
	return 0;
}
