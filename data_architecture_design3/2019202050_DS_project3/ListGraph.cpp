#include "ListGraph.h"

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_Type = type;
	m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()
{
	delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) //direct
{
	map<int,int>::iterator it;
	for (it = m_List[vertex].begin(); it != m_List[vertex].end(); it++)
	{
		m->insert({it->first,it->second});
	}
}

void ListGraph::undirectadjacent(int vertex, map<int, int>* m)//indirect
{
	map<int,int>::iterator it;
	for (it = m_List[vertex].begin(); it != m_List[vertex].end(); it++)
	{
		m->insert({it->first,it->second});
	}

	for(int i = 0; i<getSize(); i++)
	{
		if(i == vertex)
		{
			continue;
		}
		for(it = m_List[i].begin();it != m_List[i].end(); it++)
		{
			if(it->first == vertex)
			{
				m->insert({i,it->second});
			}
		}
	}
}

void ListGraph::insertEdge(int from, int to, int weight)
{
	m_List[from].insert({to,weight});
}

bool ListGraph::printGraph(ofstream* fout)
{
	if( m_Size <= 0 )
		return 0;
		
	*fout<<"=============PRINT=============="<<endl;

	for(int i=0; i<m_Size; i++)
	{
		*fout<<"["<<i<<"]";

		for(auto it_=m_List[i].begin(); it_!=m_List[i].end() && *fout<<" -> "; it_++)
		{
			*fout<<"("<<it_->first<<","<<it_->second<<")";
		}
		*fout<<endl;
	}
	*fout<<"================================="<<endl;
	return 1;
}