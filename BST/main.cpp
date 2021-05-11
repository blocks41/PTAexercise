#include <iostream>
#include <array>
//#include <queue>
#include <math.h>

#define MAXSIZE 1000

using namespace std;

array<int, MAXSIZE> Node;
array<int, MAXSIZE> Tree;

void Bubble_sort(array<int, MAXSIZE>& Node,int N);  //起泡排序，从小到大
void Build_CBST(int ALeft, int ARight, int TRoot);   //用来建CBST
int get_Left_Num(int N);   //用来返回左子树结点数

//和非递归算法相配合的
//class Tnode{
//public:
//	int index;  //下标
//	int num;   //以该节点为根的子树结点数
//};

int main() {
	int N;  //读入的结点数
	int data;  //存储的数据

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

//非递归方法，宣告失败！！
//void Build_CBST(array<int, MAXSIZE>& Node, array<int, MAXSIZE>& Tree, int N) {
//	queue<Tnode> Q;  //队列Q，用来实现中序转层序
//	int i = 0;
//	Tnode Root, Left, Right;
//
//	if (N) {  //如果结点数不为0
//		Root = { get_Left_Num(N), N };  //计算出树根
//		Q.push(Root);  //将树加入队列
//	}
//
//	while (!Q.empty()) {  //当队列不为空时
//		Tree[i] = Q.front().index;
//		if (Q.front().num !=1) {  //有左右子树
//			if(Q.front().index>Tree[0])//右子树的左子树
//				Left = { Tree[0]+ get_Left_Num(Q.front().num)\
//				, get_Left_Num(Q.front().num) };   //分别计算左子树根节点的下标， 并把左子树的结点数保存
//			else//左子树的左子树
//				Left = { get_Left_Num(Q.front().index) , get_Left_Num(Q.front().num) };
//			Q.push(Left);
//			if (Q.front().num > 2) {
//				Right = { Q.front().index + get_Left_Num(Q.front().num\
//				- Left.num - 1) + 1, Q.front().num - Left.num - 1 };     //分别计算右子树的下标，和右子树的个数保存
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