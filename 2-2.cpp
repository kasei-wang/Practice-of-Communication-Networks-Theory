#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    string readFileName;
    int iSourceVertexID ;
    cout << "readFileName:" ;
    cin >> readFileName ;
    cout << "SourceVertexID:" ;
    cin >> iSourceVertexID ;
    CGraph xxx(readFileName);
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    xxx.DijkstraAlgBeta(iSourceVertexID);
    return 0;
}
