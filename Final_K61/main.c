#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

typedef struct
{
    char name[30];
    int id;
}Sanpham;

typedef struct
{
    int id[10];
    int amount[10];
}Khohang_Sanpham;

typedef struct
{
    char name[30];
    int id;
}Khohang;

typedef struct
{
    int id1;
    int id2;
    int weight;
}Khohang_Map;

int hour (int minutes)
{
    int hours = minutes/60;
    return hours;
}

int min (int minutes)
{
    int mins = minutes%60;
    return mins;
}

int main(int argc, char* argv[])
{
    if(argc >= 9)
    {
        printf("Wrong! Again!");
    }

    int so_luong_sanpham = 1;
    Graph graph_sanpham; graph_sanpham = createGraph();
    Graph graph_khohang; graph_khohang = createGraph();
    Sanpham sanpham[10];
    Khohang khohang[10];
    Khohang_Map map[10];
    Khohang_Sanpham khohang_sanpham[10];

    //Xu li File Sanpham
    FILE* f = fopen("sanpham.txt", "r");
    if(f==NULL)
    {
        printf("Cannot open File.\n");
        exit(1);
    }

    while(!feof(f))
    {
        fscanf(f, "%s %d\n", sanpham[so_luong_sanpham].name, &sanpham[so_luong_sanpham].id);
        so_luong_sanpham++;
    }
    fclose(f);

    for(int i=1; i<so_luong_sanpham; i++) addVertex(graph_sanpham, sanpham[i].id, sanpham[i].name);

    //Xu li FIle Kho hang
    FILE* f1 = fopen("khohang.txt", "r");
    if(f1==NULL)
    {
        printf("Cannot open File.\n");
        exit(1);
    }
    
    char string1[2];
    fgets(string1, 2, f1);
    for(int i=1; i<=atoi(string1); i++)
    {
        fscanf(f1, "%s %d\n", khohang[i].name, &khohang[i].id);
        for(int j=1; j<so_luong_sanpham; j++)
        {
            fscanf(f1, "%d %d\n", &khohang_sanpham[i].id[j], &khohang_sanpham[i].amount[j]);
        }
    }

    for(int i=1; i<=atoi(string1); i++) addVertex(graph_khohang, khohang[i].id, khohang[i].name);

    fgets(string1, 2, f1);
    for(int i=1; i<=atoi(string1); i++)
    {
        fscanf(f1, "%d %d %d\n", &map[i].id1, &map[i].id2, &map[i].weight);
    }
    fclose(f1);

    for(int i=1; i<=atoi(string1); i++) non_addEdge(graph_khohang, map[i].id1, map[i].id2, map[i].weight);

    //Chuc nang
    if(argc == 2 && strcmp(argv[1], "-t")==0) printf("C-Advanced, HK20182\n");

    else if(argc == 3 && strcmp(argv[1], "-s")==0 && strcmp(argv[2], "sanpham.txt")==0)
    {
        JRB trav;
        jrb_traverse(trav, graph_sanpham.vertices) printf("%s %d\n", jval_s(trav->val), trav->key);
    }

    else if(argc == 5 && strcmp(argv[1], "-w")==0 && strcmp(argv[2], "khohang.txt")==0)
    {
        int id_khohang_1 = atoi(argv[3]);
        int id_khohang_2 = atoi(argv[4]);

        JRB search1 = jrb_find_int(graph_khohang.vertices, id_khohang_1);
        JRB search2 = jrb_find_int(graph_khohang.vertices, id_khohang_2);
        if(search1 == NULL || search2 == NULL) printf("-1\n");
        else
        {
            int weight = getEdgeValue(graph_khohang, atoi(argv[3]), atoi(argv[4]));
            if (weight == INFINITIVE_VALUE) printf("-1\n");
            else printf("%d km", weight);
        }
    }
    
    else if(argc == 4 && strcmp(argv[1], "-a")==0 && strcmp(argv[2], "khohang.txt")==0 &&strcmp(argv[3], "sanpham.txt")==0)
    {
        JRB trav1;
        jrb_traverse(trav1, graph_khohang.vertices)
        {
            printf("%s\n", jval_s(trav1->val));
            for(int i=1; i<so_luong_sanpham; i++)
            {
                printf("%s %d\n", sanpham[i].name, khohang_sanpham[jval_i(trav1->key)].amount[i]);
            }
            if(jval_i(trav1->key) != Number_of_Vertex_in_Graph(graph_khohang)) printf("----\n");
        }
    }

    else if(argc == 6 && strcmp(argv[1], "-h")==0 && strcmp(argv[2], "khohang.txt")==0 &&strcmp(argv[3], "sanpham.txt")==0)
        {
            int id_sanpham = atoi(argv[4]), id_khohang = atoi(argv[5]);


            JRB search = jrb_find_int(graph_khohang.vertices, id_khohang);
            if(search==NULL) printf("Kho hang khong ton tai.\n");
            else
            {
                printf("%s\n", khohang[id_khohang].name);
                printf("%s %d\n", sanpham[id_sanpham].name, khohang_sanpham[id_khohang].amount[id_sanpham]);
            }
            printf("--- Cac kho khe la:\n");
            int output[10];
            int amount = outdegree(graph_khohang, id_khohang, output);
            for(int i=0; i<amount; i++)
            {
                printf("%s\n", khohang[output[i]]);
                printf("%s %d\n", sanpham[id_sanpham].name, khohang_sanpham[output[i]].amount[id_sanpham]);
            }
        }

    else if(argc == 8 && strcmp(argv[1], "-g")==0 && strcmp(argv[2], "khohang.txt")==0 && strcmp(argv[3], "sanpham.txt")==0)
    {
        int id_sanpham_mua = atoi(argv[4]), so_luong_sanpham_mua = atoi(argv[5]), id_khohang_gan_nhat = atoi(argv[6]), id_khohang_du_bi = atoi(argv[7]);

        if(khohang_sanpham[id_khohang_gan_nhat].amount[id_sanpham_mua] >= so_luong_sanpham_mua) printf("Dat hang thanh cong, thoi gian giao hang la: 30 phut");
        else if (khohang_sanpham[id_khohang_gan_nhat].amount[id_sanpham_mua] + khohang_sanpham[id_khohang_du_bi].amount[id_sanpham_mua] < so_luong_sanpham_mua) printf("Dat hang khong thanh cong.\n");
        else
        {
            printf("Dat hang thanh cong, ");
            float distance[100];
            int previous[100];
            int length = Dijkstra(graph_khohang, id_khohang_du_bi, distance, previous);

            if(distance[id_khohang_gan_nhat] == INFINITIVE_VALUE) printf("404 NOT FOUND.");
            else
            {
                int minutes = (int)( (distance[id_khohang_gan_nhat] / 0.5) + 30);
                printf("thoi gian giao hang la: %d gio %d phut.\n", hour(minutes), min(minutes));
            }
        }
    }
    else printf("Don't know what to do, please re-run the Program.");

    dropGraph(graph_sanpham);
    dropGraph(graph_khohang);
    return 0;
}