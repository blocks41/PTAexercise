#include <iostream>
#include <stack>
#include <string>

using namespace std;

using BinTree = class TreeNode*;
class TreeNode {
public:
    int Data=-1;
    BinTree Left=nullptr;
    BinTree Right= nullptr;
};

BinTree BuidTree();
void PostOrderTraversal(BinTree BT);

int main() {
    BinTree BT=nullptr;

    BT = BuidTree();    //����
    PostOrderTraversal(BT);   //�����õ�������������

    return 0;
}

BinTree BuidTree() {


}

void PostOrderTraversal(BinTree BT) {     //��������ĵݹ��㷨
    static int isFirst = 1;  //�����ж��Ƿ��ǵ�һ�����

    if (BT != nullptr) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        if (isFirst) cout << BT->Data;    //�����һ���ո��ҽ�βû�пո�
        else cout << " " << BT->Data;
    }
}