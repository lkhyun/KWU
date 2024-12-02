////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File Name   :2019202050_semaphore_server.c       	                                                          //
// Date      :2023/05/27                                                                                          //
// Os      :Ubuntu 16.04 LTS 64bits                                                                               //
// Author    :Lee Kang Hyun                                                                                       //
// Student ID   :2019202050                                                                                       //
//----------------------------------------------------------------------------------------------------------------//
// Title   :System Programming Assignment #3-3                                                                    //
// Description   :  This code saves the execution result of preforked_server to a log file. To prevent multiple	  //
// threads accessing and modifying the log file at the same time, semaphore is used to control it.		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE // FNM_CASEFOLD
#define URL_LEN 256
#define BUFFSIZE 10240
#define PORTNO 40000  // port number 40000
#define SHM_KEY 40000 // shared memory key value

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
#include <sys/ipc.h>    //to use shared memory
#include <sys/shm.h>    //to use shared memory
#include <pthread.h>    //Using thread-related tools
#include <sys/time.h>   //gettimeofday
#include <semaphore.h>  //semaphore
#include <fcntl.h>      //sem_open

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
// etc..						 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// child_main						 //
// ======================================================//
// input: p -> child number				 //
//	  socket_fd -> 	server socket			 //
//	  addrlen -> client address length		 //
// output: void						 //
// 							 //
// purpose: Specifies the role of the child process	 //
// that directly connects with the client to exchange	 //
// information, receives signals from the parent, outputs//
// the contents, and terminates the process. 		 //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
// child_make					 	 //
// ======================================================//
// input: p -> child number				 //
//	  socket_fd -> 	server socket			 //
//	  addrlen -> client address length		 //
// output: pid_t 					 //
// 							 //
// purpose: This is the part that creates the child	 //
// process, which causes the child to execute the 	 //
// child_main function and the parent to return the pid. //
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// initshm                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: Creates and initializes shared memory.    	     //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// modifyshm                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: This function is called by the child process     //
// and is used to update the connection record stored in the //
// shared memory.    	     				     //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// printshm                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: Display information in shared memory.    	     //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// processcontroler1                                 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: As one of the functions that manages the number  //
// of child processes, it is called when a child process     //
// connects to a client and updates the idle process state.  //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// processcontroler2                                 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: As one of the functions that manages the number  //
// of child processes, it is called when a child process     //
// disconnects to a client and updates the idle process state//
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// sendpid                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: Update the idle process in shared memory   	     //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// changedidle                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose: A function that handles processes connected to   //
// the client and processes that are not connected to the    //
// client differently when it is terminated.    	     //
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// printlog                                 	 	     //
// ==========================================================//
// input: vptr -> Arguments passed along with thread creation//
//                                			     //
//                                       		     //
// output: void* 		                             //
//                                       		     //
//                                       		     //
//                                       		     //
// purpose:Writes the string entered by vptr to the log file.//
///////////////////////////////////////////////////////////////

typedef struct SHM_Info // Structure to be stored in shared memory
{
   struct sockaddr_in ADDR_history[10]; // connected client's address
   pid_t pid[10];                       // pid associated with the client
   time_t TIME_history[10];             // when communicating with the client
   int requestnumber;                   // The number of requests received from the client (Maximum count: 10 times)
   int IdleProcess;                     // The number of child processes not connected to the client.
   pid_t idlepid[10];                   // List of pids of child processes not connected to the client
} SHM_INFOS;

typedef struct CLI_Info // A structure containing the information of the connected client
{
   struct sockaddr_in ADDR_cli; // ip,port
   pid_t pid_proc;              // chile process pid
   time_t TIME_cli;             // connection time
} CLI_INFOS;

typedef struct IDLE_Info // Information to receive from child process
{
   pid_t pid_proc; // child process pid
   int flag;       // 0: working process 1: idle process
} IDLE_INFOS;

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // mutex initialize
static int Maxchilds;                                      // Total number of children that can be created
static int MaxIdleNum;                                     // Maximum number of unconnected children
static int MinIdleNum;                                     // Minimum number of unconnected children
static int StartProcess;                                   // Number of children to create after starting the server
static int MaxHistory;                                     // connection record limit
pid_t *pids;                                               // child's pids
time_t temptime;                                           // use anytime for print current time
int curchild;                                              // Number of children currently created
static int socket_fd;                                      // socket descriptor
static int addrlen;
int shm_id; 						   // shared memory id
const char *logfile = "server_log.txt";			   // logfile name
sem_t *mysem;						   // semaphore name
int logfd;						   // log file description			

void selectionsort(int Sflag, int rflag, char *path, int count, char list[][1024]);

void lsfunc(int aflag, int lflag, int hflag, int Sflag, int rflag, char *path, int client_fd, char *response_header, char *response_message, char *hyperlink);

void filetype(int mode, char *str);

void fileaccess(int mode, char *str);

void fileinfo(int hflag, char *path, char list[], char *response_message, char *hyperlink);

int wildcardexistence(char *str);

void signalhandler(int signal);

pid_t child_make(int p, int socket_fd, int addrlen);

void child_main(int p, int socket_fd, int addrlen);

void *initshm(void *vptr);

void *modifyshm(void *vptr);

void *printshm(void *vptr);

void *processcontroler1(void *vptr);

void *processcontroler2(void *vptr);

void *sendpid(void *vptr);

void *changedidle(void *vptr);

void *printlog(void *vptr);

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

void signalhandler(int signal) // Works when signal comes in
{
   int status;     // exit status of child
   pid_t childpid; // pid of child
   char *tmp;
   pthread_t thandler;    // thread
   char logbuf[1024] = {0,};
   if (signal == SIGALRM) // When the set alarm time runs out
   {
      printf("========= Connection History =================\n"); // print title
      printf("No.\tIP\t\tPID\tPORT\tTIME\n");                     // print item
      pthread_create(&thandler, NULL, printshm, NULL);            // Create a thread to run printshm
      pthread_join(thandler, NULL);                               // wait for thread to exit
      alarm(10);                                                  // Snooze in 10 seconds
   }
   if (signal == SIGINT) // input ctrl + c
   {
      alarm(0);
      snprintf(logbuf,1024,"^C\n");			  // ctrl + c print
      pthread_create(&thandler, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
      pthread_join(thandler, NULL);			  // wait for thread to exit
      pthread_create(&thandler, NULL, changedidle, NULL); // Create a thread to run changeidle
      pthread_join(thandler, NULL);                       // wait for thread to exit
      temptime = time(NULL);                              // Get current time
      tmp = ctime(&temptime);                             // change time format
      tmp[strcspn(tmp, "\n")] = '\0';                     // Delete newline character
      printf("[%s] Server is terminated.\n", tmp);        // end message
      snprintf(logbuf,1024,"[%s] Server is terminated.\n", tmp);
      pthread_create(&thandler, NULL, printlog, &logbuf); // Create a thread to run sendpid and has an idleproc argument.
      pthread_join(thandler, NULL);
      
      shmctl(shm_id, IPC_RMID, NULL);                     // release shared memory
      pthread_mutex_destroy(&counter_mutex);              // remove mutex
      sem_unlink("mysem");                                // semaphore unlink
      free(pids);
      exit(0); // end
   }
   if (signal == SIGTERM) // parent's exit signal
   {
      exit(0); // end
   }
   if (signal == SIGUSR1) // idle process--
   {
      pthread_create(&thandler, NULL, processcontroler1, NULL); // Create a thread to run processcontroler1
      pthread_join(thandler, NULL);                             // wait for thread to exit
   }
   if (signal == SIGUSR2) // idle process++
   {
      pthread_create(&thandler, NULL, processcontroler2, NULL); // Create a thread to run processcontroler2
      pthread_join(thandler, NULL);                             // wait for thread to exit
   }
   if (signal == SIGCHLD)
   {
      while ((childpid = waitpid(-1, &status, WNOHANG)) > 0)
      {
         temptime = time(NULL);                                     // Get current time
         tmp = ctime(&temptime);                                    // change time format
         tmp[strcspn(tmp, "\n")] = '\0';                            // Delete newline character
         printf("[%s] %d process is terminated.\n", tmp, childpid); // end message
         snprintf(logbuf,1024,"[%s] %d process is terminated.\n", tmp, childpid);
         pthread_create(&thandler, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
         pthread_join(thandler, NULL);
      }
   }
}

pid_t child_make(int p, int socket_fd, int addrlen) // create child
{
   char logbuf[1024] = {0,};
   pid_t pid;
   pthread_t logthread;
   pid = fork(); // clone process
   if (pid > 0)  // parent's work
   {
      temptime = time(NULL); // Get current time
      char *timetmp;
      timetmp = ctime(&temptime);                           // change time format
      timetmp[strcspn(timetmp, "\n")] = '\0';               // Delete newline character
      snprintf(logbuf,1024,"[%s] %d process is forked.\n", timetmp, pid);
      pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
      pthread_join(logthread,NULL);
      printf("[%s] %d process is forked.\n", timetmp, pid); // process creation message
      return pid;
   }
   if (pid == 0) // child's work
   {
      child_main(p, socket_fd, addrlen); // child's main
   }
}

void child_main(int p, int socket_fd, int addrlen)
{
   signal(SIGTERM, signalhandler); // parent's exit signal
   signal(SIGINT, SIG_IGN);        // ctrl+c ignore
   DIR *dirp;                      // directory pointer
   struct dirent *dir;
   int aflag = 0, lflag = 0, hflag = 0, Sflag = 0, rflag = 0;
   char htmlcurdirpath[1024]; // current directory
   pthread_t tmodify;

   while (1) // receiving request....
   {
      FILE *accessfp;       // file pointer
      struct stat tempstat; // stat buffer
      int client_fd;
      struct sockaddr_in client_addr;
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
      char logbuf[1024] = {0,};//log buffer
      char *tok = NULL; // tokenizer
      char accessibleIP[256] = {0};
      int accessflag = 0;  // 0:denied 1:accepted
      CLI_INFOS threadarg; // thread argument for updating client infomation in shared memory
      IDLE_INFOS idleproc; // thread argument for updating idle process in shared memory
      char *logtimetmp;
      long logloadingtime = 0;
      struct timeval logtimestart;//connect start
      struct timeval logtimeend;//connect end

      aflag = 1;
      lflag = 1; // default option
      socklen_t clientlen = addrlen;
      client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &clientlen); // get client socket
      if (client_fd < 0)                                                          // accept error
      {
         printf("Server : accept failed\n");
         continue;
      }
      read(client_fd, buf, BUFFSIZE); // receive data
      strcpy(tmp, buf);               // copy
      tok = strtok(tmp, " ");
      if (tok == NULL) // no header
      {
         continue;
      }
      strcpy(method, tok); // save method

      if (strcmp(method, "GET") == 0) // get request
      {
         tok = strtok(NULL, " ");
         strcpy(url, tok);
      }
      if(strcmp(url,"/favicon.ico") == 0)// ignore favicon.ico 
      {
         continue;
      }

      accessfp = fopen("accessible.usr", "r"); // Open the file containing the accessible IPs
      memset(accessibleIP, 0, 256);
      if (accessfp == NULL) // open failed
      {
         printf("file open error\n");
         continue;
      }
      while (!feof(accessfp)) // read to end of file
      {
         int num;
         fgets(accessibleIP, 256, accessfp);                                 // Read single line including newline
         num = strlen(accessibleIP);                                         // string length
         accessibleIP[num - 1] = '\0';                                       // Remove newline character
         if (fnmatch(accessibleIP, inet_ntoa(client_addr.sin_addr), 0) == 0) // pattern matching
         {
            accessflag = 1; // accessible ip
            break;
         }
      }
      fclose(accessfp);    // close file pointer
      if (accessflag == 0) // inaccessible ip
      {
         sprintf(response_message, "<html><head><link rel='icon' href='data:,'><title>Access Denied</title></head><body>"
                                   "<h1>Access denied!</h1><br>"
                                   "<h2>Your IP : %s</h2><br>"
                                   "<p>You have no permission to access this web server.<br>"
                                   "HTTP 403.6 - Forbidden: IP address reject</p></body></html>",
                 inet_ntoa(client_addr.sin_addr)); // Page notifying you of inaccessibility

         sprintf(response_header, "HTTP/1.1 403 FORBIDDEN\r\n"
                                  "Server:2023 simple web server\r\n"
                                  "Content-length:%lu\r\n"
                                  "Content-type:text/html\r\n\r\n",
                 strlen(response_message));                            // write header
         write(client_fd, response_header, strlen(response_header));   // send header to client
         write(client_fd, response_message, strlen(response_message)); // send message to client
         close(client_fd);                                             // Close the socket to communicate with cilent
         continue;
      }

      gettimeofday(&logtimestart,NULL);
      temptime = time(NULL);                              // Get current time
      logtimetmp = ctime(&temptime);                             // change time format
      logtimetmp[strcspn(logtimetmp, "\n")] = '\0';                     // Delete newline character
      snprintf(logbuf,1024,"========= New Client ============\nTIME : [%s]\nURL : %s\nIP : %s\nPID : %d\nPort : %d\n=================================\n\n",logtimetmp,url,inet_ntoa(client_addr.sin_addr), getpid(), client_addr.sin_port);
      pthread_create(&tmodify, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
      pthread_join(tmodify,NULL);
      printf("========= New Client ============\n");
      printf("TIME : [%s]\nURL : %s\nIP : %s\nPID : %d\nPort : %d\n",logtimetmp,url,inet_ntoa(client_addr.sin_addr), getpid(), client_addr.sin_port); // print time,url,ip,pid,port number
      printf("=================================\n\n");
      idleproc.pid_proc = getpid();
      idleproc.flag = 0;                                  // 0: working process 1: idle process
      pthread_create(&tmodify, NULL, sendpid, &idleproc); // Create a thread to run sendpid and has an idleproc argument.
      pthread_join(tmodify, NULL);                        // wait for thread to exit
      kill(getppid(), SIGUSR1);                           // processcontroler1 working

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
                 htmlcurdirpath, url); // file is not exist

         sprintf(response_header, "HTTP/1.1 404 NOTFOUND\r\n"
                                  "Server:2023 simple web server\r\n"
                                  "Content-length:%lu\r\n"
                                  "Content-type:text/html\r\n\r\n",
                 strlen(response_message));                            // write header
         write(client_fd, response_header, strlen(response_header));   // send header to client
         write(client_fd, response_message, strlen(response_message)); // send message to client
      }
      else
      {
         lsfunc(aflag, lflag, hflag, Sflag, rflag, tmpurl, client_fd, response_header, response_message, url); // calling lsfunc
      }
      // create thread argument
      threadarg.ADDR_cli.sin_addr = client_addr.sin_addr;
      threadarg.ADDR_cli.sin_port = client_addr.sin_port;
      threadarg.pid_proc = getpid();
      threadarg.TIME_cli = time(NULL);

      pthread_create(&tmodify, NULL, modifyshm, &threadarg); // Create a thread to run modifyshm and has a threadarg argument.
      pthread_join(tmodify, NULL);                           // wait for thread to exit
      close(client_fd);                                      // Close the socket to communicate with cilent
      gettimeofday(&logtimeend,NULL);			     // Get current time in microseconds
      logloadingtime = ((1000000 * (logtimeend.tv_sec - logtimestart.tv_sec)) + (logtimeend.tv_usec - logtimestart.tv_usec));
      sleep(5);

      temptime = time(NULL);                              // Get current time
      logtimetmp = ctime(&temptime);                             // change time format
      logtimetmp[strcspn(logtimetmp, "\n")] = '\0';                     // Delete newline character
      snprintf(logbuf,1024,"====== Disconnected Client ======\nTIME : [%s]\nURL : %s\nIP : %s\nPID : %d\nPort : %d\nCONNECTING TIME : %ld(us)\n=================================\n\n",logtimetmp,url,inet_ntoa(client_addr.sin_addr), getpid(), client_addr.sin_port, logloadingtime);
      pthread_create(&tmodify, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
      pthread_join(tmodify,NULL);
      printf("====== Disconnected Client ======\n");
      printf("TIME : [%s]\nURL : %s\nIP : %s\nPID : %d\nPort : %d\nCONNECTING TIME : %ld(us)\n",logtimetmp,url,inet_ntoa(client_addr.sin_addr), getpid(), client_addr.sin_port,logloadingtime); // print time,url,ip,pid,port number
      printf("=================================\n\n");
      idleproc.pid_proc = getpid();
      idleproc.flag = 1;                                  // 0: working process 1: idle process
      pthread_create(&tmodify, NULL, sendpid, &idleproc); // Create a thread to run sendpid and has an idleproc argument.
      pthread_join(tmodify, NULL);                        // wait for thread to exit
      kill(getppid(), SIGUSR2);                           // processcontroler2 working
   }
}

void *initshm(void *vptr)
{
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   if ((shm_id = shmget((key_t)SHM_KEY, sizeof(SHM_INFOS), 0666 | IPC_CREAT)) == -1) // create shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   shm_ptr = (SHM_INFOS *)shm_addr; // shared memory pointer
   shm_ptr->requestnumber = 0;
   for (int i = 0; i < Maxchilds; i++)
   {
      pthread_mutex_lock(&counter_mutex);   // mutex lock
      shm_ptr->idlepid[i] = 0;              // idlepid initialize
      pthread_mutex_unlock(&counter_mutex); // mutex unlock
   }
   pthread_exit(NULL);
}

void *modifyshm(void *vptr)
{
   int num;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   CLI_INFOS *temp = (CLI_INFOS *)vptr;               // use argument
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   pthread_mutex_lock(&counter_mutex); // mutex lock
   shm_ptr = (SHM_INFOS *)shm_addr;    // shared memory pointer
   num = shm_ptr->requestnumber;
   if (num < MaxHistory) // Save request history
   {
      shm_ptr->ADDR_history[num].sin_addr = temp->ADDR_cli.sin_addr; // ip
      shm_ptr->ADDR_history[num].sin_port = temp->ADDR_cli.sin_port; // port number
      shm_ptr->pid[num] = temp->pid_proc;                            // process pid
      shm_ptr->TIME_history[num] = temp->TIME_cli;                   // requested time
      shm_ptr->requestnumber = num + 1;
   }
   else // More than MaxHistory request records
   {
      for (int i = 1; i < MaxHistory; i++) // Clear Oldest Records
      {
         shm_ptr->ADDR_history[i - 1] = shm_ptr->ADDR_history[i]; // move forward one space
         shm_ptr->pid[i - 1] = shm_ptr->pid[i];                   // move forward one space
         shm_ptr->TIME_history[i - 1] = shm_ptr->TIME_history[i]; // move forward one space
      }
      shm_ptr->ADDR_history[num - 1].sin_addr = temp->ADDR_cli.sin_addr; // ip
      shm_ptr->ADDR_history[num - 1].sin_port = temp->ADDR_cli.sin_port; // port number
      shm_ptr->pid[num - 1] = temp->pid_proc;                            // process pid
      shm_ptr->TIME_history[num - 1] = temp->TIME_cli;                   // requested time
   }
   pthread_mutex_unlock(&counter_mutex); // mutex unlock
   pthread_exit(NULL);
}

void *printshm(void *vptr)
{
   int num;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   shm_ptr = (SHM_INFOS *)shm_addr;                            // shared memory pointer
   num = shm_ptr->requestnumber - 1;                           // Convert to index of array
   for (int i = 1; i < shm_ptr->requestnumber + 1; i++, num--) // Output up to the last 10 connection records
   {
      printf("%d\t%s\t%d\t%d\t%s", i, inet_ntoa(shm_ptr->ADDR_history[num].sin_addr), shm_ptr->pid[num], shm_ptr->ADDR_history[num].sin_port, ctime(&(shm_ptr->TIME_history[num]))); // print history
   }
   pthread_exit(NULL);
}

void *processcontroler1(void *vptr)
{
   int num;
   char *tmp;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   char logbuf[1024] = {0,};
   pthread_t logthread;
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   shm_ptr = (SHM_INFOS *)shm_addr; // shared memory pointer
   if (curchild == 0)               // The first creation of the child process is executed only once.
   {
      for (int i = 0; i < StartProcess; i++)
      {
         pids[i] = child_make(i, socket_fd, addrlen);                       // fork
         pthread_mutex_lock(&counter_mutex);                                // mutex lock
         shm_ptr->idlepid[i] = pids[i];                                     // update idle process list
         curchild++;                                                        // update number of current child process
         shm_ptr->IdleProcess++;                                            // update number of idle process
         pthread_mutex_unlock(&counter_mutex);                              // mutex unlock
         temptime = time(NULL);                                             // Get current time
         tmp = ctime(&temptime);                                            // change time format
         tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
         snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
         pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
         pthread_join(logthread,NULL);
         printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
      }
   }
   else
   {
      pthread_mutex_lock(&counter_mutex);                                // mutex lock
      shm_ptr->IdleProcess--;                                            // update number of idle process
      pthread_mutex_unlock(&counter_mutex);                              // mutex unlock
      temptime = time(NULL);                                             // Get current time
      tmp = ctime(&temptime);                                            // change time format
      tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
      snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
      pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
      pthread_join(logthread,NULL);
      printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
      if (shm_ptr->IdleProcess < MinIdleNum)                             // When there are fewer child processes waiting for connections than the condition
      {
         while (shm_ptr->IdleProcess != 5 && curchild < Maxchilds) // Match 5 less than the maximum number of children spawned
         {
            int i, j;
            for (i = 0; i < Maxchilds; i++) // Search for an empty pid spot
            {
               if (pids[i] == 0) // put in an empty pid bucket
               {
                  pids[i] = child_make(curchild, socket_fd, addrlen);
                  break;
               }
            }
            for (j = 0; j < Maxchilds; j++) // Search for an empty idle pid spot
            {
               if (shm_ptr->idlepid[j] == 0) // put in an empty idle pid bucket
               {
                  pthread_mutex_lock(&counter_mutex);   // mutex lock
                  shm_ptr->idlepid[j] = pids[i];        // update idle pid list
                  pthread_mutex_unlock(&counter_mutex); // mutex unlock
                  break;
               }
            }
            pthread_mutex_lock(&counter_mutex);                                // mutex lock
            curchild++;                                                        // update number of current child process
            shm_ptr->IdleProcess++;                                            // update number of idle process
            pthread_mutex_unlock(&counter_mutex);                              // mutex unlock
            temptime = time(NULL);                                             // Get current time
            tmp = ctime(&temptime);                                            // change time format
            tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
            snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
            pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
            pthread_join(logthread,NULL);
            printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
         }
      }
   }
   pthread_exit(NULL);
}

void *processcontroler2(void *vptr)
{
   int num;
   char *tmp;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   char logbuf[1024] = {0,};
   pthread_t logthread;
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   pthread_mutex_lock(&counter_mutex);                                // mutex lock
   shm_ptr = (SHM_INFOS *)shm_addr;                                   // shared memory pointer
   shm_ptr->IdleProcess++;                                            // update number of idle process
   temptime = time(NULL);                                             // Get current time
   tmp = ctime(&temptime);                                            // change time format
   tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
   snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
   pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
   pthread_join(logthread,NULL);
   printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
   if (shm_ptr->IdleProcess > MaxIdleNum)                             // When the number of idle processes exceeds the condition
   {
      while (shm_ptr->IdleProcess != 5) // match 5
      {
         int i, j;
         for (i = 0; i < Maxchilds; i++)
         {
            if (shm_ptr->idlepid[i] != 0) // to end idle process
            {
               kill(shm_ptr->idlepid[i], SIGKILL); // child end
               usleep(100);//100 microsecond sleep
               break;
            }
         }
         for (j = 0; j < Maxchilds; j++)
         {
            if (pids[j] == shm_ptr->idlepid[i]) // update pids and idlepid
            {
               pids[j] = 0;
               shm_ptr->idlepid[i] = 0;
               break;
            }
         }
         shm_ptr->IdleProcess--;                                            // update number of idle process
         curchild--;                                                        // update number of current child process
         temptime = time(NULL);                                             // Get current time
         tmp = ctime(&temptime);                                            // change time format
         tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
         snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
         pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
         pthread_join(logthread,NULL);
         printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
      }
   }
   pthread_mutex_unlock(&counter_mutex); // mutex unlock
   pthread_exit(NULL);
}

void *sendpid(void *vptr)
{
   int num;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   IDLE_INFOS *temp = (IDLE_INFOS *)vptr;
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   pthread_mutex_lock(&counter_mutex); // mutex lock
   shm_ptr = (SHM_INFOS *)shm_addr;    // shared memory pointer
   if (temp->flag == 0)                // When a process connects to a new client
   {
      for (int i = 0; i < Maxchilds; i++)
      {
         if (shm_ptr->idlepid[i] == temp->pid_proc)
         {
            shm_ptr->idlepid[i] = 0; // process is working
            break;
         }
      }
   }
   else // When a process disconnects to a client
   {
      for (int i = 0; i < Maxchilds; i++)
      {
         if (shm_ptr->idlepid[i] == 0)
         {
            shm_ptr->idlepid[i] = temp->pid_proc; // process is waiting
            break;
         }
      }
   }
   pthread_mutex_unlock(&counter_mutex); // mutex unlock
   pthread_exit(NULL);
}

void *changedidle(void *vptr)
{
   int num;
   char *tmp;
   void *shm_addr = (void *)0;
   SHM_INFOS *shm_ptr = NULL;
   char logbuf[1024] = {0,};
   pthread_t logthread;
   if ((shm_id = shmget((key_t)SHM_KEY, 0, 0)) == -1) // Get created shared memory
   {
      printf("shmget fail\n");
      pthread_exit(NULL);
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // attach shared memory to process
   {
      printf("shmat fail\n");
      pthread_exit(NULL);
   }
   shm_ptr = (SHM_INFOS *)shm_addr; // shared memory pointer
   for (int i = 0; i < Maxchilds; i++)
   {
      if (pids[i] != 0) // when there is a process
      {
         int flag = 0;
         for (int j = 0; j < Maxchilds; j++)
         {
            if (pids[i] == shm_ptr->idlepid[j]) // When a process is not connected to a client
            {
               flag = 1;
            }
         }
         if (flag == 0) // When a process is connected to a client
         {
            kill(pids[i], SIGTERM); // process end
         }
      }
   }
   for (int i = 0; i < Maxchilds; i++)
   {
      if (pids[i] != 0) // when there is a process
      {
         for (int j = 0; j < Maxchilds; j++)
         {
            if (pids[i] == shm_ptr->idlepid[j]) // When a process is not connected to a client
            {
               kill(pids[i], SIGTERM); // process end
               sleep(1);
               pthread_mutex_lock(&counter_mutex);                                // mutex lock
               shm_ptr->IdleProcess--;                                            // update number of idle process
               pthread_mutex_unlock(&counter_mutex);                              // mutex unlock
               temptime = time(NULL);                                             // Get current time
               tmp = ctime(&temptime);                                            // change time format
               tmp[strcspn(tmp, "\n")] = '\0';                                    // Delete newline character
               snprintf(logbuf,1024,"[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess);
               pthread_create(&logthread, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
               pthread_join(logthread,NULL);
               printf("[%s] IdleProcessCount : %d\n", tmp, shm_ptr->IdleProcess); // end message
            }
         }
      }
   }
   pthread_exit(NULL);
}

void *printlog(void *vptr)
{
   char logbuffer[1024];
   strncpy(logbuffer,(char*)vptr,1024);//concatenate argument string

   mysem = sem_open("mysem", O_RDWR);//semaphore open

   sem_wait(mysem);//locks the semaphore
   logfd = open(logfile, O_RDWR | O_APPEND);//Open file for read/write and write option from end of file
   write(logfd,logbuffer,strlen(logbuffer));
   close(logfd);
   sem_post(mysem);//unlocks the semaphore
   sem_close(mysem);//closes the semaphore
   pthread_exit(NULL);//exit thread
}

int main(int argc, char **argv) // argc: parameter number, argv[]: parameter
{
   alarm(10);                      // alarm initializing
   signal(SIGALRM, signalhandler); // connected client history print signal installation
   signal(SIGINT, signalhandler);  // install ctrl+c signal
   signal(SIGUSR1, signalhandler); // install SIGUSR1 signal
   signal(SIGUSR2, signalhandler); // install SIGUSR2 signal
   signal(SIGCHLD, signalhandler); // install SIGCHLD signal

   FILE *readconf; // file pointer
   char confbuf[30];
   struct sockaddr_in server_addr, client_addr; // socket address struct
   int opt = 1;
   pthread_t tcreate;
   char logbuf[1024] ={0,};

   if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) // socket is not open
   {
      printf("Server : Can't open stream socket\n");
      return 0;
   }

   setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // socket setting

   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // accept any address
   server_addr.sin_port = htons(PORTNO);            // Fill information into struct

   if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // bind error
   {
      printf("Server : Can't bind local address\n");
      return 0;
   }

   listen(socket_fd, 5); // waiting client

   readconf = fopen("httpd.conf", "r");      // http.conf file open
   memset(confbuf, 0, sizeof(confbuf) * 30); // initializing buf
   if (readconf == NULL)                     // open failed
   {
      printf("file open error\n");
   }
   while (!feof(readconf)) // read to end of file
   {
      char *tokbuf;
      fgets(confbuf, 30, readconf); // Read single line including newline
      tokbuf = strtok(confbuf, ":");
      if (tokbuf != NULL)
      {
         if (strcmp(tokbuf, "MaxChilds") == 0)
         {
            tokbuf = strtok(NULL, "\n");
            Maxchilds = atoi(tokbuf); // extract value of Maxchilds
         }
         else if (strcmp(tokbuf, "MaxIdleNum") == 0)
         {
            tokbuf = strtok(NULL, "\n");
            MaxIdleNum = atoi(tokbuf); // extract value of MaxIdleNum
         }
         else if (strcmp(tokbuf, "MinIdleNum") == 0)
         {
            tokbuf = strtok(NULL, "\n");
            MinIdleNum = atoi(tokbuf); // extract value of MinIdleNum
         }
         else if (strcmp(tokbuf, "StartProcess") == 0)
         {
            tokbuf = strtok(NULL, "\n");
            StartProcess = atoi(tokbuf); // extract value of StartProcess
         }
         else if (strcmp(tokbuf, "MaxHistory") == 0)
         {
            tokbuf = strtok(NULL, "\n");
            MaxHistory = atoi(tokbuf); // extract value of MaxHistory
         }
      }
   }
   fclose(readconf);                              // close file
   pthread_create(&tcreate, NULL, initshm, NULL); // create thread
   pthread_join(tcreate, NULL);                   // wait thread

   mysem = sem_open("mysem", O_CREAT | O_EXCL, 0700, 1);//Initialize and open a named semaphore
   sem_close(mysem);//closes the semaphore
   logfd = open(logfile, O_CREAT | O_TRUNC | O_RDWR, 0666);//file open
   close(logfd);//file close

   curchild = 0;
   pids = (pid_t *)malloc(Maxchilds * sizeof(pid_t));
   memset(pids, 0, Maxchilds * sizeof(pid_t));
   addrlen = sizeof(client_addr);
   temptime = time(NULL); // get current time
   char *timetmp;
   timetmp = ctime(&temptime);                   // change time format
   timetmp[strcspn(timetmp, "\n")] = '\0';       // delete newline character
   snprintf(logbuf,1024,"[%s] Server is started.\n", timetmp);
   pthread_create(&tcreate, NULL, printlog, &logbuf); // Create a thread to run printlog and has an logbuf argument.
   pthread_join(tcreate,NULL);
   printf("[%s] Server is started.\n", timetmp); // server start

   raise(SIGUSR1); // send a signal to yourself

   for (;;)
   {
      pause(); // wait until signal received
   }
}
