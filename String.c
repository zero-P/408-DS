/**
 * 串
 */
typedef struct {
    char str[maxSize+1];
    int length;
} Str;

typedef struct {
    char *ch;
    int length;
} Str;

/**
 * 赋值
 * @param  str 被赋值的串
 * @param  ch  赋值内容
 * @return     1 成功, 0 失败
 */
int strAssign(Str &str, char* ch) {
    if (str.ch)  // 清空
        free(str.ch);
    int len = 0;
    char *c = ch;
    while (*c) {   // 求 ch 串长度
        len++;
        c++;
    }
    if (!len) {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }
    str.ch = (char*)malloc(sizeof(char)*(len + 1))
    if (!str.ch)  // 分配失败
        return 0;   
    c = ch;
    for (int i = 0; i <= len; i++, c++)    // <=
        str.ch[i] = *c;
    str.length = len;
    return 1;
}

/**
 * 取串长
 * @param  str 要取长的串
 * @return     串长
 */
int strLength(Str str) {
    return str.length;
}

/**
 * 串比较
 * @param  str1 串 1
 * @param  str2 串 2
 * @return    串 1 > 串 2 返回值 > 0, 串 1 < 串 2 返回值 < 0, 串 1 = 串 2 返回值 = 0
 */
int strCompare(Str str1, Str str2) {
    for (int i = 0; i < str1.length && i < str2.length; i++)
        if (str1.ch[i] != str2.ch[i])
            return str1.ch[i] - str2.ch[i];
    return str1.length - str2.length;
}

/**
 * 串连接
 * @param  s  连接后的新串
 * @param  str1 串 1
 * @param  str2 串 2
 * @return      成功 1, 失败 0
 */
int strContact(Str &str, Str str1, Str str2) {
    if (str.ch) {  // 清空
        free(str.ch);
        str.ch = NULL;
    }
    str.length = str1.length + str2.length;
    str.ch = (char*)malloc(sizeof(char)*(str.length + 1));
    if (!str.ch)
        return 0;
    int i = 0;
    while (i < str1.length) {
        str.ch[i] = str1.ch[i];
        i++;
    }
    int j = 0;
    while (j <= str2.length) {    // <=
        str.ch[i+j] = str2.ch[j];
        j++;
    }
    return 1;
}

/**
 * 求子串
 * @param  substr 用来返回子串
 * @param  str    主串
 * @param  pos    子串位置
 * @param  len    子串长度
 * @return        成功 1, 失败 0
 */
int subString(Str &substr, Str str, int pos, int len) {
    if (pos < 0 || pos >= str.length || len < 0 || len > str.length - pos)
        return 0;
    if (substr.ch) {
        free(substr.ch);
        substr.ch = NULL;
    }
    if (len == 0) {
        substr.ch = NULL;
        substr.length = 0;
        return 1;
    }
    substr.ch = (char*)malloc(sizeof(char)*(len + 1));
    int i = pos;
    int j = 0;
    while (i < pos + len) {
        substr.ch[j] = str.ch[i];
        i++;
        j++;
    }
    substr.ch[j] = '\0';
    substr.length = len;
    return 1;
}

/**
 * 清空
 * @param  str 被清空的串
 * @return     1 成功
 */
int clearString(Str& str) {
    if (str.ch) {
        free(str.ch);
        str.ch = NULL;
    }
    str.length = 0;
    return 1;
}

/* 模式匹配算法: 求子串 (模式串) 在主串中首次出现的位置 */

/**
 * 简单模式匹配算法 (暴力匹配)
 * @param  str    主串
 * @param  substr 模式串
 * @return        模式串在主串中首次出现的位置, 没有则返回 0
 */
int index(Str str, Str substr) {
    int i = 0, j = 0, k = i;
    while (i < str.length && j < substr.length) {
        if (str.ch[i] == substr.ch[j]) {
            i++;
            j++;
        }
        else {
            j = 0;
            i = k++;
        }
    }
    if (j == substr.length)
        return k;
    return 0;
}

/**
 * next 数组算法 (求模式串每个位置的最大公共前后缀长度)
 * @param substr 模式串
 * @param next   next 数组
 */
void getNext(Str substr, int next[]) {
    int i = 0, k = -1;
    next[0] = -1;  // 模式串指针位于第一个字符且不匹配，应从主串的下一个位置与模式串第一个字符继续比较
    while (i < substr.length) {
        if (k == -1 || substr.ch[i] == substr.ch[k])        
            next[++i] = ++k;
        else
            k = next[k];
    }
}

/**
 * KMP 算法
 * @param  str    主串
 * @param  substr 模式串
 * @param  next   next 数组
 * @return        模式串在主串中首次出现的位置, 没有则返回 0
 */
int KMP(Str str, Str substr, int next[]) {
    int i = 0, j = 0;
    while (i < str.length && j < substr.length) {
        if (j == -1 || str.ch[i] == substr.ch[j]) {
            i++;
            j++;
        }
        else
            j = next[j];  // i 无需回溯
    }
    if (j == substr.length)
        return i - substr.length;
    return 0;
}

/**
 * KMP 算法改进 (next 数组改进)
 * @param substr  模式串
 * @param nextVal nextVal 数组
 */
void getNextVal(Str substr, int nextVal[]) {
    int j = 0, k = -1;
    nextVal[0] = -1;
    while (j < substr.length) {
        if (k == -1 || substr.ch[j] == substr.ch[k]) {
            if (substr.ch[++j] != substr.ch[++k])    
                nextVal[j] = k; 
            else  // 相等时指针回溯后还是不匹配，就没必要回溯到这
                nextVal[j] = nextVal[k];  // 所以再往前跳
        }
        else
            k = nextVal[k];
        // 再往前跳肯定不会再相等，因为 nextval 数组是从前往后逐个求得，这种情况显然在之前已经排除
    }
}