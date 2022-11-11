#ifndef _VERTEXSET_H_
#define _VERTEXSET_H_

#include <cstring>

class vertexSet{
private:
	int* m_Parent;
	int m_Size;

public:
	vertexSet(int size)
	{
		m_Parent = new int[size];
		m_Size = size; 
		for(int i=0; i<size; i++)
		{
			m_Parent[i] = i;
		}
	};
	~vertexSet(){
		delete m_Parent;
	};
	
	bool Check(int v1, int v2)
	{ 
		return Find(v1) == Find(v2) ? true : false; 
	};

	int Find(int v1)
	{
		if(m_Parent[v1] == v1)
			return v1;
		else
			return m_Parent[v1] = Find(m_Parent[v1]);
	}

	void Union(int v1, int v2)
	{
		m_Parent[Find(v1)] = Find(v2);
	}
};
#endif
