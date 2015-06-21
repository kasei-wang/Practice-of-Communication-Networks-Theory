#include "common.h"
using namespace std;

int main(int argc,char *argv[])
{
    double alpha,beta;
    if(argc == 1)
    {
        cout << "Alpha:" ;
        cin >> alpha ;
        cout << "Beta:" ;
        cin >> beta ;
    }
    else if(argc > 3 || argc==2 )
    {
    	   cerr <<"Useage: "<<argv[0]<<" [Alpha] [Beta] \n \t or Run "<<argv[0]<<" Directly."<<endl;
    	   return 0;
    }
    else
    {
        alpha = atof(argv[1]);
        beta = atof(argv[2]);
    }
	CGraph xxx(100,100, alpha ,beta );
	cout << "结点数：" << xxx.getVertex() << endl;
	cout << "边数：" << xxx.getEdge() << endl;
	xxx.getFile();
    xxx.getTaoYuFile();
    xxx.getLingoFile();
	return 0;
}
