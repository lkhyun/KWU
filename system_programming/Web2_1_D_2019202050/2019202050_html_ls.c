////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name   :2019202050_html_ls.c                                                                              //
// Date      :2023/04/16                                                                                          //
// Os      :Ubuntu 16.04 LTS 64bits                                                                               //
// Author    :Lee Kang Hyun                                                                                       //
// Student ID   :2019202050                                             					  //
//----------------------------------------------------------------------------------------------------------------//
// Title   :System Programming Assignment #2-1                         					  	  //
// Description   : This code generates the html_ls.html file from the implemented final_ls and outputs 		  //
// the output result in the html format before final_ls is executed. It enables access by processing hyperlinks	  //
// to video files.             			  								  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>   //malloc()
#include <dirent.h>   //struct
#include <string.h>   //for strcmp()
#include <pwd.h>      //for struct passwd
#include <grp.h>      //for struct group
#include <sys/stat.h> //for struct stat
#include <time.h>     //for struct tm
#include <unistd.h>   //for getcwd and getopt
#include <sys/types.h>
#include <fnmatch.h> //fnmatch()
#include <ctype.h>   //toupper()

FILE *file; //file stream
/////////////////////////////////////////////////////
// selectionsort               			   //
// ================================================//
// input: count -> how many files?         	   //
//        list -> file list  			   //
//	  path -> file path			   //
//	  flag -> -S -r option flag          	   //
//                     				   //
// output: void                  		   //
//                     				   //
//                     				   //
//                     				   //
// purpose: selection sorting            	   //
/////////////////////////////////////////////////////
///////////////////////////////////////////////////////
// lsfunc                         		     //
// ==================================================//
// input: flag -> -a,-l,-h,-S,-r option flag	     //
//    	  path -> file or directory path             //
//                       			     //
// output: void              		             //
//                       			     //
//                       			     //
//                       			     //
// purpose: ls command algorithm           	     //
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// filetype                             		 //
// ======================================================//
// input: mode -> numbers of st_mode          	 	 //
//     	  str -> string of st_mode           	  	 //
//                           				 //
// output: void                       			 //
//                           				 //
//                           				 //
//                           				 //
// purpose: Convert file type              		 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileaccess                             		 //
// ======================================================//
// input: mode -> numbers of st_mode               	 //
//     str -> string of st_mode             		 //
//                          				 //
// output: void                      			 //
//                          				 //
//                          				 //
//                          				 //
// purpose: Convert access rights from numbers to letters//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileinfo                             		 //
// ======================================================//
// input:               				 //
//     list -> file list				 //
//     flag -> -h option flag				 //
//     path -> file path                 		 //
//                          				 //
// output: void                      			 //
//                          				 //
//                          				 //
//                          				 //
// purpose: printing file information         		 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// wildcardexistence                             	 //
// ======================================================//
// input: str ->  string to check	         	 //
// 				            		 //
//                          				 //
// output: int -> exist is 1 , not 0                     //
//                          				 //
//                          				 //
//                          				 //
// purpose: Check if a string contains wildcards	 //
///////////////////////////////////////////////////////////
void selectionsort(int Sflag, int rflag, char *path, int count, char list[][1024]);

void lsfunc(int aflag, int lflag, int hflag, int Sflag, int rflag, char *path);

void filetype(int mode, char *str);

void fileaccess(int mode, char *str);

void fileinfo(int hflag, char *path, char list[]);

int wildcardexistence(char *str);

void selectionsort(int Sflag, int rflag, char *path, int count, char list[][1024])
{
   struct stat st;
   int filesize[1024]; // save file size for S option
   char temp[1024];    // to make filepath
   char hide1[1024];   // To compare without excluding hidden files and lowercase to uppercase
   char hide2[1024];   // To compare without excluding hidden files and lowercase to uppercase

   if (path != NULL)
   {
      for (int i = 0; i < count; i++)
      {
         strcpy(temp, path);       // path copy
         strcat(temp, "/");        // string concatenation
         strcat(temp, list[i]);    // create path
         stat(temp, &st);          // load file information
         filesize[i] = st.st_size; // save file size
      }
   }
   for (int i = 0; i < (count - 1); i++) // front string
   {
      for (int j = i + 1; j < count; j++) // rear string
      {
         if (list[i][0] == '.') // If you encounter a hidden file
         {
            for (int k = 0; k < strlen(list[i]); k++)
            {
               hide1[k] = list[i][k + 1]; // ignore hidden file
            }
         }
         else
         {
            strcpy(hide1, list[i]); // copy
         }
         if (list[j][0] == '.') // If you encounter a hidden file
         {
            for (int k = 0; k < strlen(list[j]); k++)
            {
               hide2[k] = list[j][k + 1]; // ignore hidden file
            }
         }
         else
         {
            strcpy(hide2, list[j]); // copy
         }

         for (int i = 0; i < strlen(hide1); i++)
         {
            hide1[i] = toupper(hide1[i]); // uppercase standard
         }
         for (int i = 0; i < strlen(hide2); i++)
         {
            hide2[i] = toupper(hide2[i]); // uppercase standard
         }

         if (!Sflag) // not s option
         {
            if (!rflag) // not r option
            {
               if (strcmp(hide1, hide2) > 0) // ascending order by string
               {
                  char temp[1024];          // for swap variable
                  strcpy(temp, list[i]);    // swap
                  strcpy(list[i], list[j]); // swap
                  strcpy(list[j], temp);    // swap
               }
            }
            else
            {
               if (strcmp(hide1, hide2) < 0) // descending order by string
               {
                  char temp[1024];          // for swap variable
                  strcpy(temp, list[i]);    // swap
                  strcpy(list[i], list[j]); // swap
                  strcpy(list[j], temp);    // swap
               }
            }
         }
         else
         {
            if (!rflag) // not r option
            {
               if (filesize[i] < filesize[j]) // descending order by size
               {
                  char listtemp[1024];       // for swap variable
                  strcpy(listtemp, list[i]); // swap
                  strcpy(list[i], list[j]);  // swap
                  strcpy(list[j], listtemp); // swap
                  int sizetemp;              // for swap variable
                  sizetemp = filesize[i];    // swap
                  filesize[i] = filesize[j]; // swap
                  filesize[j] = sizetemp;    // swap
               }
               else if (filesize[i] == filesize[j] && strcmp(hide1, hide2) > 0) // if the size is the same ascending order by string
               {
                  char temp[1024];          // for swap variable
                  strcpy(temp, list[i]);    // swap
                  strcpy(list[i], list[j]); // swap
                  strcpy(list[j], temp);    // swap
               }
            }
            else
            {
               if (filesize[i] > filesize[j]) // ascending order by size
               {
                  char listtemp[1024];       // for swap variable
                  strcpy(listtemp, list[i]); // swap
                  strcpy(list[i], list[j]);  // swap
                  strcpy(list[j], listtemp); // swap
                  int sizetemp;              // for swap variable
                  sizetemp = filesize[i];    // swap
                  filesize[i] = filesize[j]; // swap
                  filesize[j] = sizetemp;    // swap
               }
               else if (filesize[i] == filesize[j] && strcmp(hide1, hide2) < 0) // if the size is the same descending order by string
               {
                  char temp[1024];          // for swap variable
                  strcpy(temp, list[i]);    // swap
                  strcpy(list[i], list[j]); // swap
                  strcpy(list[j], temp);    // swap
               }
            }
         }
      }
   }
}

void filetype(int mode, char *str)
{
   if (S_ISDIR(mode)) // if directory
   {
      str[0] = 'd';   // string conversion
   }     
   else if (S_ISLNK(mode)) // if symbolic link
   {
      str[0] = 'l';   // string conversion
   } 
}

void fileaccess(int mode, char *str)
{
   if (mode & S_IRUSR) // user read access
      str[1] = 'r';    // string conversion
   if (mode & S_IWUSR) // user write access
      str[2] = 'w';    // string conversion
   if (mode & S_IXUSR) // user execute access
      str[3] = 'x';    // string conversion

   if (mode & S_IRGRP) // group read access
      str[4] = 'r';    // string conversion
   if (mode & S_IWGRP) // group write access
      str[5] = 'w';    // string conversion
   if (mode & S_IXGRP) // group execute access
      str[6] = 'x';    // string conversion

   if (mode & S_IROTH) // other read access
      str[7] = 'r';    // string conversion
   if (mode & S_IWOTH) // other write access
      str[8] = 'w';    // string conversion
   if (mode & S_IXOTH) // other execute access
      str[9] = 'x';    // string conversion
}
void fileinfo(int hflag, char *path, char list[])
{
   char temp[1024];    // for creating path
   struct passwd *pas; // struct passwd
   struct group *gru;  // struct group
   struct stat st;     // struct stat
   struct tm *ti;      // struct tm
   char str[11] = "----------";
   double changesizeformat = 0.0; // size format

   if (list == path)
   {
      strcpy(temp, path); // copy path
   }
   else
   {
      strcpy(temp, path); // copy path
      strcat(temp, "/");  // string concentration
      strcat(temp, list); // string concentration
   }

   if (lstat(temp, &st) == -1) // failed to read file information
   {
      perror("stat");                 // print error
      printf("filename: %s\n", list); // list print
      printf("filepath: %s\n", temp); // path print
   }

   filetype((int)st.st_mode, str);   // string conversion function
   fileaccess((int)st.st_mode, str); // string conversion function
   if (str[0] == '-')
   {
      fprintf(file, "<tr style = \"color: red\">");
   }
   else if (str[0] == 'd')
   {
      fprintf(file, "<tr style = \"color: blue\">");
   }
   else if (str[0] == 'l')
   {
      fprintf(file, "<tr style = \"color: green\">");
   }
   pas = getpwuid(st.st_uid);    // get struct passwd
   gru = getgrgid(st.st_gid);    // get struct group
   ti = localtime(&st.st_mtime); // get time
   char monthword[10];
   int monthnum = ti->tm_mon + 1; // insert month data
   int day = ti->tm_mday;         // insert day data
   int hour = ti->tm_hour;        // insert hour data
   int minute = ti->tm_min;       // insert minute data
   switch (monthnum)              // string conversion according to the switch variable
   {
   case 1:
      strcpy(monthword, "Jan"); // if monthnum is 1, monthword is Jan
      break;
   case 2:
      strcpy(monthword, "Feb"); // if monthnum is 2, monthword is Feb
      break;
   case 3:
      strcpy(monthword, "Mar"); // if monthnum is 3, monthword is Mar
      break;
   case 4:
      strcpy(monthword, "Apr"); // if monthnum is 4, monthword is Apr
      break;
   case 5:
      strcpy(monthword, "May"); // if monthnum is 5, monthword is May
      break;
   case 6:
      strcpy(monthword, "Jun"); // if monthnum is 6, monthword is Jun
      break;
   case 7:
      strcpy(monthword, "Jul"); // if monthnum is 7, monthword is Jul
      break;
   case 8:
      strcpy(monthword, "Arg"); // if monthnum is 8, monthword is Arg
      break;
   case 9:
      strcpy(monthword, "Sep"); // if monthnum is 9, monthword is Sep
      break;
   case 10:
      strcpy(monthword, "Oct"); // if monthnum is 10, monthword is Oct
      break;
   case 11:
      strcpy(monthword, "Nov"); // if monthnum is 11, monthword is Nov
      break;
   case 12:
      strcpy(monthword, "Dec"); // if monthnum is 12, monthword is Dec
      break;
   }
   if (hflag) // h option on
   {
      int dividecount = 0;                               // how many times is it divided?
      changesizeformat = (double)st.st_size;             // use decimal point
      while (changesizeformat > 1024 && dividecount < 4) // express only up to G
      {
         changesizeformat /= 1024; // divide
         dividecount++;            // divided count up
      }

      switch (dividecount) // Different output statements depending on the number of divisions
      {
      case 0:
         printf("%s\t %d\t %s\t %s\t %.0f\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute, list);                                                                                                               // just print
         fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.0f</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute); // html print
         break;

      case 1:
         printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'K', monthword, day, hour, minute, list);                                                                                                               // K
         fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'K', monthword, day, hour, minute); // html K print
         break;

      case 2:
         printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'M', monthword, day, hour, minute, list);                                                                                                               // M
         fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'M', monthword, day, hour, minute); // html M print
         break;

      case 3:
         printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'G', monthword, day, hour, minute, list);                                                                                                               // G
         fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'G', monthword, day, hour, minute); // html G print
         break;

      default:
         printf("%s\t %d\t %s\t %s\t %.0f\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute, list);                                                                                                               // default
         fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.0f</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute); // html default print
         break;
      }
      return;
   }
   printf("%s\t %d\t %s\t %s\t %lld\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute, list);                                                                                                               // no option
   fprintf(file, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%lld</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute); // html no h option print
}

int wildcardexistence(char *str) // wild cards?
{
   char wildcard[5] = "*?[]";
   for (int i = 0; i < strlen(str); i++)
   {
      if (strchr(wildcard, str[i]) != NULL)
      {
         return 1; // yes
      }
   }
   return 0; // no
}
void lsfunc(int aflag, int lflag, int hflag, int Sflag, int rflag, char *path) // ls algorithm
{
   DIR *dirp;             // directory pointer
   struct dirent *dir;    // directory entry
   char list[1000][1024]; // file list
   int count = 0;         // file count
   char dirpath[1024];    // directory path

   dirp = opendir(path);    // open directory with path
   realpath(path, dirpath); // create absolute path

   /* file part */
   if (dirp == NULL) // path is not directory
   {
      fprintf(file, "<table border = \"1\">\n"); // table format
      if (strcmp(path, "html_ls.html") == 0)
      {
         closedir(dirp);
         fprintf(file, "</table>\n");
         return;
      }
      if (!lflag) // not -l option
      {
         printf("%s\n", path); // just print name
         if (strcmp(path, "html_ls.html") == 0)
         {
            closedir(dirp);
            fprintf(file, "</table>\n");
            return;
         }
         fprintf(file, "<tr><th>FILE NAME</th><tr>\n"); // table head
         fprintf(file, "<tr><td>%s</td></tr>\n", path); // table row
      }

      else
      {
         struct stat st;
         stat(path, &st);                                                                                                                          // load information
         fprintf(file, "<table border = \"1\">\n");                                                                                                // table format
         fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // table header
         fileinfo(hflag, path, path);                                                                                                              // print file information
      }
      closedir(dirp); // close directory
      fprintf(file, "</table>\n");
      return;
   }
   /* directory part */
   if (!aflag) // not -a option
   {
      while ((dir = readdir(dirp)) != NULL) // until you read it all
      {
         strcpy(list[count], dir->d_name);             // copy file list
         if (strcmp(dir->d_name, "html_ls.html") == 0) // do not print html_ls.html
         {
            continue;
         }
         if (list[count][0] == '.') // Hidden files are not output targets
         {
            continue;
         }
         else // no hidden file
         {
            count++;
         }
      }
   }
   else // all file read
   {
      while ((dir = readdir(dirp)) != NULL) // until you read it all
      {
         if (strcmp(dir->d_name, "html_ls.html") == 0) // do not print html_ls.html
         {
            continue;
         }
         strcpy(list[count], dir->d_name); // copy file list
         count++;
      }
   }

   if (!lflag)
   {
      selectionsort(Sflag, rflag, path, count, list); // sorting

      printf("Directory path: %s\n", dirpath);                   // print absolute path
      fprintf(file, "<b>Directory path: %s</b><br>\n", dirpath); // html directory path
      fprintf(file, "<table border = \"1\">\n");                 // table format
      fprintf(file, "<tr><th>FILE NAME</th><tr>\n");             // table head
      for (int i = 0; i < count; i++)                            // loop by count
      {
         printf("%s\n", list[i]);                          // print
         fprintf(file, "<tr><td>%s</td></tr>\n", list[i]); // table row
      }
      printf("\n"); // newline
   }
   else // l option
   {
      struct stat st;
      int blocksize = 0; // to calculate all file block size

      selectionsort(Sflag, rflag, path, count, list);            // sorting
      printf("Directory path: %s\n", dirpath);                   // print absolute path
      fprintf(file, "<b>Directory path: %s</b><br>\n", dirpath); // html directory path
      for (int i = 0; i < count; i++)                            // loop by count
      {
         char filepath[1024];
         strcpy(filepath, path);    // copy path
         strcat(filepath, "/");     // string concentration
         strcat(filepath, list[i]); // string concentration
         stat(filepath, &st);       // load filepath information
         blocksize += st.st_blocks; // sum of sizes
      }
      printf("total: %d\n", blocksize / 2);                                                                                                     // total size print
      fprintf(file, "<b>Total: %d</b><br>\n", blocksize / 2);                                                                                   // html total block size
      fprintf(file, "<table border = \"1\">\n");                                                                                                // table format
      fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // table header
      for (int i = 0; i < count; i++)
      {
         fileinfo(hflag, path, list[i]); // print file information
      }
   }
   closedir(dirp); // close directory
   fprintf(file, "</table>\n");
}

int main(int argc, char **argv) // argc: parameter number, argv[]: parameter
{
   DIR *dirp; // directory pointer
   struct dirent *dir;
   file = fopen("html_ls.html", "w");                         // file stream
   int aflag = 0, lflag = 0, hflag = 0, Sflag = 0, rflag = 0; // option flags
   int c = 0;                                                 // for switch
   char filelist[1000][1024];                                 // file list in argv
   char dirlist[1000][1024];                                  // directory list in argv
   int filelistcount = 0;                                     // file list count
   int dirlistcount = 0;                                      // directory list count
   char htmlcurdirpath[1024];
   if (file == 0) // file is not open
   {
      printf("htmlfile open error\n");
   }

   while ((c = getopt(argc, argv, "alhSr")) != -1) // parsing command
   {
      switch (c)
      {
      case 'a':   // option a
         aflag++; // aflag set
         break;

      case 'l':   // option l
         lflag++; // lflag set
         break;

      case 'h':   // option l
         hflag++; // hflag set
         break;

      case 'S':   // option l
         Sflag++; // Sflag set
         break;

      case 'r':   // option l
         rflag++; // rflag set
         break;

      case '?': // exception
         printf("unknown option character\n");
         break;
      }
   }
   fprintf(file, "<html>\n"); // html file's start

   fprintf(file, "<head>\n"); // html head start,current directory and command part

   fprintf(file, "<title>\n");            // html title start,print current directory part
   getcwd(htmlcurdirpath, 1024);          // get current directory
   fprintf(file, "%s\n", htmlcurdirpath); // print current directory
   fprintf(file, "</title>\n");           // html title end
   fprintf(file, "<h1>");                 // html h1 tag start
   for (int i = 0; i < argc; i++)
   {
      fprintf(file, "%s ", argv[i]); // command argument print
   }
   fprintf(file, "</h1><br>\n"); // html h1 tag end and newline

   fprintf(file, "</head>\n"); // html head end

   fprintf(file, "<body>\n"); // html body start,print file or directory information

   if (argc == optind) // command has not nonoption
   {
      lsfunc(aflag, lflag, hflag, Sflag, rflag, "."); // execute lsfunc with current directory path
   }

   else // command has nonoptions
   {
      struct stat tempstat;
      for (int i = optind; i < argc; i++) // loop by numbers of nonoption argument
      {
         if (wildcardexistence(argv[i])) // wildcards?
         {
            char wildpath[1024];                      // path of file with wildcards
            char *finddir = NULL;                     // pointer to the last slash
            char wildfile[1024];                      // file with wildcards
            memset(wildpath, '\0', sizeof(wildpath)); // array setting
            memset(wildfile, '\0', sizeof(wildfile)); // array setting
            finddir = strrchr(argv[i], '/');          // find slash
            if (finddir != NULL)                      // find!
            {
               strcpy(wildfile, finddir + 1);                       // extract file
               strncpy(wildpath, argv[i], (finddir - argv[i]) + 1); // extract path
               wildpath[finddir - argv[i] + 1] = '\0';              // Insert string end point
            }
            else // not find!
            {
               strcpy(wildpath, "./");    // path is current directory
               strcpy(wildfile, argv[i]); // file is argv
            }

            if (finddir != NULL) // When there is a path in the argument
            {
               dirp = opendir(wildpath);             // open directory by path
               while ((dir = readdir(dirp)) != NULL) // until you read it all
               {
                  char *name = dir->d_name; // file name save
                  if (name[0] == '.')       // ignore hidden files
                  {
                     continue;
                  }
                  if (strcmp(dir->d_name, "html_ls.html") == 0) // html_ls is not print
                  {
                     continue;
                  }
                  if (fnmatch(wildfile, name, 0) == 0) // wild card matching
                  {
                     char temp[1024];
                     strcpy(temp, wildpath);         // path copy
                     strcat(temp, name);             // filename concentration
                     if (stat(temp, &tempstat) == 0) // success load
                     {
                        if (S_ISDIR(tempstat.st_mode)) // directory
                        {
                           strcpy(dirlist[dirlistcount++], temp); // save in directory list
                        }
                        else // file
                        {
                           strcpy(filelist[filelistcount++], temp); // save in file list
                        }
                     }
                  }
               }
               closedir(dirp); // close directory
            }
            else // When there is not a path in the argument
            {
               dirp = opendir(wildpath);             // open directory by path
               while ((dir = readdir(dirp)) != NULL) // until you read it all
               {
                  char *name = dir->d_name; // file name save
                  if (name[0] == '.')       // ignore hidden files
                  {
                     continue;
                  }
                  if (strcmp(dir->d_name, "html_ls.html") == 0) // html_ls is not print
                  {
                     continue;
                  }
                  if (fnmatch(wildfile, name, 0) == 0) // wild card matching
                  {
                     char temp[1024];
                     strcpy(temp, wildpath);         // path copy
                     strcat(temp, name);             // filename concentration
                     if (stat(temp, &tempstat) == 0) // success load
                     {
                        if (S_ISDIR(tempstat.st_mode)) // directory
                        {
                           strcpy(dirlist[dirlistcount++], temp); // save in directory list
                        }
                        else // file
                        {
                           strcpy(filelist[filelistcount++], temp); // save in file list
                        }
                     }
                  }
               }
               closedir(dirp); // close directory
            }
         }
         else // no wild card in argument
         {
            if (stat(argv[i], &tempstat) == -1) // no exist file
            {
               printf("advance_ls: cannot access '%s' : No such directory or file\n", argv[i]);
               continue;
            }
            if (stat(argv[i], &tempstat) == 0) // success load
            {
               if (S_ISDIR(tempstat.st_mode)) // directory
               {
                  strcpy(dirlist[dirlistcount++], argv[i]); // save in directory list
               }
               else // file
               {
                  strcpy(filelist[filelistcount++], argv[i]); // save in file list
               }
            }
         }
      }

      selectionsort(0, 0, NULL, filelistcount, filelist); // sorting directory list
      selectionsort(0, 0, NULL, dirlistcount, dirlist);   // sorting file list

      for (int i = 0; i < filelistcount; i++) // loop by filelistcount
      {
         lsfunc(aflag, lflag, hflag, Sflag, rflag, filelist[i]); // print filelist
      }
      for (int i = 0; i < dirlistcount; i++) // loop by dirlistcount
      {
         lsfunc(aflag, lflag, hflag, Sflag, rflag, dirlist[i]); // print dirlist
      }
   }
   fprintf(file, "</body>\n"); // html body end
   fprintf(file, "</html>");   // html file's end
   fclose(file);               // file stream close
   return 0;                   // end
}
