#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fields.h>
#include "graph.h"

typedef struct
{
    char url[250];
    int id;
    double page_rank;
}Node;

void Page_Rank_Update(Graph graph, Node* node)
{
    int count, output[10], output1[10];
    double a, page_rank[10];
    for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
    {   
        page_rank[i] = 0;
        count = indegree(graph, i, output);
        for(int j=0; j<count; j++)
        {   
            a = (double)outdegree(graph, output[j], output1);
            page_rank[i] += (node[ output[j] ].page_rank) / a;
        }
    }
    for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++) if(page_rank[i]!=0) node[i].page_rank = page_rank[i];
}

int Node_ID_to_Graph_ID (int node_id, Node* node, Graph graph)
{
    char string[250];
    for(int i=1; i<=100; i++)
    {
        if(node[i].id == node_id) strcpy(string, node[i].url);
    }

    JRB trav;
    jrb_traverse(trav, graph.vertices)
    {
        if(strcmp(string, jval_s(trav->val))==0) return jval_i(trav->key);
    }

    return 0;
}

int main()
{
    int menu = -1, count = 0;
    Graph graph; graph = createGraph();
    Node node[100];

    do
    {
        printf("___MENU___\n");
        printf("1. Chuc nang 1.\n");
        printf("2. Chuc nang 2.\n");
        printf("3. Chuc nang 3.\n");
        printf("4. Chuc nang 4.\n");
        printf("5. Chuc nang 5.\n");
        printf("6. Exit.\n");
        goal: printf("Your Order, please: "); scanf("%d", &menu);
        if(menu < 1 || menu > 7) 
        {
            printf("We don't do that here. "); goto goal;
        }
        switch (menu)
        {
        case 1:
            fflush(stdin);

            //Doc File
            IS is = new_inputstruct("webpages.txt");
            if(is == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            int i=1;
            while(get_line(is) >= 0)
            {
                if(is->line == 1) continue;
                strcpy(node[i].url, is->fields[0]);
                node[i].id = atoi(is->fields[1]);
                //printf("%d - %d %s\n", i, node[i].id, node[i].url);
                addVertex(graph, i, strdup(is->fields[0]));
                i++;
            }
            jettison_inputstruct(is);

            IS is1 = new_inputstruct("pageConnections.txt");
            if(is1 == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            while(get_line(is1) >= 0)
            {
                if(is1->line == 1) continue;
                for(int i=1; i<is1->NF; i++)
                {
                    // printf("%s %s\n", is1->fields[0], is1->fields[i]);
                    // printf("%d %d\n", Node_ID_to_Graph_ID(atoi(is1->fields[0]), node, graph), Node_ID_to_Graph_ID(atoi(is1->fields[i]), node, graph));
                    addEdge(graph, Node_ID_to_Graph_ID(atoi(is1->fields[0]), node, graph), Node_ID_to_Graph_ID(atoi(is1->fields[i]), node, graph), 1);
                }
            }
            jettison_inputstruct(is1);

            Print_Graph_Map(graph);

            int min = 10, max = 0, count, max_pos= 0, min_pos = 0;
            int output[100];
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                count = indegree(graph, i, output);
                if(max < count) 
                {
                    max = count;
                    max_pos = i;
                }
                if(min > count) 
                {
                    min = count;
                    min_pos = i;
                }
            }

            printf("Webpage co nhieu lien ket nhat: %s\n", getVertex(graph, max_pos));
            printf("Webpage co it lien ket nhat: %s\n", getVertex(graph, min_pos));

            printf("\n");
            break;
        case 2:
            fflush(stdin);
            
            for(int i=1; i<=100; i++) node[i].page_rank = 1;
            Page_Rank_Update(graph, node);

            double page_rank_max = 0, page_rank_min = 100;
            int page_rank_max_pos, page_rank_min_pos;
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                if(page_rank_max < node[i].page_rank) 
                {
                    page_rank_max = node[i].page_rank;
                    page_rank_max_pos = i;
                }
                if(page_rank_min > node[i].page_rank) 
                {
                    page_rank_min = node[i].page_rank;
                    page_rank_min_pos = i;
                }
            }

            // for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            // {
            //     printf("%s %lf\n", node[i].url, node[i].page_rank);
            // }
            // printf("\n");
            printf("Webpage co Page Rank cao nhat: %s\n", getVertex(graph, page_rank_max_pos));
            printf("Webpage co Page Rank it nhat: %s\n", getVertex(graph, page_rank_min_pos));

            printf("\n");
            break;
        case 3:
            fflush(stdin);

            int m;
            goal1: printf("How many times to PageRank?: "); scanf("%d", &m);
            if(!(m >= 10 && m <= 50)) 
            {
                printf("Must between 10 and 50.\n");
                goto goal1;
            }

            for(int i=0; i<m; i++) Page_Rank_Update(graph, node);

            Node temp;
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                for(int j=i+1; j<=Number_of_Vertex_in_Graph(graph); j++)
                {
                    if(node[i].page_rank <= node[j].page_rank)
                    {
                        temp = node[i];
                        node[i] = node[j];
                        node[j] = temp;
                    }
                }
            }

            // for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            // {
            //     printf("%s %lf\n", node[i].url, node[i].page_rank);
            // }
            // printf("\n");
            for(int i=1; i<=3; i++)
            {
                printf("%s\n", node[i].url);
            }

            printf("\n");
            break;
        case 4:
            fflush(stdin);
            
            int spam_bot[100], not_spam_bot[100], output1[100], output2[100];
            int pos1 = 0, pos2 = 0; 
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                if(indegree(graph, i, output1)!=0 && outdegree(graph, i, output2)==0)
                {
                    not_spam_bot[pos1] = i;
                    pos1++;
                }
                if(indegree(graph, i, output1)==0 && outdegree(graph, i, output2)!=0)
                {
                    spam_bot[pos2] = i;
                    pos2++;
                }
            }

            printf("Webpage chi co den, khong co ra: \n");
            for(int i=0; i<pos1; i++) printf("- %s\n", getVertex(graph, not_spam_bot[i]));
            printf("Co %d Spam bot: \n", pos2);
            for(int i=0; i<pos2; i++) printf("- %s\n", getVertex(graph, spam_bot[i]));


            printf("\n");
            break;
        case 5:
            fflush(stdin);

            int id1, id2;
            goal2:
            printf("ID1: "); scanf("%d", &id1);
            printf("ID2: "); scanf("%d", &id2);
            if(getVertex(graph, Node_ID_to_Graph_ID(id1, node, graph))==NULL)
            {
                printf("ID1 khong hop le, vui long nhap lai.\n");
                goto goal2;
            }
            else if(getVertex(graph, Node_ID_to_Graph_ID(id2, node, graph))==NULL)
            {
                printf("ID2 khong hop le, vui long nhap lai.\n");
                goto goal2;
            }
            else if(id1 == id2) printf("-1.\n");

            float distance[100];
            int previous[100];
            int length = Dijkstra(graph, Node_ID_to_Graph_ID(id1, node, graph), distance, previous);

            int path[100];
            
            int l1 = PathCreate(previous, Node_ID_to_Graph_ID(id1, node, graph), Node_ID_to_Graph_ID(id2, node, graph), 1, path);
            if(l1 == 1) printf("ROUTE NOT FOUND.\n");
            else
            {
                printf("Khoan canh nho nhat giua Webpage co %d and Webpage co %d la %d: ", id1, id2, l1-1);
                for(int i = l1; i>=1; i--)
                {
                    printf("%d ", node[path[i]].id);
                }
            }
            printf("\n");
            break;    
        case 6:
            fflush(stdin);
            dropGraph(graph);
            break;        
        }
    }while(menu != 6);
    
    return 0;
}