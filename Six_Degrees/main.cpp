#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

#define MaxVertexNum 100    //��󶥵�����Ϊ1000

using namespace std;
using Vertex = int;         // �ö����±��ʾ����,Ϊ����
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
    double BFS(Vertex V); //BFS
    void Init_Visited();  //��Visitedȫ����Ϊfalse
};

int main() {
    int Num_of_Node, Num_of_Edge;  //������������
    Vertex V1, V2;    //��
    double percent;   //�ٷֱ�

    cin >> Num_of_Node >> Num_of_Edge;  //���붥����������
    Graph G{ Num_of_Node };   //����ͼ

    //����ͼ
    for (int i = 0; i < Num_of_Edge; i++) {
        cin >> V1 >> V2;   //�����
        G.InsertEdge(V1-1, V2-1);   //�����
    }

    //��ÿ����������ý����벻����6�Ľ����ռ��������İٷֱ�
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
    //������Լ��ж���û�мӹ�������

    //����� <V1, V2>
    G[V1][V2] = 1;
    //����� <V2, V1>
    G[V2][V1] = 1;

    Ne++;//������1
}

double Graph::BFS(Vertex V) {
    queue<Vertex> Q;

    Vertex W;
    int distance = 0;  //������¼����
    int Num_of_Node;  //��������ÿ���ж��ٽ��
    int Num_of_all=0;  //����������ý����벻����6�Ľ������
    int count=1;    //��������ѭ������
    double percent;  //�ٷֱ�

    Visited[V] = true; // ���V�ѷ���,��ֹ������ѭ�� 
    Q.push(V);

    while (!Q.empty()&&distance<6) {
        Num_of_Node = 0;     //ÿ�ζ�����ֵ��Ϊ0������ÿ���ж��ٽ��
        for (int j = 0; j < count; j++) {   //��һ���ж��٣���ѭ������
            W = Q.front();
            Q.pop();
   
            for (int i = 0; i < Nv; i++) {
                if (!Visited[i] && G[W][i]) {
                    Visited[i] = true; // ���V�ѷ���,��ֹ������ѭ�� 
                    Q.push(i);
                    Num_of_Node++;
                }
            }
        }
        count = Num_of_Node;
        Num_of_all += Num_of_Node;
        distance++;
    }

    percent = static_cast<double>(Num_of_all+1) / static_cast<double>(Nv);//����ٷֱȣ������Լ�

    return 100*percent;//����ֵ
}

void Graph::Init_Visited() {
    for (int i = 0; i < Nv; i++) {
        Visited[i] = false;
    }
}