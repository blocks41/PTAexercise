//图的方法————失败

#include <iostream>
#include <queue>

using namespace std;

using WeightType = int;   //定义权重类型为int
using Vertex = int;   //定义结点类型为int

//邻接表的每一项
using PtrToAdjNode = class AdjVNode*;
class AdjVNode {
public:
    Vertex AdjV;   //邻接点下标
    PtrToAdjNode Next;  //下一个结点
};
//邻接表
using AdjList = class VNode*;
class VNode {
public:
    PtrToAdjNode FirstEdge;
    int Data;  //可以用来插入单独的点，没有边
};

//以邻接矩阵存储的图类
class Graph {
private:
    int Nv;  //顶点数 
    int Ne;  // 边数   
    AdjList G; // 邻接表
public:
    Graph(int VertexNum);  //带参构造函数
    void InsertEdge(Vertex V1, Vertex V2);    //插入边
    bool is_exist_Edge(Vertex V1, Vertex V2); //是否存在边
    void Connect();
};


//int main() {
//    int N;  //结点数
//    char flag;
//    Vertex V1, V2;
//    queue<int> Q;
//    cin >> N;  //输入结点数
//
//    Graph G{ N };   //定义图
//
//    while(1){
//        cin >> flag;
//        if (flag == 'I') {
//            cin >> V1 >> V2;
//            G.InsertEdge(V1, V2);
//        }
//        else if (flag == 'C') {
//            cin >> V1 >> V2;
//            if (G.is_exist_Edge(V1, V2)) Q.push(1);
//            else Q.push(0);
//        }
//        else if (flag == 'S') break;
//    }
//
//    while (!Q.empty()) {
//        if (Q.front()) {
//            cout << "Yes\n";
//            Q.pop();
//        }
//        else {
//            cout << "NO\n";
//            Q.pop();
//        }
//    }
//
//    G.Connect();
//
//	return 0;
//}

Graph::Graph(int VertexNum) {
    Nv = VertexNum;
    Ne = 0;
    G = new VNode[VertexNum];

    for (int i = 0; i < VertexNum; i++)
        G[i].FirstEdge= nullptr;
}

void Graph::InsertEdge(Vertex V1, Vertex V2){
    PtrToAdjNode NewNode;
    //插入边 <V1, V2>
    NewNode = new AdjVNode;  //建立结点
    NewNode->AdjV = V2;
    //  将结点插入头后
    NewNode->Next = G[V1].FirstEdge;
    G[V1].FirstEdge = NewNode;

    //插入边 <V1, V2>
    NewNode = new AdjVNode;  //建立结点
    NewNode->AdjV = V1;
    //  将结点插入头后
    NewNode->Next = G[V2].FirstEdge;
    G[V2].FirstEdge = NewNode;

    Ne++;//边数加1
}

bool Graph::is_exist_Edge(Vertex V1, Vertex V2) {   //只能判断已给的连接！！
    PtrToAdjNode Node = G[V1].FirstEdge;

    while (Node != nullptr) {
        if (Node->AdjV == V2) return true;
        Node = Node->Next;
    }
    return false;
}

void Graph::Connect() {
    if (Ne >= Nv - 1) cout << "The network is connected.";
    else cout << "There are " << Nv-Ne << " components.";  
}