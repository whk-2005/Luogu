// #include <bits/stdc++.h>

// using namespace std;

// vector<int> v;
// int n, opt, x;

// int main()
// {
//     v.reserve(100010);
//     scanf("%d", &n);
//     while (n--)
//     {
//         scanf("%d%d", &opt, &x);
//         if (opt == 1)
//             v.insert(lower_bound(v.begin(), v.end(), x), x);
//         if (opt == 2)
//             v.erase(lower_bound(v.begin(), v.end(), x));
//         if (opt == 3)
//             printf("%d\n", lower_bound(v.begin(), v.end(), x) - v.begin() + 1);
//         if (opt == 4)
//             printf("%d\n", v[x - 1]);
//         if (opt == 5)
//             printf("%d\n", v[lower_bound(v.begin(), v.end(), x) - v.begin() - 1]);
//         if (opt == 6)
//             printf("%d\n", v[upper_bound(v.begin(), v.end(), x) - v.begin()]);
//     }
//     return 0;
// }
// 以上内容过于不要脸，不用看了

// #include <algorithm>
// #include <cctype>
// #include <cmath>
// #include <cstdio>
// #include <cstring>
// #include <deque>
// #include <iostream>
// #include <list>
// #include <map>
// #include <queue>
// #include <set>
// #include <stack>
// #include <string>
// #include <vector>

// using namespace std;

// const int MAXL = 100010;
// const int INF = 2147483647;

// class Splay
// {
//   private:
//     struct node
//     {
//         int v, father; //节点值，父级节点
//         int ch[2];     //左孩子=0，右孩子=1
//         int sum;       //自己+自己下级有多少节点。在根节点为1。
//         int recy;      //记录自己被重复了几次
//     };
//     node tree[MAXL];  //Splay树主体
//     int n, points; //使用存储数,元素数

//     inline void update(int x)
//     {
//         tree[x].sum = tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + tree[x].recy;
//     }

//     inline int identify(int x)
//     {
//         return tree[tree[x].father].ch[0] == x ? 0 : 1;
//     }

//     inline void connect(int x, int f, int son) //connect(son,father,1/0)
//     {
//         tree[x].father = f;
//         tree[f].ch[son] = x;
//     } //作用：使得x的father=f，f的son=x.

//     inline void rotate(int x)
//     {
//         int y = tree[x].father;
//         int mroot = tree[y].father;
//         int mrootson = identify(y);
//         int yson = identify(x);
//         int B = tree[x].ch[yson ^ 1];
//         connect(B, y, yson);
//         connect(y, x, (yson ^ 1));
//         connect(x, mroot, mrootson);
//         update(y);
//         update(x);
//     }

//     inline void splay(int at, int to) //将at位置的节点移动到to位置
//     {
//         to = tree[to].father;
//         while (tree[at].father != to)
//         {
//             int up = tree[at].father;
//             if (tree[up].father == to)
//                 rotate(at);
//             else if (identify(up) == identify(at))
//             {
//                 rotate(up);
//                 rotate(at);
//             }
//             else
//             {
//                 rotate(at);
//                 rotate(at);
//             }
//         }
//     }

//     inline int crepoint(int v, int father)
//     {
//         n++;
//         tree[n].v = v;
//         tree[n].father = father;
//         tree[n].sum = tree[n].recy = 1;
//         return n;
//     }

//     inline void destroy(int x) //pop后摧毁节点
//     {
//         tree[x].v = tree[x].ch[0] = tree[x].ch[1] = tree[x].sum = tree[x].father = tree[x].recy = 0;
//         if (x == n)
//             n--; //最大限度优化
//     }

//   public:
//     inline int getroot() { return tree[0].ch[1]; }

//     inline int find(int v) //用于外部的find调用
//     {
//         int now = tree[0].ch[1];
//         while (true)
//         {
//             if (tree[now].v == v)
//             {
//                 splay(now, tree[0].ch[1]);
//                 return now;
//             }
//             int next = v < tree[now].v ? 0 : 1;
//             if (!tree[now].ch[next])
//                 return 0;
//             now = tree[now].ch[next];
//         }
//     }

//     inline int build(int v) //内部调用的插入函数，没有splay
//     {
//         points++;
//         if (n == 0) //特判无点状态
//         {
//             tree[0].ch[1] = 1;
//             crepoint(v, 0);
//         }
//         else
//         {
//             int now = tree[0].ch[1];
//             while (true) //向下找到一个空节点
//             {
//                 tree[now].sum++; //自己的下级肯定增加了一个节点
//                 if (v == tree[now].v)
//                 {
//                     tree[now].recy++;
//                     return now;
//                 }
//                 int next = v < tree[now].v ? 0 : 1;
//                 if (!tree[now].ch[next])
//                 {
//                     crepoint(v, now);
//                     tree[now].ch[next] = n;
//                     return n;
//                 }
//                 now = tree[now].ch[next];
//             }
//         }
//         return 0;
//     }

//     inline void push(int v) //插入元素时，先添加节点，再进行伸展
//     {
//         int add = build(v);
//         splay(add, tree[0].ch[1]);
//     }

//     inline void pop(int v) //删除节点
//     {
//         int deal = find(v);
//         if (!deal)
//             return;
//         points--;
//         if (tree[deal].recy > 1)
//         {
//             tree[deal].recy--;
//             tree[deal].sum--;
//             return;
//         }
//         if (!tree[deal].ch[0])
//         {
//             tree[0].ch[1] = tree[deal].ch[1];
//             tree[tree[0].ch[1]].father = 0;
//         }
//         else
//         {
//             int lef = tree[deal].ch[0];
//             while (tree[lef].ch[1])
//                 lef = tree[lef].ch[1];
//             splay(lef, tree[deal].ch[0]);
//             int rig = tree[deal].ch[1];
//             connect(rig, lef, 1);
//             connect(lef, 0, 1);
//             update(lef);
//         }
//         destroy(deal);
//     }

//     inline int rank(int v) //获取值为v的元素在这棵树里是第几小
//     {
//         int ans = 0, now = tree[0].ch[1];
//         while (true)
//         {
//             if (tree[now].v == v)
//                 return ans + tree[tree[now].ch[0]].sum + 1;
//             if (now == 0)
//                 return 0;
//             if (v < tree[now].v)
//                 now = tree[now].ch[0];
//             else
//             {
//                 ans = ans + tree[tree[now].ch[0]].sum + tree[now].recy;
//                 now = tree[now].ch[1];
//             }
//         }
//         if (now)
//             splay(now, tree[0].ch[1]);
//         return 0;
//     }

//     inline int atrank(int x) //获取第x小的元素的值
//     {
//         if (x > points)
//             return -INF;
//         int now = tree[0].ch[1];
//         while (true)
//         {
//             int minused = tree[now].sum - tree[tree[now].ch[1]].sum;
//             if (x > tree[tree[now].ch[0]].sum && x <= minused)
//                 break;
//             if (x < minused)
//                 now = tree[now].ch[0];
//             else
//             {
//                 x = x - minused;
//                 now = tree[now].ch[1];
//             }
//         }
//         splay(now, tree[0].ch[1]);
//         return tree[now].v;
//     }

//     inline int upper(int v) //寻找该值对应的一个最近的上界值
//     {
//         int now = tree[0].ch[1];
//         int result = INF;
//         while (now)
//         {
//             if (tree[now].v > v && tree[now].v < result)
//                 result = tree[now].v;
//             if (v < tree[now].v)
//                 now = tree[now].ch[0];
//             else
//                 now = tree[now].ch[1];
//         }
//         return result;
//     }

//     inline int lower(int v) //寻找该值对应的一个最近的下界值
//     {
//         int now = tree[0].ch[1];
//         int result = -INF;
//         while (now)
//         {
//             if (tree[now].v < v && tree[now].v > result)
//                 result = tree[now].v;
//             if (v > tree[now].v)
//                 now = tree[now].ch[1];
//             else
//                 now = tree[now].ch[0];
//         }
//         return result;
//     }
// };
// Splay F;
// int n, opt, x;

// int main()
// {
//     scanf("%d", &n);
//     while (n--)
//     {
//         scanf("%d%d", &opt, &x);
//         if (opt == 1)
//             F.push(x);
//         if (opt == 2)
//             F.pop(x);
//         if (opt == 3)
//             printf("%d\n", F.rank(x));
//         if (opt == 4)
//             printf("%d\n", F.atrank(x));
//         if (opt == 5)
//             printf("%d\n", F.lower(x));
//         if (opt == 6)
//             printf("%d\n", F.upper(x));
//     }
//     return 0;
// }

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
class FHQ_Treap
{
  private:
    struct node
    {
        int siz, val, key, lch, rch;
    } t[100010];
    int tot, seed = 2333, root = 1;

    int Rand()
    { //随机key值
        return seed = int(seed * 482711ll % 2147483647);
    }

    int NEW(int val)
    { //新建节点
        t[++tot].siz = 1;
        t[tot].val = val;
        t[tot].key = Rand();
        t[tot].lch = t[tot].rch = 0;
        return tot;
    }

    void update(int now)
    { //维护子树大小
        t[now].siz = t[t[now].lch].siz + t[t[now].rch].siz + 1;
    }

    void split(int now, int &a, int &b, int val)
    { //拆分操作
        //now原Treap，a左树，b右树，val判定值
        //注意传地址符
        if (now == 0)
        {
            a = b = 0; //若now=0分割完毕；
            return;
        }
        if (t[now].val <= val)                            //因为now左子树中的所有值都小于now的值，所以若now属于左树，那么他们都属于左树递归now的右子树；
            a = now, split(t[now].rch, t[a].rch, b, val); //a=now已经使a的右子树=now的右子树，不再递归a的右子树；
        else                                              //同上now右子树也都属于左树，递归左子树；
            b = now, split(t[now].lch, a, t[b].lch, val);
        update(now); //因为后面会用到左（右）树的siz所以更新维护
    }

    void merge(int &now, int a, int b)
    { //合并操作
        //now新树
        if (a == 0 || b == 0)
        {
            now = a + b; //若某个树已空，则将另一个树整体插入
            return;
        }
        //按照key值合并（堆性质）
        if (t[a].key < t[b].key) //若a树key值<b树，那么b树属于a树的后代，因为b树恒大于a树，那么b树一定属于a树的右后代，a的左子树不变，直接赋给now，递归合并a的右子树和b
            now = a, merge(t[now].rch, t[a].rch, b);
        else
            now = b, merge(t[now].lch, a, t[b].lch); //同理，a树一定是b树的左儿子，递归合并b的左儿子和a
        update(now);
    }

  public:
    void resize(int val)
    {
        t[1].siz = 0;
    }
    void newnode(int val)
    {
        NEW(val);
    }
    void find(int now, int rank)
    { //找第k大
        while (t[t[now].lch].siz + 1 != rank)
        {
            if (t[t[now].lch].siz >= rank)
                now = t[now].lch; //若左子树大小大于rank，找左子树
            else
                rank -= (t[t[now].lch].siz + 1), now = t[now].rch; //找右子树（rank-左子树大小-树根（大小为1））号的元素
        }
        printf("%d\n", t[now].val);
    }
    void insert(int val)
    {
        int x = 0, y = 0, z;
        z = NEW(val);           //新建节点z，作为z树
        split(root, x, y, val); //将树分为两部分，x树为<=待插入值，y树大于
        merge(x, x, z);         //合并x树和新节点z（树），赋给x树
        merge(root, x, y);      //合并新x树和y树，赋给根
        //就这么简单
    }
    void delet(int val)
    {
        int x = 0, y = 0, z = 0;
        split(root, x, y, val);       //分为x树为<=待删除，y树大于
        split(x, x, z, val - 1);      //x树分为新x树<待删除，z树等于待删除
        merge(z, t[z].lch, t[z].rch); //合并z树左右儿子，赋给z树，即丢弃z树根节点（实现删除）
        merge(x, x, z);
        merge(root, x, y); //合并，不在重复
    }
    void rank(int val)
    {
        int x = 0, y = 0;
        split(root, x, y, val - 1);   //分为小于待查找值的x树和大于等于的y树
        printf("%d\n", t[x].siz + 1); //即为待查找值的编号
        merge(root, x, y);            //合并
    }
    void val(int rank)
    {
        find(root, rank); //find查找即可
    }
    void pre(int val)
    {
        int x = 0, y = 0;
        split(root, x, y, val - 1); //x树为<=val-1值即小于val值
        find(x, t[x].siz);          //在小于val值中找最大的（编号为siz的）就是前驱
        merge(root, x, y);
    }
    void nxt(int val)
    {
        int x = 0, y = 0;
        split(root, x, y, val); //x树小于等于val值，那么y树大于val值
        find(y, 1);             //在y树中找最小的，即为后继
        merge(root, x, y);      //合并
    }
};

FHQ_Treap F;
int m;

int main()
{
    F.newnode(2147483647);
    F.resize(0);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            F.insert(x);
        if (opt == 2)
            F.delet(x);
        if (opt == 3)
            F.rank(x);
        if (opt == 4)
            F.val(x);
        if (opt == 5)
            F.pre(x);
        if (opt == 6)
            F.nxt(x);
    }
    return 0;
}