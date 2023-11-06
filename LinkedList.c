/**
 * 线性链表
 */

/* 静态链表 */
#define MaxSize 50
typedef struct {
    ElemType data;
    int next;
} SLinkList[MaxSize];

/* 单链表 */
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/**
 * 尾插法建立单链表
 * @param liList 单链表
 * @param arr 存放元素值的数组
 * @param num 元素个数
 * T(n)=O(n)
 */
void createListT (LinkList &liList, int arr[], int num) {
    // 初始化链表, 设置头结点
    liList = (LNode*)malloc(sizeof(LNode));
    liList->next = NULL;
    // s负责接纳新结点, r负责跟踪链表尾结点
    LNode *s, *r;
    r = liList;
    // 尾插逻辑
    for (int i = 0; i < num; i++) {
        // 申请新结点
        s = (LNode*)malloc(sizeof(LNode));
        s->data = arr[i];
        // 接纳新结点, 并更新r
        r->next = s;
        r = s;
    }
    r->next = NULL;  
}

/**
 * 头插法建立单链表
 * @param liList 待建单链表
 * @param arr 存放元素值的数组
 * @param num 元素个数
 * T(n)=O(n)
 */
void createListH(LinkList &liList, int arr[], int num) {
    // 初始化链表, 设置头结点
    liList = (LNode*)malloc(sizeof(LNode));
    liList->next = NULL;
    // s负责接纳新结点
    LNode *s;
    // 头插逻辑
    for (int i = 0; i < num; i++) {
        // 申请新结点
        s = (LNode*)malloc(sizeof(LNode));
        s->data = arr[i];
        // 头插
        s->next = liList->next;
        liList->next = s;
    }
}

/**
 * 后插(在给定结点p后插入新结点s)
 * T(n)=O(1)
 */
void insertBehind(LNode *p, LNode *s) {
    s->next = p->next;
    p->next = s;
}

/**
 * 在指定位序seq插入新结点s
 * T(n)=O(n)
 */
void insertBySeq(LinkList liList, int seq, LNode *s) {
    // 位序校验
    if (seq < 1) {
        return;
    }
    // 后到第i-1个结点的后面
    insertBehind(getElemBySeq(liList, seq-1), s);
}

/**
 * 前插1(在给定结点p前插入新结点s)
 * T(n)=O(n)
 */
void insertFront1(LNode *p, LNode *s, LinkList liList) {
    // 转化为后插:插到p的前驱结点的后面
    LNode *q = liList;
    while (q->next != p) {
        q = q->next;
    }
    insertBehind(q, s);
}

/**
 * 前插2(在给定结点p前插入新结点s)
 * T(n)=O(1)
 */
void insertFront2(LNode *p, LNode *s) {
    // 伪前插真后插:后插,然后数据域交换
    insertBehind(p, q);
    ElemType tmp = p->data;
    p->data = q->data;
    q->data = tmp;
}

/**
 * 根据前驱结点删除结点
 * T(n)=O(1)
 */
void delLNodeByPre(LNode *pre) {
    LNode *q = pre->next;
    pre->next = pre->next->next;
    free(q);
}

/**
 * 按位序删除结点
 * T(n)=O(n)
 */
void delLNodeBySeq(LinkList liList, int seq) {
    // 位序校验
    if (seq < 1) {
        return;
    }
    // 根据前驱结点进行删除操作
    delLNodeByPre(getElemBySeq(liList, seq-1));
}

/**
 * 根据后继结点删除结点
 * @param p 要删除的结点
 * T(n)=O(1)
 */
void delLNodeByNext(LNode *p) {
    // 不适用要删除结点是尾结点的情况
    if (p->next == NULL) {
        return;
    }
    // 将后继结点的数据域赋予其自身,然后删除后继结点
    p->data = p->next->data;
    delLNodeByPre(p);
}

/**
 * 按位序查找结点
 * 返回第seq个结点(的指针)
 * T(n)=O(n)
 */
LNode *getElemBySeq(LinkList liList, int seq) {
    // 位序校验
    if (seq < 0) {  // seq=0意味着头结点
        return NULL;
    }
    LNode *p = liList;
    while (seq-- > 0 && p != NULL) {
        p = p->next;
    }
    return p;  // 若i大于表长则返回NULL
}

/**
 * 按值查找结点
 * 返回数据域等于给定值val的第一个结点(的指针)
 * T(n)=O(n)
 */
LNode *getElemByVal(LinkList liList, ElemType val) {
    LNode *p = liList->next;
    while (p != NULL && p->data != val) {
        p = p->next;
    }
    return p;  // 找不到就返回NULL
}


/**
 * 两个非递减单链表A、B归并为一个非递减单链表C
 */
void mergeLinkList1(LinkList A, LinkList B, LinkList &C) {
    // 设置指针跟踪A、B当前的最小值结点
    LNode *p = A->next;
    LNode *q = B->next;

    // 初始化C,拿A的头结点做C的头结点
    C = A;
    C->next = NULL;

    LNode *r = C;  // 设置指针r跟踪C尾结点
    free(B);  // B的头结点没用了

    // 归并逻辑
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            r->next = p;
            p = p->next;
        } else {
            r->next = q;
            q = q->next;
        }
        r = r->next;
    }
    
    // 收尾工作
    r->next = NULL;
    if (p != NULL) {
        r->next = p;
    }
    if (q != NULL) {
        r->next = q;
    }
}

/**
 * 两个非递减单链表A、B归并为一个非递增单链表C
 */
void mergeLinkList2(LinkList A, LinkList B, LinkList &C) {
    // 初始化
    LNode *p = A->next;
    LNode *q = B->next;
    C = A;
    C->next = NULL;
    free(B);

    // 归并逻辑
    LNode *s;  // 指向要头插的结点
    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            s = p;
            p = p->next;
        } else {
            s = q;
            q = q->next;            
        }
        // 头插
        s->next = C->next;
        C->next = s;
    }

    // 收尾工作
    while (p != NULL) {
        s = p;
        p = p->next;
        // 头插
        s->next = C->next;
        C->next = s;
    }
    while (q != NULL) {
        s = q;
        q = q->next;
        // 头插
        s->next = C->next;
        C->next = s;
    }
}

/* 双链表 */
typedef struct DLNode {
    ElemType data;
    struct DLNode *prior, *next;
} DLNode, *DLinkList;

/**
 * 尾插建表
 * @param L 待建双链表
 * @param a 存放元素值的数组
 * @param n 元素个数
 */
void createDlistT(DLinkList &L, int a[], int n) {
    DLNode *s, *r;
    int i;
    L = (DLNode*)malloc(sizeof(DLNode));
    L->prior = NULL;
    L->next = NULL;
    r = L;  // 依旧跟踪
    for (i = 0; i < n; i++) {
        s = (DLNode*)malloc(sizeof(DLNode));
        s->data = a[i];
        r->next = s;
        s->prior = r;
        r = s;
    }
    r->next = NULL;
}

/**
 * 后插(s插到p后)
 */
s->next = p->next;
s->prior = p;
p->next = s;
s->next->prior = s;  // p不是原尾结点时

/**
 * 删除p的后继
 */
q = p->next;
p->next = q->next;
q->next->prior = p;
free(q);

/* 循环单链表 */
判空: 头结点的next指针是否等于头指针

/* 循环双链表 */
判空: 头结点的prior和next指针是否都等于头指针