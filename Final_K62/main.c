#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fields.h>
#include "graph.h"

int main()
{
    int menu = -1, count = 0;
    Graph graph; graph = createGraph();

    do
    {
        printf("___MENU___\n");
        printf("1. Read and Print.\n");
        printf("2. Print for Each.\n");
        printf("3. List.\n");
        printf("4. Shortest.\n");
        printf("5. Shortest but Walk.\n");
        printf("6. Exit.\n");
        goal: printf("Your Order, please: "); scanf("%d", &menu);
        if(menu < 1 || menu > 6) 
        {
            printf("We don't do that here. "); goto goal;
        }
        switch (menu)
        {
        case 1:
            fflush(stdin);

            IS is = new_inputstruct("data.txt");
            get_line(is);
            int number_castle = atoi(is->fields[0]);
            int number_edge = atoi(is->fields[1]);

            while(get_line(is) >= 0) non_addEdge(graph, atoi(is->fields[0]), atoi(is->fields[1]), atof(is->fields[2]));

            char string[20];
            for(int i=1; i<=number_castle;i++) 
            {
                sprintf(string, "Catsle %d", i);
                addVertex(graph, i, strdup(string));
            }
            jettison_inputstruct(is);

            //xu ly data
            Print_Graph_Vertex(graph);
            Print_Graph_Map(graph);

            break;
        case 2:
            fflush(stdin);
            JRB trav;
            int output[10]; 
            int output1[10];
            int amount, amount1;
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                trav = jrb_find_int(graph.vertices, i);
                printf("- %s: ", jval_s( trav->val ));
                amount = outdegree(graph, i, output);
                if(amount!=0) 
                {
                    for(int i=0; i<amount; i++)
                    {
                        printf("%d ", output[i]);
                    }
                }
                printf("\n");
            }
            break;
        case 3:
            fflush(stdin);
            JRB trav2;
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                trav2 = jrb_find_int(graph.vertices, i);
                amount = outdegree(graph, i, output);
                if(amount!=0) 
                {
                    for(int j=0; j<amount; j++)
                    {
                        if(getEdgeValue(graph, i, output[j])>=50)
                        {
                            printf("- %s ", jval_s( trav2->val ));
                            break;
                        }
                    }
                    
                }
                printf("\n");
            }

            int max = outdegree(graph, 1, output);
            int pos[100];
            int count1 = 0;
            for(int i=2; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                trav2 = jrb_find_int(graph.vertices, i);
                amount = outdegree(graph, i, output);
                if(max <= amount) max = amount;
            }            

            printf("Has most is %d. This Castle has the most: ", max);
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                if(outdegree(graph, i, output)==max) printf("Castle %d ", i);
            }
            printf("\n");
            break;
        case 4:
            fflush(stdin);
            int start, stop;
            goal1:
            printf("Input start: "); scanf("%d", &start);
            printf("Input stop: "); scanf("%d", &stop);
            if(getVertex(graph, start) == NULL || getVertex(graph, stop) == NULL)
            {
                printf("Input Error! Please do it again.\n");
                goto goal1;
            }
            
            //How to use Dijkstra
            float distance[100];
            int previous[100];
            int length = Dijkstra(graph, start, distance, previous);

            int path[100];
            
            int l1 = PathCreate(previous, start, stop, 1, path);
            if(l1 == 1) printf("ROUTE NOT FOUND.");
            else
            {
                printf("Path between Castle %d and Castle %d: ", start, stop);
                for(int i = l1; i>=1; i--)
                {
                    printf("%d ", path[i]);
                }
            }
            
            printf("\n");
            break;
        case 5:
            fflush(stdin);
            break;
        case 6:
            fflush(stdin);
            dropGraph(graph);
            break;        
        }
    }while(menu != 6);
    
    return 0;
}