#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Priority_Queue
P_Queue create_P_Queue()
{
    P_Queue p_queue = NULL;
    return p_queue;
}

int Is_P_Queue_Empty(P_Queue p_queue)
{
    return p_queue==NULL;
}

P_Queue P_Enqueue(P_Queue p_queue, int item, float priority)
{
	P_Queue temp, q;
	temp = (P_Queue)malloc(sizeof(struct p_queue));
	temp->info = item;
	temp->priority = priority;

	if( p_queue == NULL || priority < p_queue->priority )//< to >
	{
		temp->link = p_queue;
		p_queue = temp;
	}
	else
	{
		q = p_queue;
		while( q->link != NULL && q->link->priority <= priority ) q=q->link;
		temp->link = q->link;
		q->link = temp;
	}

    return p_queue;
}

P_Queue P_Dequeue(P_Queue p_queue, int* output)
{
	P_Queue temp;
	if(p_queue == NULL) printf("Queue Underflow\n");
	else
	{
		temp = p_queue;
		*output = temp->info;
		p_queue = p_queue->link;
		free(temp);
	}

    return p_queue;
}

//Queue
Queue createQueue()
{
    Dllist queue = new_dllist();
    return queue;
}

void Enqueue(Queue queue, Jval jval)
{
    dll_append(queue, jval);
}

Jval Dequeue(Queue queue)
{
    Queue node = dll_first(queue);
    int v = jval_i(node->val);
    dll_delete_node(node);
    Jval jval = new_jval_i(v);
    return jval;
}

int Is_Queue_Empty(Queue queue)
{
    return dll_empty(queue);
}

//Stack
Stack createStack()
{
    Dllist stack = new_dllist();
    return stack;
}

void Push(Stack stack, Jval jval)
{
    dll_append(stack, jval);
}

Jval Pop(Stack stack)
{
    Stack node = dll_last(stack);
    int v = jval_i(node->val);
    dll_delete_node(node);
    Jval jval = new_jval_i(v);
    return jval;
}

int Is_Stack_Empty(Stack stack)
{
    return dll_empty(stack);
}

//Graph
Graph createGraph()
{
    Graph graph;
    graph.edges = make_jrb();
    graph.vertices = make_jrb();
    return graph;
}

void addVertex(Graph graph, int id, char* name)
{
    JRB search = jrb_find_int(graph.vertices, id);
    JRB tree;
    if(search == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
    }
    else
    {
        printf("Already Exist. Cannot Insert.\n");
    }
}

char *getVertex(Graph graph, int id)
{
    JRB search = jrb_find_int(graph.vertices, id);
    if(search == NULL) return NULL;
    else return jval_s(search->val);
}

int getGraphID(Graph graph, char* name)
{
    JRB trav;
    jrb_traverse(trav, graph.vertices)
    {
        if(strcmp(name, jval_s(trav->val))==0) return jval_i(trav->key);
    }
    return -1;
}

void addEdge(Graph graph, int v1, int v2, float weight)
{
    JRB search = jrb_find_int(graph.edges, v1);
    JRB tree, node;
    if(search == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_f(weight));
    }
    else
    {
        node = jrb_find_int(graph.edges, v1);
        tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_f(weight));
    }
}

void non_addEdge(Graph graph, int v1, int v2, float weight)
{
    JRB search = jrb_find_int(graph.edges, v1);
    JRB tree, node;
    if(search == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_f(weight));
    }
    else
    {
        node = jrb_find_int(graph.edges, v1);
        tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_f(weight));
    }

    JRB search1 = jrb_find_int(graph.edges, v2);
    JRB tree1, node1;
    if(search1 == NULL)
    {
        tree1 = make_jrb();
        jrb_insert_int(graph.edges, v2, new_jval_v(tree1));
        jrb_insert_int(tree1, v1, new_jval_f(weight));
    }
    else
    {
        node1 = jrb_find_int(graph.edges, v2);
        tree1 = (JRB) jval_v(node1->val);
        jrb_insert_int(tree1, v1, new_jval_f(weight));
    }
}

int hasEdge(Graph graph, int v1, int v2)
{
    int search = 0;
    JRB node = jrb_find_int(graph.edges, v1);
    if(node!=NULL)
    {
        JRB tree = (JRB) jval_v(node->val);
    
        jrb_traverse(node, tree)
        {
            if(jval_i(node->key)==v2) search = 1;
        } 
    }
    return search;
}

int indegree(Graph graph, int v, int* output)
{
    int total = 0; 
    JRB trav, node, search;
    jrb_traverse(trav, graph.edges)
    {
        node = (JRB) jval_v(trav->val);
        search = jrb_find_int(node, v);
        if(search != NULL) output[total++] = jval_i(trav->key);
    }
    return total;
}

int outdegree(Graph graph, int v, int* output)
{
    JRB node = jrb_find_int(graph.edges, v);
    if(node == NULL) return 0;
    JRB tree = (JRB) jval_v(node->val);
    int total = 0; 
    jrb_traverse(node, tree)
    {
        output[total++] = jval_i(node->key);
    } 
    return total;
}

int getAdjacentVertices(Graph graph, int v, int* output)
{
    int output1[100]; 
    int output2[100];
    int amount1, amount2;
    amount1 = indegree(graph, v, output1);
    amount2 = outdegree(graph, v, output2);
    for(int i = amount1, j=0; i<(amount1+amount2); i++, j++)
    {
        output1[i] = output2[j];
    }
    for(int i=0; i<(amount1+ amount2); i++)
    {
        output[i] = output1[i];
    }
    return amount1+amount2;
}

int Number_of_Vertex_in_Graph(Graph graph)
{
    int stop = 0;
    JRB trav;
    jrb_traverse(trav, graph.vertices)
    {
        if(strcmp(jval_s(trav->val), "NULL")==0) continue;
        stop++;
    }
    return stop;
}

void Print_Graph_Vertex(Graph graph)
{
    JRB trav;
    jrb_traverse(trav, graph.vertices)
    {
        if(strcmp(jval_s(trav->val), "NULL")==0) continue;
        else printf("%d %s\n", trav->key, jval_s(trav->val));
    }
}

void Print_Graph_Map(Graph graph)
{
    int row, columns;
    for (row=1; row<=Number_of_Vertex_in_Graph(graph); row++)   
    {
        for(columns=1; columns<=Number_of_Vertex_in_Graph(graph); columns++)
        { 
            printf("%d ", hasEdge(graph, row, columns));
        }
        printf("\n");
    }
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

int DAG_Full_Graph(Graph graph)
{
    //Create Stuffs
    int visited[Number_of_Vertex_in_Graph(graph)];
    Stack stack = createStack();
    Jval position;
    int output[Number_of_Vertex_in_Graph(graph)];
    int n;
    int vertices;
    int stop = 0;

    //find start and stop
    JRB trav;
    jrb_traverse(trav, graph.vertices) stop++;

    //Check DAG
    for (vertices = 0; vertices<=Number_of_Vertex_in_Graph(graph); vertices++)
    {
        for(int i=0; i<=Number_of_Vertex_in_Graph(graph); i++) visited[i] = 0;

        Push(stack, new_jval_i(vertices)); 
        while(Is_Stack_Empty(stack)==0)
        {
            position = Pop(stack);
            if(*(visited + jval_i(position)) == 0)
            {
                n = outdegree (graph, jval_i(position), output);
                if(n != 0)
                {
                    for(int i=0; i<n; i++) 
                    {
                        if( output[i] == vertices ) return 0;
                        if( *(visited + output[i]) == 0) Push(stack, new_jval_i(output[i]));
                    }
                }
                *(visited + jval_i(position)) = 1;
            }
        }
    }
    return 1;
}

float getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.edges, v1);
    JRB tree = (JRB) jval_v(node->val);
    JRB search = jrb_find_int(tree, v2);
    if(search == NULL) return INFINITIVE_VALUE;
    else return jval_f(search->val);
}

void Topo_Sort (Graph graph)
{
    if ( !DAG_Full_Graph(graph) ) 
    {
        printf("Have cycles in the graph\n");
        return;
    }

    Queue queue = createQueue();
    int vertices;
    int output[Number_of_Vertex_in_Graph(graph)];
    int output1[Number_of_Vertex_in_Graph(graph)];
    Jval position;
    int count;
    int w_vertices;

    for (vertices = 0; vertices<Number_of_Vertex_in_Graph(graph); vertices++)
        if(indegree(graph, vertices, output)==0) Enqueue(queue, new_jval_i(vertices));

    while(!Is_Queue_Empty(queue))
    {
        position = Dequeue(queue);
        //print ra man hinh, co the dieu chinh
        printf("%s ", jval_s(jrb_find_int(graph.vertices, jval_i(position))->val) );
        count = outdegree(graph, jval_i(position), output);
        for(int i=0; i<count; i++)
        {
            w_vertices = indegree(graph, output[i], output1);
            if(w_vertices - 1 == 0) Enqueue(queue, new_jval_i(output[i]));
        }
        if(jrb_find_int(graph.edges, jval_i(position))!=NULL) jrb_delete_node(jrb_find_int(graph.edges, jval_i(position)));
    }
}

int Dijkstra(Graph graph, int start, float* distance, int* previous)
{
    int visited[Number_of_Vertex_in_Graph(graph)+1];
    for(int i=0; i<Number_of_Vertex_in_Graph(graph)+1; i++) visited[i]=0;

    for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++) 
    {
        *(distance + i) = INFINITIVE_VALUE;
        *(previous + i) = -1; //Graph khong co dinh ID am        
    }
    *(distance + start) = 0;

    P_Queue p_queue = create_P_Queue();
    p_queue = P_Enqueue(p_queue, start, *(distance + start));

    int count, u, lenght = 0;
    int output[Number_of_Vertex_in_Graph(graph)];
    while(!Is_P_Queue_Empty(p_queue))
    {
        p_queue = P_Dequeue(p_queue, &u);
        *(visited + u) = 1;

        count = outdegree(graph, u, output);
        for(int i=0; i<count; i++)
        {
            if( *(visited + output[i]) == 0 )
            {
                if(distance[output[i]] > distance[u] + getEdgeValue(graph, u, output[i]))
                { 
                    distance[output[i]] = distance[u] + getEdgeValue(graph, u, output[i]);
                    previous[output[i]] = u;
                    lenght++;
                    p_queue = P_Enqueue(p_queue, output[i], distance[output[i]]); 
                }
            }
        }
    }
    return lenght;
}

int BellmanFord(Graph graph, int start, float* distance, int* previous)
{
    for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++) 
    {
        *(distance + i) = INFINITIVE_VALUE;
        *(previous + i) = -1; //Graph khong co dinh ID am        
    }
    *(distance + start) = 0;

    int output[Number_of_Vertex_in_Graph(graph)];
    int count;
    float tempDistance;
    int path = 0;
    for(int v=1; v<=Number_of_Vertex_in_Graph(graph); v++)
    {
        for(int v=1; v<=Number_of_Vertex_in_Graph(graph); v++)
        {
            count = outdegree(graph, v, output);
            for(int u=0; u<count; u++)
            {
                tempDistance = getEdgeValue(graph, v, output[u]) + *(distance + output[u]);
                if(tempDistance < *(distance + v))
                {
                    *(distance + v) = tempDistance;
                    *(previous + v) = output[u];
                    path++;
                }
            }
        }
    }
    return path;
}

int PathCreate(int* previous, int start, int end, int length, int* path)
{
    if(end == -1) return 1;
    if(start == end) 
    {
        *(path + length) = start;
        return length;
    }
    int l = length;
    *(path + l) = end;
    *(path + l + 1) = *(previous + end);
    return PathCreate(previous, start, *(previous + end), length + 1, path);
}

int BFS(Graph graph, int start, int stop, int* trav)
{
    int amount = 0;
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.vertices) count++;

    int *visited = (int*)calloc(count, sizeof(int)+1);

    Queue queue = createQueue();
    Enqueue(queue, new_jval_i(start)); 

    Jval position;
    int output[count];
    int n;
    while( Is_Queue_Empty(queue)==0 )
    {
        position = Dequeue(queue);
        if( *(visited + position.i) == 0 )
        {
            *(trav + amount) = position.i;
            amount++;
            *(visited + position.i) = 1;
            if( *(visited + stop) == 1 ) break;
            n = outdegree(graph, position.i, output);
            for(int i=0; i<n; i++) 
            {
                if( *(visited + output[i]) == 0 )
                {
                    Enqueue(queue, new_jval_i(output[i]));
                } 
            }
        }
        
    }
    free(visited);
    return amount;
}

int DFS(Graph graph, int start, int stop, int* trav)
{
    int amount = 0;
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.vertices) count++;

    int *visited = (int*)calloc(count, sizeof(int)+1);

    Stack stack = createStack();
    Push(stack, new_jval_i(start)); 

    Jval position;
    int output[count];
    int n;
    while(Is_Stack_Empty(stack)==0)
    {
        position = Pop(stack);
        if( *(visited + position.i) == 0 )
        {
            *(trav + amount) = position.i;
            amount++;
            *(visited + position.i) = 1;
            if( *(visited + stop) == 1 ) break;
            n = outdegree(graph, position.i, output);
            for(int i=0; i<n; i++) 
            {
                if( *(visited + output[i]) == 0 )
                {
                    Push(stack, new_jval_i(output[i]));
                } 
            }
        }
        
    }
    free(visited);
    return amount;
}