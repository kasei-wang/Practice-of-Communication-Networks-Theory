/*
    对比DijkstraAlg和DijkstraAlgDial计算速度。
    读取十个样本图。每图随机取十对节点计算最短路。每次计算进行100次，取平均值输出。
    无参数。
*/﻿
#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    random_device rd;
    CPath Result;
    int i,j,k,iSourceVertexID,iTailVertexID;
    double Time,TimeDial;
    clock_t AClock,BClock;
    vector<string> FileName;
    FileName.push_back("output1");
    FileName.push_back("output2");
    FileName.push_back("output3");
    FileName.push_back("output4");
    FileName.push_back("output5");
    FileName.push_back("output6");
    FileName.push_back("output7");
    FileName.push_back("output8");
    FileName.push_back("output9");
    FileName.push_back("output10");

    for(i=0; i!=10; ++i) {
        CGraph TempGraph(FileName[i]);
        cout << ">>>节点数：" << TempGraph.getVertex() << endl ;
        cout << ">>>边数：  " << TempGraph.getEdge() << endl ;
        for(j=0; j!=10; ++j) {
            iSourceVertexID = rd() % TempGraph.getVertex() ;
            iTailVertexID = rd() % TempGraph.getVertex() ;
            cout << "Source:" << iSourceVertexID << "  \tTial:" << iTailVertexID << "  \t";
            for(k=0, Time=0, TimeDial=0 ; k<100; ++k) {
                AClock = clock();
                TempGraph.DijkstraAlg(iSourceVertexID,iTailVertexID,0);
                BClock = clock();
                Time+=(double)(BClock-AClock)/CLOCKS_PER_SEC;
                AClock = clock();
                TempGraph.DijkstraAlgDial(iSourceVertexID,iTailVertexID,0);
                BClock = clock();
                TimeDial+=(double)(BClock-AClock)/CLOCKS_PER_SEC;
            }
            cout << "Time:    " <<  Time/100 << " \t";
            cout << "TimeDial:" <<  TimeDial/100 << endl;
        }
    }
    return 0;
}
