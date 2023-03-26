#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>

typedef struct RedType {
    int key;        // ���������йؼ�����
}RedType;

typedef struct SqList {
    RedType* r;
    int length;
}SqList;

SqList* CreateRandomSqList(int sqListLen) {
    SqList* sq;
    int i;
    sq = (SqList*)malloc(sizeof(SqList));
    sq->length = sqListLen;
    sq->r = (RedType*)malloc((sq->length + 1) * sizeof(RedType));
    srand((unsigned)time(NULL));
    for (i = 1; i <= sq->length; i++) {
        sq->r[i].key = (int)rand();
    }
    return sq;
}

SqList* CopyRandomSqList(SqList*csq) {
    SqList* sq;
    int i;
    sq = (SqList*)malloc(sizeof(SqList));
    sq->length = csq->length;
    sq->r = (RedType*)malloc(sizeof(RedType)*(sq->length+1));
    for (i = 1; i <= sq->length; i++) {
        sq->r[i].key = csq->r[i].key;
    }
    return sq;
}

void InsertSort(SqList* L) {
    int i, j;
    for (i = 2; i <= L->length; i++) {
        if (L->r[i].key < L->r[i - 1].key) {
            L->r[0] = L->r[i];
            for (j = i - 1; L->r[0].key < L->r[j].key; --j) {
                L->r[j + 1] = L->r[j];
            }
            L->r[j + 1] = L->r[0];
        }
    }
}

void QuickSort(SqList* L, int begin, int end) {
    if (begin > end)
        return;
    int tmp = L->r[begin].key;
    int i = begin;
    int j = end;
    while (i != j) {
        while (L->r[j].key >= tmp && j > i)
            j--;
        while (L->r[i].key <= tmp && j > i)
            i++;
        if (j > i) {
            int t = L->r[i].key;
            L->r[i].key = L->r[j].key;
            L->r[j].key = t;
        }
    }
    L->r[begin].key = L->r[i].key;
    L->r[i].key = tmp;
    QuickSort(L, begin, i - 1);
    QuickSort(L, i + 1, end);
}

void Merge(RedType*SR, RedType*TR, int i, int m, int n) {
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; ++k) {
        if (SR[i].key <= SR[j].key)
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }
    if (i <= m) {
        for (l = k; i <= m; l++, i++) {
            TR[l] = SR[i];
        }
    }
    if (j <= n) {
        for (l = k; j <= n; l++, j++) {
            TR[l] = SR[j];
        }
    }
}

void MSort(RedType *SR, RedType*TR1, int s, int t) {
    RedType* TR2;
    int m;
    TR2 = (RedType*)malloc(sizeof(RedType)*(t+1));
    if (s == t) {
        TR1[s] = SR[s];
    }
    else {
        m = (s + t) / 2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
    free(TR2);
}

void MergeSort(SqList* L) {
    MSort(L->r, L->r, 1, L->length);
}

void aMerge(RedType* SR, int i, int m, int n) {
    int j, k, l;
    for (j = m + 1; j <= n; j++) {
        if (SR[j].key <= SR[j - 1].key) {
            int temp = SR[j].key;
            for (k = j - 1; temp < SR[k].key && k >= i; --k)
                SR[k + 1].key = SR[k].key;
            SR[k + 1].key = temp;
        }
    }
}

void aMSort(RedType* SR, int s, int t) {
    int m;
     if (s < t) {
        m = (s + t) / 2;
        aMSort(SR, s, m);
        aMSort(SR, m + 1, t);
        aMerge(SR, s, m, t);
    }
}

void aMergeSort(SqList* L) {
    aMSort(L->r, 1, L->length);
}

void Swap(RedType* num, int i, int j)
{
    int temp;
    temp = num[i].key;
    num[i].key = num[j].key;
    num[j].key = temp;
}

// ���ѵ���
void Heapify(RedType* num, int len, int k)
{
    if (k < len)
    {
        int root = k;           // �����
        int lchild = 2 * k + 1;   // ���ӽ��
        int rchild = 2 * k + 2;   // �Һ��ӽ��
        // �������Һ��ӽ���е������
        if (lchild < len && num[root].key < num[lchild].key)
        {
            root = lchild;
        }
        if (rchild < len && num[root].key < num[rchild].key)
        {
            root = rchild;
        }

        // ��������㵽�����
        if (root != k)
        {
            Swap(num, root, k);
            // ÿ�ν���������Ӱ�쵽��Ӧ���ӽ��������˳��
            // ������Ҫ�Խ�����ĺ��ӽ�������������ѵ���
            Heapify(num, len, root);
        }
    }
}

// ��������
void CreateHeap(RedType* num, int len)
{
    int i;
    // ���һ������±�
    int last = len - 1;
    // ���һ�����ĸ�����±�
    int parent = (last - 1) / 2;
    // �����һ�����ĸ���㵽����㣬���ν������ѵ���
    for (i = parent; i >= 0; i--)
    {
        Heapify(num, len, i);
    }
}

// ������
void HeapSort(RedType* num, int len)
{
    // �������Ѳ��������ѵ���
    CreateHeap(num, len);
    //printf("���ѵ���!\n");
    int i;
    // ����ȡ������㣨���ֵ��
    for (i = len - 1; i >= 0; i--)
    {
        // �����ѵĸ���㣨���ֵ���������һ�����
        Swap(num, i, 0);
        // ������������ĸ���㷢���˸ı䣬�ʻ���Ը���������ѵ������ѽ�����ĩβ��㲻���������
        // ����ʱ�����С�����и���㣬����ڵ���ʱֻ�迼������ӵķ�֧����
        Heapify(num, i, 0);
    }
}

void WriteToFile(int num, int SortTime[], FILE *fp) {
    char ch[20];
    for (size_t i = 0; i < num; i++)
    {
        _itoa_s(SortTime[i], ch, 10);
        strcat_s(ch, ",");
        fwrite(ch, sizeof(char), strlen(ch), fp);
    }
    fwrite("\n",sizeof(char), 1, fp);
}

void print(SqList* L) {
    for (int i = 1; i <= L->length; ++i) {
        printf("%d ", L->r[i].key);
    }
    printf("\n");
}

/*
int main() {
    SqList* L;
    int n;
    struct __timeb64 stime, etime;
    long int rmtime, rstime;
    scanf_s("%d", &n);
    L = CreateRandomSqList(n);
    _ftime64_s(&stime);
    HeapSort(L->r, L->length);
    _ftime64_s(&etime);
    free(L->r);
    free(L);

    rstime = etime.time - stime.time;
    rmtime = rstime * 1000;
    rmtime += etime.millitm - stime.millitm;

    printf("Execute time=%d", rmtime);
    return 1;
}
*/

/*
int main() {
    SqList* L;
    struct __timeb64 stime, etime;
    long int rmtime, rstime;
    char ch[20];
    FILE* fp;
    fopen_s(&fp, "Curv.csv", "w");
    for (size_t i = 1000; i <= 100000; i+=1000) {
        _itoa_s(i, ch, 10);
        strcat_s(ch, ",");
        fwrite(ch, sizeof(char), strlen(ch), fp);
    }
    fwrite("\n", sizeof(char), 1, fp);

    for (size_t i = 1000; i <= 100000; i += 1000) {
        L = CreateRandomSqList(i);
        _ftime64_s(&stime);
        QuickSort(L, 1, L->length);
        _ftime64_s(&etime);
        free(L->r);
        free(L);
        rstime = etime.time - stime.time;
        rmtime = rstime * 1000;
        rmtime += etime.millitm - stime.millitm;
        _itoa_s(rmtime, ch, 10);
        strcat_s(ch, ",");
        fwrite(ch, sizeof(char), strlen(ch), fp);
    }
    fwrite("\n", sizeof(char), 1, fp);
    fclose(fp);
    return 1;
}
*/

/*
int main() {
    SqList* L, *L1;
    struct __timeb64 stime, etime;
    long int rmtime, rstime;
    char ch[20];
    int inSortTime[105], mergeSortTime[105];
    FILE* fp;
    fopen_s(&fp, "Curv.csv", "w");

    for (size_t i = 1000; i <= 100000; i += 1000) {
        _itoa_s(i, ch, 10);
        strcat_s(ch, ",");
        fwrite(ch, sizeof(char), strlen(ch), fp);
    }
    fwrite("\n", sizeof(char), 1, fp);

    int k = 0;
    for (size_t i = 1000; i <= 100000; i += 1000) {
        L = CreateRandomSqList(i);
        L1 = CopyRandomSqList(L);

        _ftime64_s(&stime);
        QuickSort(L, 1, L->length);
        _ftime64_s(&etime);
        free(L->r);
        free(L);
        rstime = etime.time - stime.time;
        rmtime = rstime * 1000;
        rmtime += etime.millitm - stime.millitm;
        inSortTime[k] = rmtime;
        
        _ftime64_s(&stime);
        MergeSort(L1);
        _ftime64_s(&etime);
        free(L1->r);
        free(L1);
        rstime = etime.time - stime.time;
        rmtime = rstime * 1000;
        rmtime += etime.millitm - stime.millitm;
        mergeSortTime[k] = rmtime;
        k++;
    }

    WriteToFile(100, inSortTime, fp);
    WriteToFile(100, mergeSortTime, fp);
    fclose(fp);
    return 1;
}
*/
