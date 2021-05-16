#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MinData -1
#define MAXSIZE 1001

using namespace std;

using HuffmanTree =class TreeNode*;
class TreeNode {
private:
    int Weight=0;   //权重
    HuffmanTree Left=nullptr;
    HuffmanTree Right=nullptr;

public:
    friend class MinHeap;

    int WPL(int Depth);   //用来计算最优编码长度,H是深度
    bool is_suc_BuildHT(string Code, vector<int> Weight_,int index);    //用来将读入的编码转换成树,判断是否成功
};

class MinHeap {
private:
    HuffmanTree Elements[MAXSIZE];       //存储堆元素的数组
    int Size;           //堆的当前元素个数
    int Capacity;      //堆的最大容量,这里是指存入的结点数

public:
    MinHeap(int MaxSize);

    HuffmanTree Huffman();       //构造哈夫曼树
    void AddData(vector<int> Weight_);  //先按完全二叉树加入数据
    HuffmanTree Delete();   //取出堆顶
    void PercDown(int Root);         //下滤函数
    void BuildMinHeap();               //按权重调整函数
    void Insert(HuffmanTree item);     //插入元素 
};

int main()
{
    HuffmanTree T;           //为了求最小WPL而建的树
    int Num_of_Node, Num_of_test;    //结点数，检查的个数
    vector<int> Weight;  //存放权重值
    int CodeLen;    //最优WPL
    queue<int> Q;  //用来存放判断的结果  
    int count = 0;  //为了结尾输出没有换行符

    cin >> Num_of_Node;       //输入结点数
    MinHeap H{ Num_of_Node };   //建立堆H

    char c_;
    int weight_;
    for (int i = 0; i < Num_of_Node; i++) {    //将权重值读入到数组中
        cin >> c_ >> weight_;
        Weight.push_back(weight_);
    }

    H.AddData(Weight);   //加入数据，按照完全二叉树
    H.BuildMinHeap();    //按权值将堆调整为最小堆
    T=H.Huffman();  //生成哈夫曼树

    CodeLen = T->WPL(0);  //求最小WPL

    cin >> Num_of_test;   //读入要测试的数量
    for (int i = 0; i < Num_of_test; i++) {
        int flag = 1;
        char C;
        string Code;
        HuffmanTree HT=new TreeNode;   //根据编码构建的树

        for (int j = 0; j < Num_of_Node; j++) {     //测试编码
            cin >> C >> Code;
            if (Code.length() > Num_of_Node - 1) flag = 0;   //长度不符合
            if (flag && !HT->is_suc_BuildHT(Code, Weight, j)) flag = 0;    //长度符合了就建树
        }
        if (flag&& (HT->WPL(0) == CodeLen)) Q.push(true);  //判断树是否建成，建成是否符合前缀码规范，符合了就再判断WPL
        else  Q.push(false); //否则直接判断不是

        delete HT;
    }

    while (!Q.empty()) {
        if (Q.front()) cout << "Yes";
        else cout << "No";

        Q.pop();
        count++;
        if (count != Num_of_test) cout << endl;
    }

    return 0;
}

bool TreeNode::is_suc_BuildHT(string Code, vector<int> Weight_, int index) {
    int i = 0;

    if (i < Code.length()) {
        if (Code[i] == '0') {
            if (Left == nullptr) {
                HuffmanTree T = new TreeNode;
                T->Weight = Weight_[index];
                Left = T;
                if (Code.length() == 1) return true; 
            }
            if (Code.length() == 1) return false;
            else return Left->is_suc_BuildHT(Code.substr(i + 1), Weight_, index);
        }
        else if (Code[i] == '1') {
            if (Right == nullptr) {
                HuffmanTree T = new TreeNode;
                T->Weight = Weight_[index];
                Right = T;
                if (Code.length() == 1) return true;
            }
            if (Code.length() == 1) return false;
            else return Right->is_suc_BuildHT(Code.substr(i + 1), Weight_, index);
        }
    }  
}

int TreeNode::WPL(int Depth) {
    if (Left == nullptr && Right == nullptr)
        return Depth * Weight;
    else if (Left && Right) return Left->WPL(Depth + 1) + Right->WPL(Depth + 1);
    else return -1000;  //在上一步建树的时候，可能会有树不符合哈夫曼树的特点3
}

HuffmanTree MinHeap::Huffman(){    //假设H->Capacity个权重值已经存放在H->Element[]->Weight
    HuffmanTree T;

    for (int i = 1; i < Capacity; i++)
    {
        T = new TreeNode;
        T->Left = Delete();
        T->Right = Delete();
        T->Weight = T->Left->Weight + T->Right->Weight;

        Insert(T);     //将T插入最小堆
    }
    T = Delete();

    return T;
}

MinHeap::MinHeap(int MaxSize) {
    Size = MaxSize;
    Capacity = MaxSize;
    HuffmanTree Node = new TreeNode;
    Node->Weight = MinData;             //定义哨兵为堆中所有元素的最小值
    Elements[0] = Node;
}

void MinHeap::AddData(vector<int> Weight_) {
    for (int i = 0; i < Capacity; i++) {
        HuffmanTree Node = new TreeNode;
        Node->Weight = Weight_[i];
        Elements[i + 1] = Node;
    }
}

HuffmanTree MinHeap::Delete(){
    int Parent, child;
    HuffmanTree MinItem, temp;
    /*有需要可以插入判断堆是否为空*/
    MinItem = Elements[1];
    temp = Elements[Size--];
    for (Parent = 1; Parent * 2 <= Size; Parent = child)
    {
        child = Parent * 2;
        if ((child < Size) && \
            (Elements[child]->Weight > Elements[child + 1]->Weight))
            child++;
        if (temp->Weight <= Elements[child]->Weight) break;
        else
            Elements[Parent] = Elements[child];
    }
    Elements[Parent] = temp;

    return MinItem;
}

void MinHeap::PercDown(int Root){ /* 下滤：将H中以Elements[p]为根的子堆调整为最小堆 */
    int Parent, Child;
    HuffmanTree X;

    X = Elements[Root]; /* 取出根结点存放的值 */
    for (Parent = Root; Parent * 2 <= Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != Size) && (Elements[Child]->Weight > Elements[Child + 1]->Weight))
            Child++;  /* Child指向左右子结点的较小者 */
        if (X->Weight <= Elements[Child]->Weight) break; /* 找到了合适位置 */
        else  /* 下滤X */
            Elements[Parent] = Elements[Child];
    }
    Elements[Parent] = X;
}

void MinHeap::BuildMinHeap(){ /* 调整Elements[]中的元素，使满足最小堆的有序性  */
  /* 这里假设所有H->Size个元素已经存在Elements[]中 */

    int i;

    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = Size / 2; i > 0; i--)
        PercDown(i);
}

void MinHeap::Insert(HuffmanTree item){
    int i;
    /*有需要可以判断堆是否已满*/
    i = ++Size;    //指向堆最后一个元素的位置
    for (; Elements[i / 2]->Weight > item->Weight; i /= 2) {      //哨兵解决了插入的结点是所有结点最小的情况
        Elements[i] = Elements[i / 2];
    }
    Elements[i] = item;
}