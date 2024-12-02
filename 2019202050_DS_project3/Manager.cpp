#include "Manager.h"

Manager::Manager()
{
	graph = nullptr;
	fout.open("log.txt", ios::app);
	load = 0;
}

Manager::~Manager()
{
	if(load) //graph exist = 1, not 0
		delete graph;
	fout.close();
}

void Manager::run(const char* command_txt){
	ifstream fin;
	fin.open(command_txt);
	if(!fin)
	{
		fout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	char* str=NULL;
	char* str2=NULL;
	char buf[129]={0}; //command line storage

	while(fin.getline(buf, 128))//getline to buf from command.txt
	{
		str = strtok(buf," ");
		if(strcmp(str,"LOAD")==0)
		{
			str2 = strtok(NULL," ");
			if(str2 == NULL)
			{
				fout<<"txt path is wrong"<<endl;
				printErrorCode(100);
				continue;
			}
			if(!LOAD(str2))
			{
				printErrorCode(100);
			}
		}
		else if(strcmp(str,"PRINT")==0)
		{
			if(!PRINT())
			{
				printErrorCode(200);
			}
		}
		else if(strcmp(str,"BFS")==0)
		{
			str2 = strtok(NULL," ");
			if(str2 == NULL)
			{
				fout<<"more parameter please"<<endl;
				printErrorCode(300);
				continue;
			}
			if(!mBFS(atoi(str2)))
			{
				printErrorCode(300);
			}
		}
		else if(strcmp(str,"DFS")==0)
		{
			str2 = strtok(NULL," ");
			if(str2 == NULL)
			{
				fout<<"more parameter please"<<endl;
				printErrorCode(400);
				continue;
			}
			if(!mDFS(atoi(str2)))
			{
				printErrorCode(400);
			}
		}
		else if(strcmp(str,"DFS_R")==0)
		{
			str2 = strtok(NULL," ");
			if(str2 == NULL)
			{
				fout<<"more parameter please"<<endl;
				printErrorCode(500);
				continue;
			}
			if(!mDFS_R(atoi(str2)))
			{
				printErrorCode(500);
			}
		}
		else if(strcmp(str,"KRUSKAL")==0)
		{
			if(!mKRUSKAL())
			{
				printErrorCode(600);
			}
		}
		else if(strcmp(str,"DIJKSTRA")==0)
		{
			str2 = strtok(NULL," ");
			if(str2 == NULL)
			{
				fout<<"more parameter please"<<endl;
				printErrorCode(700);
				continue;
			}
			if(!mDIJKSTRA(atoi(str2)))
			{
				printErrorCode(700);
			}
		}
		else if(strcmp(str,"BELLMANFORD")==0)
		{
			str2 = strtok(NULL," ");
			char* str3 = strtok(NULL," ");
			if(str2 == NULL || str3 == NULL)
			{
				fout<<"more parameter please"<<endl;
				printErrorCode(800);
				continue;
			}
			if(!mBELLMANFORD(atoi(str2),atoi(str3)))
			{
				printErrorCode(800);
			}
		}
		else if(strcmp(str,"FLOYD")==0)
		{
			if(!mFLOYD())
			{
				printErrorCode(900);
			}
		}
		else if(strcmp(str,"EXIT")==0)
		{
			break;
		}
	}	
	fin.close();
}

bool Manager::LOAD(char* filename)
{
	ifstream gin;
	char graphinfo[100];
	gin.open(filename);
	if(!gin)
	{
		fout<<"graphfile is not open"<<endl;
		return false;
	}
	gin.getline(graphinfo,100);//list? matrix?
	if(graphinfo[0] == 'L') //listgraph
	{
		if(load == 1) //previous graph data delete
			delete graph;
		char* temp1 = NULL;
		char* temp2 = NULL;
		gin.getline(graphinfo,100);//graph size?
		if(graphinfo == NULL)
		{
			fout<<"graph information is empty"<<endl;
			return false;
		}
		graph = new ListGraph(0,atoi(graphinfo)); //new graph!
		load = 1;//graph is created

		while(gin.getline(graphinfo,100))
		{
			int startvertex;
			temp1 = strtok(graphinfo," ");
			temp2 = strtok(NULL," ");
			if(temp2 == NULL) //parameter is only one? startvertex
			{
				startvertex = atoi(temp1);
				continue;
			}
			else //parameter is two? endvertex,weight
			{
				graph->insertEdge(startvertex,atoi(temp1),atoi(temp2));
			}
		}
	}
	else if(graphinfo[0] == 'M') //matrix graph
	{
		if(load == 1)
			delete graph;
		char* temp1 = NULL;
		char* temp2 = NULL;
		int startvertex = 0;
		int endvertex = 0;
		gin.getline(graphinfo,100);//graph size?
		if(graphinfo == NULL)
		{
			fout<<"graph information is empty"<<endl;
			return false;
		}
		graph = new MatrixGraph(0,atoi(graphinfo)); //new graph!
		load = 1;//graph is created

		while(gin.getline(graphinfo,100))
		{
			temp1 = strtok(graphinfo," ");
			while(temp1 != NULL)
			{
				graph->insertEdge(startvertex,endvertex++,atoi(temp1));
				temp1 = strtok(NULL," ");
			}
			endvertex = 0;
			startvertex++;
		}
	}
	else
	{
		fout<<"Can only be made from lists or arrays"<<endl;
		return false;
	}
	gin.close();
	fout<<"===========LOAD=========="<<endl;
	fout<<"Success"<<endl;
	fout<<"========================="<<endl;
	return true;
}

bool Manager::PRINT()
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(graph->printGraph(&fout))
		return true;
	return false;
}

bool Manager::mBFS(int vertex)
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(!BFS(graph,vertex,&fout))
	{
		return false;
	}
	return true;
}

bool Manager::mDFS(int vertex)
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(!DFS(graph,vertex,&fout))
	{
		return false;
	}
	return true;
}

bool Manager::mDFS_R(int vertex)
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(vertex >= graph->getSize())
    {
        fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
	vector<bool> visit(graph->getSize());//visited set
	fout<<"======== DFS_R ========"<<endl;
    fout<<"startvertex: "<<vertex<<endl;
	if(!DFS_R(graph,&visit,vertex,&fout))
	{
		return false;
	}
	fout<<endl;
	fout<<"======================="<<endl;
	return true;
}

bool Manager::mDIJKSTRA(int vertex)
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(vertex >= graph->getSize())
    {
        fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
	fout<<"======== DIJKSTRA ========"<<endl;
    fout<<"startvertex: "<<vertex<<endl;
	if(!Dijkstra(graph,vertex,&fout))
	{
		return false;
	}
	fout<<endl;
	fout<<"======================="<<endl;
	return true;
}

bool Manager::mKRUSKAL()
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	fout<<"======== KRUSKAL ========"<<endl;
	if(!Kruskal(graph,&fout))
	{
		return false;
	}
	fout<<endl;
	fout<<"======================="<<endl;
	return true;
}

bool Manager::mBELLMANFORD(int s_vertex, int e_vertex)
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	if(s_vertex >= graph->getSize() && e_vertex >= graph->getSize())
    {
        fout<<"vertex is not exist in graph"<<endl;
        return false;
    }
	fout<<"======== BELLMAN-FORD ========"<<endl;
	if(!Bellmanford(graph,s_vertex,e_vertex,&fout))
	{
		return false;
	}
	fout<<endl;
	fout<<"======================="<<endl;
	return true;
}

bool Manager::mFLOYD()
{
	if(load == 0)
	{
		fout<<"no graph was formed"<<endl;
		return false;
	}
	fout<<"======== FLOYD ========"<<endl;
	if(!FLOYD(graph,&fout))
	{
		return false;
	}
	fout<<endl;
	fout<<"======================="<<endl;
	return true;
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}
