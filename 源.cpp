#include<bits/stdc++.h> 
using namespace std;
int ans[1001];
int t,n,x,flag,a[1001];

void find(int x,int tot)
{
	if(x<0) return;
	else
	if(x==0)
	{
		cout<<ans[1];
		for(int i=2;i<=tot;i++) cout<<"+"<<ans[i];
		cout<<endl;
		flag=1;
		return;
	}
	else
	{
		for(int i=ans[tot];i>=1;i--)
		{
			if(a[i])
			{
				a[i]--;ans[tot+1]=i;
				find(x-i,tot+1); 
				a[i]++;
			}
		}
	}
}

int main()
{
	while(scanf("%d%d",&t,&n)==2)
	{
	flag=0;
	memset(a,0,sizeof(a));
	memset(ans,0,sizeof(ans));
	ans[0]=t;
	for(int i=0;i<n;i++)
	{
		cin>>x;a[x]++;
	}
	find(t,0);
	if(flag==0) cout<<"NONE";
	}
	return 0;
}
