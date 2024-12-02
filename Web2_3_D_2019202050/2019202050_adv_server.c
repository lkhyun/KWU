////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name   :2019202050_adv_server.c                                                                           //
// Date      :2023/05/08                                                                                          //
// Os      :Ubuntu 16.04 LTS 64bits                                                                               //
// Author    :Lee Kang Hyun                                                                                       //
// Student ID   :2019202050                                                                                       //
//----------------------------------------------------------------------------------------------------------------//
// Title   :System Programming Assignment #2-3                                                                    //
// Description   :  This code is a program that can process the response to the request by duplicating 		  //
//the process through the fork function when many requests come in at the same time. It responds only to 	  //
//IPs in the accessible IP list, otherwise it sends a connection error page. 		                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE // FNM_CASEFOLD
#define URL_LEN 256
#define BUFFSIZE 10240
#define PORTNO 40000 // port number 40000

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
#include <fnmatch.h>    //fnmatch()
#include <ctype.h>      //toupper()
#include <sys/socket.h> //communication tools
#include <netinet/in.h> //for byte order
#include <arpa/inet.h>  //convert dotted decimal to binary
#include <sys/wait.h>   //waitpid()
#include <signal.h>     //signal

/////////////////////////////////////////////////////
// selectionsort                           	   //
// ================================================//
// input: count -> how many files?                 //
//        list -> file list                        //
//     path -> file path            		   //
//     flag -> -S -r option flag                   //
//                                    		   //
// output: void                           	   //
//                                    		   //
//                                    		   //
//                                    		   //
// purpose: selection sorting                  	   //
/////////////////////////////////////////////////////
////////////////////////////////////////////////////////
// lsfunc                                    	      //
// ===================================================//
// input: flag -> -a,-l,-h,-S,-r option flag          //
//        path -> file or directory path 	      //
//	  client_fd-> file send to client             //
//        response_header,message -> server's response//
//	  hyperlink -> url relative path	      //
//						      //
// output: void                                       //
//                                     		      //
//                                     		      //
//                                     		      //
// purpose: ls command algorithm                      //
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// filetype                                    		 //
// ======================================================//
// input: mode -> numbers of st_mode                  	 //
//          str -> string of st_mode                     //
//                                         		 //
// output: void                                 	 //
//                                        		 //
//                                        		 //
//                                        		 //
// purpose: Convert file type                     	 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileaccess                                    	 //
// ======================================================//
// input: mode -> numbers of st_mode                   	 //
//     str -> string of st_mode                      	 //
//                                       		 //
// output: void                                		 //
//                                       		 //
//                                       		 //
//                                       		 //
// purpose: Convert access rights from numbers to letters//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// fileinfo                                    		 //
// ======================================================//
// input:                            			 //
//     list -> file list             			 //
//     flag -> -h option flag             		 //
//     path -> file path                        	 //
//     response_message -> server's response		 //
//     hyperlink -> url relative path			 //
//                                       		 //
// output: void                                	 	 //
//                                       		 //
//                                       	 	 //
//                                       		 //
// purpose: printing file information                	 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// wildcardexistence                                 	 //
// ======================================================//
// input: str ->  string to check                	 //
//                                			 //
//                                       		 //
// output: int -> exist is 1 , not 0                     //
//                                       		 //
//                                       		 //
//                                       		 //
// purpose: Check if a string contains wildcards    	 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// signalhandler					 //
// ======================================================//
// input: signal -> kind of signal			 //
// output: void						 //
// 							 //
// purpose: Get the exit status of the child, release the//
// system resources used by the child, and manage alarms //
///////////////////////////////////////////////////////////
struct sockaddr_in ADDR_history[10];//connected client's address
int PID_history[10];//The child process that communicated with the client
time_t TIME_history[10];//when communicating with the client
int requestnumber = 0;//The number of requests received from the client (Maximum count: 10 times)
int totalrequestnumber = 0;//total number of requests
void selectionsort(int Sflag, int rflag, char *path, int count, char list[][1024]);

void lsfunc(int aflag, int lflag, int hflag, int Sflag, int rflag, char *path, int client_fd, char *response_header, char *response_message, char *hyperlink);

void filetype(int mode, char *str);

void fileaccess(int mode, char *str);

void fileinfo(int hflag, char *path, char list[], char *response_message, char *hyperlink);

int wildcardexistence(char *str);

void signalhandler(int signal);

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
      str[0] = 'd'; // string conversion
   }
   else if (S_ISLNK(mode)) // if symbolic link
   {
      str[0] = 'l'; // string conversion
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
void fileinfo(int hflag, char *path, char list[], char *response_message, char *hyperlink)
{
   char temp[1024] = {
       0,
   }; // for creating file information load path
   char temp2[1024] = {
       0,
   };                  // for creating hyperlink
   struct passwd *pas; // struct passwd
   struct group *gru;  // struct group
   struct stat st;     // struct stat
   struct tm *ti;      // struct tm
   char str[11] = "----------";
   double changesizeformat = 0.0; // size format
   char messagebuf[BUFFSIZE] = {
       0,
   };

   strcpy(temp, path); // path copy
   strcat(temp, "/");  // string concentration
   strcat(temp, list); // string concentration

   if (strcmp(list, ".") == 0) // current folder
   {
      strcpy(temp2, hyperlink); // just copy
   }
   else if (strcmp(list, "..") == 0) // parent folder
   {
      strcpy(temp2, hyperlink);
      char temp3[1024];                   // hyperlink creating temp tool
      char *findpoint = NULL;             // slash finding
      memset(temp3, '\0', sizeof(temp3)); // array initializing
      findpoint = strrchr(temp2, '/');    // slash point return
      if (findpoint != NULL)              // slash find!
      {
         strncpy(temp3, temp2, (findpoint - temp2) + 1); // copy front to slash point
         temp3[findpoint - temp2 + 1] = '\0';            // insert \0
      }
      if (temp3[strlen(temp3) - 1] == '/') // if end of string is '/'
      {
         temp3[strlen(temp3) - 1] = '\0'; // change '/' to '\0'
      }
      if (strcmp(temp3, "") == 0) // hyperlink is empty?
      {
         strcpy(temp3, ".."); // go parent folder
      }
      strcpy(temp2, temp3); // temp2 is hyperlink
   }
   else // general files and directories
   {
      if (strcmp(hyperlink, "/") == 0) // root directory
      {
         strcat(temp2, "/");
         strcat(temp2, list);
      }
      else
      {
         strcpy(temp2, hyperlink); // sub directory
         strcat(temp2, "/");
         strcat(temp2, list);
      }
   }

   if (lstat(temp, &st) == -1) // failed to read file information
   {
      perror("stat");                 // print error
      printf("filename: %s\n", list); // list print
      printf("filepath: %s\n", temp); // path print
   }

   filetype((int)st.st_mode, str);   // string conversion function
   fileaccess((int)st.st_mode, str); // string conversion function
   if (str[0] == '-')                // general file
   {
      sprintf(messagebuf, "<tr style = \"color: red\">"); // color is red
      strcat(response_message, messagebuf);               // concentrate in response_message
   }
   else if (str[0] == 'd') // directory
   {
      sprintf(messagebuf, "<tr style = \"color: blue\">"); // color is red
      strcat(response_message, messagebuf);                // concentrate in response_message
   }
   else if (str[0] == 'l') // directory
   {
      sprintf(messagebuf, "<tr style = \"color: green\">"); // color is red
      strcat(response_message, messagebuf);                 // concentrate in response_message
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
   // if (hflag) // h option on
   // {
   //    int dividecount = 0;                               // how many times is it divided?
   //    changesizeformat = (double)st.st_size;             // use decimal point
   //    while (changesizeformat > 1024 && dividecount < 4) // express only up to G
   //    {
   //       changesizeformat /= 1024; // divide
   //       dividecount++;            // divided count up
   //    }

   //    switch (dividecount) // Different output statements depending on the number of divisions
   //    {
   //    case 0:
   //       printf("%s\t %d\t %s\t %s\t %.0f\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute, list);                                                                                                                     // just print
   //       sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.0f</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute); // html print
   //       strcat(response_message, messagebuf);
   //       break;

   //    case 1:
   //       printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'K', monthword, day, hour, minute, list);                                                                                                                     // K
   //       sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'K', monthword, day, hour, minute); // html K print
   //       strcat(response_message, messagebuf);
   //       break;

   //    case 2:
   //       printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'M', monthword, day, hour, minute, list);                                                                                                                     // M
   //       sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'M', monthword, day, hour, minute); // html M print
   //       strcat(response_message, messagebuf);
   //       break;

   //    case 3:
   //       printf("%s\t %d\t %s\t %s\t %.1f%c\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'G', monthword, day, hour, minute, list);                                                                                                                     // G
   //       sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.1f%c</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, 'G', monthword, day, hour, minute); // html G print
   //       strcat(response_message, messagebuf);
   //       break;

   //    default:
   //       printf("%s\t %d\t %s\t %s\t %.0f\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute, list);                                                                                                                     // default
   //       sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%.0f</td><td>%s %d %d:%d</td></tr>\n", temp, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, changesizeformat, monthword, day, hour, minute); // html default print
   //       strcat(response_message, messagebuf);
   //       break;
   //    }
   //    return;
   // }
   // printf("%s\t %d\t %s\t %s\t %lld\t %s %d %d:%d %s\n", str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute, list);                                                                                                                      // no option
   sprintf(messagebuf, "<td><a href = \"%s\" style = \"color: blue\">%s</a></td><td>%s</td><td>%d</td><td>%s</td><td>%s</td><td>%lld</td><td>%s %d %d:%d</td></tr>\n", temp2, list, str, (int)st.st_nlink, pas->pw_name, gru->gr_name, (long long)st.st_size, monthword, day, hour, minute); // html no h option print
   strcat(response_message, messagebuf);
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
void lsfunc(int aflag, int lflag, int hflag, int Sflag, int rflag, char *path, int client_fd, char *response_header, char *response_message, char *hyperlink) // ls algorithm
{
   FILE *file;            // file stream
   long filesize;         // requested file's size by client
   char buf[BUFFSIZE];    // file buffer
   DIR *dirp;             // directory pointer
   struct dirent *dir;    // directory entry
   char list[1000][1024]; // file list
   int count = 0;         // file count
   char dirpath[1024];    // directory path
   char messagebuf[BUFFSIZE] = {
       0,
   }; // before putting it response_message
   char currentdir[1024] = {
       0,
   }; // current working directory

   dirp = opendir(path);     // open directory with path
   realpath(path, dirpath);  // create absolute path
   getcwd(currentdir, 1024); // current working directory

   /* file part */
   if (dirp == NULL) // path is not directory
   {
      file = fopen(path, "rb"); // file open binary readonly
      fseek(file, 0, SEEK_END); // file end point
      filesize = ftell(file);   // extract file size
      fseek(file, 0, SEEK_SET); // to original point

      if (fnmatch("*.jpg", path, FNM_CASEFOLD) == 0 ||
          fnmatch("*.png", path, FNM_CASEFOLD) == 0 ||
          fnmatch("*.jpeg", path, FNM_CASEFOLD) == 0) // image file
      {
         sprintf(response_header, "HTTP/1.1 200 OK\r\n"
                                  "Server:2023 simple web server\r\n"
                                  "Content-length:%ld\r\n"
                                  "Content-type:image/*\r\n\r\n",
                 filesize); // header: Response status, server, length of information, type of information(image)
      }
      else if (fnmatch("*.html", path, FNM_CASEFOLD) == 0) // html
      {
         sprintf(response_header, "HTTP/1.1 200 OK\r\n"
                                  "Server:2023 simple web server\r\n"
                                  "Content-length:%ld\r\n"
                                  "Content-type:text/html\r\n\r\n",
                 filesize); // header: Response status, server, length of information, type of information(image)
      }
      else // general file
      {
         sprintf(response_header, "HTTP/1.1 200 OK\r\n"
                                  "Server:2023 simple web server\r\n"
                                  "Content-length:%ld\r\n"
                                  "Content-type:text/plain\r\n\r\n",
                 filesize); // header: Response status, server, length of information, type of information(image)
      }
      write(client_fd, response_header, strlen(response_header)); // send header
      long nsize = 0;                                             // currently sent size
      while (nsize != filesize)                                   // Transfer complete?
      {
         long sizepiece = fread(buf, 1, BUFFSIZE, file); // Bring the size of the buffer by 1
         nsize += sizepiece;                             // add
         write(client_fd, buf, sizepiece);               // send to client
      }
      fclose(file);   // file close
      closedir(dirp); // close directory
      return;
   }
   /* directory part */

   sprintf(response_message, "<html><head><link rel='icon' href='data:,'><title>%s</title></head><body>", currentdir); // html beginning
   if (strcmp(hyperlink, "/") == 0)                                                                                    // root directory
   {
      sprintf(messagebuf, "<h1>Welcome To System Programming HTTP</h1><br>"); // welcome
      strcat(response_message, messagebuf);
   }
   else
   {
      sprintf(messagebuf, "<h1>System Programming HTTP</h1><br>"); // general page
      strcat(response_message, messagebuf);
   }

   if (!aflag) // not -a option
   {
      while ((dir = readdir(dirp)) != NULL) // until you read it all
      {
         strcpy(list[count], dir->d_name); // copy file list
         if (list[count][0] == '.')        // Hidden files are not output targets
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
         strcpy(list[count], dir->d_name); // copy file list
         count++;
      }
   }

   if (!lflag)
   {
      selectionsort(Sflag, rflag, path, count, list); // sorting

      // printf("Directory path: %s\n", dirpath); // print absolute path
      for (int i = 0; i < count; i++) // loop by count
      {
         // printf("%s\n", list[i]); // print
      }
      // printf("\n"); // newline
   }
   else // l option
   {
      struct stat st;
      int blocksize = 0; // to calculate all file block size

      selectionsort(Sflag, rflag, path, count, list); // sorting
      // printf("Directory path: %s\n", dirpath);                         // print absolute path
      sprintf(messagebuf, "<b>Directory path: %s</b><br>\n", dirpath); // html directory path
      strcat(response_message, messagebuf);
      for (int i = 0; i < count; i++) // loop by count
      {
         char filepath[1024];
         strcpy(filepath, path); // copy path
         strcat(filepath, "/");
         strcat(filepath, list[i]); // string concentration
         stat(filepath, &st);       // load filepath information
         blocksize += st.st_blocks; // sum of sizes
      }
      // printf("total: %d\n", blocksize / 2);                         // total size print
      sprintf(messagebuf, "<b>Total: %d</b><br>\n", blocksize / 2); // html total block size
      strcat(response_message, messagebuf);
      sprintf(messagebuf, "<table border = \"1\">\n"); // table format
      strcat(response_message, messagebuf);
      sprintf(messagebuf, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // table header
      strcat(response_message, messagebuf);
      for (int i = 0; i < count; i++)
      {
         fileinfo(hflag, path, list[i], response_message, hyperlink); // print file information
      }
   }
   closedir(dirp);                                // close directory
   sprintf(messagebuf, "</table></body></html>"); // html end
   strcat(response_message, messagebuf);
   sprintf(response_header, "HTTP/1.0 200 OK\r\n"
                            "Server:2023 simple web server\r\n"
                            "Content-length:%lu\r\n"
                            "Content-type:text/html\r\n\r\n",
           strlen(response_message));

   write(client_fd, response_header, strlen(response_header));   // send header to client
   write(client_fd, response_message, strlen(response_message)); // send message to client
}

void signalhandler(int signal)//Works when signal comes in
{
   int status;//exit status of child
   pid_t childpid;//pid of child
   if (signal == SIGCHLD)//When the child process terminates
   {
      while ((childpid = waitpid(-1, &status, WNOHANG)) > 0)//To collect the status of two or more terminated children
      {
         printf("wait for child process\n");
         printf("child pid = %d\n",childpid);
      }
   }
   else if (signal == SIGALRM)//When the set alarm time runs out
   {
      int num = requestnumber - 1;//Convert to index of array
      printf("========= Connection History =================\n");
      printf("Number of request(s) : %d\n", totalrequestnumber);//total number of requests
      printf("No.\tIP\t\tPID\tPORT\tTIME\n");//print item
      for (int i = totalrequestnumber; i > totalrequestnumber-requestnumber; i--, num--)//Output up to the last 10 connection records 
      {
         printf("%d\t%s\t%d\t%d\t%s\t\n", i, inet_ntoa(ADDR_history[num].sin_addr), PID_history[num], ADDR_history[num].sin_port, ctime(&TIME_history[num]));
      }
      alarm(10);//Snooze in 10 seconds
   }
}

int main(int argc, char **argv) // argc: parameter number, argv[]: parameter
{
   alarm(10);//alarm initializing
   signal(SIGCHLD, signalhandler);//child's exit signal installation
   signal(SIGALRM, signalhandler);//connected client history print signal installation

   FILE *accessfp;//file pointer
   DIR *dirp; // directory pointer
   struct dirent *dir;
   int aflag = 0, lflag = 0, hflag = 0, Sflag = 0, rflag = 0;
   char htmlcurdirpath[1024];
   struct sockaddr_in server_addr, client_addr; // socket address struct
   int socket_fd, client_fd;                    // socket descriptor
   int len, len_out;
   int opt = 1;

   if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) // socket is not open
   {
      printf("Server : Can't open stream socket\n");
      return 0;
   }

   setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // socket setting

   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//accept any address
   server_addr.sin_port = htons(PORTNO); // Fill information into struct

   if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // bind error
   {
      printf("Server : Can't bind local address\n");
      return 0;
   }

   listen(socket_fd, 5);//waiting client

   while (1) // receiving request....
   {
      struct stat tempstat;               // stat buffer
      pid_t PID = 0;
      char buf[BUFFSIZE] = {
          0,
      };
      char tmp[BUFFSIZE] = {
          0,
      };
      char response_header[BUFFSIZE] = {
          0,
      };
      char response_message[BUFFSIZE] = {
          0,
      };
      char url[URL_LEN] = {
          0,
      };
      char method[20] = {
          0,
      };                // get,host....
      char *tok = NULL; // tokenizer
      char accessibleIP[256] = {0};
      int accessflag = 0;//0:denied 1:accepted

      aflag = 1;
      lflag = 1;                                                            // default option
      len = sizeof(client_addr);                                            // client address size
      client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &len); // get client socket
      if (client_fd < 0)                                                    // accept error
      {
         printf("Server : accept failed\n");
         return 0;
      }
      read(client_fd, buf, BUFFSIZE); // receive data
      strcpy(tmp, buf);               // copy
      tok = strtok(tmp, " ");
      if (tok == NULL)//no header
      {
         continue;
      }
      strcpy(method, tok); // save method

      if (strcmp(method, "GET") == 0)//get request
      {
         tok = strtok(NULL, " ");
         strcpy(url, tok);
      }

      accessfp = fopen("accessible.usr", "r");//Open the file containing the accessible IPs
      memset(accessibleIP, 0, 256);
      if (accessfp == NULL)//open failed
      {
         printf("file open error\n");
         return 0;
      }
      while (!feof(accessfp))//read to end of file
      {
         int num;
         fgets(accessibleIP, 256, accessfp);//Read single line including newline
         num = strlen(accessibleIP);//string length
         accessibleIP[num - 1] = '\0';//Remove newline character
         if (fnmatch(accessibleIP, inet_ntoa(client_addr.sin_addr), 0) == 0)//pattern matching
         {
            accessflag = 1;//accessible ip
            break;
         }
      }
      fclose(accessfp);//close file pointer
      PID = fork();//spawn child process
      if (PID == 0) // child's work
      {
         close(socket_fd);//Close server socket
         if (accessflag == 0)//inaccessible ip
         {
            sprintf(response_message, "<html><head><link rel='icon' href='data:,'><title>Access Denied</title></head><body>"
                                      "<h1>Access denied!</h1><br>"
                                      "<h2>Your IP : %s</h2><br>"
                                      "<p>You have no permission to access this web server.<br>"
                                      "HTTP 403.6 - Forbidden: IP address reject</p></body></html>",
                    inet_ntoa(client_addr.sin_addr));//Page notifying you of inaccessibility

            sprintf(response_header, "HTTP/1.1 403 FORBIDDEN\r\n"
                                     "Server:2023 simple web server\r\n"
                                     "Content-length:%lu\r\n"
                                     "Content-type:text/html\r\n\r\n",
                    strlen(response_message));//write header
            write(client_fd, response_header, strlen(response_header));   // send header to client
            write(client_fd, response_message, strlen(response_message)); // send message to client
            close(client_fd);//Close the socket to communicate with cilent
            exit(0);//End process
         }
         printf("========= New Client ============\n");
         printf("IP : %s\nPort : %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port); // convert address and print with port number
         printf("=================================\n\n");

         char tmpurl[URL_LEN]; // lsfunc's path
         getcwd(tmpurl, URL_LEN);
         if (strcmp(url, "/") == 0) // root directory is only l option
         {
            aflag = 0;
         }
         else // al option
         {
            strcat(tmpurl, url);
         }
         getcwd(htmlcurdirpath, 1024); // error printing tool

         if (stat(tmpurl, &tempstat) == -1)
         {
            sprintf(response_message, "<html><head><link rel='icon' href='data:,'><title>%s</title></head><body>"
                                      "<h1>Not Found</h1><br>"
                                      "<p>The request URL %s was not found on this server<br>"
                                      "HTTP 404 - Not Page Found</p></body></html>",
                    htmlcurdirpath, url);//file is not exist

            sprintf(response_header, "HTTP/1.1 404 NOTFOUND\r\n"
                                     "Server:2023 simple web server\r\n"
                                     "Content-length:%lu\r\n"
                                     "Content-type:text/html\r\n\r\n",
                    strlen(response_message));//write header
            write(client_fd, response_header, strlen(response_header));   // send header to client
            write(client_fd, response_message, strlen(response_message)); // send message to client
         }
         else
         {
            lsfunc(aflag, lflag, hflag, Sflag, rflag, tmpurl, client_fd, response_header, response_message, url); // calling lsfunc
         }
         printf("====== Disconnected Client ======\n");
         printf("IP : %s\nPort : %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port); // convert address and print with port number
         printf("=================================\n\n");
         close(client_fd);//Close the socket to communicate with cilent
         sleep(10);//Intentional delay to see if multitasking is going on
         exit(0);//end process
      }
      else if(PID>0)//parent's work
      {
         close(client_fd);//Close the socket to communicate with cilent
         if (accessflag == 0)//inaccessible ip
         {
            continue;//get request back
         }
         totalrequestnumber++;//total number of requests
         if (requestnumber < 10)//Save request history
         {
            ADDR_history[requestnumber].sin_addr = client_addr.sin_addr;//ip
            ADDR_history[requestnumber].sin_port = client_addr.sin_port;//port number
            PID_history[requestnumber] = PID;//child's pid
            TIME_history[requestnumber] = time(NULL);//requested time
            requestnumber++;
         }
         else//More than 10 request records
         {
            for (int i = 1; i < 10; i++)//Clear Oldest Records
            {
               ADDR_history[i - 1] = ADDR_history[i];//move forward one space
               PID_history[i - 1] = PID_history[i];//move forward one space
               TIME_history[i - 1] = TIME_history[i];//move forward one space
            }
            ADDR_history[requestnumber-1].sin_addr = client_addr.sin_addr;//ip
            ADDR_history[requestnumber-1].sin_port = client_addr.sin_port;//port number
            PID_history[requestnumber - 1] = PID;//child's pid
            TIME_history[requestnumber - 1] = time(NULL);//requested time
         }
      }
      else//pid == -1
      {
         printf("fork error\n");
      }
   }
   close(socket_fd);//close server's socket
   return 0; // end
}
