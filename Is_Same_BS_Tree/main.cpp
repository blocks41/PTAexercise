#include <iostream>

using namespace std;

using TreeNode = class Node*;
class Node {
public:
	int data;
	TreeNode Left;
	TreeNode Right;
};

TreeNode buildTree(int Num_of_Node);  //建树
TreeNode Insert(int data, TreeNode BT);   //插入结点
bool Is_Same_BK_Tree(TreeNode T0, TreeNode T1);  //判断是否是同一棵二叉搜索树

int main() {
	int Num_of_Node;   //树的结点数
	int N;     //需要判断的序列数
	int count = 0;  //用来记录需要判断
	int result[100];  //用来记录结果

	while (1) {
		cin >> Num_of_Node;
		if (Num_of_Node == 0) break;  //如果是0就退出循环

		cin >> N;
		TreeNode T0 = buildTree(Num_of_Node);   //接受输入建成树，返回头节点	
		for (int i = count; i < N + count; i++) {
			TreeNode T1 = buildTree(Num_of_Node);
			if (Is_Same_BK_Tree(T0, T1)) result[i+1]=1;
			else result[i+1]=0;
		}
		count += N;
	}

	for (int i = 0; i < count; i++) {   //输出最后的结果
		if (result[i + 1] == 1) cout << "Yes";
		else cout << "No";
		if (i != count - 1) cout << endl;
	}

	return 0;
}

TreeNode buildTree(int Num_of_Node) {
	TreeNode BT = nullptr;  
	int node;

	for (int i = 0; i < Num_of_Node; i++) {
		cin >> node;
		BT = Insert(node, BT);
	}
	return BT;
}

TreeNode Insert(int data, TreeNode BT) {
	if (!BT) {  //如果树为空，就建一个节点
		BT = new Node;
		BT->data = data;
		BT->Left = BT->Right = nullptr;
	}
	else if (data < BT->data) {   //应插入左子树， 递归调用
		BT->Left=Insert(data, BT->Left);
	}
	else if (data > BT->data) {   //右子树递归
		BT->Right=Insert(data, BT->Right);
	}

	return BT;
}

bool Is_Same_BK_Tree(TreeNode T0, TreeNode T1) {
	if (T0 == nullptr && T1 == nullptr) return true; //如果两个结点都为空， 返回true
	if ((T0 == nullptr && T1 != nullptr) || (T1 == nullptr && T0 != nullptr)) \
		return false;  //一个空一个不空, 返回false
	if (T0->data != T1->data) return false;  //两个根节点不同 ，返回false
	if (T0->data == T1->data) return (Is_Same_BK_Tree(T0->Left, T1->Left) && \
		Is_Same_BK_Tree(T0->Right, T1->Right));     //如果根节点相同，就递归的看左右子节点
}