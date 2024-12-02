#include "GraphMethod.h"

bool BFS(Graph* graph, int vertex,ofstream* fout)
{
    if(vertex >= graph->getSize())
    {
        *fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
    *fout<<"======== BFS ========"<<endl;
    *fout<<"startvertex: "<<vertex<<endl;
    int access;
    queue<int> q;
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    bool* visited = new bool[graph->getSize()]{0};//visited set
    visited[vertex] = 1;
    q.push(vertex);
    while(!q.empty())
    {
        access = q.front();
        graph->undirectadjacent(access,&adjacentnode);//undirected graph
        q.pop();
        *fout<<access;
        for(it = adjacentnode.begin();it!=adjacentnode.end();it++)
        {
            if(!visited[it->first])
            {
                q.push(it->first);
                visited[it->first] = 1;
            }
        }
        adjacentnode.clear();
        if(!q.empty())
        {
            *fout<<" -> ";
        }
        else
            *fout<<endl;
    }
    *fout<<"===================="<<endl;
    delete [] visited;

    return true;
}

bool DFS(Graph* graph, int vertex,ofstream* fout)
{
    if(vertex >= graph->getSize())
    {
        *fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
    *fout<<"======== DFS ========"<<endl;
    *fout<<"startvertex: "<<vertex<<endl;
    int access;
    stack<int> s;
    map<int,int> adjacentnode;
    map<int,int>::reverse_iterator it; // vertex ascending order for stack
    bool* visited = new bool[graph->getSize()]{0};
    visited[vertex] = 1;
    s.push(vertex);
    while(!s.empty())
    {
        access = s.top();
        graph->undirectadjacent(access,&adjacentnode);
        s.pop();
        *fout<<access;
        for(it = adjacentnode.rbegin();it!=adjacentnode.rend();it++)
        {
            if(!visited[it->first])
            {
                s.push(it->first);
                visited[it->first] = 1;
            }
        }
        adjacentnode.clear();
        if(!s.empty())
        {
            *fout<<" -> ";
        }
        else
            *fout<<endl;
    }
    *fout<<"===================="<<endl;
    delete [] visited;

    return true;
}

bool DFS_R(Graph* graph, vector<bool> *visit, int vertex,ofstream* fout)
{
    if(vertex >= graph->getSize())
    {
        *fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    (*visit)[vertex] = true;
    *fout<<vertex;
    graph->undirectadjacent(vertex,&adjacentnode);
    for (it = adjacentnode.begin(); it != adjacentnode.end(); it++)
    {
        if (!(*visit)[it->first])
        {
            *fout << " -> ";
            DFS_R(graph, visit, it->first, fout);//recursive
        }
    }


    return true;
}

bool Kruskal(Graph* graph,ofstream* fout)
{
    int n = graph->getSize();
    int n2 = n*n;
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    int pathinfo[n][n] = {0,}; //copy graph and directionality removal
    int weightlist[n2] = {0,}; //weight array
    int parent[n]; //set
    int kruskalgraph[n][n] = {0,}; //final graph
    int num=0; //weight number
    int full=0; //check number of edges
    int cost = 0; //total cost of MST

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            pathinfo[i][j] = 0;
            kruskalgraph[i][j] = 0;
        }
    }

    for(int i = 0; i<n;i++)
    {
        graph->getAdjacentEdges(i,&adjacentnode);
        for(it = adjacentnode.begin();it != adjacentnode.end();it++)
        {
            pathinfo[i][it->first] = it->second;
            if(pathinfo[i][it->first] == pathinfo[it->first][i])//If vertices pointing to each other have the same weight
            {
                pathinfo[i][it->first] = 0;
                continue;
            }
            else if((pathinfo[i][it->first] < pathinfo[it->first][i]) && (pathinfo[it->first][i] != 0))//If vertices point to each other and have different weights
            {
                pathinfo[it->first][i] = 0;
                continue;
            }
            else if((pathinfo[i][it->first] > pathinfo[it->first][i]) && (pathinfo[it->first][i] != 0))//If vertices point to each other and have different weights
            {
                pathinfo[i][it->first] = 0;
                continue;
            }
        }
        adjacentnode.clear();//for new adjacent vertices
    }

    for(int i = 0;i<n;i++) //weightlist initializing
    {
        for(int j = 0; j<n; j++)
        {
            if(pathinfo[i][j] != 0)
            {
                weightlist[num++] = pathinfo[i][j];
            }
        }
    }

    quick(weightlist,0,(num-1)); //quick and insertion sorting

    for(int i = 0;i<n;i++) //root initializing
    {
        parent[i] = -1;
    }

    for(int i = 0; i<num;)
    {
        for(int j = 0; j<n; j++)
        {
            for(int k = 0; k<n; k++)
            {
                if(pathinfo[j][k] == weightlist[i])
                {
                    pathinfo[j][k] = 0;
                    int s1 = findset(j,parent);
                    int s2 = findset(k,parent);
                    if(s1 != s2)//If not in the same set
                    {
                        unionset(s1,s2,parent);// union
                        kruskalgraph[j][k] = weightlist[i++];//insert final graph
                        cost += kruskalgraph[j][k];//calculate cost
                        full++;
                    }
                    else
                    {
                        i++;
                    }
                    if(full == n-1 || i == num){break;} //MST generation
                }
            }
            if(full == n-1 || i == num){break;}//MST generation
        }
        if(full == n-1 || i == num){break;}//MST generation
    }
    if(full != n-1)
    {
        *fout<<"The number of edges is less than n-1"<<endl;
        return false;
    }

    for(int i = 0; i<n;i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(kruskalgraph[i][j] != 0)
            {
                kruskalgraph[j][i] = kruskalgraph[i][j];//directionality removal
            }
        }
    }

	for(int i=0; i<n; i++)
	{
		*fout<<"["<<i<<"]";
		for(int j=0; j<n ; j++)
		{
            if(kruskalgraph[i][j] != 0)
            {
                *fout<<" "<<j<<"("<<kruskalgraph[i][j]<<")";
            }
		}
		*fout<<endl;
	}
    *fout<<"cost: "<<cost<<endl;

    return true;
}

bool Dijkstra(Graph* graph, int vertex,ofstream* fout)
{
    if(vertex >= graph->getSize())
    {
        *fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
    int n = graph->getSize();
    int pathinfo[2][n];//pathinfo[0] = distance, pathinfo[1] = prev
    bool set[n];
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    for(int i = 0;i<n; i++)//initialize
    {
        set[i] = false;
        pathinfo[0][i] = MAX;
        pathinfo[1][i] = MAX;
    }
    pathinfo[0][vertex] = 0;

    for(int i = 0; i<n-1;i++)// n vertex have n-1 path but 0 to 0 path's distance is 0.
    {
        int u;
        for(u = 0; u<n;u++)//Choose one of those not in the set
        {
            if(set[u]==false)
            {
                break;
            }
        }
        for(int j = u+1;j<n;j++)//After u, choose the one that is not in the set.
        {
            if(set[j]==false)
            {
                if(pathinfo[0][j]<=pathinfo[0][u])
                {
                    u = j;
                }
            }
        }

        set[u]=true;
        graph->getAdjacentEdges(u,&adjacentnode);
        for(it = adjacentnode.begin();it != adjacentnode.end();it++)
        {
            if(it->second<0)
            {
                *fout<<"negative weight"<<endl;
                return false;
            }
            int temp = pathinfo[0][it->first];
            if(set[it->first] == false)
            {
                pathinfo[0][it->first]= min(pathinfo[0][u]+(it->second),pathinfo[0][it->first]);
            }
            if(pathinfo[0][it->first]!=temp) //prev is modified
            {
                pathinfo[1][it->first] = u; //prev update
            }
        }
        adjacentnode.clear();
    }
    for(int i = 0; i<n;i++)
    {
        *fout<<"["<<i<<"] ";
        if(pathinfo[1][i] == MAX)//When there is no previous vertex
        {
            *fout<<"x"<<endl;
        }
        else
        {
            stack<int> a;
            int temp = i;
            while(temp != vertex)
            {
                a.push(temp);
                temp = pathinfo[1][temp];
            }
            *fout<<temp;
            while(!a.empty())
            {
                *fout<<"->"<<a.top();
                a.pop();
            }
            *fout<<"("<<pathinfo[0][i]<<")"<<endl;
        }
    }

    return true;
}

bool Bellmanford(Graph* graph, int s_vertex, int e_vertex,ofstream* fout)
{
    if(s_vertex >= graph->getSize() || e_vertex >= graph->getSize())
    {
        *fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
    int n = graph->getSize();
    int pathinfo[2][n];//pathinfo[0] = d(v,k), pathinfo[1] = p(v,k)
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    for(int i = 0; i<n;i++) //initialize
    {
        if(i == s_vertex)
        {
            pathinfo[0][i] = 0; //start == end
            pathinfo[1][i] = MAX;
        }
        else
        {
            pathinfo[0][i] = MAX;
            pathinfo[1][i] = MAX;
        }
    }
    graph->getAdjacentEdges(s_vertex,&adjacentnode);
    for(it = adjacentnode.begin(); it != adjacentnode.end(); it++)//k = 1
    {
        pathinfo[0][it->first] = it->second;
        pathinfo[1][it->first] = s_vertex;
    }

    for(int k = 2; k < n+1; k++)//0 and 1 is initialized
    {
        for(int p = 0;p<n;p++)//one row
        {
            if(p == s_vertex)
            {
                continue;
            }
            for (int j = 0; j < n; j++)//Is j incoming vertex?
            {
                adjacentnode.clear();
                graph->getAdjacentEdges(j, &adjacentnode);
                it = adjacentnode.find(p);
                if(it == adjacentnode.end())
                {
                    continue;
                }
                else
                {
                    int temp = pathinfo[0][p];
                    pathinfo[0][p]= min(pathinfo[0][p],(pathinfo[0][j] + it->second));
                    if(pathinfo[0][p] != temp)
                    {
                        if(k == n)
                        {
                            *fout<<"negative cycle"<<endl;
                            return false;
                        }
                        pathinfo[1][p] = j;
                    }
                }
            }
        }
    }

    stack<int> a;
    int temp = e_vertex;
    if (pathinfo[1][temp] == MAX)
    {
        *fout << "x" << endl;
        return true;
    }
    while (temp != s_vertex)
    {
        if (pathinfo[1][temp] == MAX)
        {
            *fout << "x" << endl;
            return true;
        }
        a.push(temp);
        temp = pathinfo[1][temp];
    }
    *fout << temp;
    while (!a.empty())
    {
        *fout << "->" << a.top();
        a.pop();
    }
    *fout << endl;
    *fout << "cost: " << pathinfo[0][e_vertex] << endl;
    return true;
}

bool FLOYD(Graph* graph,ofstream* fout)
{
    int n = graph->getSize();
    int pathinfo[n][n];
    map<int,int> adjacentnode;
    map<int,int>::iterator it;
    
    for(int i=0; i<n ; i++) // i to i path is 0, others MAX
    {
        for(int j=0; j<n;j++)
        {
            if(i == j)
            {
                pathinfo[i][j] = 0;
                continue;
            }
            pathinfo[i][j] = MAX;
        }
    }

    for(int i =0;i<n;i++) //k = 0
    {
        graph->getAdjacentEdges(i,&adjacentnode);
        for(it = adjacentnode.begin(); it != adjacentnode.end();it++)
        {
            pathinfo[i][it->first] = it->second;
        }
        adjacentnode.clear();
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                pathinfo[i][j] = min(pathinfo[i][j],(pathinfo[i][k] + pathinfo[k][j]));
            }
        }
    }

    for(int i = 0; i < n ; i++)
    {
        if(pathinfo[i][i]<0)//negative cycle?
        {
            *fout<<"negative cycle"<<endl;
            return false;
        }
    }

    *fout<<'\t';
	for(int i=0; i<n; i++)
	{
		*fout<<"["<<i<<"]"<<'\t';
	}
	*fout<<endl;

	for(int i=0; i<n; i++)
	{
		*fout<<"["<<i<<"]";
		for(int j=0; j<n && *fout<<'\t'; j++)
		{
            if(pathinfo[i][j] >= 900000)//Decrements the value of MAX when negative weights are computed
            {
                *fout<<"x";
                continue;
            }
			*fout<<pathinfo[i][j];
		}
		*fout<<endl;
	}
    return true;
}

void quick(int arr[],int left,int right)
{
    if (left<right)
    {
        if (right-left+1<=6)//When the size of the partition is less than 6
        {
            insertionsort(arr,left,right);
        }
        else
        {
            int i = left;
            int j = right+1;
            int pivot = arr[left];
            do
            {
                do
                {
                    i++;
                } while (arr[i] < pivot);//Until you find something on the left that is greater than the pivot
                do
                {
                    j--;
                } while (arr[j] > pivot);//Until you find something smaller than the pivot on the right
                if (i < j)//find and swap
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            } while (i < j);
            int temp = arr[left];//Insert the pivot in the middle
            arr[left] = arr[j];
            arr[j] = temp;

            quick(arr, left, j - 1);//left of pivot
            quick(arr, j + 1, right);//right of pivot
        }
    }
}
void insertionsort(int arr[],int start,int end)// n is array size
{
    for(int i = (start+1); i<=end;i++)
    {
        int temp = arr[i];
        insertion(temp,arr,i-1);
    }
}
void insertion(int e,int arr[],int n)
{
    while(e<arr[n])
    {
        arr[n+1]=arr[n];
        n--;
        if(n < 0)
            break;
    }
    arr[n+1] = e;
}
void unionset(int a, int b,int parent[])
{
    int temp = parent[a] + parent[b];//root's weight update
    if(parent[a]>parent[b])//tree merge
    {
        parent[a] = b;
        parent[b] = temp;
    }
    else//tree merge
    {
        parent[b] = a;
        parent[a] = temp;
    }
}
int findset(int a,int parent[])
{
    int r;
    for(r = a; parent[r] >= 0; r = parent[r]);//finding root

    while(a != r)//Change the parent of vertices from a to root to root
    {
        int s = parent[a];
        parent[a] = r;
        a = s;
    }
    return r;
}