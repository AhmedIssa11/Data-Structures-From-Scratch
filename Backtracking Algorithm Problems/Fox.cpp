#include<iostream>
using namespace std;

class CNode {

public:
	int S1[4];
	int S2[4];
	int info;
	CNode* pNext;


};

class CStack {

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

	/* void Display()
	{
		CNode* PTrav;
		PTrav = pHead;
		while (PTrav != NULL)
		{
			for (int i = 0; i < 4; i++)
			{
				cout << PTrav->S1[i];
			}
			cout << endl;
			for (int i = 0; i < 4; i++)
			{
				cout << PTrav->S2[i];
			}
			cout << endl;
			PTrav = PTrav->pNext;
		}
	} */


};

class CList
{
public:
	CNode* pHead;
	CNode* pTail;

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


	void Remove(int v)
	{
		CNode* pTrav = pHead;
		CNode* pB = NULL;
		while (pTrav != NULL)
		{
			if (pTrav->info == v)
			{
				break;
			}
			pB = pTrav;
			pTrav = pTrav->pNext;
		}

		if (pB != NULL)
		{
			pB->pNext = pTrav->pNext;
			if (pTail == pTrav)
			{
				pTail = pB;
			}

			else
			{
				pHead = pTrav->pNext;
			}

			delete pTrav;
		}

	}
};

CNode* CreateInitState()
{
	CNode* pnn = new CNode;
	for (int i = 0; i < 4; i++)
	{
		pnn->S1[i] = 1;
		pnn->S2[i] = 0;
	}

	pnn->pNext = NULL;
	return pnn;
}

int IsVisited(CNode* pnn, CList& Visit)
{

	CNode* pTrav = Visit.pHead;
	int F = 0,R = 0;

	while (pTrav != NULL)
	{
		F = 0;
		for (int i = 0; i < 4; i++)
		{
			if (pTrav->S1[i] == pnn->S1[i])
			{
				F++;
				if (F == 4)
				{
					R = 1;
					break;
				}
			}
		}
		pTrav = pTrav->pNext;
		if (R == 1)
		{
			return R;
			break;
		}
	}

	return R;
}

void ExpandChildren(CNode* pCurr, CStack& S, CList& Visit)
{
	int Result = 1, K = 0;
	Visit.Attach(pCurr);

	if (pCurr->S1[3] == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			CNode* pnn = new CNode;
			for (int r = 0; r < 4; r++)
			{
				pnn->S1[r] = pCurr->S1[r];
				pnn->S2[r] = pCurr->S2[r];
			}
			pnn->pNext = NULL;
			pnn->S1[i] = 0;
			pnn->S2[i] = 1;
			pnn->S1[3] = 0;
			pnn->S2[3] = 1;

			//cout << "Boat : "<<pnn->S1[3] << endl;
			//cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3]  << endl;
			//cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << endl << endl;
			//system("pause");

			if (!((pnn->S1[0] == 1 && pnn->S1[2] == 1) || (pnn->S1[1] == 1 && pnn->S1[2] == 1)))
			{
				//cout << "Legal : " << endl;
				Result = IsVisited(pnn, Visit);
				if (Result == 0)
				{
					//cout << "Not Visited" << endl;
					S.Push(pnn);
				}
			}
		}
	}

	else
	{
		for (int i = 0; i < 4; i++)
		{
			CNode* pnn = new CNode;
			for (int r = 0; r < 4; r++)
			{
				pnn->S1[r] = pCurr->S1[r];
				pnn->S2[r] = pCurr->S2[r];
			}
			pnn->pNext = NULL;
			pnn->S1[i] = 1;
			pnn->S2[i] = 0;
			pnn->S1[3] = 1;
			pnn->S2[3] = 0;

			//cout << "Boat : " << pnn->S1[3] << endl;
			//cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3]  << endl;
			//cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << endl << endl;
			//system("pause");
			if (!((pnn->S2[0] == 1 && pnn->S2[2] == 1) || (pnn->S2[1] == 1 && pnn->S2[2] == 1)))
			{
				Result = IsVisited(pnn, Visit);
				if (Result == 0)
				{
					S.Push(pnn);
				}
			}
		}
	}


}

void Display(CNode* pnn)
{
	cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << endl;
	cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << endl << endl;
}

int Status(CNode* pnn)
{
	int F = 1;
	for (int i = 0; i < 4; i++)
	{
		if (pnn->S1[i] != 0)
		{
			F = 0;
			return F;
		}
	}
	return F;
}

void BackTrack()
{
	CStack S;
	CList Visit;
	CNode* pnn = CreateInitState();
	S.Push(pnn);

	while (S.pHead != NULL)
	{
		CNode* pCurr = S.Pop();
		//S.Display();
		Display(pCurr);
		ExpandChildren(pCurr, S, Visit);
		if (Status(pCurr) == 1)
		{ 
			break;
		}
	}	
}

int main()
{

	BackTrack();

	cout << endl << endl;;
	system("pause");
}