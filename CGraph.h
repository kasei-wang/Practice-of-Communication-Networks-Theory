#include "common.h"

using namespace std;

class CGraph
{
private:
    unsigned int nVertex;
    list<int> lstVertex;
    list<CEdge*> plstIncident;
    vector<vector<int> > vecGraphWeight;

    //根据边list建立节点list并统计节点数目
    void buildlstVertex()
    {
        //建立list迭代器，重置结点数目为0，清空结点列表
        list<CEdge*>::iterator k;
        nVertex = 0;
        lstVertex.clear();
        //遍历边的list
        for (k = plstIncident.begin(); k != plstIncident.end(); ++k) {
            //查找点的list，未发现边的起点/终点则将其插入结点list
            if (find(lstVertex.begin(), lstVertex.end(), (**k).getHead()) == lstVertex.end()) {
                lstVertex.push_back((*k)->getHead());
                ++nVertex;
            }
            if (find(lstVertex.begin(), lstVertex.end(), (**k).getTail()) == lstVertex.end()) {
                lstVertex.push_back((*k)->getTail());
                ++nVertex;
            }
        }
        lstVertex.sort();
        return;
    }

    void MapVertexID()
    {
        //将结点ID映射到连续整数
        int i=0;
        map<int,int> mapVertexID;
        list<int> lstVertexAfterMap=lstVertex;
        for(i=0;i<nVertex;++i) {
            mapVertexID.insert(pair<int,int>(lstVertexAfterMap.front(),i));
            lstVertexAfterMap.pop_front();
        }
        lstVertexAfterMap.clear();

        list<int>::iterator itelstVertex=lstVertex.begin();
        list<CEdge*>::iterator iteplstIncident=plstIncident.begin();

        //映射Vertex列表
        for(;itelstVertex!=lstVertex.end();++itelstVertex) {
            lstVertexAfterMap.push_back( mapVertexID.find(*itelstVertex)->second );
        }
        lstVertex=lstVertexAfterMap;

        //映射Incident列表
        for(;iteplstIncident!=plstIncident.end();++iteplstIncident) {
            (**iteplstIncident).setHead( mapVertexID.find( (**iteplstIncident).getHead() )->second );
            (**iteplstIncident).setTail( mapVertexID.find( (**iteplstIncident).getTail() )->second );
        }
    }


    void buildvecGraphWeight()
    {
        vector<vector<int> > vecGraph(lstVertex.size(), vector<int>(lstVertex.size(),0));
        list<CEdge*>::iterator iteIncident;
        for(iteIncident=plstIncident.begin();iteIncident!=plstIncident.end();++iteIncident) {
            vecGraph[(**iteIncident).getHead()][(**iteIncident).getTail()]=(**iteIncident).getWeight();
            vecGraph[(**iteIncident).getTail()][(**iteIncident).getHead()]=(**iteIncident).getWeight();
        }
        vecGraphWeight=vecGraph;
    }

    void clearplstIncident()
    {
        list<CEdge*>::iterator itepIncident;
        for(itepIncident=plstIncident.begin(); itepIncident!=plstIncident.end(); ++itepIncident){
            delete *itepIncident;
        }
        plstIncident.clear();
    }

    //ER图生成算法
    void ER(unsigned int nERVertex, unsigned int nEREdge)
    {
        clearplstIncident();
        std::random_device rd;
        unsigned int uEdge , uTmp=nERVertex*nERVertex,uHead,uTail;
        list<unsigned int> lstuIDEdge;
        do {
            uHead=rd()%nERVertex;
            uTail=rd()%uHead;
            if(uHead!=uTail) {
                plstIncident.push_back(new CEdge( uHead ,uTail, rd()%100 , rd()%100 ));
            }
        }
        while (plstIncident.size() < nEREdge);

        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
        return;
    }

    //Waxman生成算法
    void Waxman(unsigned int nMatrixEdgeSize,unsigned int nWaxmanVertex, double alpha,double beta)
    {
        beta=1/(beta*nMatrixEdgeSize*sqrt(2));
        clearplstIncident();
        std::random_device rd;
        float arrVertexP[nWaxmanVertex][nWaxmanVertex];
        vector<int> vecWaxmanVertex;
        unsigned int m,i,j;
        do {
            m = rd() % (nMatrixEdgeSize*nMatrixEdgeSize);
            if (find(vecWaxmanVertex.begin(), vecWaxmanVertex.end(),m) == vecWaxmanVertex.end())
                vecWaxmanVertex.push_back(m);
        }
        while (vecWaxmanVertex.size() < nWaxmanVertex);
        sort(vecWaxmanVertex.begin(), vecWaxmanVertex.end());
        for(i=0; i<nWaxmanVertex; ++i)
            for(j=i,++j; j<nWaxmanVertex; ++j) {
                arrVertexP[i][j]=sqrt(pow(vecWaxmanVertex[j]%nMatrixEdgeSize - vecWaxmanVertex[i]%nMatrixEdgeSize ,2)+pow( vecWaxmanVertex[j]/nMatrixEdgeSize - vecWaxmanVertex[i]/nMatrixEdgeSize ,2 ));
                if( (double)(alpha*exp(-arrVertexP[i][j]*beta)) > (double)(rd()%RAND_MAX)/RAND_MAX )
                    plstIncident.push_back(new CEdge(vecWaxmanVertex[i],vecWaxmanVertex[j],arrVertexP[i][j],rd()%nMatrixEdgeSize));
        }
        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
        return;
    }
    void CapacityConstraint(int minCap)
    {
        int i,j;
        list<CEdge*>::iterator iteplstIncident;
        for(iteplstIncident=plstIncident.begin(); iteplstIncident != plstIncident.end();) {
            if( (**iteplstIncident).getCap() < minCap ) {
                delete *iteplstIncident;
                iteplstIncident = plstIncident.erase(iteplstIncident);
            }
            else
                ++iteplstIncident;
        }
        buildlstVertex();
        buildvecGraphWeight();
    }

public:
    CGraph(unsigned int nERVertex,unsigned int nEREdge)
    {
        do {
            ER(nERVertex,nEREdge);
        }
        while (getConnectivityBFS()==0);
        MapVertexID();
    }
    CGraph(unsigned int nMatrixEdge, unsigned int nWaxmanVertex,double alpha,double beta)
    {
        unsigned int n=0;
        do {
            n++;
            Waxman(nMatrixEdge,nWaxmanVertex,alpha,beta);
        }
        while (getConnectivityBFS()==0);
        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
        cout << "生成次数" << n << endl;
    }
    CGraph()
    {
        return;
    }
    CGraph(list<CEdge*> plstEdge)
    {
        plstIncident=plstEdge;
        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
    }
    CGraph(string inputfile)
    {
        clearplstIncident();
        char chrSplit1=';';
        string strCEdge;
        unsigned int istrCEdge,iLengthstrCEgde,iFlagstrCEdge;
        vector<int> CEdgeMember;
        ifstream file;
        file.open(inputfile,ios::in);
        if(!file) {
            cerr << "ERROR! Unable to Read File !" << endl;
            return;
        }
        while(file.peek()!=EOF) {
            getline(file,strCEdge);
            if( strCEdge[0] != '#' ) {
                iLengthstrCEgde=strCEdge.length();
                CEdgeMember.clear();
                for(istrCEdge=0,iFlagstrCEdge=0; istrCEdge<=iLengthstrCEgde; ++istrCEdge) {
                    if(strCEdge[istrCEdge]==chrSplit1||istrCEdge==iLengthstrCEgde) {
                        CEdgeMember.push_back(atoi((strCEdge.substr(iFlagstrCEdge,istrCEdge-iFlagstrCEdge)).c_str()));
                        iFlagstrCEdge=istrCEdge+1;
                    }
                }
                plstIncident.push_back(new CEdge(CEdgeMember[0],CEdgeMember[1],CEdgeMember[2],CEdgeMember[3]));
            }
        }
        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
    }
    CGraph(vector<vector<int> > vecGraphWeightInput)
    {
        vecGraphWeight = vecGraphWeightInput;
        int i,j,ivecGraphWeightXSize=vecGraphWeightInput.size(),ivecGraphWeightYSize;
        vector<int>::iterator itevecGraphWeightY;
        for(i=0; i<ivecGraphWeightXSize; ++i) {
            for(ivecGraphWeightYSize = vecGraphWeightInput[i].size(), j=0; j<ivecGraphWeightYSize; ++j) {
                if( vecGraphWeightInput[i][j] != 0 ) {
                    plstIncident.push_back(new CEdge(i,j,vecGraphWeightInput[i][j]));
                }
            }
        }
        buildlstVertex();
    }
    CGraph(CGraph &x)
    {
        nVertex=x.nVertex;
        lstVertex=x.lstVertex;
        plstIncident=x.plstIncident;
        buildlstVertex();
        MapVertexID();
        buildvecGraphWeight();
    }
    ~CGraph()
    {
        clearplstIncident();
    }
    int getVertex()
    {
        return nVertex;
    }
    int getEdge()
    {
        return plstIncident.size();
    }

    //连通性判断，使用广度优先遍历
    bool getConnectivityBFS()
    {
        //待搜索结点
        int iSearchVertex;
        deque<int> deqSearchVertex;
        deque<int> deqSearchVertexNext;
        //待遍历结点
        list<int> lstTempVertex=lstVertex;
        //待遍历边
        list<CEdge*> plstSearchIncident=plstIncident;
        list<CEdge*>::iterator iteIncident=plstSearchIncident.begin();
        //初始化待搜索结点列表，将一个结点从待遍历移至待搜索
        deqSearchVertex.push_back(lstTempVertex.front());
        lstTempVertex.remove(deqSearchVertex.back());
        //循环直到待搜索结点列表为空
        while(deqSearchVertex.empty()==false) {
            while(deqSearchVertex.empty()==false) {
                iSearchVertex = deqSearchVertex.front();
                for(iteIncident=plstSearchIncident.begin(); iteIncident!=plstSearchIncident.end(); ) {
                    if((**iteIncident).getHead() == iSearchVertex
                        && find(lstTempVertex.begin(),lstTempVertex.end(),(**iteIncident).getTail())!=lstTempVertex.end() ) {
                            deqSearchVertexNext.push_back((**iteIncident).getTail());
                            lstTempVertex.remove(deqSearchVertexNext.back());
                            iteIncident=plstSearchIncident.erase(iteIncident);
                    }
                    else ++iteIncident;
                }
                deqSearchVertex.pop_front();
            }
            deqSearchVertex=deqSearchVertexNext;
            deqSearchVertexNext.clear();
        }

        //若此时仍有未遍历点，为非联通，否则为联通
        if (lstTempVertex.empty()==false)
            return false;
        else
            return true;
    }

    CPath DijkstraAlg(int isourceVertex,int itailVertex,int iminCap)
    {
        unsigned int i,j;
        if(iminCap != 0) {
            CapacityConstraint(iminCap);
        }
        vector<vector<int> > vecGraph=vecGraphWeight;

        //init vecVertex by INFI DISTANCE
        vector<vector<int> > vecVertex(nVertex, vector<int>(2,10000000));
        vector<vector<int> > vecResultPath;
        //[0] PreVertex
        vecVertex[isourceVertex][0]=isourceVertex;
        //[1] Distance
        vecVertex[isourceVertex][1]=0;
        map<int,int>    mapMarkVertexPre;
        map<int,int>    mapMarkVertexDistence;
        map<int,int>::iterator itemapMarkVertex;

        //init mapMarkVertexDistence by INFI DISTANCE
        for(i=0 ;i<nVertex ; ++i) {
            mapMarkVertexDistence[i]=10000000;
        }
        mapMarkVertexDistence.erase(isourceVertex);

        //Update(source)
        for(itemapMarkVertex=mapMarkVertexDistence.begin();itemapMarkVertex!=mapMarkVertexDistence.end();++itemapMarkVertex) {
            if( vecGraph[itemapMarkVertex->first][isourceVertex] != 0 ) {
                mapMarkVertexPre[itemapMarkVertex->first]=isourceVertex;
                mapMarkVertexDistence[itemapMarkVertex->first] = vecGraph[itemapMarkVertex->first][isourceVertex];
            }
        }

        while(mapMarkVertexDistence.empty() != true) {
            j=mapMarkVertexDistence.begin()->first;
            for(itemapMarkVertex=mapMarkVertexDistence.begin();itemapMarkVertex!=mapMarkVertexDistence.end();++itemapMarkVertex) {
                if(mapMarkVertexDistence[j] > itemapMarkVertex->second)
                    j=itemapMarkVertex->first;
            }
            vecVertex[j][0]=mapMarkVertexPre[j];
            vecVertex[j][1]=mapMarkVertexDistence[j];
            mapMarkVertexPre.erase(j);
            mapMarkVertexDistence.erase(j);
            //Update(j)
            for(itemapMarkVertex=mapMarkVertexDistence.begin();itemapMarkVertex!=mapMarkVertexDistence.end();++itemapMarkVertex) {
                if( vecGraph[itemapMarkVertex->first][j] != 0 &&
                    vecGraph[itemapMarkVertex->first][j]+vecVertex[j][1] < itemapMarkVertex->second ) {
                    mapMarkVertexPre[itemapMarkVertex->first]=j;
                    mapMarkVertexDistence[itemapMarkVertex->first] = vecGraph[itemapMarkVertex->first][j]+vecVertex[j][1];
                }
            }
        }

        i=itailVertex;
        while( i != isourceVertex ) {
            vecResultPath.push_back(vector<int>(2,i));
            (*(vecResultPath.end()-1))[1] = vecVertex[i][1] ;
            i = vecVertex[i][0];
        }
        vecResultPath.push_back(vector<int>(2,i));
        (*(vecResultPath.end()-1))[1] = 0 ;
        CPath Result(vecResultPath);
        return Result;
    }
    CPath DijkstraAlgDial(int isourceVertex,int itailVertex,int iminCap)
    {
        unsigned int i,j;
        if(iminCap != 0) {
            CapacityConstraint(iminCap);
        }
        vector<vector<int> > vecGraph = vecGraphWeight;

        //init vecVertex by INFI DISTANCE
        vector<vector<int> > vecVertex(nVertex, vector<int>(2,10000000));
        vector<vector<int> > vecResultPath;
        //[0] PreVertex
        vecVertex[isourceVertex][0]=isourceVertex;
        //[1] Distance
        vecVertex[isourceVertex][1]=0;
        map<int,int>    mapMarkVertexPre;
        multimap<int,int> mmpMarkVertexDistence;
        multimap<int,int>::iterator itemmpMarkVertex,itemmpMarkVertexBegin;

        for(i=0 ;i<nVertex ; ++i) {
            if(i!=isourceVertex)
                mmpMarkVertexDistence.insert(pair<int,int>(10000000,i));
        }

        for(itemmpMarkVertex=mmpMarkVertexDistence.begin();itemmpMarkVertex!=mmpMarkVertexDistence.end();) {
            if( vecGraph[itemmpMarkVertex->second][isourceVertex] != 0 ) {
                mapMarkVertexPre[itemmpMarkVertex->second]=isourceVertex;
                mmpMarkVertexDistence.insert(pair<int,int>(vecGraph[itemmpMarkVertex->second][isourceVertex],itemmpMarkVertex->second));
                itemmpMarkVertex=mmpMarkVertexDistence.erase(itemmpMarkVertex);
            }
            else {
                ++itemmpMarkVertex;
            }
        }

        while( !mmpMarkVertexDistence.empty() ) {
            itemmpMarkVertexBegin=mmpMarkVertexDistence.begin();
            i=itemmpMarkVertexBegin->second;
            j=itemmpMarkVertexBegin->first;
            vecVertex[i][0]=mapMarkVertexPre[i];
            vecVertex[i][1]=j;

            mapMarkVertexPre.erase(i);
            mmpMarkVertexDistence.erase(itemmpMarkVertexBegin);

            //Update(i)
            for(itemmpMarkVertex=mmpMarkVertexDistence.begin();itemmpMarkVertex!=mmpMarkVertexDistence.end();) {
                if( vecGraph[itemmpMarkVertex->second][i] != 0 &&
                    vecGraph[itemmpMarkVertex->second][i]+j < itemmpMarkVertex->first ) {
                        mapMarkVertexPre[itemmpMarkVertex->second]=i;
                        mmpMarkVertexDistence.insert(pair<int,int>(vecGraph[itemmpMarkVertex->second][i]+j,itemmpMarkVertex->second));
                        itemmpMarkVertex=mmpMarkVertexDistence.erase(itemmpMarkVertex);
                }
                else {
                    ++itemmpMarkVertex;
                }
            }
        }

        i=itailVertex;
        while( i != isourceVertex ) {
            vecResultPath.push_back(vector<int>(2,i));
            (*(vecResultPath.end()-1))[1] = vecVertex[i][1] ;
            i = vecVertex[i][0];
        }
        vecResultPath.push_back(vector<int>(2,i));
        (*(vecResultPath.end()-1))[1] = 0 ;
        CPath Result(vecResultPath);
        return Result;
    }

    void DijkstraAlgBeta(int isourceVertex)
    {
        unsigned int i,j;
        list<int> TemplstVertex=lstVertex;

        vector<vector<float> > vecGraph(nVertex, vector<float>(3,0));
        for(i=0 ;i<nVertex ;++i )
            for(j=0 ;j<nVertex ;++j ) {
                vecGraph[i][j]=vecGraphWeight[i][j];
        }

        vector<vector<float> > vecVertex(nVertex, vector<float>(3,0));
        vector<vector<float> > vecMarkVertex;
        bool bolEmptyMarkVertex=false;
        for(i=0 ;i<nVertex ; ++i) {
            //ID
            vecVertex[i][0]=i;
            TemplstVertex.pop_front();
            //树上前继节点ID
            vecVertex[i][1]=0;
            //距离标记
            vecVertex[i][2]=0;
            //初始化源节点
            if( vecVertex[i][0] == isourceVertex ) {
                    vecVertex[i][1] = isourceVertex ;
                    vecVertex[i][2] = 1;
                }
        }

        vecMarkVertex=vecVertex;
        for(i=0 ; i < nVertex ; ++i) {
            if( vecMarkVertex[i][0] == isourceVertex ) {
                vecMarkVertex[i][0]=-1;
                    break;
            }
        }

        //Update(source)更新距离标记
        for(i=0 ; i < nVertex ; ++i) {
            if( vecGraph[i][isourceVertex] != 0 &&
                vecMarkVertex[i][0] != -1 &&
                vecGraph[i][isourceVertex]*vecMarkVertex[isourceVertex][2] >= vecMarkVertex[i][2] ) {
                    vecMarkVertex[i][1] = isourceVertex;
                    vecMarkVertex[i][2] = vecGraph[i][isourceVertex]*vecMarkVertex[isourceVertex][2];
            }
        }

        while(bolEmptyMarkVertex==false) {
            for(i=0,j=0 ; i < nVertex ; ++i) {
                if( vecMarkVertex[i][0] != -1) {
                        j=vecMarkVertex[i][0];
                        break;
                }
            }
            //取通过率最大的结点为J,将它加到树上,并从标记点中删除
            for(i=0 ; i < nVertex ; ++i) {
                if( vecMarkVertex[i][2] > vecMarkVertex[j][2] && vecMarkVertex[i][0] != -1)
                    j=vecMarkVertex[i][0];
            }
            vecMarkVertex[j][0] = -1 ;
            vecVertex[j][1]=vecMarkVertex[j][1];
            vecVertex[j][2]=vecMarkVertex[j][2];

            //Update(j)，更新距离标记
            for(i=0 ; i < nVertex ; ++i) {
                if( vecGraph[i][j] != 0 &&
                    vecMarkVertex[i][0] != -1 &&
                    vecGraph[i][j]*vecMarkVertex[j][2] >= vecMarkVertex[i][2] ) {
                        vecMarkVertex[i][1] = j;
                        vecMarkVertex[i][2] = vecGraph[i][j]*vecMarkVertex[j][2];
                }
            }

            bolEmptyMarkVertex=true;
            for(i=0 ; i < nVertex ; ++i) {
                if( vecMarkVertex[i][0] != -1) {
                        bolEmptyMarkVertex=false;
                        break;
                }
            }
        }
        for(i=0;i<nVertex;++i) {
            cout << "<<====" << "到\t" << i << "\t最大通过率路径" << "====>>" << endl ;
            cout << "|-" <<"节点 " << "  ---  " << "通过率" << endl ;
            j=i;
            while(j!=isourceVertex) {
                cout << "|- " <<vecVertex[j][0] << "   ---   " << vecVertex[j][2] << endl ;
                j=vecVertex[j][1];
            }
            cout << "|- " <<vecVertex[j][0] << "   ---   " << vecVertex[j][2] << endl ;
            cout << "<<========================================>>" << endl ;
        }
    }

    //使用BFS寻找最小跳路径，返回为source->tail
    deque<int> BFS_FindPathMinHop(const vector<vector<int> >* pvecGraph,int isourceVertex,int itailVertex)
    {
        if(pvecGraph==NULL)pvecGraph=&vecGraphWeight;
        //存储BFS生成树,pair的firs是当前节点i，是其前继
        map<int,int> mapBFSTree;
        mapBFSTree[isourceVertex]=isourceVertex;

        deque<int> deqResult;
        queue<int> queVertexSearch;
        queue<int> queVertexSearchNext;
        queVertexSearch.push(isourceVertex);
        int i,iVertexSearch;
        cout << (*pvecGraph)[5][1] <<"xxx"<< endl;

        while( !queVertexSearch.empty() ) {
            while( !queVertexSearch.empty() ) {
                while( !queVertexSearchNext.empty() ) {
                    queVertexSearchNext.pop();
                }
                iVertexSearch=queVertexSearch.front();
                cout << "iVertexSearch:" << iVertexSearch << endl;
                for(i=0; i<nVertex ; ++i) {
                    if( (*pvecGraph)[iVertexSearch][i] !=0 && mapBFSTree.count(i) == 0 ) {
                        mapBFSTree[i]=iVertexSearch;
                        cout << i << "->" << iVertexSearch << endl;
                        queVertexSearchNext.push(i);
                    }
                }
                queVertexSearch.pop();
            }
            queVertexSearch=queVertexSearchNext;
            cout << "====" << endl;
        }

        if( mapBFSTree.count(itailVertex) == 0 )
            return deqResult;


        iVertexSearch=itailVertex;
        while( iVertexSearch != isourceVertex ) {
            deqResult.push_front(iVertexSearch);
            iVertexSearch = mapBFSTree[iVertexSearch];
        }
        deqResult.push_front(iVertexSearch);
        deque<int>::iterator ite=deqResult.begin();
        for(;ite!=deqResult.end();++ite) {
            cout << *ite << "-";
        }
        return deqResult;
    }

    void Edmond_Karp_MaxFlow(int isourceVertex,int itailVertex)
    {
        int iActiveVertex,iAdmissibleVertex;
        int iMaxFlow=0,iVertex,iVertexNext,iFlow;
        vector<vector<int> > vecGraphResidual=vecGraphWeight;
        vector<vector<int> > vecFlow(nVertex, vector<int>(nVertex,0));
        deque<int> deqMinHopPath=BFS_FindPathMinHop(&vecGraphResidual,isourceVertex,itailVertex);
        deque<int>::iterator itedeqMinHopPath;
        deque<int>::iterator itedeqMinHopPathEnd;
        while( !deqMinHopPath.empty() ) {
            itedeqMinHopPath=deqMinHopPath.begin();
            itedeqMinHopPathEnd=deqMinHopPath.end()-1;
            iMaxFlow = vecGraphResidual[*deqMinHopPath.begin()][*(deqMinHopPath.begin()+1)];
            for(itedeqMinHopPath=deqMinHopPath.begin();itedeqMinHopPath!=itedeqMinHopPathEnd;++itedeqMinHopPath) {
                iMaxFlow = min(iMaxFlow,vecGraphResidual[*itedeqMinHopPath][*(itedeqMinHopPath+1)]);
            }
            for(itedeqMinHopPath=deqMinHopPath.begin();itedeqMinHopPath!=itedeqMinHopPathEnd;++itedeqMinHopPath) {
                vecGraphResidual[*itedeqMinHopPath][*(itedeqMinHopPath+1)]-=iMaxFlow;
                vecGraphResidual[*(itedeqMinHopPath+1)][*itedeqMinHopPath]+=iMaxFlow;
                vecFlow[*itedeqMinHopPath][*(itedeqMinHopPath+1)]+=iMaxFlow;
                iFlow=min(vecFlow[*itedeqMinHopPath][*(itedeqMinHopPath+1)],vecFlow[*(itedeqMinHopPath+1)][*itedeqMinHopPath]);
                vecFlow[*itedeqMinHopPath][*(itedeqMinHopPath+1)]-=iFlow;
                vecFlow[*(itedeqMinHopPath+1)][*itedeqMinHopPath]-=iFlow;
            }
            deqMinHopPath=BFS_FindPathMinHop(&vecGraphResidual,isourceVertex,itailVertex);
        }
        for(iActiveVertex=0;iActiveVertex<nVertex;++iActiveVertex)
            for(iAdmissibleVertex=0;iAdmissibleVertex<nVertex;++iAdmissibleVertex) {
                if(vecFlow[iActiveVertex][iAdmissibleVertex]!=0)
                cout << "vecFlow[" << iActiveVertex<<"]["<<iAdmissibleVertex<<"]=" << vecFlow[iActiveVertex][iAdmissibleVertex] <<endl;
        }
    }

    //返回存储<ID,Hop>的map，不含iRootVertex
    map<int,int> BFS_HopMap(const vector<vector<int> >* pvecGraph,int iRootVertex)
    {
        int iHop=1;
        if(pvecGraph==NULL)pvecGraph=&vecGraphWeight;
        //存储BFS生成树,pair的first是当前节点i，second是其跳数
        map<int,int> mapVertexHop;

        queue<int> queVertexSearch;
        queue<int> queVertexSearchNext;
        queVertexSearch.push(iRootVertex);
        int i=0,iVertexSearch;

        while( !queVertexSearch.empty() ) {
            while( !queVertexSearch.empty() ) {
                iVertexSearch=queVertexSearch.front();
                for(i=0; i<nVertex ; ++i) {
                    if( (*pvecGraph)[iVertexSearch][i] !=0 && mapVertexHop.count(i)==0 ) {
                        mapVertexHop.insert( pair<int,int>(i,iHop) );
                        queVertexSearchNext.push(i);
                    }
                }
                queVertexSearch.pop();
            }
            ++iHop;
            queVertexSearch=queVertexSearchNext;
            while( !queVertexSearchNext.empty() ) {
                queVertexSearchNext.pop();
            }
        }
        return mapVertexHop;
    }

    void Preflow_Push_FIFO_MaxFlow(int isourceVertex,int itailVertex)
    {
        int iActiveVertex,iAdmissibleVertex,iHop,iFlow=0;
        //存储剩余网络
        vector<vector<int> > vecGraphResidual=vecGraphWeight;
        //存储流网络
        vector<vector<int> > vecFlow(nVertex, vector<int>(nVertex,0));
        //存储结点距离标记，并初始化源结点路由标记
        map<int,int> mapVertexDistanceLabel=BFS_HopMap(&vecGraphResidual,itailVertex);
        mapVertexDistanceLabel[isourceVertex]=nVertex;
        //存储结点的多余流量
        map<int,int> mapVertexExcess;
        //ActiveVertex结点队列，FIFO
        deque<int> deqActiveVertex;
        //初始化，尽量从源节点推送流量
        for(int i=0 ;i<nVertex ;++i ) {
            if(vecGraphResidual[isourceVertex][i]!=0) {
                mapVertexExcess[i]=vecGraphResidual[isourceVertex][i];
                vecFlow[isourceVertex][i]+=vecGraphResidual[isourceVertex][i];
                vecGraphResidual[isourceVertex][i]-=vecFlow[isourceVertex][i];
                vecGraphResidual[i][isourceVertex]+=vecFlow[isourceVertex][i];
                deqActiveVertex.push_back(i);
            }
        }

        while( !deqActiveVertex.empty() ) {
            iActiveVertex=deqActiveVertex.front();
            iHop=mapVertexDistanceLabel[iActiveVertex]-1;
            iFlow=0;
            //寻找Admissible边，确定可用流量
            for(iAdmissibleVertex=0;iAdmissibleVertex<nVertex;++iAdmissibleVertex) {
                if( mapVertexDistanceLabel[iAdmissibleVertex]==iHop
                    && vecGraphResidual[iActiveVertex][iAdmissibleVertex] >0 ) {
                        iFlow=min(mapVertexExcess[iActiveVertex],vecGraphResidual[iActiveVertex][iAdmissibleVertex]);
                        break;
                }
            }

            if(iFlow != 0 ) {
                //更新节点的多余流量
                mapVertexExcess[iActiveVertex]-=iFlow;
                mapVertexExcess[iAdmissibleVertex]+=iFlow;
                //更新流网络
                vecFlow[iActiveVertex][iAdmissibleVertex]+=iFlow;
                //更新剩余网络
                vecGraphResidual[iActiveVertex][iAdmissibleVertex]-=iFlow;
                vecGraphResidual[iAdmissibleVertex][iActiveVertex]+=iFlow;
                //简化流网络，确保不存在两个结点互相推送流量
                iFlow=min(vecFlow[iActiveVertex][iAdmissibleVertex],vecFlow[iAdmissibleVertex][iActiveVertex]);
                vecFlow[iActiveVertex][iAdmissibleVertex]-=iFlow;
                vecFlow[iAdmissibleVertex][iActiveVertex]-=iFlow;

                if(mapVertexExcess[iActiveVertex] == 0)
                    deqActiveVertex.pop_front();
                //更新ActiveVertex队列，注意源节点和宿节点不加入队列
                if( find(deqActiveVertex.begin(),deqActiveVertex.end(),iAdmissibleVertex)==deqActiveVertex.end()
                    && iAdmissibleVertex!=isourceVertex
                    && iAdmissibleVertex!=itailVertex )
                        deqActiveVertex.push_back(iAdmissibleVertex);
            }
            //若找不到Admissible边，重设距离标记
            else {
                iHop=nVertex;
                for(iAdmissibleVertex=0;iAdmissibleVertex<nVertex;++iAdmissibleVertex) {
                    if( vecGraphResidual[iActiveVertex][iAdmissibleVertex] > 0 ) {
                        iHop=min(iHop,mapVertexDistanceLabel[iAdmissibleVertex]);
                    }
                }
                mapVertexDistanceLabel[iActiveVertex]=iHop+1;
            }
        }

        //输出结果
        for(iActiveVertex=0;iActiveVertex<nVertex;++iActiveVertex)
            for(iAdmissibleVertex=0;iAdmissibleVertex<nVertex;++iAdmissibleVertex) {
                if(vecFlow[iActiveVertex][iAdmissibleVertex]!=0)
                    cout << "vecFlow[" << iActiveVertex<<"]["<<iAdmissibleVertex<<"]=" << vecFlow[iActiveVertex][iAdmissibleVertex] <<endl;
        }
        for(iActiveVertex=0;iActiveVertex<nVertex;++iActiveVertex) {
            if(mapVertexExcess[iActiveVertex]!=0)
                cout << "mapVertexExcess[" << iActiveVertex << "]" << mapVertexExcess[iActiveVertex] << endl;
        }
    }

    //输出到文件
    void getFile(string FileName)
    {
        ofstream file;
        file.open(FileName);
        file << "# VertexNum: " << lstVertex.size() << endl;
        file << "# EdgeNUm:   " << plstIncident.size() << endl;
        list<CEdge*>::iterator itepIncident = plstIncident.begin();
        for (; itepIncident != plstIncident.end(); ++itepIncident) {
                file << (*itepIncident)->getHead() << ";" << (*itepIncident)->getTail()
                     << ";" << (*itepIncident)->getWeight() << ";" << (*itepIncident)->getCap() << endl;
        }
        file.close();
        return;
    }

    void getLingoFile(string FileName)
    {
        ofstream file;
        file.open(FileName);
        list<CEdge*>::iterator itepIncident = plstIncident.begin();
        list<int>::iterator itelstVertex = lstVertex.begin();

        file << "!vertex;" << endl ;
        for(; itelstVertex != lstVertex.end() ; ++itelstVertex) {
            file << *itelstVertex << " " ;
        }
        file << "~" << endl << "!links;" << endl ;
        for(; itepIncident != plstIncident.end(); ++itepIncident) {
        	file << (*itepIncident)->getHead() << "," << (*itepIncident)->getTail() << " "
    			 << (*itepIncident)->getTail() << "," << (*itepIncident)->getHead() << " ";
        }
    	file << "~" << endl << "!cost;" << endl;
        for(itepIncident = plstIncident.begin() ; itepIncident != plstIncident.end(); ++itepIncident) {
            file << (*itepIncident)->getWeight() << " "  << (*itepIncident)->getWeight() << " ";
        }
    	file << "~" << endl;

        file.close();
        return;
    }
};
