/**
 * 稀疏矩阵
 */


/* 顺序存储 */
/* 三元组表示*/
/**
 * 三元组建立
 * @param A 存储稀疏矩阵的二维数组
 * @param m A行数
 * @param n A列数
 * @param B 三元组
 */
void createTrimat(float A[][maxSize], int m, int n, float B[][3]) {
    int k = 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0) {
                B[k][0] = A[i][j];  // 值
                B[k][1] = i;  // 行标
                B[k][2] = j;  // 列标
                ++k;
            }
    B[0][0] = k - 1;  // 第0行用来存储非零元素个数、行数和列数
    B[0][1] = m;
    B[0][2] = n;
}

/**
 * 通过三元组打印稀疏矩阵
 * @param B 三元组
 */
void print(float B[][3]) {
    int k = 1;
    for (int i = 0; i < B[0][1]; ++i) {
        for (int j = 0; j < B[0][2]; ++j) {
            if (i == (int)B[k][1] && j == (int)B[k][2]) {
                printf("%d ", B[k][0]);
                k++;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

/* 伪地址表示 */
每行只有两个存储单元：值与伪地址
伪地址即元素在矩阵中按照行优先或列优先存储的相对位置
对于m×n的稀疏矩阵，其元素A[i][j]的伪地址计算方法：n(i−1)+j。可反推真实地址

/* 链式存储 */
/* 邻接表表示 */

/* 十字链表表示 */
tpyedef struct OLNode {  // 普通表结点
    int row, col;  // 行列下标
    struct OLNode *right, *down;  // 该非零元所在行表和列表的后继链域
    float val;
} OLNode;

tpyedef struct {  // 头结点
    OLNode *rhead, *chead;
    int m, n, k;  // 行数、列数、非零元个数
} CrossList;

int createcrossListmat(float A[][maxSize], int m, int n, int k, CrossList &M) {
    if (M.rhead) {
        free(M.rhead);
    }
    if (M.chead) {
        free(M.chead);
    }
    M.m = m;
    M.n = n;
    M.k = k;
    
    // 初始化行、列头结点
    if (!(M.rhead = (OLNode*)malloc(sizeof(OLNode)*m))) return 0;  // 行
    for (int i = 0; i < m; i++) {
        M.rhead[i].right = NULL;
        M.rhead[i].down = NULL;
    }

    if(!(M.chead = (OLNode*)malloc(sizeof(OLNode)*n))) return 0;  // 列
    for (int i = 0; i < n; i++) {
        M.chead[i].right = NULL;
        M.chead[i].down = NULL;
    }
    
    // 设置指向每个列结点的尾指针
    OLNode *temp_c[maxSize];
    for (int j = 0; j < n; j++)
        temp_c[j] = &(M.chead[j]);  // 在双重循环里建会浪费空间
    for (int i = 0; i < m; i++) {
        OLNode *r = &(M.rhead[i]);
        for (int j = 0; j < n; j++) {  // 效果是一行一行建
            if (A[i][j] != 0) {
                OLNode *p = (OLNode*)malloc(sizeof(OLNode));
                p->cow = i;
                p->rol = j;
                p->val = A[i][j];
                p->down = NULL;
                p->right = NULL;
                r->right = p;
                r = p;
                temp_c[j]->down = p;
                temp_c[j] = p;
            }
        }
    }
    return 1;
}