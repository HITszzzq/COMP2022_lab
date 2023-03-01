#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
} Graph;


Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
void computeEcc(Graph g, int *diameter, int *radius);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
void DFS(Graph g,int *visited,int v); //递归不写函数声明会报警告
int mincost(int D[],int S[],int start,int N);

/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s ", g.vertex[path[k]]);
        path_length += g.matrix[path[k]][path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[path[k]]);
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    //TODO
    int i = 0;
    int visited[g.N];
    int *p;
    p = visited;
    for(i = 0;i < g.N;i++) //初始化
    {
        visited[i] = 0;
    }
    DFS(g,p,0);
    for(i = 0;i < g.N;i++)
    {
        if(visited[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

void DFS(Graph g,int *visited,int v) //深度优先遍历
{
    int i = 0;
    visited[v] = 1;
    for(i = 0;i < g.N;i++)
    {
        if((g.matrix[v][i] < max_dis) && (!visited[i]))
        {
            DFS(g,visited,i);
        }
    }
    return;
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    //TODO
    int i = 0,j = 0;
    for(i = 0;i < g.N;i++) //初始化
    {
        node_degree[i] = 0;
    }
    for(i = 0;i < g.N;i++)
    {
        for(j = i + 1;j < g.N;j++) //减少循环次数
        {
            if(g.matrix[i][j] < max_dis)
            {
                node_degree[i]++;
                node_degree[j]++;
            }
        }
    }
    return;
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    //TODO
    int i = 0,j = 0,k = 0;
    double sum = 0;
    double LCC[g.N];
    for(i = 0;i < g.N;i++)
    {
        LCC[i] = 0;
    }
    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g,degree);
    for(i = 0;i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
        {
            for(k = 0;k < g.N;k++)
            {
                if((i != j) && (i != k) && (j != k) && (g.matrix[i][j] < max_dis) && (g.matrix[i][k] < max_dis) && (g.matrix[j][k] < max_dis))
                {
                    LCC[i] = LCC[i] + 1;
                }
            }
        }
    }
    for(i = 0;i < g.N;i++)
    {
        if(degree[i] * (degree[i] - 1) != 0)
        {
            sum = sum + LCC[i] / (double)(degree[i] * (degree[i] - 1));
        }
    }
    return sum / (double)g.N;
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    int i = 0;
    int j = 0;
    int k = 0;
    int p = end;
    int depath[g.N];
    int sum = 0;
    int S[g.N]; //标记是否确定最短路径
    int D[g.N]; //带权长度
    int P[g.N]; //最短路径
    for(i = 0;i < g.N;i++)
    {
        D[i] = g.matrix[start][i];
        S[i] = 0;
        P[i] = start;
    }
    S[start] = 1;
    for(i = 0;i < g.N;i++)
    {
        if(i != start) //排除结点自身
        {
            j = mincost(D,S,start,g.N);
            S[j] = 1;
            for(k = 0;k < g.N;k++)
            {
                if(k != start) //排除结点自身
                {
                    if(S[k] != 1)
                    {
                        sum = D[j] + g.matrix[j][k];
                        if(sum < D[k])
                        {
                            D[k] = sum;
                            P[k] = j;
                        }
                    }
                }
            }
        }
    }
    i = 0;
    while(p != start)
    {
        depath[i] = p;
        p = P[p];
        i++;
    }
    depath[i] = start;
    j = 0;
    while(i >= 0)
    {
        path[j] = depath[i];
        j++;
        i--;
    }
    return D[end];
}

int mincost(int D[],int S[],int start,int N)
{
    int temp = max_dis;
    int i = 0,j = 0;
    for(i = 0;i < N;i++)
    {
        if(i != start) //排除自身结点
        {
            if(!S[i] && D[i] < temp)
            {
                temp = D[i];
                j = i;
            }
        }
    }
    return j;
}

/**
 * 计算图的直径和半径，提示: Floyd算法
 * @param g 图
 * @param diameter 指向直径变量的指针
 * @param radius 指向半径变量的指针
 * @return void
 */
void computeEcc(Graph g, int *diameter, int *radius)
{
    //TODO
    int i = 0;
    int j = 0;
    int k = 0;
    int A[g.N][g.N];
    int Dia = 0;
    int Rad = max_dis;
    int E[g.N];
    for(i = 0;i < g.N;i++) //初始化
    {
        E[i] = 0;
    }
    for(i = 0;i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
        {
            A[i][j] = g.matrix[i][j];
        }
    }
    for(k = 0;k < g.N;k++)
    {
        for(i = 0;i < g.N;i++)
        {
            for(j = 0;j < g.N;j++)
            {
                if(A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }
    for(i = 0;i < g.N;i++)
    {
        for(j = 0;j < g.N;j++)
        {
            if(A[i][j] > E[i])
            {
                E[i] = A[i][j];
            }
        }
    }
    for(i = 0;i < g.N;i++)
    {
        if(E[i] > Dia)
        {
            Dia = E[i];
        }
        if(E[i] < Rad)
        {
            Rad = E[i];
        }
    }
    *diameter = Dia;
    *radius = Rad;
    return;
}

int main() {
    int node_num;
    int edge_num;
    int num;
    int ca = 1;
    int task = 0;
    printf("Please input the number of task:");
    scanf("%d",&task);
    switch(task)
    {
        case 1:
            if (freopen("stu.in", "r", stdin) == NULL) {
                printf("There is an error in reading file stu.in");
            }
            while (scanf("%d %d\n", &node_num, &edge_num) != EOF) {
                printf("\ncase %d:\n", ca++);
                int start_idx, end_idx, weight;
                Graph g = createGraph(node_num);
                for(int i = 0; i < node_num; i++) {
                    sprintf(g.vertex[i], "%d", i);
                }
                for (int i = 0; i < edge_num; i++) {
                    scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
                    g.matrix[start_idx][end_idx] = weight;
                    g.matrix[end_idx][start_idx] = weight;
                }

                printf("connected: %d\n", isConnected(g));

                int *degree = (int *)malloc(sizeof(int) * g.N);
                nodeDegree(g, degree);
                printf("degree distribution:\n");
                for(int i=0; i<g.N; i++)
                {
                    printf("node%s:%d,", g.vertex[i], degree[i]);
                }
                printf("\n");
                free(degree);

                double c = clusteringCoefficient(g);
                printf("clustering coefficient:%f\n", c);

                if(isConnected(g))
                {
                    int *short_path = (int *)malloc(sizeof(int) * g.N);
                    int dis = dijkstra(g, 1, 3, short_path);
                    printf("the shortest path between 1 and 3: %d\n", dis);
                    printPath(dis, short_path, g);
                    free(short_path);

                    int diameter, radius;
                    computeEcc(g, &diameter, &radius);
                    printf("diameter:%d\n", diameter);
                    printf("radius:%d\n", radius);
                }
            }
            break;
        case 2:
            if (freopen("metro.txt", "r", stdin) == NULL) {
                printf("There is an error in reading file metro.txt");
            }
            scanf("%d\n", &node_num);
            scanf("%d\n", &edge_num);
            Graph g = createGraph(node_num);
            for(int i = 0;i < edge_num;i++)
            {
                scanf("%d\n",&num);
                int station[num];
                int distance;
                scanf("%d %d\n",&station[0],&distance);
                for(int k = 1;k < num;k++)
                {
                    scanf("%d %d\n",&station[k],&distance);
                    g.matrix[station[k]][station[k-1]] = distance;
                    g.matrix[station[k-1]][station[k]] = distance;
                    for(int m = k - 2;m >= 0;m--)
                    {
                        g.matrix[station[m]][station[k]] = g.matrix[station[m]][station[m+1]] + g.matrix[station[m+1]][station[k]];
                        g.matrix[station[m]][station[k]] = g.matrix[station[k]][station[m]];
                    }
                }
            }
            fclose(stdin);
            if (freopen("no2metro.txt", "r", stdin) == NULL) {
                printf("There is an error in reading file no2metro.txt");
            }
            scanf("%d\n",&node_num);
            for(int i = 0;i < node_num;i++)
            {
                scanf("%d ",&i);
                scanf("%s\n",&g.vertex[i]);
            }
            fclose(stdin);
            printf("connected: %d\n", isConnected(g));
            int *degree = (int *)malloc(sizeof(int) * g.N);
            nodeDegree(g,degree);
            int degreemax = 0;
            int stationmax;
            for(int i = 0;i < node_num;i++)
            {
                if(degree[i] > degreemax)
                {
                    degreemax = degree[i];
                    stationmax = i;
                }
            }
            printf("\"%s\" station has most changes: %d\n",g.vertex[stationmax],degreemax/2);
            if(isConnected(g))
            {
                int start,end;
                int flag = 0;
                for(int i = 0;i < g.N;i++)
                {
                    if(!strcmp(g.vertex[i],"大学城"))
                    {
                        start = i;
                        flag++;
                    }
                    if(!strcmp(g.vertex[i],"机场"))
                    {
                        end = i;
                        flag++;
                    }
                    if(flag == 2)
                    {
                        break;
                    }
                }
                int *short_path = (int *)malloc(sizeof(int) * g.N);
                int dis = dijkstra(g, start, end, short_path);
                printf("the shortest path between \"大学城站\" and \"机场站\":%d\n", dis);
                printPath(dis, short_path, g);
                free(short_path);
                int diameter, radius;
                computeEcc(g, &diameter, &radius);
                printf("diameter:%d\n", diameter);
                printf("radius:%d\n", radius);
            }
            break;
        default:
            break;
    }
    return 0;
}
