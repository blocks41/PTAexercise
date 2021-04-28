#include <iostream>
#include <stack>
#include <string>

using namespace std;

#define Left_ 0
#define Right_ 1

using BinTree = class TreeNode*;
class TreeNode {
public:
    int Data=-1;
    BinTree Left=nullptr;
    BinTree Right= nullptr;
};

BinTree BuidTree();    //用来接受中序遍历的语句，并且转换为树
void PostOrderTraversal(BinTree BT);   //将树后序遍历输出
//void PostOrderTraversal_(BinTree BT);  //非遍历

int main() {
    BinTree BT=nullptr;

    BT = BuidTree();    //建树
    PostOrderTraversal(BT);   //将建好的树后序遍历输出
   // PostOrderTraversal_(BT);

    return 0;
}

BinTree BuidTree() {
    stack<BinTree> S;  //存放结点
    string s;   //暂存语句
    int x;    //表示结点的数字
    BinTree BT = nullptr;  //树
    BinTree father=nullptr;  //表示父节点，nullptr代表根结点
    int child = Left_;  //用来表示孩子节点是右还是左
    int N;  //用来输入结点数，从而可以计算语句数

    cin >> N;
    for (int i = 0; i < N*2; i++) {
        cin>>s;
        if (s.length() == 4) {  //语句是push x
            cin >> x;
            if (!father) {
                BT = new TreeNode;  //树
                BT->Data = x;  //如果是根节点就赋值
                father = BT;//保存当前父节点
                S.push(father);
            }
            else if (child == Left_) {    //如果标记是左孩子就在左节点加
                BinTree LN = new TreeNode;
                LN->Data = x;
                father->Left = LN;
                father = LN;
                S.push(father);
            }
            else if (child == Right_) {   //如果标记是右孩子就在右节点加
                BinTree RN = new TreeNode;
                RN->Data = x;
                father->Right = RN;
                father = RN;
                S.push(father);
                child = Left_;   //假如下一个语句是push就还在左节点加
            }
        }
        else {  //语句是pop
            father = S.top();   //保存当前父节点
            S.pop();
            child = Right_;  //遇到pop就更改child
        }
    }
    return BT;  //返回结点指针
}

void PostOrderTraversal(BinTree BT) {     //后序遍历的递归算法
    static int isFirst = 1;  //用来判断是否是第一个结点

    if (BT != nullptr) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        if (isFirst) {
            cout << BT->Data;    //输出隔一个空格，且结尾没有空格
            isFirst = 0;
        }
        else cout << " " << BT->Data;
    }
}

/*
void PostOrderTraversal_(BinTree BT) {
    BinTree B = BT;
    BinTree temp = nullptr; //暂时保存上次输出的树结点
    stack<BinTree> S;
    int isFirst = 1;

    while (B || !S.empty()) {
        while (B) {
            S.push(B);
            B = B->Left;
        }
        if (!S.empty()) {
            B = S.top();
            S.pop();
            // 若右子树为空，或上次抛出的是右儿子，则可以抛出，temp不是NULL就是上次输出的右子树
            if (B->Right == nullptr || B->Right == temp) {
                if (isFirst) {
                    cout << B->Data;
                    isFirst = 0;
                }
                else {
                    cout << " " << B->Data;
                }
                temp = B;    //更新上一次输出的树结点
                B = nullptr; // 整个子树遍历完了，指针置为NULL,后续将弹出其父结点
            }
            //若当前结点仍有右子树，则将当前结点重新压入栈，将T指向其右子树
            else {
                S.push(B);
                B = B->Right;
            }
        }
    }
}
*/