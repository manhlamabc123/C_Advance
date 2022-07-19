#include "libfdr\jrb.h"
#include "libfdr\jval.h"
#include "libfdr\dllist.h"

typedef Dllist Stack;
Stack createStack();
void Push(Stack queue, Jval jval);
Jval Pop(Stack queue);
int Is_Queue_Stack(Stack queue);

typedef Dllist Queue;
Queue createQueue();
void Enqueue(Queue queue, Jval jval);
Jval Dequeue(Queue queue);
int Is_Queue_Empty(Queue queue);

typedef struct p_queue
{
	float priority;
	int info;
	struct p_queue *link;
}*P_Queue ;

P_Queue create_P_Queue();
int Is_P_Queue_Empty(P_Queue p_queue);
P_Queue P_Enqueue(P_Queue p_queue, int item, float priority);
P_Queue P_Dequeue(P_Queue p_queue, int* output);

#define INFINITIVE_VALUE 10000000

typedef struct 
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
int getGraphID(Graph graph, char* name);
void addEdge(Graph graph, int v1, int v2, float weight);
void non_addEdge(Graph graph, int v1, int v2, float weight);
int hasEdge(Graph graph, int v1, int v2);
float getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int Number_of_Vertex_in_Graph(Graph graph);
void Print_Graph_Vertex(Graph graph);
void Print_Graph_Map(Graph graph);
void dropGraph(Graph graph);

int BFS(Graph graph, int start, int stop, int* trav);
int DFS(Graph graph, int start, int stop, int* trav);

int DAG_Full_Graph(Graph graph);
void Topo_Sort (Graph graph);

int Dijkstra(Graph graph, int start, float* distance, int* previous);
int BellmanFord(Graph graph, int start, float* distance, int* previous); //No negative Cycle
int PathCreate(int* previous, int start, int end, int length, int* path); //Length Input has to be 1