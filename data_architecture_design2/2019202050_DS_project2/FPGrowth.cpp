#include "FPGrowth.h"


FPGrowth::~FPGrowth() 
{
	flog.close();
}

void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) 
{
	list<string>::iterator it;
	FPNode* move = root;
	FPNode* temp = NULL;
	map<string,FPNode*>::iterator m;
	for(it = item_array.begin();it !=item_array.end();it++)
	{
		temp = move->getChildrenNode(*it);
		if (temp == NULL)//childrennode is not exist
		{
			temp = new FPNode();
			temp->setstring(*it);
			temp->setParent(move);
			temp->updateFrequency(frequency);
			move->pushchildren(*it, temp);
			move = temp;
			temp = table->getNode(*it);
			if(temp == NULL)
			{
				table->setNode(move,*it);
			}
			else
			{
				while(temp->getNext() != NULL)
				{
					temp = temp ->getNext();
				}
				temp->setNext(move);
			}
		}
		else //node is exist so update frequency
		{
			temp->updateFrequency(frequency);
			move = temp;
		}
	}
}

map<set<string>,int> FPGrowth::getFrequentPatterns(HeaderTable* pTable)
{
	string item;
	set<string> frequentset;//set from fptree singlepath
	set<string>::iterator sit;

	multimap<int,set<string>> frequentmap; //Sets with frequencies
	multimap<int,set<string>> finalfrequentmap; //final sets with frequencies above the threshold
	multimap<int,set<string>>::iterator mit;

	map<set<string>,int> powersetmap;//powerset is saved here
	map<set<string>,int>::iterator pit;
	map<set<string>,int>* powersetptr = &powersetmap;
	vector<string> powerdata;

	map<string,int> frequenttable;//temp table
	map<string,int>::iterator tit;

	map<set<string>,int> returnmap;//for return last patterns
	map<set<string>,int>::iterator returntemp;
	list<pair<int,string>>::iterator it;
	list<pair<int,string>> l = pTable->getindexTable();

	FPNode* temp = NULL;
	FPNode* temp1 = NULL;
	int frequent;
	string good; //leaf node item

	for(it = l.begin();it!=l.end();it++)
	{
		if(it->first >= threshold)
		{
			temp = table->getNode(it->second);
			good = temp->getstring();
			while (temp != NULL)
			{
				temp1 = temp;
				frequent = temp1->getFrequency(); //leaf node frequency save
				while (temp1->getFrequency() != 0)//until root
				{
					frequentset.insert(temp1->getstring());
					tit = frequenttable.find(temp1->getstring());
					if(tit == frequenttable.end())
					{
						frequenttable.insert({temp1->getstring(),frequent});
					}
					else
					{
						tit->second += frequent;
					}
					temp1 = temp1->getParent();
				}
				frequentmap.insert({frequent,frequentset});//frequentset and frequent save
				frequentset.clear();
				temp = temp->getNext();
			}
			for(tit = frequenttable.begin();tit != frequenttable.end();tit++)
			{
				if(tit->second < threshold)
				{
					item = tit->first;
					for(mit = frequentmap.begin();mit != frequentmap.end();mit++)
					{
						mit->second.erase(item);//Delete infrequent items
					}
				}
			}
			for(mit = frequentmap.begin();mit != frequentmap.end();mit++)
			{
				for(sit = mit->second.begin();sit != mit->second.end();sit++)
				{
					powerdata.push_back(*sit);//vector initializing
				}
				int a = mit->second.size();
				int* ptr = new int[a];
				powerSet(powersetptr,powerdata,good,mit->first,ptr,0);//get subset
				for(pit = powersetmap.begin();pit != powersetmap.end();pit++)
				{
					finalfrequentmap.insert({pit->second,pit->first});//insert multimap
				}
				powersetmap.clear();
				powerdata.clear();
				delete[] ptr;

			}
			frequenttable.clear();//for loop
			frequentmap.clear();
		}
	}

	for(mit = finalfrequentmap.begin();mit != finalfrequentmap.end();mit++)
	{
		returntemp = returnmap.find(mit->second);
		if(returntemp == returnmap.end() && mit->second.size()>1)//Choose more than frequency
		{
			returnmap.insert({mit->second,mit->first});//final frequent set
		}
		else if(returntemp != returnmap.end())
		{
			returntemp->second += mit->first;//update
		}	
	}
	return returnmap;
}



void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}

bool FPGrowth::printList() 
{
	table->descendingIndexTable();
	list<pair<int,string>>::iterator it;
	list<pair<int,string>> l = table->getindexTable();
	*fout <<"item    Frequency"<<endl;
	for(it = l.begin(); it != l.end(); it++)
	{
		*fout<< it->second <<", "<< it->first<<endl;
	}
	return true;
}
bool FPGrowth::printTree() 
{
	table->ascendingIndexTable();
	list<pair<int,string>>::iterator it;
	list<pair<int,string>> l = table->getindexTable();
	FPNode* temp = NULL;
	*fout <<"{StandardItem  Frequency} (Path_Item  Frequency)"<<endl;
	for(it = l.begin();it!=l.end();it++)
	{
		if(it->first >= threshold)//print more than frequency
		{
			*fout<<"{"<<it->second<<", "<<it->first<<"}"<<endl;
			temp = table->getNode(it->second);
			while (temp != NULL)
			{
				FPNode* temp1 = temp;
				while (temp1->getFrequency() != 0)
				{
					*fout<<"("<< temp1->getstring()<<", "<<temp1->getFrequency()<<")";
					temp1 = temp1->getParent();
				}
				*fout<<endl;
				temp = temp->getNext();
			}
			*fout<<endl;
		}
	}
	return true;
}
void FPGrowth::saveFrequentPatterns()//print frequentpattern to log
{
	map<set<string>,int>::iterator mit;
	set<string>::iterator sit;
	for(mit = frequentPatterns.begin(); mit != frequentPatterns.end();mit++)
	{
		if (mit->second >= threshold)
		{
			flog<<mit->second;
			for(sit = mit->first.begin();sit != mit->first.end();sit++)
			{
				flog<<"\t"<<*sit;
			}
			flog<<endl;
		}
	}
}
