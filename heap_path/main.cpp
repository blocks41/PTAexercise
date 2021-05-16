#include <iostream>

#define MinData -10001

using namespace std;

class MinHeap {
public:
    int* Elements;       //存储堆元素的数组
    int Size;           //堆的当前元素个数
    int Capacity;      //堆的最大容量

public:
    MinHeap(int MaxSize) {
        Elements = new int[MaxSize + 1];     //给哨兵留位置
        Size = 0;
        Capacity = MaxSize;
        Elements[0] = MinData;             //定义哨兵为堆中所有元素的最小值
    }

    void Insert(int item) {     //插入元素 
        int i;

        i = ++Size;    //指向堆最后一个元素的位置
        for (; Elements[i / 2] > item; i /= 2)      //哨兵解决了插入的结点是所有结点最大的情况
            Elements[i] = Elements[i / 2];
        Elements[i] = item;
    }
    int Delete() {         //删除元素
        int Parent, child;
        int MinItem, temp;

        MinItem = Elements[1];
        temp = Elements[Size--];
        for (Parent = 1; Parent * 2 <= Size; Parent = child)
        {
            child = Parent * 2;
            if ((child < Size) && \
                (Elements[child] > Elements[child + 1]))
                child++;
            if (temp <= Elements[child]) break;
            else
                Elements[Parent] = Elements[child];
        }
        Elements[Parent] = temp;
        return MinItem;
    }
    void Out_path(int index) { //输出路径
        while (index != 1) {
            cout << Elements[index] << ' ';
            index /= 2;
        }
        cout << Elements[1];
    }
};

int main() {
    int node, path;
    int item, index;
    int i;
    MinHeap H{ 1000 };

    cin >> node >> path;
    for (i = 0; i < node; i++) {
        cin >> item;
        H.Insert(item);
    }

    for (i = 0; i < path; i++) {
        cin >> index;
        H.Out_path(index);
        if (i != path - 1) cout << "\n";
    }

    return 0;
}