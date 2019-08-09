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

	SearchTree()
		:strNode(nullptr)
		,dstNode(nullptr)
	{
		Fcost = 0;
		Hcost = 0;
		Gcost = 0;

		for (int i = 0; i < 65; i++)
		{
			for (int j = 0; j < 97; j++)
			{
				Map[i][j].visitF = false;
				Map[i][j].x = i;
				Map[i][j].y = j;
				
			}
		}
		for (int i = 0; i < 65; i++)
		{
			for (int j = 0; j < 97; j++)
			{
				SetChild(&Map[i][j],i,j);
			}
		}
	}
	
	void SetChild(scNode* Node,int x,int y)
	{
		if (x < 65 && x > 0
			&& y < 97 && y > 0)
		{
			Node->child[0] = &Map[x - 1][y - 1];
			Node->child[1] = &Map[x][y - 1];
			Node->child[2] = &Map[x + 1][y - 1];
			Node->child[3] = &Map[x - 1][y];
			Node->child[4] = &Map[x + 1][y];
			Node->child[5] = &Map[x - 1][y + 1];
			Node->child[6] = &Map[x][y + 1];
			Node->child[7] = &Map[x + 1][y + 1];
		}
	}
	scNode** GetChild(scNode* parentNode)
	{
		return parentNode->child;
	};

	int callDist(scNode* str, scNode* dst)
	{
		return sqrt(dst->x - str->x) + sqrt(dst->y - str->x);
	}
	void NextNode(int n,scNode* InNode)
	{
		InNode = InNode->child[n];
	}
	
	std::vector<std::pair<int, int>> FindPath(std::pair<int,int> str, std::pair<int, int> dst)
	{
		int count = 0;
		strNode = &Map[str.first][str.second];
		dstNode = &Map[dst.first][dst.second];
		while (str != dst)
		{
			scNode** child = GetChild(strNode);
			std::pair<int, int> minPos = std::make_pair(str.first, str.second);
			int min = 10000;
			int childNum = -1;
			for (int i = 0; i < 8; i++)
			{
				if (min < callDist(GetChild(strNode)[i], dstNode))
				{
					childNum = i;
					min = callDist(GetChild(strNode)[i], dstNode);
					minPos.first = GetChild(strNode)[i]->x;
					minPos.second = GetChild(strNode)[i]->y;
				}
			}
			NextNode(childNum,strNode);
			path[count] = std::make_pair(minPos.first, minPos.second);
			count++;
		}
		
		return path;
	}
	std::vector<std::pair<int,int>> path;
};