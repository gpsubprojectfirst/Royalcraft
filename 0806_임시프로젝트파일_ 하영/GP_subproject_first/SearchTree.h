#pragma once
class scNode
{
public:
	int x;
	int y;
	bool visitF;
	scNode* parent;
	scNode* child[8];//8방향
};
class SearchTree
{
public:
	scNode Map[65][97];
	scNode* strNode;
	scNode* dstNode;
	int Fcost;// 총 코스트
	int Hcost; // 예상 코스트
	int Gcost; //현재 이동 코스트

	SearchTree();
	void SetChild(scNode* Node, int x, int y);
	scNode** GetChild(scNode* parentNode);
	int callDist(scNode* str, scNode* dst);
	scNode* NextNode(int n, scNode* InNode);
	
	void FindPath(std::pair<int, int> str, std::pair<int, int> dst, myUnit* mUnit);
};