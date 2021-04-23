#include <iostream>
#include <queue>

#define MaxSize 100
#define Null -1

class TreeNode {
public:
	int left;     //�����
	int right;    //�Ҷ��� 

    TreeNode() {
        left = Null;
        right = Null;
    }
}T[MaxSize];

int BuildTree(TreeNode* T);
void LeavesOut(std::queue<int> Q ,int Root);

int main() {
    int R;   //������ڵ�
    std::queue<int> Q;   //����һ���������������⽫�����±�����
    
    R = BuildTree(T);   //����
    LeavesOut(Q, R);   //��Ҷ�ӽڵ����
}

int BuildTree(TreeNode* T) {
    int Num, i, check[MaxSize]{ 0 }, Root = Null;
    char cl, cr;

    std::cin >> Num;
    if (Num){
        for (i = 0; i < Num; i++){
            std::cin >> cl >> cr;
            if (cl != '-') {                    //�ж������Ƿ�ָ��ĳ�����
                T[i].left = cl - '0';          //����Ľ�������ֱ�ʾ
                check[T[i].left] = 1;         //����ָ���checkֵ��Ϊ1���ų��Ǹ��ڵ�Ŀ���
            }
            else{
                T[i].left = Null;
            }

            if (cr != '-'){      //��ͬ��
                T[i].right = cr - '0';
                check[T[i].right] = 1;
            }
            else{
                T[i].right = Null;
            }
        }

        for (i = 0; i < Num; i++)            //���check��ֵΪ0��Ϊ���ڵ�
            if (!check[i]) break;
        Root = i;                         //�����ڵ㱣����Root��
    }
    return Root;
}

void LeavesOut(std::queue<int> Q ,int Root) {
    if (Root != Null) Q.push(Root);     //�����ڵ�������
    else std::cout << "the tree is empty!";

    while (Root != Null) {    //������ǿ�����ִ��
        if (T[Root].left==T[Root].right) {       //�ж��Ƿ���Ҷ�ӽ��
            std::cout << Root<<" ";      //���
        }
        else {              //���ӽڵ㰴���Ҽ������
            if (T[Root].left != Null) {
                Q.push(T[Root].left);
            }
            if (T[Root].right != Null) {
                Q.push(T[Root].right);
            }
        }
        Q.pop();       //������Ԫ�س���
        if (Q.size() == 0) break;    //�������Ϊ�վ�break
        Root = Q.front();
    }
}