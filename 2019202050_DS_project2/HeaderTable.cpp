#include "HeaderTable.h"

HeaderTable::~HeaderTable() {

}


void HeaderTable::insertTable(char* item, int frequency) 
{
	list<pair<int,string>>::iterator it;
	for(it = indexTable.begin();it != indexTable.end();it++)
	{
		if(strcmp(it->second.c_str(),item)==0)
		{
			it->first++;
			descendingIndexTable();
			return;
		}
	}
	indexTable.push_back(make_pair(frequency,item));
	dataTable.insert({item,NULL});
}
int HeaderTable::find_frequency(string item){
	list<pair<int,string>>::iterator it;
	for(it = indexTable.begin(); it != indexTable.end();it++)
	{
		if(it->second == item)
		{
			return it->first;
		}
	}
	return 0;
}
void HeaderTable::setNode(FPNode* node, string item)
{
	dataTable[item]= node;
}
