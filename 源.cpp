#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
#include<sys/timeb.h>
void Perm(int*, int, int);
void Swap(int&, int&);
using namespace std;

int main()
{

	int a[10] = { 0,1,2,3,4,5,6,7,8 };
	struct _timeb stime, etime;           //�洢�㷨���еĿ�ʼʱ��ͽ���ʱ��
	long int rmtime, rstime;              //�����Ӧ����ͺ�����
	ofstream outfile;
	string readfilename;
	cout << "�����뽫Ҫ�򿪵��ļ�����";
	cin >> readfilename;
	outfile.open(readfilename, ios::out);
	if (!outfile)
	{
		cout << "�ļ���ʧ��" << endl;
		exit(0);
	}

	for (int i = 5; i <= 9; i++)
		outfile << i << (i == 9 ? "": ",");
	outfile << endl;
	for (int j = 4; j <= 8; j++) {
		_ftime64_s(&stime);
		//��ȡ�㷨ִ��ǰ��ϵͳʱ��
		Perm(a, 0, j);
		_ftime64_s(&etime);                   //��ȡ�㷨ִ�к��ϵͳʱ��
		rstime = etime.time - stime.time;               //����ʱ���
		rmtime = rstime * 1000 + (etime.millitm - stime.millitm);
		outfile << rmtime << (j == 8 ? "" : ",");
	}
	outfile.close();

	return 0;
}

void Perm(int* list, int k, int m)
{

	int i;
	if (k == m) {
		for (i = 0; i <= m; i++)
			printf("%d ", list[i]);
		printf("\n");

	}
	else {
		for (i = k; i <= m; i++) {
			Swap(list[k], list[i]);
			Perm(list, k + 1, m);
			Swap(list[k], list[i]);
		}
	}
	return;
}

void Swap(int& i, int& j)
{
	int temp;
	temp = i;
	i = j;
	j = temp;
	return;
}
