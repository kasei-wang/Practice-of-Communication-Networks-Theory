#include "common.h"
using namespace std;

class CPath
{
private:
    int iHop,iLength;
    vector<vector<int> > vecPathDistence;
public:
    CPath()
    {
        iHop = 0;
        iLength = 0;
    }
    CPath(vector<vector<int> > vecPathDistenceInput)
    {
        int i;
        iLength = 0;
        vecPathDistence=vecPathDistenceInput;
        iHop = vecPathDistence.size();
        for(i=0; i<iHop; ++i) {
            iLength+=vecPathDistenceInput[i][1];
        }
    }
    CPath(CPath &x)
    {
        iHop = x.iHop;
        iLength = x.iLength;
        vecPathDistence = x.vecPathDistence;
    }
    void push_back(pair<int,int> vertex)
    {
        vecPathDistence.push_back(vector<int>(2,0));
        (*(vecPathDistence.end()-1))[0] = vertex.first ;
        (*(vecPathDistence.end()-1))[1] = vertex.second ;
        ++iHop;
        iLength+=vertex.second;
    }
    int getHop()
    {
        return iHop;
    }
    int getLength()
    {
        return iLength;
    }
    void PrintScreen()
    {
        int i;
        cout << "> Hop:" << iHop << "\t";
        cout << "> Length:" << iLength << endl;
        cout << "> Path:    " ;
        for(i=iHop-1; i>0; --i) {
            cout << vecPathDistence[i][0] << "->" ;
        }
        cout << vecPathDistence[0][0] ;
        cout << endl << "> Distence:" ;
        for(i=iHop-1; i>0; --i) {
            cout << vecPathDistence[i][1] << "->" ;
        }
        cout << vecPathDistence[0][1] ;
        cout << endl;
    }
};
