#pragma once
#include <string>
#include <cstring>
#include <map>
#include <cmath>
using namespace std;
class FPNode
{
private:
	int frequency;
	FPNode* parent;
	FPNode* next;
	map<string, FPNode*> children;
	string good;
public:
	FPNode();
	~FPNode();
	void setParent(FPNode* node) { this->parent = node; }
	void setNext(FPNode* node) { next = node; }
	void pushchildren(string item, FPNode* node) { children.insert(map<string, FPNode*>::value_type(item, node)); }
	void updateFrequency(int frequency) { this->frequency += frequency; }
	void setstring(string item){this->good = item;}

	int getFrequency() { return frequency; }
	string getstring() { return good; }
	FPNode* getParent() { return parent; }
	FPNode* getNext() { return next; }
	FPNode* getChildrenNode(string item);
	map<string, FPNode*> getChildren() { return children; }
};


