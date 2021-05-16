//ͼ�ķ�����������ʧ��

#include <iostream>
#include <queue>

using namespace std;

using WeightType = int;   //����Ȩ������Ϊint
using Vertex = int;   //����������Ϊint

//�ڽӱ��ÿһ��
using PtrToAdjNode = class AdjVNode*;
class AdjVNode {
public:
    Vertex AdjV;   //�ڽӵ��±�
    PtrToAdjNode Next;  //��һ�����
};
//�ڽӱ�
using AdjList = class VNode*;
class VNode {
public:
    PtrToAdjNode FirstEdge;
    int Data;  //�����������뵥���ĵ㣬û�б�
};

//���ڽӾ���洢��ͼ��
class Graph {
private:
    int Nv;  //������ 
    int Ne;  // ����   
    AdjList G; // �ڽӱ�
public:
    Graph(int VertexNum);  //���ι��캯��
    void InsertEdge(Vertex V1, Vertex V2);    //�����
    bool is_exist_Edge(Vertex V1, Vertex V2); //�Ƿ���ڱ�
    void Connect();
};


//int main() {
//    int N;  //�����
//    char flag;
//    Vertex V1, V2;
//    queue<int> Q;
//    cin >> N;  //��������
//
//    Graph G{ N };   //����ͼ
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
    //����� <V1, V2>
    NewNode = new AdjVNode;  //�������
    NewNode->AdjV = V2;
    //  ��������ͷ��
    NewNode->Next = G[V1].FirstEdge;
    G[V1].FirstEdge = NewNode;

    //����� <V1, V2>
    NewNode = new AdjVNode;  //�������
    NewNode->AdjV = V1;
    //  ��������ͷ��
    NewNode->Next = G[V2].FirstEdge;
    G[V2].FirstEdge = NewNode;

    Ne++;//������1
}

bool Graph::is_exist_Edge(Vertex V1, Vertex V2) {   //ֻ���ж��Ѹ������ӣ���
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