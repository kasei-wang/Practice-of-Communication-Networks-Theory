#include "common.h"
using namespace std;

class CPath
{
private:
    int iHop,iLength;
    vector<vector<int> > vecPathDistence;
public:
    CPath(vector<vector<int> > vecPathDistenceInput)
    {
        vecPathDistence=vecPathDistenceInput;
        iHop = vecPathDistence.size();
        iLength = (*vecPathDistenceInput.end())[1];
    }
    CPath(CPath &x)
    {
        iHop = x.iHop;
        iLength = x.Length;
        vecPathDistence = x.vecPathDistence;
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
        cout << "Hop:" << iHop << endl;
        cout << "Length" << iLength << endl;
        cout << "Path:" ;
        for(i=0; i<iHop; ++i) {
            cout << vecPathDistence[i][0] ;
        }
        cout << endl << "Distence:" ;
        or(i=0; i<iHop; ++i) {
            cout << vecPathDistence[i][1] ;
        }
        cout << endl;
    }
}
