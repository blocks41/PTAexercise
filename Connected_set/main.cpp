#include <iostream>
#include <queue>

#define MaxVertexNum 10    //��󶥵�����Ϊ100

using namespace std;
using Vertex=int;         // �ö����±��ʾ����,Ϊ����
using WeightType = int;   //����Ȩ������Ϊint

//ͼ
class Graph {
public:
    int Nv;  // ������
    int Ne;  // ���� 
    WeightType G[MaxVertexNum][MaxVertexNum]; // �ڽӾ��� 
    bool* Visited;  //��־�Ƿ���ʹ�
public:
    Graph(int VertexNum);  //���ι��캯��
    void InsertEdge(Vertex V1, Vertex V2);    //�����
    void DFS(Vertex V); //DFS
    void BFS(Vertex V); //BFS
    void Init_Visited();  //��Visitedȫ����Ϊfalse
};

int main() {
    int Num_of_Node, Num_of_Edge;  //������������
    Vertex V1, V2;    //��

    cin >> Num_of_Node >> Num_of_Edge;  //���붥����������
    Graph G{ Num_of_Node };   //����ͼ

    //����ͼ
    for (int i = 0; i < Num_of_Edge; i++) {
        cin >> V1 >> V2;   //�����
        G.InsertEdge(V1, V2);   //�����
    }
    
    //DFS
    G.Init_Visited();  //����ʶ��ʼΪfalse
    for (int i = 0; i < Num_of_Node; i++) {
        if (G.Visited[i] != true) {
            cout << "{ ";
            G.DFS(i);
            cout << "}\n";
        }
    }
    G.Init_Visited();  //����ʶ��ʼΪfalse
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
    //������Լ��ж���û�мӹ�������

    //����� <V1, V2>
    G[V1][V2] = 1;
    //����� <V2, V1>
    G[V2][V1] = 1;

    Ne++;//������1
}

void Graph::DFS(Vertex V) {
    cout << V << " ";    //���V
    Visited[V] = true; // ���V�ѷ���,��ֹ������ѭ�� 

    for (int i=0; i<Nv; i++) {
        if (!Visited[i] && G[V][i]) {
            DFS(i);
        }
    }
}

void Graph::BFS(Vertex V) {
    queue<Vertex> Q;
    Vertex W;

    cout << V << " ";    //���V
    Visited[V] = true; // ���V�ѷ���,��ֹ������ѭ�� 
    Q.push(V);

    while (!Q.empty()) {
        W = Q.front();
        Q.pop();
        for (int i = 0; i < Nv; i++) {
            if (!Visited[i] && G[W][i]) {
                cout << i << " ";    //���V
                Visited[i] = true; // ���V�ѷ���,��ֹ������ѭ�� 
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