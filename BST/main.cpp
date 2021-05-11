#include <iostream>
#include <array>
//#include <queue>
#include <math.h>

#define MAXSIZE 1000

using namespace std;

array<int, MAXSIZE> Node;
array<int, MAXSIZE> Tree;

void Bubble_sort(array<int, MAXSIZE>& Node,int N);  //�������򣬴�С����
void Build_CBST(int ALeft, int ARight, int TRoot);   //������CBST
int get_Left_Num(int N);   //�������������������

//�ͷǵݹ��㷨����ϵ�
//class Tnode{
//public:
//	int index;  //�±�
//	int num;   //�Ըýڵ�Ϊ�������������
//};

int main() {
	int N;  //����Ľ����
	int data;  //�洢������

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> data;
		Node[i] = data;
	}

	Bubble_sort(Node, N);
	Build_CBST( 0, N-1, 0);

	for (int i = 0; i < N; i++) {
		cout << Tree[i];
		if (i != N - 1) cout << " ";
	}

	return 0;
}

void Bubble_sort(array<int, MAXSIZE>& Node, int N) {
	int tag;
	int i, j, t;

	for (i = N-1; i > 0; i--) {
		tag = 1;
		for (j = 0; j < i; j++) {
			if (Node[j] > Node[j + 1]) {
				t = Node[j];
				Node[j] = Node[j + 1];
				Node[j + 1] = t;
				tag = 0;
			}
		}
		if (tag) break;
	}
}

void Build_CBST(int ALeft, int ARight, int TRoot) {
	int n = ARight - ALeft + 1;
	if (n == 0) return;
	int L = get_Left_Num(n);
	Tree[TRoot] = Node[ALeft + L];
	int LeftTRoot = TRoot * 2 + 1;
	int RightTRoot = LeftTRoot + 1;
	Build_CBST(ALeft, ALeft + L - 1, LeftTRoot);
	Build_CBST(ALeft+L+1, ARight, RightTRoot);
}

//�ǵݹ鷽��������ʧ�ܣ���
//void Build_CBST(array<int, MAXSIZE>& Node, array<int, MAXSIZE>& Tree, int N) {
//	queue<Tnode> Q;  //����Q������ʵ������ת����
//	int i = 0;
//	Tnode Root, Left, Right;
//
//	if (N) {  //����������Ϊ0
//		Root = { get_Left_Num(N), N };  //���������
//		Q.push(Root);  //�����������
//	}
//
//	while (!Q.empty()) {  //�����в�Ϊ��ʱ
//		Tree[i] = Q.front().index;
//		if (Q.front().num !=1) {  //����������
//			if(Q.front().index>Tree[0])//��������������
//				Left = { Tree[0]+ get_Left_Num(Q.front().num)\
//				, get_Left_Num(Q.front().num) };   //�ֱ�������������ڵ���±꣬ �����������Ľ��������
//			else//��������������
//				Left = { get_Left_Num(Q.front().index) , get_Left_Num(Q.front().num) };
//			Q.push(Left);
//			if (Q.front().num > 2) {
//				Right = { Q.front().index + get_Left_Num(Q.front().num\
//				- Left.num - 1) + 1, Q.front().num - Left.num - 1 };     //�ֱ�������������±꣬���������ĸ�������
//				Q.push(Right);
//			}
//		}
//		Q.pop();
//		i++;
//	}
//}

int get_Left_Num(int N) {
	int H=1;
	if (!N) return 0;
	while (N > (pow(2, H) - 1)) H++;

	if (N - (pow(2, H - 1) - 1) <= pow(2, H - 2))
		return N - pow(2, H - 1) + pow(2, H - 2);
	else return pow(2, H - 1) - 1;
}