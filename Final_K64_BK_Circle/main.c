#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fields.h>
#include "graph.h"

typedef struct
{
    int id;
    char name[25];
}Data;

int getGraphID_Data(Graph graph, Data *data, int id)
{
    char name[30];
    for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
    {
        if(data[i].id == id) strcpy(name, data[i].name);
    }

    JRB trav;
    jrb_traverse(trav, graph.vertices)
    {
        if(strcmp(jval_s(trav->val), name)==0) return jval_i(trav->key);
    }
    return -1;
}

int main()
{
    int menu = -1, count = 0;
    Graph graph; graph = createGraph();
    Data data[100];

    do
    {
        printf("___MENU___\n");
        printf("1. Input Data.\n");
        printf("2. List friend.\n");
        printf("3. Popular person.\n");
        printf("4. Check friend.\n");
        printf("5. Suggest friend.\n");
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

            IS is = new_inputstruct("users.txt");
            if(is == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            get_line(is);
            int num_users = atoi(is->fields[0]);
            for(int i=0; i<num_users; i++)
            {
                get_line(is);
                data[i+1].id = atoi(is->fields[0]);
                strcpy(data[i+1].name, is->fields[1]);
                printf("%d %s\n", data[i+1].id, data[i+1].name);
                addVertex(graph, i+1, strdup(is->fields[1]));
            }

            jettison_inputstruct(is);

            printf("\n");

            IS is1 = new_inputstruct("friends.txt");
            if(is1 == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            while(get_line(is1) >= 0)
            {
                printf("%s ", is1->fields[0]);
                for(int i=1; i<is1->NF; i++)
                {
                    printf("%s ", is1->fields[i]); 
                    addEdge(graph, getGraphID_Data(graph, data, atoi(is1->fields[0])), getGraphID_Data(graph, data, atoi(is1->fields[i])), 1);
                }
                printf("\n");
            }

            jettison_inputstruct(is1);

            // Print_Graph_Map(graph);
            // Print_Graph_Vertex(graph);

            printf("\n");
            break;
        case 2:
            fflush(stdin);
            
            char name[25];
            goal1: printf("Nhap: "); gets(name); fflush(stdin);
            if(getGraphID(graph, name)==-1)
            {
                printf("Input Error.\n");
                goto goal1;
            }

            int output[100];
            int count = outdegree(graph, getGraphID(graph, name), output);
            if(count < 1) printf("Khong co ban!");
            else 
            {
                for(int i=0; i<count; i++)
                {
                    printf("%s\n", getVertex(graph, output[i]));
                }
            }

            printf("\n");
            break;
        case 3:
            fflush(stdin);

            int count2[100], output2[100];

            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++) count2[i] = outdegree(graph, i, output2);

            Data temp; 
            int temp1;
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                for(int j=i+1; j<=Number_of_Vertex_in_Graph(graph); j++)
                {
                    if(count2[i] < count2[j])
                    {
                        temp = data[i];
                        data[i] = data[j];
                        data[j] = temp;

                        temp1 = count2[i];
                        count2[i] = count2[j];
                        count2[j] = temp1;
                    }
                }
            }

            printf("%-25s %-20s\n", "User", "Number of Friends");
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                printf("%-25s %-20d\n", getVertex(graph, getGraphID_Data(graph, data, data[i].id)), count2[i]);
            }


            printf("\n");
            break;
        case 4:
            fflush(stdin);
            
            char string[25][25];
            goal2:
            printf("Ten nguoi 1: "); gets(string[0]); fflush(stdin);
            printf("Ten nguoi 2: "); gets(string[1]); fflush(stdin);
            if(getGraphID(graph, string[0])==-1 || getGraphID(graph, string[1])==-1)
            {
                printf("Input Error.\n");
                goto goal2;
            }

            if(hasEdge(graph, getGraphID(graph, string[0]), getGraphID(graph, string[1]))) printf("They are friend.\n");
            else printf("They are not friend.\n");
            
            printf("\n");
            break;
        case 5:
            fflush(stdin);
            
            char string1[25];
            goal3:
            printf("Ten nguoi: "); gets(string1); fflush(stdin);
            if(getGraphID(graph, string1)==-1)
            {
                printf("Input Error.\n");
                goto goal3;
            }

            int trav[100], amount;
            amount = BFS(graph, getGraphID(graph, string1), -1, trav);
            // for(int i=0; i<amount; ++i)
            // {
            //     printf("%s ", getVertex(graph, trav[i]));
            // }
            // printf("\n");

            int count4, output4[100];
            count4 = outdegree(graph, getGraphID(graph, string1), output4);

            for(int i=0 + 1 + count4; i<amount; ++i)
            {
                printf("%s ", getVertex(graph, trav[i]));
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