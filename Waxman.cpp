#include "common.h"
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
