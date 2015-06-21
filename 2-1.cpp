#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    string readFileName;
    clock_t a,b;
    int iSourceVertexID ,iTailVertexID;
    cout << "readFileName:" ;
    cin >> readFileName ;
    cout << "SourceVertexID:" ;
    cin >> iSourceVertexID ;
    cout << "TailVertexID:" ;
    cin >> iTailVertexID ;
    CGraph xxx(readFileName);
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    a = clock();
    xxx.DijkstraAlg(iSourceVertexID,iTailVertexID,0);
    b = clock();
    cout << "Time:" <<  (double)(b-a)/CLOCKS_PER_SEC << endl;
    return 0;
}
