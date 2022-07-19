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
        printf("1. Read file.\n");
        printf("2. Chuc nang 2.\n");
        printf("3. Chuc nang 3.\n");
        printf("4. Chuc nang 4.\n");
        printf("5. Chuc nang 5.\n");
        printf("6. Chuc nang 6.\n");
        printf("7. Chuc nang 7.\n");
        printf("8. Chuc nang 8.\n");
        printf("9. Chuc nang 9.\n");
        printf("10. Exit.\n");
        goal: printf("Your Order, please: "); scanf("%d", &menu);
        if(menu < 1 || menu > 11) 
        {
            printf("We don't do that here. "); goto goal;
        }
        switch (menu)
        {
        case 1:
            fflush(stdin);

            IS is = new_inputstruct("tiepXucGan.txt");
            if(is == NULL)
            {
                printf("Cannot open file.");
                exit(1);
            }

            get_line(is);
            int number_vertex = atoi(is->fields[0]);
            char charater;
            char string[10];
            for(int i=1; i<=number_vertex; i++)
            {
                charater = 64 + i;
                sprintf(string, "%c", charater);
                string[1] = '\0';
                addVertex(graph, i, strdup(string));
            }

            while(get_line(is) >= 0)
            {
                for(int i=1; i<is->NF; i++)
                {
                    addEdge(graph, getGraphID(graph, is->fields[0]), getGraphID(graph, is->fields[i]), 1);
                }
            }

            jettison_inputstruct(is);

            printf("\n");
            break;
        case 2:
            fflush(stdin);
            
            int count, output[10];
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                printf("%s: ", getVertex(graph, i));
                count = outdegree(graph, i, output);
                for(int j=0; j<count; j++)
                {
                    printf("%s ", getVertex(graph, output[j]));
                }
                printf("\n");
            }

            printf("\n");
            break;
        case 3:
            fflush(stdin);

            char string1[10], string2[10];
            goal1:
            printf("Ten nguoi thu nhat: "); gets(string1); fflush(stdin);
            printf("Ten nguoi thu hai: "); gets(string2); fflush(stdin);
            if(getGraphID(graph, string1)==-1 || getGraphID(graph, string2)==-1)
            {
                printf("Input Error. Please do it again.\n");
                goto goal1;
            }

            if(hasEdge(graph, getGraphID(graph, string1), getGraphID(graph, string2))==1)
            {
                printf("Co tiep xuc.\n");
            }
            else printf("Khong tiep xuc.\n");

            printf("\n");
            break;
        case 4:
            fflush(stdin);
            
            char string3[10];
            goal2:
            printf("Ten nguoi can tim: "); gets(string3); fflush(stdin);
            if(getGraphID(graph, string3)==-1)
            {
                printf("Input Error. Please do it again.\n");
                goto goal2;
            }
            
            printf("Nhung nguoi tiep xuc voi %s la: ", string3);
            int output1[10];
            int count1 = outdegree(graph, getGraphID(graph, string3), output1);
            for(int i=0; i<count1; i++)
            {
                printf("%s ", getVertex(graph, output1[i]));
            }

            printf("\n");
            break;
        case 5:
            fflush(stdin);
            
            int max_tiep_xuc = 0, count3, output2[10];
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                count3 = outdegree(graph, i, output2);
                if(max_tiep_xuc < count3) max_tiep_xuc = count3;
            }

            printf("Nhung nguoi tiep xuc nhieu nhat: ");
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                count3 = outdegree(graph, i, output2);
                if(max_tiep_xuc == count3) printf("%s ", getVertex(graph, i));
            }

            printf("\n");
            break;
        case 6:
            fflush(stdin);
            
            char string4[10];
            goal3:
            printf("F0: "); gets(string4); fflush(stdin);
            if(getGraphID(graph, string4)==-1)
            {
                printf("Input Error. Please do it again.\n");
                goto goal3;
            }

            printf("Danh sach F1: ");
            int output3[10];
            int count4 = outdegree(graph, getGraphID(graph, string4), output3);
            for(int i=0; i<count4; i++)
            {
                printf("%s ", getVertex(graph, output3[i]));
            }
            printf("\n");
            printf("Danh sach F2: ");
            int count5[10], output4[10];
            int print = 1;
            for(int i=0; i<count4; i++)
            {
                count5[i] = outdegree(graph, output3[i], output4);
                for(int j=0; j<count5[i]; j++)
                {
                    for(int k=0; k<count4; k++)
                    {
                        if(output4[j] == output3[k] || output4[j] == getGraphID(graph, string4)) 
                        {
                            print = 0;
                            break;
                        }
                        else print = 1;
                    }
                    if(print) printf("%s ", getVertex(graph, output4[j]));
                }
            }

            printf("\n");
            break;
        case 7:
            fflush(stdin);
            
            char string5[10];
            goal5: printf("Ten nguoi bo sung: "); gets(string5); fflush(stdin);
            if(getGraphID(graph, string5) > 0)
            {
                printf("Nguoi nay da ton tai");
                goto goal5;
            }
            addVertex(graph, Number_of_Vertex_in_Graph(graph)+1, string5);

            int number;
            printf("Nguoi nay tiep xuc voi may nguoi: "); scanf("%d", &number); fflush(stdin);

            char string6[10][10];
            for(int i=0; i<number; i++)
            {
                goal4: printf("Nguoi thu %d: ", i+1); gets(string6[i]); fflush(stdin);
                if(getGraphID(graph, string6[i])==-1) 
                {
                    printf("Nguoi nay khong ton tai.\n");
                    goto goal4;
                }
                else if(strcmp(string6[i], string5)==0)
                {
                    printf("Trung nguoi.\n");
                    goto goal4;
                }
                non_addEdge(graph, getGraphID(graph, string5), getGraphID(graph, string6[i]), 1);
            }

            Print_Graph_Vertex(graph);
            Print_Graph_Map(graph);

            printf("\n");
            break;
        case 8:
            fflush(stdin);
            
            char string7[2][10];
            goal6: 
            printf("Ten nguoi 1: "); gets(string7[0]); fflush(stdin);
            printf("Ten nguoi 2: "); gets(string7[1]); fflush(stdin);
            if(getGraphID(graph, string7[0]) == -1 || getGraphID(graph, string7[1]) == -1 )
            {
                printf("Co nguoi khong ton tai.\n");
                goto goal6;
            }

            addEdge(graph, getGraphID(graph, string7[0]), getGraphID(graph, string7[1]), 1);

            printf("\n");
            break;
        case 9:
            fflush(stdin);
            
            FILE* f = fopen("tiepXucGan_copy.txt", "w");
            int amount, out[10];
            //sprintf(str, "%d\n", Number_of_Vertex_in_Graph(graph));
            fprintf(f, "%d\n", Number_of_Vertex_in_Graph(graph));
            for(int i=1; i<=Number_of_Vertex_in_Graph(graph); i++)
            {
                fprintf(f, "%s ", getVertex(graph, i));
                amount = outdegree(graph, i, out);
                for(int j=0; j<amount; j++)
                {
                    fprintf(f, "%s ", getVertex(graph, out[j]));
                }
                if(i != Number_of_Vertex_in_Graph(graph)) fputs("\n", f);
            }
            fclose(f);

            printf("\n");
            break;  
        case 10:
            fflush(stdin);
            dropGraph(graph);
            break;        
        }
    }while(menu != 10);
    
    return 0;
}