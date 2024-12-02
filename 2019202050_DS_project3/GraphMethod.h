#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, int vertex,ofstream* fout);
bool DFS(Graph* graph, int vertex,ofstream* fout);
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex,ofstream* fout);
bool Kruskal(Graph* graph,ofstream* fout);
bool Dijkstra(Graph* graph, int vertex,ofstream* fout);
bool Bellmanford(Graph* graph, int s_vertex, int e_vertex,ofstream* fout);
bool FLOYD(Graph* graph,ofstream* fout);
void quick(int arr[], int left, int right);
void insertionsort(int arr[],int start,int end);
void insertion(int e,int arr[],int n);
void unionset(int a, int b,int parent[]);
int findset(int a,int parent[]);

#endif
