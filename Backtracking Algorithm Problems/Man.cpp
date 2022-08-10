#include<iostream>
using namespace std;

class CNode
{
public:
	int S1[6], S2[6], boat;
	CNode* pNext;
};

class CStack
{
public:
	CNode *pHead;
	CNode *pTail;

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
			cout << "S1: ";
			for (int i = 0; i < 6; i++)
			{
				cout << pTrav->S1[i];
			}
			cout << endl;
			cout << "S2: ";
			for (int i = 0; i < 6; i++)
			{
				cout << pTrav->S2[i];
			}
			cout << endl<<endl;
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
		int j = 1;
		while (pTrav != NULL)
		{
			cout << "Visit " << j << ": "<<endl;
			for (int i = 0; i < 6; i++)
			{
				cout << pTrav->S1[i]<<" ";
			}
			cout << endl;
			for (int i = 0; i < 6; i++)
			{
				cout << pTrav->S2[i]<<" ";
			}
			pTrav = pTrav->pNext;
			cout << endl<<endl;
			j++;
		}
	}
};

CNode* CreateInitState()
{
	CNode* pnn = new CNode[1];
	for (int i = 0; i < 6; i++)
	{
		pnn->S1[i] = 1;
		pnn->S2[i] = 0;
	}
	pnn->pNext = NULL;
	pnn->boat = 0;
	return pnn;
}

int IsVisited(CNode* pnn, CList& Visit,int &ct)
{
	int F1=0,F=0;
	CNode* pTrav = Visit.pHead;
	while (pTrav != NULL)
	{
		F1 = 0;

		for (int i = 0; i < 6; i++)
		{
			if (pTrav->S1[i] == pnn->S1[i])
			{
				F1++;
				if (F1 == 6)
				{
					F = 1;
					break;
				}
			}
		}
		pTrav = pTrav->pNext;
		if (F == 1)
		{
			if (pnn->boat == 0 && pnn->S1[0] == 1 && pnn->S1[1] == 1 && pnn->S1[2] == 1 && pnn->S1[3] == 1 && pnn->S1[4] == 0 && pnn->S1[5] == 0)
			{
				ct++;
				if (ct == 1)
				{
					F = 0;
				}
			}
			return F;
			break;
		}
	}
	return F;
}

int IsLegal(CNode* pnn)
{
	int F = 0, tot1 = 0, tot2 = 0, tot3 = 0, tot4 = 0, M1[6] = {8,8,3,3,5,5};
	
		//side 1
		for (int i = 0; i < 6; i++)
		{
			if (i % 2 == 0 && pnn->S1[i] == 1)
			{
				tot1 += M1[i]; //people
			}
			if (i % 2 != 0 && pnn->S1[i] == 1)
			{
				tot2 += M1[i];  //money
			}
		}

		//side 2
		for (int i = 0; i < 6; i++)
		{
			if (i % 2 == 0 && pnn->S2[i] == 1)
			{
				tot3 += M1[i]; //people
			}
			if (i % 2 != 0 && pnn->S2[i] == 1)
			{
				tot4 += M1[i];  //money
			}
		}
		//cout << "tot1 : " << tot1 << endl;
		//cout << "tot2 : " << tot2 << endl;
		//cout << "tot3 : " << tot3 << endl;
		//cout << "tot4 : " << tot4 << endl;
		if (tot1 <= tot2 && tot3 <= tot4)
		{
			F = 1;
			//cout << "Legal :" << endl;
			//cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
			//cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl << endl;
		}
		else
		{
			if (pnn->S2[0] == 0 && pnn->S2[2] == 0 && pnn->S2[4] == 0) 
			{
				F = 1;
			}
			if (pnn->S1[0] == 0 && pnn->S1[2] == 0 && pnn->S1[4] == 0)
			{
				F = 1;
			}
		}
	
	return F;
	
}

void ExpandChildren(CNode *pCurr,CStack &S,CList &Visit,int &ct)
{
	//Visit.Attach(pCurr);
	//Visit.Display();
	Visit.Attach(pCurr);
	//cout << "Added to visited list" << endl;
	int C=0,Visited=1;
	//boat = 0;
	
	if (pCurr->boat==0)
	{	
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 6; i++)
			{
				//cout << "Man :" << C << endl;
				if (pCurr->S1[C] == 1 && pCurr->S1[i] == 1 )
				{
					CNode* pnn = new CNode;
					for (int j = 0; j < 6; j++)
					{
						pnn->S1[j] = pCurr->S1[j];
						pnn->S2[j] = pCurr->S2[j];
					}
					pnn->pNext = NULL;

		
					pnn->S1[i] = 0;
					pnn->S2[i] = 1;
					pnn->S1[C] = 0;
					pnn->S2[C] = 1;

					pnn->boat = 1;
					//cout << "Boat : " << pnn->boat << endl;
					//cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
					//cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl;

					int Legal = IsLegal(pnn);
					//cout << "Legal : " << Legal << endl;
					if (Legal == 1)
					{
						Visited = IsVisited(pnn, Visit,ct);
						//cout << "Visited : " << Visited << endl;
						if (Visited == 0)
						{
							cout << "Boat: " << pnn->boat << endl;
							cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
							cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl;
							system("pause");
							cout << endl;
							cout << "Node has been pushed"<<endl;
							S.Push(pnn);
						}
					}
					//cout << "Visited : " << Visited << endl;
					//system("pause");
					//cout << endl;
				}

			}
			C += 2;
		}
		//boat = 0;
	}
	else
	{
		C = 0;
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < 6; i++)
			{
				//cout << "Man :" << C << endl;
				if (pCurr->S2[C] == 1 && pCurr->S2[i] == 1)
				{
					CNode* pnn = new CNode;
					for (int j = 0; j < 6; j++)
					{
						pnn->S1[j] = pCurr->S1[j];
						pnn->S2[j] = pCurr->S2[j];
					}
					pnn->pNext = NULL;


					pnn->S1[i] = 1;
					pnn->S2[i] = 0;
					pnn->S1[C] = 1;
					pnn->S2[C] = 0;
					//cout << "What's The Hell !!" << endl;


					pnn->boat = 0;
					//cout << "Boat : " << pnn->boat << endl;
					//cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
					//cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl;
					int Legal = IsLegal(pnn);
					//cout << "Legal : " << Legal << endl;
					if (Legal == 1)
					{
						Visited = IsVisited(pnn, Visit,ct);
						//cout << "Visited : " << Visited << endl;

						if (Visited == 0)
						{
							cout << "Boat: " << pnn->boat << endl;
							cout << "S1: " << pnn->S1[0] << pnn->S1[1] << pnn->S1[2] << pnn->S1[3] << pnn->S1[4] << pnn->S1[5] << endl;
							cout << "S2: " << pnn->S2[0] << pnn->S2[1] << pnn->S2[2] << pnn->S2[3] << pnn->S2[4] << pnn->S2[5] << endl;
							system("pause");
							cout << endl;
							cout << "Node has been pushed"<<endl;
							S.Push(pnn);
						}
					}
					//cout << "Visited : " << Visited << endl;
					//system("pause");
					//cout << endl;
				}
			}
			C += 2;
		}
		//boat = 1;
	}

}


int Check(CNode* pnn)
{
	int F = 0;
	for (int i = 0; i < 6; i++)
	{
		if (pnn->S2[i] != 1)
		{
			F = 1;
			break;
		}
	}
	return F;
}
void BackTracking()
{
	//int boat = 1;
	int ct = 0;
	CStack S;
	CList Visit;
	CNode* pnn = CreateInitState();
	S.Push(pnn);

	//else tracing
	//CNode* pnn1;pnn1 = new CNode[1];
	//pnn1->S1[0] = 0;pnn1->S1[1] = 1;pnn1->S1[2] = 1;pnn1->S1[3] = 1;pnn1->S1[4] = 1;pnn1->S1[5] = 1;
	//pnn1->S2[0] = 1;pnn1->S2[1] = 0;pnn1->S2[2] = 0;pnn1->S2[3] = 0;pnn1->S2[4] = 0;pnn1->S2[5] = 0;
	//S.Push(pnn1);

	while (S.pHead != NULL)
	{
		CNode* pCurr = S.Pop();
		cout << "Pop : " << endl;
		cout << "S1:" << pCurr->S1[0] << pCurr->S1[1] << pCurr->S1[2] << pCurr->S1[3] << pCurr->S1[4] << pCurr->S1[5]<< endl;
		cout << "S2:" << pCurr->S2[0] << pCurr->S2[1] << pCurr->S2[2] << pCurr->S2[3] << pCurr->S2[4] << pCurr->S2[5] << endl;
		cout << "Boat: " << pnn->boat << endl << endl;
		//system("pause");
		cout << endl;
		//S.Display();
		ExpandChildren(pCurr, S, Visit,ct);
		if (Check(pCurr) == 0)
		{
			//S.Display();
			cout << "True"<<endl;
			break;
		}
	}
	cout << "Out Of Loop" << endl;

}


int main()
{
	BackTracking();
	system("pause");
}