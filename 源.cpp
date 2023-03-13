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

/*--------��������������Ĵ洢�ṹ--------*/
int indegree[MVNum];//��Ÿ��������
int topo[MVNum];//��¼�������еĶ�����
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
		G.vertices[i].firstarc = NULL;//��ʼ����ͷ����ָ����ΪNULL
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
		int cnt = 0;//���ñ����洢�ڽӵ���Ϊi�Ľ�����
		for (int j = 0; j < G.vexnum; j++) {
			ArcNode* p = new ArcNode;//����ָ������߽���ָ��
			p = G.vertices[j].firstarc;
			while (p) {//��pδָ�����������ĩβʱ����ѭ��
				if (p->adjvex == i)//��ĳ�߽���ڽӵ������iʱ����������++
					cnt++;
				p = p->nextarc;//ָ�벻�����ָ
			}
			indegree[i] = cnt;//���������������indegree������
		}
	}
}

Status TopologicalSort(ALGraph G, int topo[]) {
	//����ͼG�����ڽӱ�洢�ṹ
	//��G�޻�·��������G��һ����������topo[]������OK������ERROR
	FindInDegree(G, indegree);//�����������ȴ�������indegree��
	SqStack S;
	InitStack(S);//��ʼ��ջ
	for (int i = 0; i < G.vexnum; i++) {
		if (!indegree[i]) Push(S, i);//���Ϊ0�߽�ջ
	}
	int m = 0;//������������u����ʼΪ0
	while (!StackEmpty(S)) {
		int i = 0;
		Pop(S, i);//��ջ������vi��ջ
		topo[m] = i;//��vi������������������topo��
		++m;//������������
		ArcNode* p = new ArcNode;
		p = G.vertices[i].firstarc;//pָ��vi�ĵ�һ���ڽӵ�
		while (p != NULL) {
			int k = p->adjvex;//vkΪvi���ڽӵ�
			--indegree[k];//vi��ÿ���ڽӵ����ȼ�һ
			if (indegree[k] == 0) Push(S, k);//����ȼ�Ϊ0������ջ
			p = p->nextarc;//pָ�򶥵�vi��һ���ڽӽ��
		}
	}
	if (m < G.vexnum) return ERROR;//������ͼ�л�·
	else return OK;
}

/*������������Ľ��*/
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

/*��������
���룺
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