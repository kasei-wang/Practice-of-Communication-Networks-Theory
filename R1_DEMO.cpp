/*
    对比DijkstraAlg和DijkstraAlgDial计算速度。
    共有3个参数：输入文件名、源节点、宿节点。
*/
#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    string readFileName;
    CPath Result;
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
        iTailVertexID = atoi(argv[3]);
    }
    clock_t AClock,BClock,CClock,DClock;
    CGraph xxx(readFileName);
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;

    AClock = clock();
    Result=xxx.DijkstraAlg(iSourceVertexID,iTailVertexID,0);
    BClock = clock();
    Result.PrintScreen();

    CClock = clock();
    Result=xxx.DijkstraAlgDial(iSourceVertexID,iTailVertexID,0);
    DClock = clock();
    Result.PrintScreen();

    cout << "Time:    " <<  (double)(BClock-AClock)/CLOCKS_PER_SEC << endl;
    cout << "TimeDial:" <<  (double)(DClock-CClock)/CLOCKS_PER_SEC << endl;
    return 0;
}
