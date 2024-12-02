#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include <fstream>
#include <iostream>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree();
	bool		Insert(int key, set<string> set);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(int n); //tree node search
	
	FrequentPatternNode*	searchforprint(double n);//frequent node search
	bool	printbptree(string item, int frequency);
	bool	printFrequency(string item, int min_frequency);
	bool	printConfidence(string item, double item_frequency, double min_confidence);
	bool 	printRange(string item, int min, int max);
	int 	minimum();
	int 	maximum();

};

#endif
