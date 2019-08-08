#pragma once
#include "myMap.h"

class scNode
{
public:
	bool visitF;
	scNode* parent;
	scNode* child[8];//8방향
};
class SearchTree
{
public:
	scNode Map[101][163];
	scNode* strNode;
	scNode* dstNode;
	int Fcost;// 총 코스트
	int Hcost; // 예상 코스트
	int Gcost; //현재 이동 코스트

	SearchTree()
	{
		for (int i = 0; i < 101; i++)
		{
			for (int j = 0; j < 163; j++)
			{
				Map[i][j].visitF = false;
				SetChild(&Map[i][j],i,j);
			}
		}
	}
	
	void SetChild(scNode* Node,int x,int y)
	{
		if( x <101 && x > 0
			&& y < 163 && y > 0)
		Node->child[0] = &Map[x - 1][y - 1];
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = &Map[x + 1][y - 1];
		Node->child[3] = &Map[x - 1][y];
		Node->child[4] = &Map[x][y];
		Node->child[5] = &Map[x + 1][y];
		Node->child[6] = &Map[x - 1][y + 1];
		Node->child[7] = &Map[x][y + 1];
		Node->child[8] = &Map[x + 1][y + 1];
	}
	scNode** GetChild(scNode* parentNode)
	{
		for(auto& it : parentNode->child)
		return parentNode->child;
	};

	void NextNode(int n,scNode* InNode)
	{
		InNode = InNode->child[n];
	}
	
	std::vector<std::pair<int, int>> FindPath(std::pair<int,int> str, std::pair<int, int> dst)
	{
		strNode = &Map[str.first][str.second];
		dstNode = &Map[dst.first][dst.second];
		return path;
	}
	std::vector<std::pair<int,int>> path;
};