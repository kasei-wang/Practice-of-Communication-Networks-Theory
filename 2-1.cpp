#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    string readFileName;
    int iSourceVertexID,iTailVertexID;
    if(argc == 1) {
        cout << "readFileName:" ;
        cin >> readFileName ;
        cout << "SourceVertexID:" ;
        cin >> iSourceVertexID ;
        cout << "TailVertexID:" ;
        cin >> iTailVertexID ;
    }
    else if(argc == 4){
        string strInput(argv[1]);
        readFileName=strInput;
        iSourceVertexID = atoi(argv[2]);
        //cout << iSourceVertexID << endl;
        iTailVertexID = atoi(argv[3]);
    }
    clock_t a,b;
    CGraph xxx(readFileName);
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    a = clock();
    xxx.DijkstraAlg(iSourceVertexID,iTailVertexID,0);
    xxx.DijkstraAlgDial(iSourceVertexID,iTailVertexID,0);
    b = clock();
    cout << "Time:" <<  (double)(b-a)/CLOCKS_PER_SEC << endl;
    return 0;
}
