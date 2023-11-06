/**
 * 树与二叉树
 */

/* 一般二叉树 */
typedef struct BTNode {
    ElemType data;
    struct BTNode *lchild, *rchild;
} BTNode, *BTree;

/**
 * 先序遍历 NLR
 */
void preOrder(BTree t) {
    if (t == NULL) return;
    
    visit(t);
    preOrder(t->lchild);
    preOrder(t->rchild);
}

/**
 * 中序遍历 LNR
 */
void inOrder(BTree t) {
    if (t == NULL) return;

    inOrder(t->lchild);
    visit(t);
    inOrder(t->rchild);
}

/**
 * 后序遍历 LRN
 */
void postOrder(BTree t) {
    if (t == NULL) return;

    postOrder(t->lchild);
    postOrder(t->rchild);
    visit(t);
}

/**
 * 先序遍历非递归
 */
void preOrderNonrecursion(BTree t) {
    SqStack st;
    initStack(st);
    BTNode *p = t;
    while (p || !isEmpty(st)) {
        if (p) {
            visit(p);
            push(st, p);
            p = p->lchild;
        } else {
            pop(st, p);
            p = p->rchild;
        }
    }
}

/**
 * 中序遍历非递归
 */
void inOrderNonrecursion(BTree t) {
    SqStack st;
    initStack(st);
    BTNode *p = t;
    while (p || !isEmpty(st)) {
        if (p) {
            push(st, p);
            p = p->lchild;
        } else {
            pop(st, p);
            visit(p);
            p = p->rchild;
        }
    }
}

/**
 * 后序遍历非递归
 */
void postOrderNonrecursion(BTree t){
    SqStack st;
    initStack(st);
    BTNode *p = t;
    BTNode *r = NULL;  // 指向上一次访问的结点
    while (p || !isEmpty(st)) {
        if (p) {
            push(st, p);
            p = p->lchild;
        } else {
            getTop(st, p);
            if (p->rchild && p->rchild != r) {
                p = p->rchild;
            }
            else {
                pop(st, p);
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
}

/**
 * 层次遍历
 */
void levelOrder(BTree t) {
    SqQueue qu;
    initQueue(qu);
    BTNode *p = t;
    enQueue(qu, t);
    while (!isEmpty(qu)) {
        int size = qu.size;
        while (size > 0) {
            deQueue(qu, p);
            --size;
            visit(p);
            if (p->lchild) {
                enQueue(qu, p->lchild);
            }
            if (p->rchild) {
                enQueue(qu, p->rchild);
            }
        }
    }
}

/* 线索二叉树 */
tpyedef struct TBTNode {
    ElemType data;
    struct TBTNode *lchild, *rchild;
    int ltag, rtag;
} TBTNode, *TBTree;

/* 中序线索二叉树 */

/**
 * 通过中序遍历对二叉树线索化
 * @param p   当前访问的结点
 * @param pre 上一个访问的结点
 */
void inThread(TBTNode *&p, TBTNode *&pre) {
    if (p == NULL) return;

    // 线索化左子树
    inThread(p->lchild, pre);

    // 建立当前结点前驱线索
    if (p->lchild == NULL) {
        p->lchild = pre;
        p->ltag = 1;
        // p->lchild为NULL且pre也为NULL,
        // 说明p是中序遍历序列中的第一个结点
    }

    // 建立前驱结点后继线索
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 当前结点处理完毕,标记成为上一个访问的结点
    pre = p;

    // 线索化右子树
    inThread(p->rchild, pre);
}

/**
 * 通过中序遍历建立中序线索二叉树
 */
void createInThread(TBTree t) {
    if (t == NULL) return;

    // 中序遍历线索化二叉树
    TBTNode* pre = NULL;
    inThread(t, pre);

    // 处理最后一个结点
    pre->rchild = NULL;
    pre->rtag = 1;
}

/**
 * 带头结点的中序线索二叉树
 *
 * 头结点lchild指向二叉树根结点,rchild指向中序遍历时访问的最后一个结点
 * 同时令中序序列第一个结点的lchild和最后一个结点的rchild均指向头结点
 *
 * 这好比为二叉树建立了一个双向循环线索链表,方便从前往后或从后往前对线索二叉树进行遍历
 */

/**
 * 求中序线索二叉树中中序序列下的第一个结点
 * @param  p 中序线索二叉树根结点
 * @return   目标结点
 */
TBTNode *firstNodeIn(TBTNode *p) {
    while (p->ltag == 0) {
        p = p->lchild;  // 即最左结点
    }
    return p;
}

/**
 * 求中序线索二叉树中中序序列下的最后一个结点
 * @param  p 中序线索二叉树根结点
 * @return   目标结点
 */
TBTNode *lastNodeIn(TBTNode *p) {
    while (p->rtag == 0) {
        p = p->rchild;  // 即最右结点
    }
    return p;
}

/**
 * 求中序线索二叉树中结点在中序序列下的前驱
 * @param  p 中序线索二叉树某结点
 * @return   p的前驱结点
 */
TBTNode *priorNodeIn(TBTNode *p) {
    if (p->ltag == 1) {
        return p->lchild;  // 有线索
    } else {
        return lastNodeIn(p->lchild);  // 左子树最右结点
    }  
}

/**
 * 求中序线索二叉树中结点在中序序列下的后继
 * @param  p 中序线索二叉树某结点
 * @return   p的后继结点
 */
TBTNode *nextNodeIn(TBTNode *p) {
    if (p->rtag == 1) {
        return p->rchild;  // 有线索
    } else {
        return firstNodeIn(p->rchild);  // 右子树最左结点
    }
}

/**
 * 中序线索二叉树的中序遍历
 */
void inOrder(TBTree t) {
    for (TBTNode *p = firstNodeIn(t); p != NULL; p = nextNodeIn(p)) {
        visit(p);
    }
}

/* 先序线索二叉树 */
/**
 * 通过先序遍历对二叉树线索化
 * @param p   当前访问的结点
 * @param pre 上次访问的结点
 */
void preThread(TBTNode *&p, TBTNode *&pre) {
    if (p == NULL) return;

    // 建立当前结点前驱线索
    if (p->lchild == NULL) {
        p->lchild = pre;
        p->ltag = 1;
    }
    // 建立前驱结点后继线索
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 标记当前结点成为上一个访问过的结点
    pre = p;

    // 线索化左子树
    preThread(p->lchild, pre);

    // 线索化右子树
    preThread(p->rchild, pre);
}

/**
 * 求先序线索二叉树中结点在先序序列下的前驱
 * 为其双亲或是左兄弟子树最右叶结点，都需要找到双亲，要是有左孩子，就无法找到
 */

/**
 * 求先序线索二叉树中结点在先序序列下的后继
 */
TBTNode *nextNodePre(TBTNode *p) {
    return p->ltag == 0 ? p->lchild : p->rchild;
}

/**
 * 先序线索二叉树的先序遍历
 */
void preOrder(TBTree t) {
    if (t ！= NULL) {
        TBTNode *p = T;
        while (p ！= NULL) {
            while (p->ltag == 0) {  //一路向左
                visit(p);
                p = p->lchild;
            }
            visit(p);
            p = p->rchild;  
        }
    }
}

/**
 * 通过后序遍历对二叉树线索化
 * @param p   正在访问的结点
 * @param pre 刚刚访问过的结点
 */
void postThread(TBTNode *p, TBTNode *&pre) {
    if (p == NULL) return;

    // 线索化左子树
    postThread(p->lchild, pre);

    // 线索化右子树
    postThread(p->rchild, pre);  

    // 建立当前结点的前驱线索
    if (!p->lchild) {
        p->lchild = pre;
        p->ltag = 1;
    }

    // 建立前驱结点的后继线索
    if (pre && !pre->rchild) {  
        pre->rchild = p;
        pre->rtag = 1;
    }

    // 标记当前结点成为上一个访问过的结点
    pre = p;
}

/**
 * 求后序线索二叉树中结点p在后序序列下的前驱
 */
TBTNode *priorNodePost(TBTNode *p) {
    return p->rtag == 0 ? p->rchild : p->lchild;
    // 有右孩子 → 右孩子
    // 无右孩子但有左孩子 → 左孩子
    // 左右孩子都无 → 左链域(线索)    
}

/**
 * 求后序线索二叉树中结点在后序序列下的后继
 *
 * 为其双亲或是右兄弟子树最左叶结点，都需要找到双亲，要是有右孩子，就无法找到
 */

/**
 * 后序线索二叉树的后序遍历
 *
 * 后继不一定找得到，想遍历就需要栈的支持，或再给结点增加指针域
 */


/* 二叉排序树 BST */
/**
 * 查找关键字 非递归
 * @param  T   二叉排序树
 * @param  key 关键字
 * @return     关键字结点
 */
BTNode *BSTSearch(BTree T, int key) {
    while (T && key != T->data) {
        T = key < T->data ? T->lchild : T->rchild;
    }
    return T;
}

/**
 * 插入关键字
 * @param  T   二叉排序树
 * @param  key 关键字
 * @return     成功1,失败0
 */
int BSTInsert(BTree &T, int key) {
    if (!T) {
        T = (BTree)malloc(sizeof(BTNode));
        T->data = key;
        T->lchild = T->rchild = NULL;
        return 1;
    } else if (key == T->data) {
        return 0;
    } else if (key < T->data) {
        return BSTInsert(T->lchild, key);
    } else {
        return BSTInsert(T->rchild, key);
    }
}

/**
 * 删除
 */
// -1. 叶子结点直接删
// -2. 只有左/右子树，拿子树替换上
// -3. 左右子树都有，则拿直接前驱(左子树最右)/直接后继(右子树最左)值原位低缓，再按前两种情况删该直接前驱/直接后继

/**
 * 构造
 * @param T   二叉排序树
 * @param key 关键字数组
 * @param n   关键字个数
 */
void createBST(BTree &T, int key[], int n) {
    T = NULL;
    for (int i = 0; i < n; i++) {
        BSTInsert(T, key[i]);
    }
}

/* 树 (双亲表示法) */
#define MAX_TREE_SIZE 100
/**
 * 结点
 */
typedef struct {
    ElemType data;
    int parent;
} TNode;
/**
 * 树
 */
typedef struct {
    TNode nodes[MAX_TREE_SIZE];
    int n;
} Tree;

/* 树 (孩子兄弟表示法/二叉树表示法) */
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstChild, *nextSibling;
} CSNode, *CSTree;

/* 并查集 */
/* 存储结构:树(森林)的双亲表示 */
#define SIZE 100
int s[SIZE];  // 集合元素数组(双亲指针数组)

/**
 * 并查集的初始化
 * 将集合中的每个元素都初始化为只有一个单元素的子集合
 */
void initial(int s[]) {
    for (int i = 0; i < SIZE; ++i) {
        s[i] = -1;
    }
}

/**
 * 查找集合中单元素x所在的子集合,返回该子集合的根结点
 *
 * 判断两个元素是否属于同一集合,只需分别找到它们的根结点,比较根结点是否相同即可
 */
int find(int s[], int x) {
    while (s[x] > 0) {
        x = s[x];
    }
    return x;
}

/**
 * 求两个不相交子集合的并集
 * 把子集合root2并入root1
 */
void union(int s[], int root1, int root2) {
    if (root1 == root2) {
        return;
    }
    s[root2] = root1;
}
// 如果将两个元素所在的集合合并为一个集合,那么就需要先找到两个元素的根结点