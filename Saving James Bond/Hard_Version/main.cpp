#include <iostream>
#include <queue>
#include <math.h>

#define MaxVertexNum 101    //最大顶点数设为101，最大鳄鱼数加初始位置

using namespace std;
using Vertex = int;         // 用顶点下标表示顶点,为整型
using WeightType = int;   //定义权重类型为int

using point = struct Node;
struct Node {    //坐标
    int x;
    int y;
};

//图
class Graph {
public:
    int Nv;  // 顶点数
    int Ne;  // 边数 
    int jump;  //跳跃距离
    int Num_of_Jump;    //跳跃次数
    WeightType G[MaxVertexNum][MaxVertexNum]; // 邻接矩阵 
    point* Data;   //存放点信息
    bool* Visited;  //标志是否访问过
public:
    Graph(int VertexNum, int jump_);  //带参构造函数
    void InsertEdge(Vertex V1, Vertex V2);    //插入边
    void BuildEdge();    //将符合的点连上边
    bool DFS(Vertex V); //DFS
    void Init_Visited();  //将Visited全部变为false
};

int main() {
    int Num_of_cro, jump_dis;   //鳄鱼数，跳跃距离
    int x, y;   //坐标

    cin >> Num_of_cro >> jump_dis;
    Graph G{ Num_of_cro + 1, jump_dis };   //创建图

    //读入点的值
    for (int i = 1; i <= Num_of_cro; i++) {
        cin >> x >> y;
        G.Data[i].x = x;
        G.Data[i].y = y;
    }

    G.BuildEdge();   //将符合的点连上边
    G.Init_Visited();

    if (G.DFS(0)) cout << "Yes";
    else cout << "No";

    return 0;
}

Graph::Graph(int VertexNum, int jump_) {
    Nv = VertexNum;
    Ne = 0;
    Num_of_Jump = 0;
    Data = new point[VertexNum];
    Visited = new bool[VertexNum];

    this->jump = jump_;
    for (int i = 0; i < VertexNum; i++) {
        for (int j = 0; j < VertexNum; j++) {
            G[i][j] = 0;
        }
    }
    Data[0].x = 0;
    Data[0].y = 0;
}

void Graph::InsertEdge(Vertex V1, Vertex V2) {
    //这里可以加判断有没有加过这条边

    //插入边 <V1, V2>
    G[V1][V2] = 1;
    //插入边 <V2, V1>
    G[V2][V1] = 1;

    Ne++;//边数加1
}

void Graph::BuildEdge() {
    for (int i = 1; i < Nv; i++) {
        int dis = pow(Data[i].x, 2) + pow(Data[i].y, 2);
        if ((pow(dis, 0.5) - 7.5) <= jump) {
            InsertEdge(0, i);
        }
    }
    for (int i = 1; i < Nv; i++) {
        for (int j = i + 1; j < Nv; j++) {
            if ((pow(Data[i].x - Data[j].x, 2) + pow(Data[i].y - Data[j].y, 2)) <= pow(jump, 2)) {
                InsertEdge(i, j);
            }
        }
    }
}

bool Graph::DFS(Vertex V) {
    int flag = 0;
    Visited[V] = true; // 标记V已访问,防止出现死循环 

    for (Vertex i = 0; i < Nv; i++) {
        if (!Visited[i] && G[V][i]) {
            if ((pow(50 - abs(Data[i].x), 2) <= pow(jump, 2)) || (pow(50 - abs(Data[i].y), 2) <= pow(jump, 2))) {
                flag = 1;
                break;
            }
            if (DFS(i)) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) return true;
    else return false;
}

void Graph::Init_Visited() {
    for (int i = 0; i < Nv; i++) {
        Visited[i] = false;
    }
}