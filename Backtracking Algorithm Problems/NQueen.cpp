
#include<iostream>
using namespace std;
class CNode
{
public:
	int board[4][4];
	CNode* pNext;
};

class CStack
{
public:
	CNode* pHead;
	CNode* pTail;

	CStack()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CStack()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}

	void Push(CNode* pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pnn->pNext = pHead;
			pHead = pnn;
		}
	}

	CNode* Pop()
	{
		CNode* pTrav = pHead;
		if (pTrav == NULL)
		{
			return NULL;
		}
		else
		{
			pHead = pTrav->pNext;
			pTrav->pNext = NULL;
		}
		return pTrav;
	}

	void Display()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					cout << pTrav->board[r][c] << "  ";
				}
				cout << endl;
			}
			cout << endl << endl;
			pTrav = pTrav->pNext;
		}
	}
};

class CList
{
public:
	CNode* pHead, * pTail;

	CList()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CList()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}

	void Attach(CNode* pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pTail->pNext = pnn;
			pTail = pnn;
		}
	}

	void Display()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			for (int r = 0; r < 4; r++)
			{
				for (int c = 0; c < 4; c++)
				{
					cout << pTrav->board[r][c] << "  ";
				}
				cout << endl;
			}
			cout << endl << endl;
			pTrav = pTrav->pNext;
		}
	}
};

int isLegal(CNode *pnn, int row, int col)
{
	int i, j,F=1;

	/* Check this row on left side */
	for (i = 0; i < col; i++)
	{
		if (pnn->board[row][i]==1)
		{
			F = 0;
	    }
	}

	/* Check upper diagonal on left side */
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
	{
		if (pnn->board[i][j]==1)
		{
			F = 0;
		}
	}

	/* Check lower diagonal on left side */
	for (i = row, j = col; j >= 0 && i < 4; i++, j--)
	{
		if (pnn->board[i][j]==1)
		{
			F = 0;
		}
	}
	return F;
}

CNode* CreateInitState()
{
	CNode* pnn = new CNode[1];
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			pnn->board[r][c] = 0;
		}
	}
	pnn->pNext = NULL;
	return pnn;
}

int ExpandChildren(CNode *pnn, int col)
{
	if (col >= 4)
	{
		return 1;
	}

	for (int i = 0; i < 4; i++)
	{
		/*
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				cout << pnn->board[r][c] << "  ";
			}
			cout << endl;
		}
		cout << endl << endl;
		system("pause"); */

		if (isLegal(pnn, i, col)==1) 
		{
			pnn->board[i][col] = 1;
			if (ExpandChildren(pnn, col + 1))
			{
				return 1;
			}
			else
			{
				pnn->board[i][col] = 0; 
			}
		}
	}
	return 0;
}

void BackTracking()
{
	CStack S;
	CList Visit;
	CNode* pnn = new CNode[1];
	pnn = CreateInitState();
	S.Push(pnn);

	if (ExpandChildren(pnn, 0) == 1)
	{
		S.Display();
		cout << "True"<<endl;
	}
	else
	{
		cout << "False" << endl;
	}
}

int main()
{
	BackTracking();
	system("pause");
}
