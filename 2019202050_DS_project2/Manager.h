#pragma once
#include "FPGrowth.h"
#include "BpTree.h"

class Manager
{
private:
	char cmd[100]; //which command?
	FPGrowth* fpgrowth;
	BpTree* bptree;
public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		fpgrowth = new FPGrowth(&flog,threshold);
		bptree = new BpTree(&flog,bpOrder);
	}

	~Manager()//destructor
	{
		
	}

	ifstream fin; //command.txt
	ifstream din; //market.txt
	ofstream flog; //log.txt
	

	void run(const char* command);
	bool LOAD();
	bool BTLOAD();
	
	bool PRINT_ITEMLIST();
	bool PRINT_FPTREE();

	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_BPTREE(char* item, int min_frequency);
	bool SAVE();

	void printErrorCode(int n);
	void printSuccessCode();
	void memoryfree();
	void indexmemoryfree(BpTreeNode* temp);


};

