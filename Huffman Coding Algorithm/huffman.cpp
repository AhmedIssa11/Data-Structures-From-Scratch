#include<iostream>
#include<fstream>
#include<string>
using namespace std;


class CNode {

public:

    char CaD;
    int info;
    long length;
    char letter[258];
    char bits[258];
    CNode* pNext;
    CNode* pDownLeft;
    CNode* pDownRight;
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
            pTail->pNext = NULL;

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
};

class CList {

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
            pTrav = NULL;
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
        }
        else
        {
            pHead = pTrav->pNext;
        }

        delete pTrav;
    }


};

class CTree {

public:
    CNode* pRoot;
    CNode* pCurr1;
    CNode* pCurr2;

    CTree()
    {
        pRoot = NULL;
    }

    ~CTree()
    {
        Bye(pRoot);
    }

    void Bye(CNode* pT)
    {
        if (pT == NULL)
        {
            return;
        }

        Bye(pT->pDownLeft);
        Bye(pT->pDownRight);
        delete pT;
    }



};

void Disp(CNode* pT) {

    if (pT == NULL)
    {
        return;
    }

    if (pT != NULL)    
    {
        Disp(pT->pDownLeft);
    }
    cout << "  [" << pT->letter << "] " << pT->info << "  " << endl;
    Disp(pT->pDownRight);

}

void Code(CNode* pT, CNode* pB, char b[], int i, int& k, CList& L, int c) {

    if (pT == NULL)
    {
        return;
    }



    if (i > 0 && k == 1)
    {
        c++;
        b[c] = '0';
        b[c + 1] = '\0'; 
    }
    else if (k == 0)
    {
        c++;
        b[c] = '1';
        b[c + 1] = '\0'; 
    }


    i++;
    pB = pT;
    k = 1;
    Code(pT->pDownLeft, pB, b, i, k, L, c);

    for (int j = 0; b[j] != '\0'; j++)
    {
        pT->bits[j] = b[j];
    }
    if (pT->pDownLeft == NULL && pT->pDownRight == NULL)
    {
//        cout << endl << " [";
//        cout << pT->letter[0] << "] Repeated= " << pT->info << "   Code= ";
        for (int j = 0; pT->bits[j] != '\0'; j++)
        {
//            cout << pT->bits[j];
        }

        CNode* pnn = new CNode;

        pnn->letter[0] = pT->letter[0];

        pnn->info = pT->info;
        for (int j = 0; pT->bits[j] != '\0'; j++)
        {
            pnn->bits[j] = pT->bits[j];
        }

        L.Attach(pnn);
        return;
    }



    k = 0;
    pB = pT;
    Code(pT->pDownRight, pB, b, i, k, L, c);


}


int main()
{
    ifstream fileIn;
    ofstream fileComp;
    ofstream fileDecomp;
    string text = "";
    CNode* pnn0 = NULL;
    CNode* pnn = NULL;
    CList L;
    CList L2;
    CList LTemp;
    CStack S;
    CTree T;
    int ct = 0;
    int f = 0;
    int accessed = 0;
    long min = 99999999;

    fileIn.open("Put any file here", ifstream::binary);
    
        fileIn.seekg (0, fileIn.end);
        long E = fileIn.tellg();
        fileIn.seekg (0, fileIn.beg);
        char ch;
        for (int i = 0; i < E; i++)
        {
            fileIn.read (&ch , 1);
            text += ch;
        }
    
    
    if (!fileIn.is_open())
    {
        cout << "File not exists." << endl << endl;
    }
    else
    {
//        while (getline(data, text)) {}

        for (int i = -255; i < 256; i++)
        {
                ct = 0;
                for (long j = 0; j < E; j++)
                {
                    if (text[j] == i)
                    {
                        ct++;
                        pnn0 = new CNode;
                        pnn0->letter[0] = text[j];
                        pnn0->pNext = NULL;
                        accessed = 1;
                    }
                }

                if (accessed == 1)
                {
                    pnn0->info = ct;
                    LTemp.Attach(pnn0);
                    accessed = 0;
                }

        }

        CNode* pTrav = LTemp.pHead;
        int ctotal = 0;
        while (pTrav != NULL)
        {
            ctotal++;
            pTrav = pTrav->pNext;
        }

        pTrav = LTemp.pHead;
        CNode* pTemp = LTemp.pHead;
        CNode* pSelect = LTemp.pHead;
        CNode* pB1 = LTemp.pHead;
        CNode* pB2 = LTemp.pHead;
        int i;
        int a;
        for (int k = 0; k < ctotal; k++)
        {
            i = 0;
            pTemp = LTemp.pHead;
            a = 0;
            min = 99999999999;
            while (pTemp != NULL)
            {
                i++;

                if (pTemp->info < min)
                {
                    min = pTemp->info;
                    pSelect = pTemp;
                    pB2 = pB1;
                    a = i;
                }

                if (pTemp->pNext == NULL)
                {
                    break;
                }
                pB1 = pTemp;
                pTemp = pTemp->pNext;
            }

            if (a == 1)
            {
                LTemp.pHead = pSelect->pNext;
                L.Attach(pSelect);
                pSelect = NULL;

            }

            else if (a == ctotal)
            {

                LTemp.pTail = pB2;
                LTemp.pTail->pNext = NULL;
                pSelect->pNext = NULL;
                L.Attach(pSelect);
                pSelect = NULL;
            }
            else
            {
                
                pB2->pNext = pSelect->pNext;
                pSelect->pNext = NULL;
                L.Attach(pSelect);
                pSelect = NULL;
                
                
            }
        }
        
        cout << endl;
        pTrav = L.pHead;
        int ctletters = 0;
        int All = 0;
        while (pTrav != NULL)
        {
            ctletters++;
            cout << " letter [" << pTrav->letter[0] << "] Repeated= " << pTrav->info << " Time(s)";
            cout << endl;
            All += pTrav->info;
            CNode* pnn00 = new CNode;
            pnn00->letter[0] = pTrav->letter[0];
            pnn00->info = pTrav->info;
            pnn00->bits[0] = pTrav->bits[0];
            L2.Attach(pnn00);
            pTrav = pTrav->pNext;
        }
        cout << endl;
        cout << " letters used are " << ctletters << endl;
        cout << " All read letters = " << All << endl;
        cout << " All actual letters = " << E << endl;
        cout << "___________________________\n\n Processing: \n";
        pTrav = L.pHead;
        pTemp = L.pHead;
        CNode* pB = L.pHead;
        
        if(pTrav->pNext == NULL)
        {
            pnn = new CNode;
            pnn->letter[0] = pTrav->letter[0];
            pnn->info = pTrav->info;
            pnn->bits[0] = '1';
            LTemp.pHead = pnn;
            cout << "\n PNN: [";
            cout << pnn->letter[0];
            cout << "] Total= " << pnn->info << endl;
        }

        while (pTrav->pNext != NULL)
        {
            pnn = new CNode;
            int T = 0;
            for (int n = 0; pTrav->letter[n] != '\0'; T++, n++)
            {
                pnn->letter[T] = pTrav->letter[n];
            }

            for (int n = 0; pTrav->pNext->letter[n] != '\0'; T++, n++)
            {
                pnn->letter[T] = pTrav->pNext->letter[n];
            }

            pnn->pDownLeft = pTrav;
            pnn->pDownRight = pTrav->pNext;
            pnn->info = pTrav->info + pTrav->pNext->info;
            f = 0;
            cout << "\n PNN: [";
            for (int n = 0; pnn->letter[n] != '\0'; n++)
            {
                cout << pnn->letter[n];
            }
            cout << "] Total= " << pnn->info << endl;
            if (pTrav->pNext->pNext != NULL)
            {
                f = 0;
                pTemp = pTrav->pNext->pNext;
                if (pTemp->pNext != NULL)
                {
                    while (pTemp->pNext != NULL)
                    {
                        if ((pnn->info > pTemp->info&& pnn->info < pTemp->pNext->info) || (pnn->info == pTemp->info && pnn->info < pTemp->pNext->info) || (pnn->info > pTemp->info&& pnn->info == pTemp->pNext->info))
                        {
                            pnn->pNext = pTemp->pNext;
                            pTemp->pNext = pnn;
                            f = 1;
                            break;
                        }



                        else if (pnn->info < pTrav->pNext->pNext->info)
                        {
                            pnn->pNext = pTemp;
                            L.pHead = pnn;
                            f = 1;
                            break;
                        }
                        pB = pTemp;
                        pTemp = pTemp->pNext;
                    }
                    if (f == 0)
                    {
                        pnn->pNext = NULL;
                        L.pTail->pNext = pnn;
                        L.pTail = pnn;
                    }

                }

                else if (pTemp->pNext == NULL && pTemp != NULL)
                {
                    while (pTemp != NULL)
                    {
                        if (pnn->info > pTemp->info)
                        {
                            pTemp->pNext = pnn;
                            pnn->pNext = NULL;
                            break;
                        }
                        else
                        {
                            pTrav->pNext->pNext = pnn;
                            pnn->pNext = pTemp;
                            break;
                        }
                        pTemp = pTemp->pNext;
                    }
                }
            }
            else
            {
                pnn->pNext = NULL;
                L.pHead = pnn;
                cout <<  " Last Head: [" << L.pHead->letter << "] Repeated= " << L.pHead->pDownLeft->info + L.pHead->pDownRight->info << endl;
                break;
            }

            pB = pTrav;
            pTrav = pTrav->pNext->pNext;
            cout <<  " Next Head: [" << pTrav->letter << "]  Repeated= " << pTrav->info << endl;          // Little check...
            L.pHead = pTrav;
        }
        
       


        cout << endl;
        cout << "___________________________\n\n";
        pTrav = L.pHead;
        cout << " The Tree Display: \n\n";
        Disp(pTrav);            // To check whether I am true or not...
        cout << endl;
        cout << "___________________________\n";
        pTrav = L.pHead;
        pB = L.pHead;
        char b[258];
        int j = 0;
        int k = 1;
        int c = -1;
        CList L3;
        CList L4;
        Code(pTrav, pB, b, j, k, L3, c);

        cout << "\n Ordered List With Code (bits): \n";

        pTrav = L2.pHead;
        pTemp = L3.pHead;
        while (pTrav != NULL)
        {
            pTemp = L3.pHead;

            while (pTemp != NULL)
            {
                if (pTrav->letter[0] == pTemp->letter[0])
                {
                    cout << endl << " [" << pTemp->letter << "] Repeated= " << pTemp->info << "   Code= " << pTemp->bits;
                    pnn = new CNode;
                    for (int n = 0; pTemp->letter[n] != '\0'; n++)
                    {
                        pnn->letter[n] = pTemp->letter[n];
                    }

                    pnn->info = pTemp->info;

                    for (int n = 0; pTemp->bits[n] != '\0'; n++)
                    {
                        pnn->bits[n] = pTemp->bits[n];
                    }
                    pnn->pNext = NULL;
                    L4.Attach(pnn);
                    break;
                }
                pTemp = pTemp->pNext;
            }
            pTrav = pTrav->pNext;
        }
        char choice1;
        cout << "\n\n---------------------------\n\n Do you want to Compress your file? ENTER y for YES : ";
        cin >> choice1;
        cout<<endl;
        if(choice1 == 'y' || choice1 == 'Y')
        {
            fileComp.open("/Users/mahmoud/Desktop/Compressed.txt");
            L4.pHead->length = E;

            int iBit = 7;
            char Temp = 0;
            CList LComp;
            CNode* pnnComp;
            char m = 1;
            int MCount = 0;
            cout<<endl;
            for (int i = 0; i < text.length(); i++)
            {
                pTrav = L4.pHead;
                while (pTrav != NULL)
                {
                    if (pTrav->letter[0] == text[i])
                    {
//                        cout<<text[i];
                        for (int j = 0; pTrav->bits[j] != '\0'; j++)
                        {
                            if (pTrav->bits[j] == '1')
                            {
                                Temp = Temp | (m << iBit);
                            }
                            
                            iBit--;
                            if (iBit < 0)
                            {
                                MCount++;
                                pnnComp = new CNode;
                                pnnComp->CaD = Temp;
                                pnnComp->pNext = NULL;
                                LComp.Attach(pnnComp);
                                fileComp << pnnComp->CaD;
                                int O = pnnComp->CaD;
//                                cout<< " [" << O << "]  ";
                                iBit = 7;
                                Temp = 0;
                            }
                        }
                    }
                    pTrav = pTrav->pNext;
                }
                if(i == text.length() - 1 && iBit < 7)
                {
                    MCount++;
                    pnnComp = new CNode;
                    pnnComp->CaD = Temp;
                    pnnComp->pNext = NULL;
                    LComp.Attach(pnnComp);
                    fileComp << pnnComp->CaD;
                    int O = pnnComp->CaD;
//                    cout<< " [" << O << "]  ";
                    break;
                }
            }
            
            int W;
            CNode* pC = LComp.pHead;
            cout<<" [ File Compressed Successfully ] \n\n Go and Check the Compressed.txt file in your Desktop...";
            fileComp.close();
            fileIn.close();
            
            cout << endl << endl;
            char choice2;
            cout << "\n---------------------------\n\n Do you want to DeCompress your file? ENTER y for YES : ";
            cin >> choice2;
            cout<<endl<<endl;
            
            if(choice2 == 'y' || choice2 == 'Y')
            {
                fileDecomp.open("/Users/mahmoud/Desktop/DeComp.psd", ofstream::binary);

                CList LDeComp;
                CNode* pnnDeComp;
                char TempBits[258];
                iBit = 7;
                pTrav = L4.pHead;
                int NB = 0;
                m = 1;
                int count1 = 0;
                int count2 = 0;
                int count3 = 0;
                
                pC = LComp.pHead;
                for (int i = 0; i < MCount;)
                {
                    Temp = pC->CaD;
                    char Result = Temp & (m << iBit);
            
                    if (Result != 0 || Result != '\0')
                    {
                        TempBits[NB] = '1';
                    }
                    else
                    {
                        TempBits[NB] = '0';
                    }
                    NB++;
                    pTemp = L4.pHead;
                    while (pTemp != NULL)
                    {
                        for (int k = 0; TempBits[k] != '\0'; k++)
                        {
                            count1++;
                        }
                        for (int k = 0; pTemp->bits[k] != '\0'; k++)
                        {
                            count2++;
                        }
                        if (count1 == count2)
                        {
                            for (int k = 0; k < count1; k++)
                            {
                                if (pTemp->bits[k] == TempBits[k])
                                {
                                    count3++;
            
                                if (count3 == count1)
                                {
                                    pnnDeComp = new CNode;
                                    pnnDeComp->CaD = pTemp->letter[0];
                                    pnnDeComp->pNext = NULL;
                                    LDeComp.Attach(pnnDeComp);
                                    fileDecomp << pnnDeComp->CaD;
                                    for (int y = 0; TempBits[y] != '\0'; y++)
                                    {
                                        TempBits[y] = '\0';
                                    }
                                    NB = 0;
                                    break;
                                }
                                }
                            }
                        }
                    count1 = 0;
                    count2 = 0;
                    count3 = 0;
                    pTemp = pTemp->pNext;
                }
            
                    iBit--;
                    count1 = 0;
                    count2 = 0;
                    count3 = 0;
                    
                if (iBit < 0)
                {
                    iBit = 7;
                    pC = pC->pNext;
                    i++;
                    
                }

            
            }
                
            
                cout<<" [ File DeCompressed Successfully ] \n\n Go and Check the DeCompressed.png file in your Desktop...";
            }
            else
            {
                fileDecomp.close();
                cout << "\n\n\n\n\n";
                   return(0);
            }
        }
        else
        {
            fileDecomp.close();
            cout << "\n\n\n\n\n";
               return(0);
        }
        
        fileDecomp.close();
        cout << "\n\n\n\n\n";
           return(0);
    }
   
}
