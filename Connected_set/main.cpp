#include <iostream>
#include <queue>

#define MaxVertexNum 10    //最大顶点数设为100

using namespace std;
using Vertex=int;         // 用顶点下标表示顶点,为整型
using WeightType = int;   //定义权重类型为int

//图
class Graph {
public:
    int Nv;  // 顶点数
    int Ne;  // 边数 
    WeightType G[MaxVertexNum][MaxVertexNum]; // 邻接矩阵 
    bool* Visited;  //标志是否访问过
public:
    Graph(int VertexNum);  //带参构造函数
    void InsertEdge(Vertex V1, Vertex V2);    //插入边
    void DFS(Vertex V); //DFS
    void BFS(Vertex V); //BFS
    void Init_Visited();  //将Visited全部变为false
};

int main() {
    int Num_of_Node, Num_of_Edge;  //顶点数、边数
    Vertex V1, V2;    //点

    cin >> Num_of_Node >> Num_of_Edge;  //输入顶点数、边数
    Graph G{ Num_of_Node };   //定义图

    //输入图
    for (int i = 0; i < Num_of_Edge; i++) {
        cin >> V1 >> V2;   //输入边
        G.InsertEdge(V1, V2);   //插入边
    }
    
    //DFS
    G.Init_Visited();  //将标识初始为false
    for (int i = 0; i < Num_of_Node; i++) {
        if (G.Visited[i] != true) {
            cout << "{ ";
            G.DFS(i);
            cout << "}\n";
        }
    }
    G.Init_Visited();  //将标识初始为false
    for (int i = 0; i < Num_of_Node; i++) {
        if (G.Visited[i] != true) {
            cout << "{ ";
            G.BFS(i);
            cout << "}\n";
        }
    }

    return 0;
}

Graph::Graph(int VertexNum) {
    Nv = VertexNum;
    Ne = 0;
    Visited = new bool;

    for (int i = 0; i < VertexNum; i++) {
        for (int j = 0; j < VertexNum; j++) {
            G[i][j] = 0;
       }
    }
}

void Graph::InsertEdge(Vertex V1, Vertex V2) {
    //这里可以加判断有没有加过这条边

    //插入边 <V1, V2>
    G[V1][V2] = 1;
    //插入边 <V2, V1>
    G[V2][V1] = 1;

    Ne++;//边数加1
}

void Graph::DFS(Vertex V) {
    cout << V << " ";    //输出V
    Visited[V] = true; // 标记V已访问,防止出现死循环 

    for (int i=0; i<Nv; i++) {
        if (!Visited[i] && G[V][i]) {
            DFS(i);
        }
    }
}

void Graph::BFS(Vertex V) {
    queue<Vertex> Q;
    Vertex W;

    cout << V << " ";    //输出V
    Visited[V] = true; // 标记V已访问,防止出现死循环 
    Q.push(V);

    while (!Q.empty()) {
        W = Q.front();
        Q.pop();
        for (int i = 0; i < Nv; i++) {
            if (!Visited[i] && G[W][i]) {
                cout << i << " ";    //输出V
                Visited[i] = true; // 标记V已访问,防止出现死循环 
                Q.push(i);
            }
        }
    }
}

void Graph::Init_Visited() {
    for (int i = 0; i < Nv; i++) {
        Visited[i] = false;
    }
}