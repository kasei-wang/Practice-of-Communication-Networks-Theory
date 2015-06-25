/*
    waxman生成图，共有5个参数，分别为：矩阵边长、节点数目、alpha参数、beta参数、输出文件名。
    输出文件格式为：
    # VertexNum: 节点数
    # EdgeNUm:   边数
    起点;终点;属性1;属性2
    起点;终点;属性1;属性2
    ......
*/
﻿#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    unsigned int nMatrixSize,nVertexNum;
    double alpha,beta;
    string strFile;
    if(argc == 1)
    {
        cout << "MatrixSize:" ;
        cin >> nMatrixSize ;
        cout << "VertexNum:" ;
        cin >> nVertexNum ;
        cout << "Alpha:" ;
        cin >> alpha ;
        cout << "Beta:" ;
        cin >> beta ;
        cout << "OutoutFile:" ;
        cin >> strFile ;
    }
    else
    {
        nMatrixSize = atoi(argv[1]);
        nVertexNum = atoi(argv[2]);
        alpha = atof(argv[3]);
        beta = atof(argv[4]);
        string strOutput(argv[5]);
        strFile = strOutput;
    }
    CGraph xxx( nMatrixSize, nVertexNum, alpha, beta );
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    xxx.getFile(strFile);
    return 0;
}
