#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

#define MaxVertexNum 100    //最大顶点数设为1000

using namespace std;
using Vertex = int;         // 用顶点下标表示顶点,为整型
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
    double BFS(Vertex V); //BFS
    void Init_Visited();  //将Visited全部变为false
};

int main() {
    int Num_of_Node, Num_of_Edge;  //顶点数、边数
    Vertex V1, V2;    //点
    double percent;   //百分比

    cin >> Num_of_Node >> Num_of_Edge;  //输入顶点数、边数
    Graph G{ Num_of_Node };   //定义图

    //输入图
    for (int i = 0; i < Num_of_Edge; i++) {
        cin >> V1 >> V2;   //输入边
        G.InsertEdge(V1-1, V2-1);   //插入边
    }

    //对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比
    for (int i = 0; i < Num_of_Node; i++) {
        G.Init_Visited();
        percent = G.BFS(i);
        cout.setf(ios::fixed);
        cout <<i+1<< ": "<<fixed << setprecision(2) << percent <<"%"<< endl;
    }

    return 0;
}

Graph::Graph(int VertexNum) {
    Nv = VertexNum;
    Ne = 0;
    Visited = new bool[VertexNum];

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

double Graph::BFS(Vertex V) {
    queue<Vertex> Q;

    Vertex W;
    int distance = 0;  //用来记录距离
    int Num_of_Node;  //用来计数每层有多少结点
    int Num_of_all=0;  //用来计数与该结点距离不超过6的结点总数
    int count=1;    //用来计数循环次数
    double percent;  //百分比

    Visited[V] = true; // 标记V已访问,防止出现死循环 
    Q.push(V);

    while (!Q.empty()&&distance<6) {
        Num_of_Node = 0;     //每次都将该值设为0，计算每层有多少结点
        for (int j = 0; j < count; j++) {   //这一层有多少，就循环几遍
            W = Q.front();
            Q.pop();
   
            for (int i = 0; i < Nv; i++) {
                if (!Visited[i] && G[W][i]) {
                    Visited[i] = true; // 标记V已访问,防止出现死循环 
                    Q.push(i);
                    Num_of_Node++;
                }
            }
        }
        count = Num_of_Node;
        Num_of_all += Num_of_Node;
        distance++;
    }

    percent = static_cast<double>(Num_of_all+1) / static_cast<double>(Nv);//计算百分比，加上自己

    return 100*percent;//返回值
}

void Graph::Init_Visited() {
    for (int i = 0; i < Nv; i++) {
        Visited[i] = false;
    }
}