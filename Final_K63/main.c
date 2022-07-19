#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fields.h>
#include "graph.h"

typedef struct
{
    int id1;
    int id2;
    int distance;
}Data;

int main()
{
    int menu = -1, count = 0;
    Graph graph; graph = createGraph();
    Data data[100];

    do
    {
        printf("___MENU___\n");
        printf("1. In danh sach dinh.\n");
        printf("2. Tim ban than thiet.\n");
        printf("3. Kiem tra quan he bac cau.\n");
        printf("4. Tim ban chung.\n");
        printf("5. Thoat.\n");
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
            if(is == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            get_line(is);
            int num_vertex = atoi(is->fields[0]);
            int num_edge = atoi(is->fields[1]);

            while(num_vertex > 0)
            {
                get_line(is);
                addVertex(graph, atoi(is->fields[0]), strdup(is->fields[1]));
                num_vertex--;
            }

            while(num_edge > 0)
            {
                get_line(is);
                non_addEdge(graph, atoi(is->fields[0]), atoi(is->fields[1]), atoi(is->fields[2]));
                num_edge--;
            }
            jettison_inputstruct(is);

            Print_Graph_Vertex(graph);
            Print_Graph_Map(graph);

            printf("\n");
            break;
        case 2:
            fflush(stdin);

            int ID;
            printf("Nhap ID: "); scanf("%d", &ID);
            JRB search = jrb_find_int(graph.vertices, ID);
            if(search==NULL) printf("-1\n");
            else
            {
                int output[10];
                int count = outdegree(graph, ID, output);
                if(count == 0) printf("-1\n");
                else
                {
                    float weight = getEdgeValue(graph, ID, output[0]);
                    for(int i=1; i<count; i++)
                    {
                        if (getEdgeValue(graph, ID, output[i])>weight) weight = getEdgeValue(graph, ID, output[i]);
                    }
                    printf("%g\n", weight);
                    
                    for(int i=0; i<count; i++) printf("%d %s\n", output[i], jval_s(jrb_find_int(graph.vertices, output[i])->val));
                }
            }
            
            printf("\n");
            break;
        case 3:
            fflush(stdin);

            int id1, id2;
            printf("ID1: "); scanf("%d", &id1);
            printf("ID2: "); scanf("%d", &id2);

            float distance[100];
            int previous[100];
            int length = Dijkstra(graph, id1, distance, previous);
            if(hasEdge(graph, id1, id2)) printf("-1\n");
            else if(previous[id2]==INFINITIVE_VALUE) printf("-1\n");
            else printf("1\n");

            printf("\n");
            break;
        case 4:
            fflush(stdin);
            int id3, id4;
            printf("ID1: "); scanf("%d", &id3);
            printf("ID2: "); scanf("%d", &id4);

            int output1[10], output2[10], common[10];
            int count1, count2, count3 = 0;
            count1 = outdegree(graph, id3, output1);
            count2 = outdegree(graph, id4, output2);
            for(int i=0; i<count1; i++)
            {
                for(int j=0; j<count2; j++)
                {
                    if(output1[i]==output2[j]) 
                    {
                        common[count3] = output1[i];
                        count3++;
                    }
                }
            }

            if(count3==0) printf("Khong co ban chung.\n");
            else
            {
                printf("%d\n", count3);
                for(int i=0; i<count3; i++)
                {
                    printf("%d %s\n", common[i], jval_s(jrb_find_int(graph.vertices, common[i])->val) );
                }
            }
            
            printf("\n");
            break;
        case 5:
            fflush(stdin);
            dropGraph(graph);
            break;        
        }
    }while(menu != 5);
    
    return 0;
}