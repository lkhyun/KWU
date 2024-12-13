#pragma once
#include "HeaderTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <utility>

class FPGrowth
{
private:
	int threshold;
	FPNode* fpTree;
	HeaderTable* table;
	map<set<string>, int> frequentPatterns;
	ofstream* fout;
	ofstream flog;
public:
	FPGrowth(ofstream *fout, int threshold) {
		this->threshold = threshold;
		flog.open("result.txt");
		flog.setf(ios::fixed);
		fpTree = new FPNode();  table = new HeaderTable;
		this->fout = fout;
	}
	~FPGrowth();
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); }
	void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency);
	
	bool frequentPatternSetting() //frequentpattern
	{
		table->ascendingIndexTable();
		frequentPatterns = getFrequentPatterns(table);
		saveFrequentPatterns();
		if(frequentPatterns.size()==0)
		{
			return false;
		}
		return true;
	}

	map<set<string>,int> getFrequentPatterns(HeaderTable* pTable);
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth);
	int item_frequency(string item) {return table->find_frequency(item);}
	FPNode* getTree() { return fpTree; }
	HeaderTable* getHeaderTable() { return table; }
	int getthreshold(){return threshold;}

	bool printList();
	bool printTree();
	void saveFrequentPatterns();

	};


