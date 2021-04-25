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

    BT = BuidTree();    //建树
    PostOrderTraversal(BT);   //将建好的树后序遍历输出

    return 0;
}

BinTree BuidTree() {


}

void PostOrderTraversal(BinTree BT) {     //后序遍历的递归算法
    static int isFirst = 1;  //用来判断是否是第一个结点

    if (BT != nullptr) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        if (isFirst) cout << BT->Data;    //输出隔一个空格，且结尾没有空格
        else cout << " " << BT->Data;
    }
}