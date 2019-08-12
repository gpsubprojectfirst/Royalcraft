#pragma once
#include<list>
class scNode
{
public:
	int Gcost;
	int Hcost;
	int x;
	int y;
	
	bool visitF;
	
	scNode* parent;
	scNode* child[8];//8πÊ«‚


};
class SearchTree
{
public:
	scNode Map[65][97];
	scNode* strNode;
	scNode* dstNode;
	
	SearchTree();
	
	void Init();
	void Delete();

	std::list<scNode*> openList;
	
	void SortList();
	bool CompareCost(const scNode* first,const scNode* second);
	void SetChild(scNode* Node, int x, int y);
	scNode** GetChild(scNode* parentNode);
	//int callDist(scNode* str, scNode* dst);
	
	int callHcost(scNode* str, scNode* dst);
	
	scNode* NextNode(int n, scNode* InNode);
	void copyNode(scNode& src, scNode& dst);
	void FindPath(std::pair<int, int> str, std::pair<int, int> dst, myUnit* mUnit);
};