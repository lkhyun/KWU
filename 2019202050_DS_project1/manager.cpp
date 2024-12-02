#include "manager.h"


Manager::~Manager()
{
    if (logout.is_open()) //log stream close
        logout.close();
    if (cmdin.is_open()) //command stream close
        cmdin.close();
    delete bst;
}
void Manager::PrintERROR(int num) //when an error occurs
{
    logout << "========ERROR========" << endl;
    logout << num << endl;
    logout << "=====================" << endl;
}
void Manager::nodeprint(Loaded_LIST *node) //nodeprint for debug
{
    Loaded_LIST *temp = node;
    Loaded_LIST_Node *temp1 = temp->list_root;
    do
    {
        temp1 = temp -> list_root;
        while (temp1 != NULL)
        {
            logout << temp1;
            temp1 = temp1->nextnode;
        }
        if(temp->list_down != NULL)
            temp = temp->list_down;
        else
            break;
    } while (true);
}
void Manager::nodeisfull() //when exceed the list's limit for deleting node
{
    Loaded_LIST* temp1 = bufferlist;
    Loaded_LIST_Node* temp2 =NULL;
    while(temp1->list_root == NULL)//If a node in the list is empty
    {
        temp1 = temp1 ->list_down;
    }
    temp2 = temp1->list_root;
    if(temp1->list_root->nextnode == NULL)// only one node in list
    {
        delete temp2;
        temp2 = NULL;
        temp1->list_root = NULL;
    }
    else //general situation
    {
        temp1->list_root = temp1->list_root->nextnode;
        delete temp2;
        temp2 = NULL;
    }
}
void Manager::inorderprint(Database_BST_Node* node) //for PRINT command
{
    if(node == NULL) 
        return;
    else
    {
        inorderprint(node->left);
        logout<<node;
        inorderprint(node->right);
    } 
}
void Manager::preorder(Database_BST_Node* node) //for SELECT command
{
    if(node == NULL)
        return;
    else
    {
        if(node->unique_number==selectnumber) 
            selectfile = node;
        preorder(node->left);
        preorder(node->right);
    } 
}
void Manager::bstmemoryfree(Database_BST_Node* node)
{
    if(node == NULL)
        return;
    bstmemoryfree(node->left);
    bstmemoryfree(node->right);
    delete node;
}
void Manager::Run(const char *file_path)
{
    cmdin.open(file_path);            // open command file
    logout.open("log.txt", ios::app); // open log txt
    if (!cmdin)                       // fail to open file
    {
        logout << "File Open Error" << endl;
        return;
    }

    char line[100];       // one line is saved in txt
    char imagedata[100]; // one line is saved in csv
    FILE* inputfile; 
    FILE* outputfile;
    unsigned char inputpic[256][256];
    unsigned char outputpic[256][256];
    unsigned char outputpic_resized[128][128];
    while (!cmdin.eof())
    {
        endflag = 0; //Used as a flag when an error occurs
        cmdin.getline(line, 100);
        char *cmd = strtok(line, " "); //command container
        

        if (strcmp(cmd, "LOAD") == 0)
        {
            logout<<"========LOAD========"<<endl;
            readcsv.open("img_files/filesnumbers.csv");
            if (!readcsv.is_open()) //when csv file is not open
            {
                PrintERROR(100);
                continue;
            }
            while(!readcsv.eof())
            {
                readcsv.getline(imagedata, 100);
                char *data1 = strtok(imagedata, ",");
                char *data2 = strtok(NULL, ".");

                if(bufferlist == NULL) // when list is empty
                {
                    Loaded_LIST *temp1 = new Loaded_LIST();
                    bufferlist = temp1;
                }
                if(listfull==100)
                {
                    nodeisfull();
                    listfull--;
                }
                bufferlist->insertnode(data2,"img_files",data1);
                listfull++;
                
            }
            readcsv.close();
            
            nodeprint(bufferlist);
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "ADD") == 0)
        {
            char *cmd2 = strtok(NULL, " "); //directory
            char *cmd3 = strtok(NULL, " "); //raw file's name
            char *cmd5 = strtok(NULL," "); //If more arguments
            if(cmd2 == NULL||cmd3 ==NULL)//ADD command parameter is damaged
            {
                PrintERROR(200);
                continue;
            }
            if(cmd5 != NULL)//If more arguments
            {
                PrintERROR(200);
                continue;
            }
            char cmd4[100] = "./";//create path
            strcat(cmd4,cmd2);
            strcat(cmd4,"/");
            strcat(cmd4,cmd3);
            readcsv.open(cmd4);
            if (!readcsv.is_open()) //csvfile is not open
            {
                PrintERROR(200);
                continue;
            }
            if (bufferlist == NULL)//load command first
            {
                PrintERROR(200);
                continue;
            }
            Loaded_LIST* temp = bufferlist;
            while(temp->list_down != NULL)//add list
            {
                    temp=temp->list_down;
            }
            Loaded_LIST* temp1 = new Loaded_LIST;
            temp->list_down =temp1;
            while(!readcsv.eof())
            {
                readcsv.getline(imagedata, 100);
                char *data1 = strtok(imagedata, ",");//unique number only
                char *data2 = strtok(NULL, "."); //remove extension
                
                if(listfull==100)
                {
                    nodeisfull();
                    listfull--;
                }
                temp1->insertnode(data2,cmd2,data1);
                listfull++;   
            }
            readcsv.close();
            logout<<"========ADD========"<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "MODIFY") == 0)
        {
            
            char* cmd2 = strtok(NULL,"\"");
            char* cmd3 = strtok(NULL,"\"");
            char* cmd4 = strtok(NULL," ");
            char* cmd6 = strtok(NULL," ");
            char* cmd5 = strtok(cmd2," ");
            //modify command line

            if((cmd5 == NULL || cmd3 ==NULL) || cmd4 ==NULL) //when MODIFY command parameter is damaged
            {
                PrintERROR(300);
                continue;
            }
            if(cmd6 != NULL)//when too many parameter
            {
                PrintERROR(300);
                continue;
            }
            Loaded_LIST* temp1 = bufferlist;
            Loaded_LIST_Node* temp2 =NULL;

            while(temp1 != NULL)
            {
                temp2=temp1->list_root;
                while(temp2 != NULL)
                {
                    if(temp2->unique_number.compare(cmd4)==0)//unique_number is already exist
                    {
                        PrintERROR(300);
                        endflag = 1;
                        break;
                    }
                    temp2= temp2->nextnode;
                }
                if(endflag == 1)
                    break;
                temp1= temp1->list_down;
            }
            if(endflag == 1)
                continue;
            temp1 = bufferlist;
            temp2 = NULL;

            while(temp1 != NULL)
            {
                if(temp1->folder.compare(cmd5)==0) // when find the list
                {
                    bool tf = temp1->deletenode(cmd3,cmd5,cmd4);//delete the node in list
                    if(!tf)//node is not exist
                    {
                        PrintERROR(300);
                        endflag = 1;
                        break;
                    }
                    else
                        break;
                }
                temp1 = temp1->list_down;
            }
            if(endflag == 1)
                continue;
            if(temp1 == NULL)//folder is not exist
            {
                PrintERROR(300);
                continue;
            }
            logout<<"=======MODIFY======="<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "MOVE") == 0)
        {
            Loaded_LIST* temp1 = bufferlist;
            Loaded_LIST* temp2 = bufferlist;
            Loaded_LIST_Node *temp3 = bufferlist->list_root;
            Loaded_LIST_Node *temp4 = bufferlist->list_root;
            
            if(bufferlist->list_root == NULL)//linked list is not exist
            {
                PrintERROR(400);
                continue;
            }
            while (bufferlist != NULL)
            {
                temp1 = bufferlist;
                while (temp1->list_down != NULL)//to the lowest list
                {
                    temp2 = temp1;
                    temp1 = temp1->list_down;
                }
                temp3 = temp1->list_root;
                while (temp3->nextnode != NULL)//to the rightmost node
                {
                    temp4 = temp3;
                    temp3 = temp3->nextnode;
                }
                if(bstfull == 300)
                {
                    bool tf = bst->deletenode();
                    if(tf)
                    {
                        bstfull--;
                    }
                }
                const char* strtoch = temp3->unique_number.c_str();//convert string to char
                int chtoint = atoi(strtoch);//convert char to int
                bool tf = bst->insertnode(temp3->m_name,temp3->dirname,chtoint);
                if(tf)
                {
                    bstfull++;
                }
                if(temp3 == temp4)//when current list and following list are same
                {
                    if(temp1 == temp2)//when current node and following node are same
                    { 
                        bufferlist = NULL;
                    }
                    else
                    {
                        temp2->list_down = NULL;
                    }  
                    delete temp1;
                    temp1 = NULL;
                }
                else
                {
                    temp4->nextnode = NULL;
                }
                delete temp3;
                temp3 = NULL;
            }
            logout<<"========MOVE========"<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "PRINT") == 0)
        {
            if(bst->bst_root == NULL)//bst is empty
            {
                PrintERROR(500);
                continue;
            }
            logout<<"========PRINT========"<<endl;
            inorderprint(bst->bst_root);
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "SEARCH") == 0)
        {
            char* cmd2 = strtok(NULL, "\"");
            if(cmd2 == NULL)//parameter is not exist
            {
                PrintERROR(600);
                continue;
            }   
            Database_BST_Node * search = bst->bst_root;
            if (search == NULL)//bst is empty
            {
                PrintERROR(600);
                continue;
            }
            logout<<"=======SEARCH======="<<endl;
            Queue<Database_BST_Node*> q(300);                
            Stack<Database_BST_Node*> temp(300);
            Stack<Database_BST_Node*> saveorder(300);

            temp.Push(search);       //iterative postorder
            while(!temp.Empty())
            {
                search = temp.Pop();
                saveorder.Push(search);
                if(search->left != NULL)
                    temp.Push(search->left);
                if(search->right != NULL)
                    temp.Push(search->right);
            }
            while(!saveorder.Empty())
            {
                search = saveorder.Pop();
                q.push(search);
            }
            while(!q.empty()) //boyer algorithm
            {
                search = q.pop();
                int len1 = search->m_name.length(); //bst word length
                int len2 = strlen(cmd2); //input word length
                int len3 = len2-1; //Index to be compared with the input word end from bst word
                int i = 0; //Let me know how far loop has compared
                while(len3 < len1)
                {
                    if(cmd2[len2-1] == search->m_name[len3]) //If the end of the input word is the same when compared with the word in bst
                    {
                        for(i = 1;i<len2;i++)//Compare from the end as much as the length of the input word
                        {
                            if(cmd2[(len2-1)-i] != search->m_name[len3-i]) //If the comparison is different
                            {
                                len3 = len3+len2-i; //Skips the input word length, but subtracts the same number from the back.
                                break; //again
                            }
                            if (i == len2-1)
                            {
                                logout << search << endl;//print if found
                                len3++;
                            }
                        }
                    }
                    else//If the last character is different
                    {
                        for(i=1; i<len2;i++) //how much to skip
                        {
                            if(cmd2[(len2-1)-i] == search->m_name[len3])
                            {
                                len3 = len3 + i;
                                break;
                            }
                            if (i == len2-1)
                            {
                                len3= len3 + len2;
                            }
                        }
                    }
                }
            }
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd, "SELECT") == 0)
        {
            char *cmd2 = strtok(NULL," ");
            char *cmd3 = strtok(NULL," ");
            if(cmd2==NULL)//parameter is not exist
            {
                PrintERROR(700);
                continue;
            }
            if(cmd3 != NULL)//too many parameter
            {
                PrintERROR(700);
                continue;
            }
            selectnumber = atoi(cmd2);//char to int for compare
            preorder(bst->bst_root);//search
            if(selectfile == NULL)//unique_number is not exist in bst
            {
                PrintERROR(700);
                continue;
            }
            char loadimages[100]= "./";
            string dirtemp = selectfile->dirname;
            string filename = selectfile->m_name;
            strcat(loadimages,dirtemp.c_str());
            strcat(loadimages,"/images/");
            strcat(loadimages,filename.c_str());
            strcat(loadimages,".RAW");
            //create routh
            inputfile = fopen(loadimages,"rb");
            if(inputfile == NULL)//image file is not exist
            {
                PrintERROR(700);
                continue;
            }
            fread(inputpic,sizeof(unsigned char),256*256,inputfile);
            fclose(inputfile);
            logout<<"=======SELECT======="<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd,"EDIT") == 0)
        {
            char* cmd2 = strtok(NULL," ");
            char* cmd3 = strtok(NULL," ");
            char* cmd4 = strtok(NULL," ");
            if(cmd2 == NULL)//parameter is damaged
            {
                PrintERROR(800);
                continue;
            }
            if(cmd4 != NULL)// too many parameter
            {
                PrintERROR(800);
                continue;
            }
            if(selectfile == NULL) //no file
            {
                PrintERROR(800);
                continue;
            }
            if(strcmp(cmd2,"-f")==0)//flipped
            {
                imageStack symmetry(70000);
                for(int i = 0;i<256;i++)
                {
                    for(int j = 0; j<256;j++)
                    {
                        symmetry.Push(inputpic[i][j]);
                    }
                }
                for(int i = 0;i<256;i++)
                {
                    for(int j = 0; j<256;j++)
                    {
                        outputpic[i][j]=symmetry.Pop();
                    }
                }
                char modified_filename[100]="./Result/"; //file name create
                strcat(modified_filename,selectfile->m_name.c_str());
                strcat(modified_filename,"_flipped");
                strcat(modified_filename,".RAW");
                outputfile = fopen(modified_filename,"wb");//open file stream
                fwrite(outputpic,sizeof(unsigned char), 256*256,outputfile);//write
                
            }
            else if(strcmp(cmd2,"-l")==0)//adjusted
            {
                if(cmd3 == NULL)//more parameter for -l command
                {
                    PrintERROR(800);
                    continue;
                }
                unsigned int num = atoi(cmd3);//how bright
                imageQueue lighter(70000);
                for(int i = 0;i<256;i++)
                {
                    for(int j = 0; j<256;j++)
                    {
                        lighter.push(inputpic[i][j]);
                    }
                }
                for(int i = 0;i<256;i++)
                {
                    for(int j = 0; j<256;j++)
                    {
                        unsigned int temp = lighter.pop()+num;
                        if(temp>255)//too much
                            outputpic[i][j] = 255;
                        else
                            outputpic[i][j]= temp;
                    }
                }
                char modified_filename[100]="./Result/"; 
                strcat(modified_filename,selectfile->m_name.c_str());
                strcat(modified_filename,"_adjusted");
                strcat(modified_filename,".RAW");
                outputfile = fopen(modified_filename,"wb");
                fwrite(outputpic,sizeof(unsigned char), 256*256,outputfile);
            }
            else if(strcmp(cmd2,"-r")==0)//resized
            {
                for(int i = 0;i<256;i+=2)//height half
                {
                    for(int j = 0; j<256;j+=2)//width half
                    {
                        unsigned int temp = (inputpic[i][j] + inputpic[i+1][j] + inputpic[i][j+1] + inputpic[i+1][j+1])/4;//average
                        outputpic_resized[i/2][j/2] = temp;
                    }
                }
                char modified_filename[100]="./Result/"; 
                strcat(modified_filename,selectfile->m_name.c_str());
                strcat(modified_filename,"_resized");
                strcat(modified_filename,".RAW");
                outputfile = fopen(modified_filename,"wb");
                fwrite(outputpic_resized,sizeof(unsigned char), 128*128,outputfile);
            }
            fclose(outputfile);
            logout<<"========EDIT========"<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else if (strcmp(cmd,"EXIT") == 0)//memoryfree
        {
            if(bufferlist!=NULL)
            {
                Loaded_LIST* del1;
                Loaded_LIST_Node* del2; 
                if(bufferlist != NULL)
                {
                    while(bufferlist->list_down != NULL)
                    {
                        del1 = bufferlist;
                        while(del1->list_root != NULL)
                        {
                            del2 = del1->list_root;
                            del1->list_root = del1->list_root->nextnode;
                            delete del2;
                            del2= NULL;
                        }
                        bufferlist = bufferlist->list_down;
                        delete del1;
                        del1 = NULL;
                    }
                }
            }
            if(bst!=NULL)
            {
                if (bst->bst_root != NULL)
                {
                    bstmemoryfree(bst->bst_root);
                }
            }
            logout<<"========EXIT========"<<endl;
            logout<<"SUCCESS"<<endl;
            logout<<"===================="<<endl;
        }
        else
        {
            logout<<"wrong command"<<endl;
            PrintERROR(777);
            continue;
        }
    }
}
