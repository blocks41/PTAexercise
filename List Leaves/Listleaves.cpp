#include <iostream>
#include <queue>

#define MaxSize 100
#define Null -1

class TreeNode {
public:
	int left;     //左儿子
	int right;    //右儿子 

    TreeNode() {
        left = Null;
        right = Null;
    }
}T[MaxSize];

int BuildTree(TreeNode* T);
void LeavesOut(std::queue<int> Q ,int Root);

int main() {
    int R;   //保存根节点
    std::queue<int> Q;   //建立一个队列用来按题意将结点的下标排序
    
    R = BuildTree(T);   //建树
    LeavesOut(Q, R);   //将叶子节点输出
}

int BuildTree(TreeNode* T) {
    int Num, i, check[MaxSize]{ 0 }, Root = Null;
    char cl, cr;

    std::cin >> Num;
    if (Num){
        for (i = 0; i < Num; i++){
            std::cin >> cl >> cr;
            if (cl != '-') {                    //判断左孩子是否指向某个结点
                T[i].left = cl - '0';          //输入的结点用数字表示
                check[T[i].left] = 1;         //将被指向的check值设为1，排除是根节点的可能
            }
            else{
                T[i].left = Null;
            }

            if (cr != '-'){      //右同上
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else{
                T[i].right = Null;
            }
        }

        for (i = 0; i < Num; i++)            //如果check的值为0则为根节点
            if (!check[i]) break;
        Root = i;                         //将根节点保存在Root上
    }
    return Root;
}

void LeavesOut(std::queue<int> Q ,int Root) {
    if (Root != Null) Q.push(Root);     //将根节点加入队列
    else std::cout << "the tree is empty!";

    while (Root != Null) {    //如果不是空树就执行
        if (T[Root].left==T[Root].right) {       //判断是否是叶子结点
            std::cout << Root<<" ";      //输出
        }
        else {              //将子节点按左右加入队列
            if (T[Root].left != Null) {
                Q.push(T[Root].left);
            }
            if (T[Root].right != Null) {
                Q.push(T[Root].right);
            }
        }
        Q.pop();       //将队首元素出队
        if (Q.size() == 0) break;    //如果队列为空就break
        Root = Q.front();
    }
}