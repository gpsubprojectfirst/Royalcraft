#include "pch.h"
#include "SearchTree.h"

SearchTree::SearchTree()
	:strNode(nullptr)
	, dstNode(nullptr)
{
	Init();
}

void SearchTree::Init()
{
	for (int i = 0; i < TILECNTX; i++)
	{
		for (int j = 0; j < TILECNTY; j++)
		{
			Map[i][j].visitF = false;
			Map[i][j].x = i;
			Map[i][j].y = j;
			Map[i][j].Gcost = 0;
			Map[i][j].Hcost = 0;
			Map[i][j].parent = nullptr;
		}
	}
	for (int i = 0; i < TILECNTX; i++)
	{
		for (int j = 0; j < TILECNTY; j++)
		{
			SetChild(&Map[i][j], i, j);
		}
	}
}

void SearchTree::Set(MyMap* mMap)
{
	for (int i = 0; i < TILECNTX; i++)
	{
		for (int j = 0; j < TILECNTY; j++)
		{
			Map[i][j].visitF = false;
		}
	}
	for (int i = 0; i < TILECNTX; i++)
	{
		for (int j = 0; j < TILECNTY; j++)
		{
			if(mMap->Infos[i][j].flags == 1 )
				Map[i][j].visitF = true;
		}
	}
}
void SearchTree::SetTile(int x, int y)
{
	Map[x][y].visitF = true;

}
void SearchTree::Delete()
{
	Init();
	openList.clear();
}
void SearchTree::SetChild(scNode* Node, int x, int y)
{
	//예외처리??
	if (x == 0 && y == 0)
	{
		Node->child[0] = nullptr;
		Node->child[1] = nullptr;
		Node->child[2] = nullptr;
		Node->child[3] = nullptr;
		Node->child[4] = &Map[x + 1][y];
		Node->child[5] = nullptr;
		Node->child[6] = &Map[x][y + 1];
		Node->child[7] = &Map[x + 1][y + 1];
	}
	if (x < TILECNTX-1 && x > 0
		&& y == 0)
	{
		Node->child[0] = nullptr;
		Node->child[1] = nullptr;
		Node->child[2] = nullptr;
		Node->child[3] = &Map[x - 1][y];
		Node->child[4] = &Map[x + 1][y];
		Node->child[5] = &Map[x - 1][y + 1];
		Node->child[6] = &Map[x][y + 1];
		Node->child[7] = &Map[x + 1][y + 1];
	}
	if (x == 0 &&
		y < TILECNTY-1 && y > 0)
	{
		Node->child[0] = nullptr;
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = &Map[x + 1][y - 1];
		Node->child[3] = nullptr;
		Node->child[4] = &Map[x + 1][y];
		Node->child[5] = nullptr;
		Node->child[6] = &Map[x][y + 1];
		Node->child[7] = &Map[x + 1][y + 1];
	}
	if (x == TILECNTX-1 &&
		y < TILECNTY-1 && y > 0)
	{
		Node->child[0] = &Map[x - 1][y - 1];
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = nullptr;
		Node->child[3] = &Map[x - 1][y];
		Node->child[4] = nullptr;
		Node->child[5] = &Map[x - 1][y + 1];
		Node->child[6] = &Map[x][y + 1];
		Node->child[7] = nullptr;
	}
	if (x == 0 && y == TILECNTY -1 )
	{
		Node->child[0] = nullptr;
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = &Map[x + 1][y - 1];
		Node->child[3] = nullptr;
		Node->child[4] = &Map[x + 1][y];
		Node->child[5] = nullptr;
		Node->child[6] = nullptr;
		Node->child[7] = nullptr;
	}
	if (x < TILECNTX - 1 && x > 0
		&& y == TILECNTY - 1)
	{
		Node->child[0] = &Map[x - 1][y - 1];
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = &Map[x + 1][y - 1];
		Node->child[3] = &Map[x - 1][y];
		Node->child[4] = &Map[x + 1][y];
		Node->child[5] = nullptr;
		Node->child[6] = nullptr;
		Node->child[7] = nullptr;
	}
	if (x == TILECNTX - 1 && y == TILECNTY - 1)
	{
		Node->child[0] = &Map[x - 1][y - 1];
		Node->child[1] = &Map[x][y - 1];
		Node->child[2] = nullptr;
		Node->child[3] = &Map[x - 1][y];
		Node->child[4] = nullptr;
		Node->child[5] = nullptr;
		Node->child[6] = nullptr;
		Node->child[7] = nullptr;
	}
	if (x < TILECNTX - 1 && x > 0
		&& y < TILECNTY - 1 && y > 0)
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
//void SearchTree::SetParent();
scNode** SearchTree::GetChild(scNode* parentNode)
{
	return parentNode->child;
};
scNode* GetParent(scNode* Node)
{
	return Node->parent;
}
//
int SearchTree::callHcost(scNode* str, scNode* dst)
{
		if (str)//장애물 검사
	{
		//str->visitF = true;
		
		//양수 계산
		return  int(10 * sqrt(pow(dst->x - str->x,2) + pow(dst->y - str->y,2)));
	}

}

scNode* SearchTree::NextNode(int n, scNode* InNode)
{
	return InNode->child[n];
}

void copyNode(scNode& src, scNode& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.visitF = src.visitF;
	dst.parent = src.parent;
	
	for(int i =0 ; i<8 ; i++)
		dst.child[i] = src.child[i];
}
bool SearchTree::CompareCost(const scNode* first,const scNode* second)
{
	return first->Hcost + first->Gcost <= second->Hcost + second->Gcost;
}
void SearchTree::SortList()
{
	if (openList.size() < 2) return;
	scNode* temp;
	bool bContinue = true;
	
	//openList.sort();

	while (bContinue)
	{
		bContinue = false;
		for (auto& it : openList)
		{
			if (!CompareCost(openList.front(),it))
			{			
				temp = it;

				it = openList.front();

				openList.front() = temp;

				bContinue = true;

			}

		}
	}
}

void SearchTree::FindPath(std::pair<int, int> str, std::pair<int, int> dst, std::stack<std::pair<int, int>>* vecPath)
{
	strNode = &Map[str.first][str.second];
	dstNode = &Map[dst.first][dst.second];
	
	openList.push_front(strNode);
	int Fcost = 0;
	int Hcost = 0;

	strNode->visitF = true;
	strNode->Gcost = 0;

	while (!openList.empty())
	{
		strNode = openList.front();
		openList.pop_front();
		//cout << strNode->x << " , " << strNode->y << endl;
		if (strNode == dstNode)
		{
			while (strNode != nullptr)
			{
				vecPath->push(std::make_pair(strNode->x, strNode->y));
				strNode = GetParent(strNode);
			}
			break;
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				auto temp = GetChild(strNode);
				auto tempChild = temp[i];
				if (tempChild == nullptr)
				{
					continue;
				}
				if (tempChild->visitF)
				{
					continue;
				}
				else
				{
					tempChild->visitF = true;
					tempChild->parent = strNode;

					//자식 노드 위치에 따라 Gcost 증가
					if (i == 0 || i == 2 || i == 5 || i == 7)
					{
						tempChild->Gcost = tempChild->parent->Gcost + 14;
					}
					else
					{
						tempChild->Gcost = tempChild->parent->Gcost + 10;
					}

					Hcost = callHcost(tempChild, dstNode);
					tempChild->Hcost = Hcost;

					openList.push_back(tempChild);
				}
			}
			//열린리스트 정렬
			SortList();
			//openList.sort();
		}
	}
	Delete();
}