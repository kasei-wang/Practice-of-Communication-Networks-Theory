#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    string readFileName;
    int iSourceVertexID ,iMinCap;
    cout << "readFileName:" ;
    cin >> readFileName ;
    cout << "SourceVertexID:" ;
    cin >> iSourceVertexID ;
    cout << "MinCap:" ;
    cin >> iMinCap ;
    CGraph xxx(readFileName);
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    xxx.DijkstraAlg(iSourceVertexID,-1,iMinCap);
    return 0;
}
