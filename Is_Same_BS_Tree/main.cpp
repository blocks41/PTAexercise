#include <iostream>

using namespace std;

using TreeNode = class Node*;
class Node {
public:
	int data;
	TreeNode Left;
	TreeNode Right;
};

TreeNode buildTree(int Num_of_Node);  //����
TreeNode Insert(int data, TreeNode BT);   //������
bool Is_Same_BK_Tree(TreeNode T0, TreeNode T1);  //�ж��Ƿ���ͬһ�ö���������

int main() {
	int Num_of_Node;   //���Ľ����
	int N;     //��Ҫ�жϵ�������
	int count = 0;  //������¼��Ҫ�ж�
	int result[100];  //������¼���

	while (1) {
		cin >> Num_of_Node;
		if (Num_of_Node == 0) break;  //�����0���˳�ѭ��

		cin >> N;
		TreeNode T0 = buildTree(Num_of_Node);   //�������뽨����������ͷ�ڵ�	
		for (int i = count; i < N + count; i++) {
			TreeNode T1 = buildTree(Num_of_Node);
			if (Is_Same_BK_Tree(T0, T1)) result[i+1]=1;
			else result[i+1]=0;
		}
		count += N;
	}

	for (int i = 0; i < count; i++) {   //������Ľ��
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
	if (!BT) {  //�����Ϊ�գ��ͽ�һ���ڵ�
		BT = new Node;
		BT->data = data;
		BT->Left = BT->Right = nullptr;
	}
	else if (data < BT->data) {   //Ӧ������������ �ݹ����
		BT->Left=Insert(data, BT->Left);
	}
	else if (data > BT->data) {   //�������ݹ�
		BT->Right=Insert(data, BT->Right);
	}

	return BT;
}

bool Is_Same_BK_Tree(TreeNode T0, TreeNode T1) {
	if (T0 == nullptr && T1 == nullptr) return true; //���������㶼Ϊ�գ� ����true
	if ((T0 == nullptr && T1 != nullptr) || (T1 == nullptr && T0 != nullptr)) \
		return false;  //һ����һ������, ����false
	if (T0->data != T1->data) return false;  //�������ڵ㲻ͬ ������false
	if (T0->data == T1->data) return (Is_Same_BK_Tree(T0->Left, T1->Left) && \
		Is_Same_BK_Tree(T0->Right, T1->Right));     //������ڵ���ͬ���͵ݹ�Ŀ������ӽڵ�
}