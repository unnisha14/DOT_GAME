#include<bits/stdc++.h>
using namespace std;

class dots{
	int n,A,B;
	int **arr,**comb;
	public:
		dots()
		{
			A=B=0;
			cout<<"\nEnter the maximum grid matrix you want to play :- ";
			cin>>n;
			
			cout<<"\nNodes";
			int x=0;			
			for (int i=0;i<n;i++)
			{
				cout<<"\n";
				for (int j=0;j<n;j++)
				{
					cout<<++x<<"\t";
				}
			}
			
			arr = new int*[n*n+1];
			for (int i=0;i<=n*n;i++)
				arr[i] = new int[4];
			
			comb = new int*[(n-1)*(n-1)];
			for (int i=0;i<(n-1)*(n-1);i++)
				comb[i] = new int[4];
			
			for (int i=0;i<=n*n;i++)
				for (int j=0;j<4;j++)
					arr[i][j] = 0;
					
			for (int i=0;i<(n-1)*(n-1);i++)
				for (int j=0;j<4;j++)
					comb[i][j] = 0;
		}
		
		void input();
		void put_in_combo(int,int,int,int);
		int combination(int,int,int,int);
		int detect_loop(int,int);
		void result();
};

void dots::input()
{
	int x,y,i,d=0;
	i=1;
	cout<<"\nEnter 2 nodes at a time that is to be connected\n";
	while (comb[(n-1)*(n-1)-1][3]==0)
	{
		if (i!=d)
		{
			if (i==1)
				cout<<"\nPlayer 1 = ";
			else
				cout<<"\nPlayer 2 = ";	
		}
		d=i;
		cin>>x>>y;
		int j=0;
		while (j<4 && arr[x][j]!=0)
			j++;
		arr[x][j] = y;
		j=0;
		while (j<4 && arr[y][j]!=0)
			j++;
		arr[y][j] = x;
		
		//for (int k=0;k<4;k++)
			//cout<<"\n"<<arr[x][k]<<" "<<arr[y][k];
		
		int z = detect_loop(x,y);
		//cout<<"\nz = "<<z<<" i = "<<i;
		if (z>0)
		{
			if (i==1)
				A+=z;
			else
				B+=z;
		}
		else
		{
			if (i==1)
				i=0;
			else
				i=1;
		}
		//result();
	}
}

void dots::put_in_combo(int a,int b,int c,int d)
{
	int i=0;
	while (comb[i][0]!=0 && i<(n-1)*(n-1))
		i++;
	if (i<(n-1)*(n-1))
	{
		comb[i][0]=a;
		comb[i][1]=b;
		comb[i][2]=c;
		comb[i][3]=d;
	}
}

int dots::combination(int a,int b,int c,int d)
{
	int j=0,p[4],i=0,q[4],m=4;
	q[0]=a;q[1]=b;q[2]=c;q[3]=d;
	sort(q,q+m);
	while (comb[i][0]!=0 && i<(n-1)*(n-1))
	{
		for (j=0;j<4;j++)
			p[0]=comb[i][j];
		
		sort(p,p+m);
		for (j=0;j<4;j++)
			if (p[j]!=q[j])
				break;
		
		if (j!=4)
			i++;
		else
			break;
	}
	if (j==4)
		return 0;
	else
		return 1;
}

int dots::detect_loop(int x,int y)
{
	int count=0,i=0;
	int a[4],v[4];
	for (int k=0;k<4;k++)
		v[k]=-1;
	a[0] = x;a[1] = y;
	
	while (i<4 && arr[y][i]!=0)
	{
		if (arr[y][i]!=x)
		{
			v[count] = arr[y][i];
			count++;	
		}
		i++;
	}
	//cout<<"\nv x y";
	//for (int k=0;k<4;k++)
		//cout<<"\n"<<v[k]<<" "<<arr[x][k]<<" "<<arr[y][k];
	count = 0;
	i = 0;
	
	//cout<<"\nx = "<<x<<" y = "<<y;
	while (i<4 && arr[x][i]!=y)
	{
		int t=0,p=-1;
		//cout<<"\np = "<<p;
		//cout<<"\narr[x][i] = "<<arr[x][i];
		while (t<4 && arr[arr[x][i]][t]!=0)
		{
			//cout<<"\narr[arr[x][i]][t] = "<<arr[arr[x][i]][t]<<" i = "<<i<<" t = "<<t;
			if (arr[arr[x][i]][t] == v[0])
				p=0;
			else if(arr[arr[x][i]][t] == v[1])
				p=1;
			else if(arr[arr[x][i]][t] == v[2])
				p=2;
			else if(arr[arr[x][i]][t] == v[3])
				p=3;
			t++;
			if (p!=-1)
				break;
		}
		//cout<<"\np = "<<p;
		if (p!=-1 && combination(x,y,v[p],arr[x][i])!=0)
		{
			put_in_combo(x,y,v[p],arr[x][i]);
			count++;
		}
		i++;
	}
	return count;
}

void dots::result()
{
	if (A>B)
		cout<<"\nPlayer 1 won";
	else
		cout<<"\nPlayer 2 won";
	cout<<"\nScore\nPlayer 1 = "<<A<<"\tPlayer 2 = "<<B;
}

int main()
{
	dots d;
	d.input();
	d.result();
	
	return 0;
}
