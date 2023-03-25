#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>

typedef struct RedType {
    int key;        // ´ýÅÅÐòÐòÁÐ¹Ø¼ü×ÖÏî
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


void print(SqList* L) {
    for (int i = 1; i <= L->length; ++i) {
        printf("%d ", L->r[i].key);
    }
    printf("\n");
}
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
        InsertSort(L);
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

int main() {
    SqList* L;
    int n;
    struct __timeb64 stime, etime;
    long int rmtime, rstime;
    scanf_s("%d", &n);
    L = CreateRandomSqList(n);

    _ftime64_s(&stime);
    QuickSort(L, 1, L->length);
    _ftime64_s(&etime);
    free(L->r);
    free(L);

    rstime = etime.time - stime.time;
    rmtime = rstime * 1000;
    rmtime += etime.millitm - stime.millitm;

    printf("Execute time=%d", rmtime);
    return 1;
}
