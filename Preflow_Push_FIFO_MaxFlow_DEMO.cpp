#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    CGraph xxx("sample.txt");
    cout << "结点数：" << xxx.getVertex() << endl;
    cout << "边数：" << xxx.getEdge() << endl;
    xxx.Preflow_Push_FIFO_MaxFlow(1,5);
    return 0;
}
