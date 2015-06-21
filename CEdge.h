#include "common.h"
using namespace std;

class CEdge
{
private:
	int nHead, nTail, nWeight, nCapacity;
public:
	CEdge(int Head, int Tail, int Weight, int Capacity)
	{
		nHead = Head;
		nTail = Tail;
		nWeight = Weight;
		nCapacity = Capacity;
	}
	CEdge(int Head, int Tail, int Weight)
	{
		nHead = Head;
		nTail = Tail;
		nWeight = Weight;
		nCapacity = 0;
	}
	CEdge(int Head, int Tail)
	{
		nHead = Head;
		nTail = Tail;
		nWeight = 0;
		nCapacity = 0;
	}
	CEdge()
	{
		nHead = 0;
		nTail = 0;
		nWeight = 0;
		nCapacity = 0;
	}
	CEdge(CEdge & x)
	{
		nHead = x.nHead;
		nTail = x.nTail;
		nWeight = x.nWeight;
		nCapacity = x.nCapacity;
	}
	//  ~CEdge();
	int getHead()
	{
		return nHead;
	}
	void setHead(int isetHead)
	{
		nHead = isetHead;
	}

	int getTail()
	{
		return nTail;
	}
	void setTail(int isetTail)
	{
		nTail = isetTail;
	}

	int getWeight()
	{
		return nWeight;
	}
	void setWeight(int isetWeight)
	{
		nWeight = isetWeight;
	}

	int getCap()
	{
		return nCapacity;
	}
	void getCap(int isetCap)
	{
		nCapacity = isetCap;
	}
	/*
	char* getLine(char* buffer)
	{
        sprintf(buffer, "%d;%d;%d;%d;", getHead(), getTail(), getWeight(), getCap());
		return buffer;
	}
	*/
	bool operator<(CEdge& x)
	{
		if (nWeight < x.getWeight())
			return true;
		else return false;
	}
	bool operator>(CEdge& x)
	{
		if (nWeight > x.getWeight())
			return true;
		else return false;
	}
};

