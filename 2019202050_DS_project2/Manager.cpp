#include "Manager.h"

void Manager::run(const char* command)
{
	fin.open(command); //command load
	flog.open("./log.txt",ios::app);
	if(!fin)//When the file does not open
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())//Escape when the file is finished
	{
		fin.getline(cmd,100);
		char *cmd1 = strtok(cmd,"\t");
		
		if(strcmp(cmd1,"LOAD")==0)
		{
			flog <<"========LOAD========"<<endl;
			if(LOAD())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(100);
			}
		}
		else if(strcmp(cmd1,"BTLOAD")==0)
		{
			flog <<"========BTLOAD========"<<endl;
			if(BTLOAD())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(200);
			}
		}
		else if(strcmp(cmd1,"PRINT_ITEMLIST") == 0)
		{
			if(PRINT_ITEMLIST())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(300);
			}
		}
		else if(strcmp(cmd1,"PRINT_FPTREE") == 0)
		{
			flog <<"========PRINT_FPTREE========"<<endl;
			
			if(PRINT_FPTREE())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(400);
			}
			
		}
		else if(strcmp(cmd1,"PRINT_BPTREE") == 0)
		{
			flog <<"========PRINT_BPTREE========"<<endl;
			char* cmd2 = strtok(NULL,"\t");
			char* cmd3 = strtok(NULL,"\t");
			char* cmd4 = strtok(NULL,"\t");
			if(cmd2 == NULL || cmd3 == NULL || cmd4 != NULL)//parameter is damaged
			{
				printErrorCode(500);
				continue;
			}
			if(PRINT_BPTREE(cmd2,atoi(cmd3)))
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(500);
			}
		}
		else if(strcmp(cmd1,"PRINT_CONFIDENCE") == 0)
		{
			flog <<"========PRINT_CONFIDENCE========"<<endl;
			double rate;
			char* cmd2 = strtok(NULL,"\t");
			char* cmd3 = strtok(NULL,"\t");
			char* cmd4 = strtok(NULL,"\t");
			if(cmd2 == NULL || cmd3 == NULL || cmd4 != NULL)//parameter is damaged
			{
				printErrorCode(600);
				continue;
			}
			rate = atof(cmd3);
			if(PRINT_CONFIDENCE(cmd2,rate))
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(600);
			}
		}
		else if(strcmp(cmd1,"PRINT_RANGE") == 0)
		{
			flog <<"========PRINT_RANGE========"<<endl;
			char* cmd2 = strtok(NULL,"\t");
			char* cmd3 = strtok(NULL,"\t");
			char* cmd4 = strtok(NULL,"\t");
			char* cmd5 = strtok(NULL,"\t");
			if(cmd2 == NULL || cmd3 == NULL || cmd4 == NULL || cmd5 != NULL)//parameter is damaged
			{
				printErrorCode(600);
				continue;
			}
			if(PRINT_RANGE(cmd2,atoi(cmd3),atoi(cmd4)))
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(700);
			}
		}
		else if(strcmp(cmd1,"SAVE") == 0)
		{
			flog <<"========SAVE========"<<endl;
			if(SAVE())
			{
				printSuccessCode();
			}
			else
			{
				printErrorCode(800);
			}
		}
		else if(strcmp(cmd1,"EXIT") == 0)
		{
			flog <<"========EXIT========"<<endl;
			memoryfree();
			flog <<"success"<<endl;
			flog <<"===================="<<endl;
		}
	}
	flog.close();
	fin.close();
	return;
}

bool Manager::LOAD()
{
	int frequency = 0;
	char purchase[1000];
	list<pair<int,string>> templist;
	list<string> goodlist; //save the path
	din.open("./market.txt");
	if(!din)
	{
		flog << "File Open Error" << endl;
		return false;
	}
	if(fpgrowth->getTree()->getChildren().size() != 0) 
	{
		flog<< "FPGrowth is already exist"<<endl;
		return false;
	}
	while(din.getline(purchase,1000))
	{
		char* item = strtok(purchase,"\t");
		while(item != NULL)
		{
			fpgrowth->createTable(item,1); //table create
			item = strtok(NULL,"\t");
		}
	}
	din.close();
	din.open("./market.txt");
	while(din.getline(purchase,1000))
	{
		char* item = strtok(purchase,"\t");
		while(item != NULL)
		{
			frequency = fpgrowth->getHeaderTable()->find_frequency(item);
			if(fpgrowth->getthreshold()<=frequency)
			{
				templist.push_back(make_pair(frequency,item));
			}
			item = strtok(NULL,"\t");
		}
		templist.sort(greater<pair<int, string>>()); // for table-based sort
		list<pair<int,string>>::iterator it;
		for(it = templist.begin();it !=templist.end();)
		{
			goodlist.push_back(it->second);
			it = templist.erase(it);
		}
		fpgrowth->createFPtree(fpgrowth->getTree(),fpgrowth->getHeaderTable(),goodlist,1);
		goodlist.clear();
	}
	din.close();
	return true;
}

bool Manager::BTLOAD()
{
	int bpkey;
	set<string> frequentpattern; //result.txt's data save
	char frequentset[1000];
	
	din.open("./result.txt");
	if(bptree->getRoot() != NULL)
	{
		flog<<"bptree is already exist"<<endl;
		return false;
	}
	if(!din)
	{
		flog << "File Open Error" << endl;
		return false;
	}
	while(din.getline(frequentset,1000))
	{
		char* item = strtok(frequentset,"\t");
		bpkey = atoi(item);
		item = strtok(NULL,"\t");
		while(item != NULL)
		{
			frequentpattern.insert(item);
			item = strtok(NULL,"\t");
		}
		bptree->Insert(bpkey,frequentpattern);
		frequentpattern.clear();
	}
	din.close();
	return true;
}

bool Manager::PRINT_ITEMLIST() 
{
	flog <<"========PRINT_ITEMLIST========"<<endl;
	if(fpgrowth->getHeaderTable()->getindexTable().size() == 0) //table is empty
		return false;
	return fpgrowth->printList();
}

bool Manager::PRINT_FPTREE() 
{
	if(fpgrowth->getTree()->getChildren().size() == 0)//tree is empty
	{
		return false;
	}
	return fpgrowth->printTree();
}

bool Manager::PRINT_BPTREE(char* item, int min_frequency) 
{
	if(bptree->getRoot() == NULL)//tree is empty
	{
		return false;
	}
	return bptree->printbptree(item,min_frequency);
}

bool Manager::PRINT_CONFIDENCE(char* item, double rate) 
{
	if(bptree->getRoot() == NULL)//tree is empty
	{
		return false;
	}
	int frequency = fpgrowth->getHeaderTable()->find_frequency(item);
	return bptree->printConfidence(item,frequency,rate);
}

bool Manager::PRINT_RANGE(char* item, int start, int end) 
{
	if(bptree->getRoot() == NULL)//tree is empty
	{
		return false;
	}
	return bptree->printRange(item,start,end);
}

bool Manager::SAVE()
{
	return fpgrowth->frequentPatternSetting();
}
void Manager::memoryfree()
{
	map<string,FPNode*> deletefptree;
	map<string,FPNode*>::iterator it;
	map<int,FrequentPatternNode*>* deletepatterns;
	map<int,FrequentPatternNode*>:: iterator mit;
	FPNode* temp;
	BpTreeNode* deletedatanode = bptree->getRoot();
	BpTreeNode* deletetemp;
	deletefptree = fpgrowth->getHeaderTable()->getdataTable();
	for(it = deletefptree.begin();it!= deletefptree.end();it++)
	{
		temp = it->second;
		while(temp != NULL)
		{
			delete temp;
			temp = temp->getNext();
		}
	}
	delete fpgrowth; //fpgrowth free

	indexmemoryfree(bptree->getRoot());//bptree indexnode free

	while(deletedatanode -> getMostLeftChild() != NULL)
	{	
		deletedatanode = deletedatanode->getMostLeftChild();
	}
	while(deletedatanode != NULL)
	{
		deletetemp = deletedatanode;
		deletedatanode = deletedatanode->getNext();
		deletepatterns = deletetemp->getDataMap();
		for(mit = deletepatterns->begin();mit!=deletepatterns->end();mit++)
		{
			delete mit->second;//frequentpatternnode free
		}
		delete deletetemp; //datanode free
	}

	delete bptree;//bptree free

}
void Manager::indexmemoryfree(BpTreeNode* temp)
{
	map<int,BpTreeNode*>* deleteindex = temp->getIndexMap();
	map<int,BpTreeNode*>:: iterator it;
	if(temp->getMostLeftChild()->getMostLeftChild() != NULL)
	{
		indexmemoryfree(temp->getMostLeftChild());
		for(it = deleteindex->begin();it != deleteindex->end();it++)
		{
			indexmemoryfree(it->second);
		}
		delete temp;
	}
}
void Manager::printErrorCode(int n) 
{				
	flog << "ERROR "  << n << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() 
{
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}

