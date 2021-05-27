#include <iostream>
#include <queue>
#include <math.h>

#define MaxVertexNum 101    //��󶥵�����Ϊ101������������ӳ�ʼλ��

using namespace std;
using Vertex = int;         // �ö����±��ʾ����,Ϊ����
using WeightType = int;   //����Ȩ������Ϊint

using point = struct Node;
struct Node {    //����
    int x;
    int y;
};

//ͼ
class Graph {
public:
    int Nv;  // ������
    int Ne;  // ���� 
    int jump;  //��Ծ����
    int Num_of_Jump;    //��Ծ����
    WeightType G[MaxVertexNum][MaxVertexNum]; // �ڽӾ��� 
    point* Data;   //��ŵ���Ϣ
    bool* Visited;  //��־�Ƿ���ʹ�
public:
    Graph(int VertexNum, int jump_);  //���ι��캯��
    void InsertEdge(Vertex V1, Vertex V2);    //�����
    void BuildEdge();    //�����ϵĵ����ϱ�
    bool DFS(Vertex V); //DFS
    void Init_Visited();  //��Visitedȫ����Ϊfalse
};

int main() {
    int Num_of_cro, jump_dis;   //����������Ծ����
    int x, y;   //����

    cin >> Num_of_cro >> jump_dis;
    Graph G{ Num_of_cro + 1, jump_dis };   //����ͼ

    //������ֵ
    for (int i = 1; i <= Num_of_cro; i++) {
        cin >> x >> y;
        G.Data[i].x = x;
        G.Data[i].y = y;
    }

    G.BuildEdge();   //�����ϵĵ����ϱ�
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
    //������Լ��ж���û�мӹ�������

    //����� <V1, V2>
    G[V1][V2] = 1;
    //����� <V2, V1>
    G[V2][V1] = 1;

    Ne++;//������1
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
    Visited[V] = true; // ���V�ѷ���,��ֹ������ѭ�� 

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