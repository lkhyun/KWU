#include "BpTree.h"
BpTree::~BpTree()
{

}
bool BpTree::Insert(int key, set<string> set) 
{
	if(root == NULL) //first insert
	{
		FrequentPatternNode* patterntemp = new FrequentPatternNode(); //patternnode
		patterntemp-> setFrequency(key);
		patterntemp->InsertList(set);
		BpTreeNode* datanodetemp = new BpTreeDataNode();
		datanodetemp->insertDataMap(key,patterntemp);
		root = datanodetemp;
		return true;
	}
	else //data is existed in tree
	{
		BpTreeNode* searchnode = searchDataNode(key);
		if(searchnode == NULL)//key is not exist,
		{
			BpTreeNode* insertlocation1 = root;
			BpTreeNode* insertlocation2 = NULL;
			map<int,FrequentPatternNode*>* inserttemp1;
			map<int,FrequentPatternNode*>* inserttemp2;

			FrequentPatternNode *patterntemp = new FrequentPatternNode(); // patternnode is ready
			patterntemp->setFrequency(key);
			patterntemp->InsertList(set);

			while(insertlocation1 ->getMostLeftChild() != NULL)
			{
				insertlocation1 = insertlocation1->getMostLeftChild();
			}
			if(insertlocation1->getNext() != NULL)
			{
				insertlocation2 = insertlocation1;
				insertlocation1 = insertlocation1->getNext();
			}
			while(insertlocation1 != NULL)
			{
				if(insertlocation2 == NULL)//only one node in datanode
				{
					insertlocation1->insertDataMap(key,patterntemp);
					if(excessDataNode(insertlocation1)) //split?
					{
						splitDataNode(insertlocation1);
						return true;
					}
					return true;
				}
				else //have many datanodes
				{
					map<int,FrequentPatternNode*>::iterator it1;
					map<int,FrequentPatternNode*>::iterator it2;
					inserttemp1 = insertlocation1->getDataMap();
					inserttemp2 = insertlocation2->getDataMap();
					it1 = inserttemp1->begin();
					it2 = inserttemp2->begin();
					if(it2->first>key)
					{
						insertlocation2->insertDataMap(key, patterntemp);
						if (excessDataNode(insertlocation2)) // split?
						{
							splitDataNode(insertlocation2);
							insertlocation2 = insertlocation2->getParent();
							while (excessIndexNode(insertlocation2))
							{
								splitIndexNode(insertlocation2);
								insertlocation2 = insertlocation2->getParent();
							}
							return true;
						}
						return true;
					}
					else if(it2->first<key && it1->first>key)
					{
						insertlocation2->insertDataMap(key,patterntemp);
						if (excessDataNode(insertlocation2)) // split?
						{
							splitDataNode(insertlocation2);
							insertlocation2 = insertlocation2->getParent();
							while (excessIndexNode(insertlocation2))
							{
								splitIndexNode(insertlocation2);
								insertlocation2 = insertlocation2->getParent();
							}
							return true;
						}
						return true;
					}
				}
				insertlocation2 = insertlocation1;
				insertlocation1 = insertlocation1->getNext();
			}
			insertlocation2->insertDataMap(key, patterntemp);
			if (excessDataNode(insertlocation2)) // split?
			{
				splitDataNode(insertlocation2);
				insertlocation2 = insertlocation2->getParent();
				while (excessIndexNode(insertlocation2))
				{
					splitIndexNode(insertlocation2);
					insertlocation2 = insertlocation2->getParent();
				}
				return true;
			}
			return true;
		}
		else //key is already exist, so insert in existed datanode
		{
			map<int,FrequentPatternNode*>* nodemap;
			map<int,FrequentPatternNode*>::iterator it;
			FrequentPatternNode *patterntemp;
			nodemap = searchnode->getDataMap();
			it = (*nodemap).find(key);
			patterntemp = it->second;
			patterntemp->InsertList(set);
			return true;
		}
	}
	return true;
}

BpTreeNode* BpTree::searchDataNode(int n) {
	BpTreeNode* pCur = root;
	map<int,FrequentPatternNode*>* searchmap;
	map<int,FrequentPatternNode*>::iterator it;

	while(pCur->getMostLeftChild() != NULL)// datanode access
	{
		pCur = pCur->getMostLeftChild();
	}
	while(pCur != NULL)
	{
		searchmap = pCur->getDataMap();
		it = (*searchmap).find(n);
		if(it != (*searchmap).end()) //nodedata is exist
			return pCur;
		pCur = pCur->getNext();
	}
	return pCur;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) 
{
	BpTreeNode* newdatanode = new BpTreeDataNode();
	map<int,FrequentPatternNode*>* splitdata;
	map<int,FrequentPatternNode*>::iterator it;
	
	splitdata = pDataNode->getDataMap();
	for (int i = 0; i < order-(order / 2); i++)//data share
	{
		it = --((*splitdata).end());
		newdatanode->insertDataMap(it->first, it->second);
		pDataNode->deleteMap(it->first);
	}
	newdatanode->setNext(pDataNode->getNext()); //splited nodes are connected
	newdatanode->setPrev(pDataNode);
	if(pDataNode->getNext()!=NULL)
	{
		pDataNode->getNext()->setPrev(newdatanode);
	}
	pDataNode->setNext(newdatanode);

	splitdata = newdatanode->getDataMap();
	if(pDataNode->getParent()==NULL) //no parent, so first split
	{
		BpTreeNode* newindexnode = new BpTreeIndexNode();
		it =(*splitdata).begin();
		newindexnode->insertIndexMap(it->first,newdatanode);
		newindexnode->setMostLeftChild(pDataNode);
		newdatanode->setParent(newindexnode);
		pDataNode->setParent(newindexnode);
		root = newindexnode;
	}
	else //parent is existed
	{
		BpTreeNode* indexnode = pDataNode->getParent();
		it =(*splitdata).begin();
		indexnode->insertIndexMap(it->first,newdatanode);
		newdatanode->setParent(indexnode);
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) 
{
	BpTreeNode* newindexnode = new BpTreeIndexNode();
	BpTreeNode* linknode;
	map<int,BpTreeNode*>* splitindex;
	map<int,BpTreeNode*>::iterator it;
	
	splitindex = pIndexNode->getIndexMap();
	for (int i = 0; i < order-(order / 2); i++)//data share
	{
		it = --((*splitindex).end());
		newindexnode->insertIndexMap(it->first, it->second);
		pIndexNode->deleteMap(it->first);
	}
	splitindex = newindexnode->getIndexMap();
	for(it = (*splitindex).begin(); it != (*splitindex).end();it++)//splited node has new parent
	{
		it->second->setParent(newindexnode);
	}
	it = (*splitindex).begin();
	newindexnode->setMostLeftChild(it->second);
	if(pIndexNode->getParent()==NULL) //no parent, so first split
	{
		BpTreeNode* newindexparent = new BpTreeIndexNode();
		newindexparent->insertIndexMap(it->first,newindexnode);
		newindexnode->deleteMap(it->first);
		newindexparent->setMostLeftChild(pIndexNode);
		newindexnode->setParent(newindexparent);
		pIndexNode->setParent(newindexparent);
		root = newindexparent;
	}
	else //parent is existed
	{
		BpTreeNode* indexparent = pIndexNode->getParent();
		indexparent->insertIndexMap(it->first,newindexnode);
		newindexnode->deleteMap(it->first);
		newindexnode->setParent(indexparent);
	}
}
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}


bool BpTree::printConfidence(string item, double item_frequency, double min_confidence)
{
	bool exist=0;
	bool flag=0;
	double frequency = item_frequency*min_confidence;//for search
	double confidence;//pattern confidence
	FrequentPatternNode *patternnode;
	multimap<int, set<string>> patternlist;
	multimap<int, set<string>>::iterator mit;
	set<string> patternset;
	set<string>::iterator sit;
	if(frequency < minimum())//if out of range
	{
		frequency = minimum();
	}
	while (frequency<=maximum())
	{
		patternnode = searchforprint(frequency);
		if(patternnode == NULL)
		{
			frequency++;
			continue;
		}
		patternlist = patternnode->getList();
		for (mit = patternlist.begin(); mit != patternlist.end(); mit++)
		{
			patternset = mit->second;
			for (sit = patternset.begin(); sit != patternset.end(); sit++)
			{
				if (item.compare(*sit) == 0)// item is exist!
				{
					exist = 1;
					if(flag == 0)
					{
						*fout <<"FrequentPattern  Frequency  Confidence"<<endl;
						flag = 1;
					}
					
				}
			}
			if (exist == 1)
			{
				*fout << "{ ";
				for (sit = patternset.begin(); sit != --patternset.end(); sit++)
				{
					*fout << " " << *sit<<", ";
				}
				*fout << *sit <<" }   ";
				*fout<<patternnode->getFrequency()<<"   ";
				confidence = (double)patternnode->getFrequency()/item_frequency;
				*fout<<confidence<<endl;
			}
			exist = 0;
		}
		frequency++;
	}
	if(flag==1)
	{
		return true;
	}
	return false;
}
bool BpTree::printRange(string item, int min, int max) 
{
	bool exist=0;
	bool flag = 0;
	FrequentPatternNode *patternnode;
	multimap<int, set<string>> patternlist;
	multimap<int, set<string>>::iterator mit;
	set<string> patternset;
	set<string>::iterator sit;
	if(min < minimum())
	{
		min = minimum();
	}
	while (min<=max)//range
	{
		patternnode = searchforprint(min);
		if(patternnode == NULL)
		{
			min++;
			continue;
		}
		patternlist = patternnode->getList();
		for (mit = patternlist.begin(); mit != patternlist.end(); mit++)
		{
			patternset = mit->second;
			for (sit = patternset.begin(); sit != patternset.end(); sit++)
			{
				if (item.compare(*sit) == 0)//item is exist!
				{
					exist = 1;
					if(flag == 0)
					{
						*fout <<"FrequentPattern  Frequency"<<endl;
						flag = 1;
					}
				}
			}
			if (exist == 1)
			{
				*fout << "{ ";
				for (sit = patternset.begin(); sit != --patternset.end(); sit++)
				{
					*fout << " " << *sit<<", ";
				}
				*fout <<*sit<< " }   ";
				*fout << patternnode->getFrequency()<<endl;
			}
			exist = 0;
		}
		min++;
	}
	if(flag == 1)
	{
		return true;
	}
	return false;
}


bool BpTree::printbptree(string item, int frequency) 
{
	bool exist=0;
	bool flag = 0;
	FrequentPatternNode *patternnode;
	multimap<int, set<string>> patternlist;
	multimap<int, set<string>>::iterator mit;
	set<string> patternset;
	set<string>::iterator sit;
	if(frequency < minimum())
	{
		frequency = minimum();
	}
	while (frequency <= maximum())
	{
		patternnode = searchforprint(frequency);
		if(patternnode == NULL)//Couldn't find it.
		{
			frequency++;
			continue;
		}
		patternlist = patternnode->getList();
		for (mit = patternlist.begin(); mit != patternlist.end(); mit++)
		{
			patternset = mit->second;
			for (sit = patternset.begin(); sit != patternset.end(); sit++)
			{
				if (item.compare(*sit) == 0)
				{
					exist = 1;
					if(flag==0)
					{
						*fout <<"FrequentPattern  Frequency"<<endl;
						flag = 1;
					}
				}
			}
			if (exist == 1)
			{
				*fout << "{ ";
				for (sit = patternset.begin(); sit != --patternset.end(); sit++)
				{
					*fout << " " << *sit<<", ";
				}
				*fout <<*sit<< " }   ";
				*fout << patternnode->getFrequency()<<endl;
			}
			exist = 0;
		}
		frequency++;
	}
	if(flag == 1)
	{
		return true;
	}
	return false;
}

FrequentPatternNode* BpTree::searchforprint(double n)
{
	int doubleup = ceil(n);
	BpTreeNode* searchnode = root;
	map<int,BpTreeNode*>* searchindex;
	map<int,BpTreeNode*>::iterator indexit1;
	map<int,BpTreeNode*>::iterator indexit2;
	map<int,FrequentPatternNode*>* searchdata;
	map<int,FrequentPatternNode*>::iterator datait;
	if(searchnode == NULL)
	{
		return NULL;
	}
	while(searchnode->getMostLeftChild()!=NULL)//difference of datanode and indexnode
	{
		searchindex = searchnode->getIndexMap();
		indexit1 = (*searchindex).begin();
		while (true)
		{
			if(indexit1->first > doubleup && indexit1 == (*searchindex).begin())//node search
			{
				searchnode = searchnode->getMostLeftChild();
				break;
			}
			else if(indexit1->first <= doubleup)//node search
			{
				indexit2 = indexit1++;
				if(indexit1 == (*searchindex).end())
				{
					searchnode = indexit2->second;
					break;
				}
			}
			else if(indexit1->first > doubleup)//nodesearch
			{
				searchnode = indexit2->second;
				break;
			}
		}
	}
	searchdata = searchnode->getDataMap();
	for(datait = (*searchdata).begin();datait != (*searchdata).end();datait++)
	{
		if(datait->first == doubleup)//frequent pattern find!
		{
			return datait->second;
		}
	}
	return NULL;
	
}
int BpTree::minimum()//most low frequency
{
	BpTreeNode* searchnode = root;
	map<int,FrequentPatternNode*>* searchdata;
	map<int,FrequentPatternNode*>::iterator datait;
	while(searchnode->getMostLeftChild() != NULL)
	{
		searchnode = searchnode->getMostLeftChild();
	}
	searchdata = searchnode->getDataMap();
	datait = searchdata->begin();
	return datait->first;
}
int BpTree::maximum()//most high frequency
{
	BpTreeNode* searchnode = root;
	map<int,FrequentPatternNode*>* searchdata;
	map<int,FrequentPatternNode*>::iterator datait;
	while(searchnode->getMostLeftChild() != NULL)
	{
		searchnode = searchnode->getMostLeftChild();
	}
	while(searchnode->getNext() != NULL)
	{
		searchnode=searchnode->getNext();
	}
	searchdata = searchnode->getDataMap();
	datait = searchdata->end();
	datait--;
	return datait->first;
}