#include<iostream>
#include<string>
using namespace std;
#define MVNum 100
#define OK 1
#define ERROR 0
#define MaxInt 100
typedef string VerTexType;
typedef int Status;
typedef int SElemType;

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
}ArcNode;
typedef struct VNode {
	VerTexType data;
	ArcNode* firstarc;
}VNode, AdjList[MVNum];

typedef struct {
	int vexnum, arcnum;
	AdjList vertices;
}ALGraph;

/*--------拓扑排序辅助数组的存储结构--------*/
int indegree[MVNum];//存放各顶点入度
int topo[MVNum];//记录拓扑序列的顶点编号
Status InitStack(SqStack& S) {
	S.base = new SElemType[MaxInt];
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = MaxInt;
	return OK;
}

Status StackEmpty(SqStack S) {
	if (S.top == S.base) return OK;
	return ERROR;
}

Status Push(SqStack& S, SElemType e) {
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top = e;
	S.top++;
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	if (S.base == S.top) return ERROR;
	S.top--;
	e = *S.top;
	return OK;
}

int LocateVex(ALGraph G, VerTexType v) {
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vertices[i].data == v)
			return i;
	}
	return -1;
}

void CreateUDG(ALGraph& G) {
	cin >> G.vexnum >> G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {
		cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;//初始化表头结点的指针域为NULL
	}
	for (int k = 0; k < G.arcnum; k++) {
		VerTexType v1, v2;
		cin >> v1 >> v2;
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* p1 = new ArcNode;
		p1->adjvex = j;
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1;
	}
}

void FindInDegree(ALGraph G, int indegree[]) {
	for (int i = 0; i < G.vexnum; i++) {
		int cnt = 0;//设置变量存储邻接点域为i的结点个数
		for (int j = 0; j < G.vexnum; j++) {
			ArcNode* p = new ArcNode;//定义指向各个边结点的指针
			p = G.vertices[j].firstarc;
			while (p) {//当p未指到单个链表的末尾时继续循环
				if (p->adjvex == i)//当某边结点邻接点域等于i时，计数变量++
					cnt++;
				p = p->nextarc;//指针不断向后指
			}
			indegree[i] = cnt;//将计数结果保留在indegree数组中
		}
	}
}

Status TopologicalSort(ALGraph G, int topo[]) {
	//有向图G采用邻接表存储结构
	//若G无回路，则生成G的一个拓扑排序topo[]并返回OK，否则ERROR
	FindInDegree(G, indegree);//求出各结点的入度存入数组indegree中
	SqStack S;
	InitStack(S);//初始化栈
	for (int i = 0; i < G.vexnum; i++) {
		if (!indegree[i]) Push(S, i);//入度为0者进栈
	}
	int m = 0;//对输出顶点计数u，初始为0
	while (!StackEmpty(S)) {
		int i = 0;
		Pop(S, i);//将栈顶顶点vi出栈
		topo[m] = i;//将vi保存在拓扑序列数组topo中
		++m;//对输出顶点计数
		ArcNode* p = new ArcNode;
		p = G.vertices[i].firstarc;//p指向vi的第一个邻接点
		while (p != NULL) {
			int k = p->adjvex;//vk为vi的邻接点
			--indegree[k];//vi的每个邻接点的入度减一
			if (indegree[k] == 0) Push(S, k);//若入度减为0，则入栈
			p = p->nextarc;//p指向顶点vi下一个邻接结点
		}
	}
	if (m < G.vexnum) return ERROR;//该有向图有回路
	else return OK;
}

/*输出拓扑排序后的结果*/
void PrintResult(ALGraph G) {
	if (TopologicalSort(G, topo)) {
		for (int i = 0; i < G.vexnum; i++) {
			cout << G.vertices[topo[i]].data << " ";
		}
	}
}

int main() {
	ALGraph G;
	CreateUDG(G);
	PrintResult(G);
	return 0;
}

/*测试数据
输入：
6 8
v1 v2 v3 v4 v5 v6
v1 v2
v1 v3
v1 v4
v3 v2
v3 v5
v4 v5
v6 v4
v6 v5

*/