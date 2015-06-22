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

}
