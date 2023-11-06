/**
 * 顺序查找
 */
typedef struct {
    ElemType *elem;
    int tableLen;
} SSTable;

int seqSearch(SSTable st, ElemType key) {
    st.elem[0] = key;  // 哨兵,作用是使下面的for循环不必判断数组越界
    for (int i = st.tableLen; st.elem[i] != key; i--);
    return i;  // 若返回0则查找失败
}


/**
 * 折半查找/二分查找
 */
int BSearch(SSTable st, ElemType key) {
    int low = 0, high = st.length - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (st.elem[mid] == key) {
            return mid;
        } else if (st.elem[mid] > key) {
            high = mid - 1;
        } else {
            low = low + 1;
        }
    }
    return -1;
}