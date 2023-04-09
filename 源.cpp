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
	struct _timeb stime, etime;           //存储算法运行的开始时间和结束时间
	long int rmtime, rstime;              //计算对应的秒和毫秒数
	ofstream outfile;
	string readfilename;
	cout << "请输入将要打开的文件名：";
	cin >> readfilename;
	outfile.open(readfilename, ios::out);
	if (!outfile)
	{
		cout << "文件打开失败" << endl;
		exit(0);
	}

	for (int i = 5; i <= 9; i++)
		outfile << i << (i == 9 ? "": ",");
	outfile << endl;
	for (int j = 4; j <= 8; j++) {
		_ftime64_s(&stime);
		//获取算法执行前的系统时间
		Perm(a, 0, j);
		_ftime64_s(&etime);                   //获取算法执行后的系统时间
		rstime = etime.time - stime.time;               //计算时间差
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
