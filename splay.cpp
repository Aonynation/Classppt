#include <bits/stdc++.h>
using namespace std;

const int N=100005;
const int oo=1000000000;

struct Node
{int pos;//λ�� 
 int val;//�߶� 
}a[N];
int n,root;
int ch[N][2],f[N],sz[N],rev[N];

inline int read()
{int x=0,f=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
 return x*f;
}

bool cmp(Node a,Node b)
{if (a.val==b.val)
   return a.pos<b.pos;
 else
   return a.val<b.val;
}

int get(int x)//�ж�x�Ƿ��Ǹ��׽����Ҷ���
{
 return ch[f[x]][1]==x;
}

void pushup(int x)//����ϴ� 
{
 sz[x]=sz[ch[x][1]]+sz[ch[x][0]]+1;
}

void pushdown(int x)//����´� 
{if (rev[x])
   {if(ch[x][0]) rev[ch[x][0]]^=1;
    if(ch[x][1]) rev[ch[x][1]]^=1;
    swap(ch[x][0],ch[x][1]);
    rev[x]=0;
   }
}

void rotate(int x) //��ת
{int y=f[x],z=f[y]; //yΪx�ĸ��׽ڵ�,zΪx�����Ƚڵ�
 int kind=get(x); //���x��y�Ķ�������,����ӷ���0,���򷵻�1
 pushdown(y); pushdown(x);//����´�
 ch[y][kind]=ch[x][kind^1];  //ѡx�Ĳ���y->xͬ��Ķ��Ӹ�y,��֤BST
 ch[x][kind^1]=y; //yΪx�Ĳ���y->xͬ��Ķ���
 f[ch[y][kind]]=y; f[y]=x;f[x]=z; //�������Եĸ��׽ڵ�
 if (z) ch[z][ch[z][1]==y]=x; //����x��Ϊz->y��һ��Ķ���
 pushup(y); pushup(x); //����ϴ�
}

void splay(int x,int anc) //ͨ��һϵ����ת��x����Ϊ���anc���ӽ�� 
{for (int fa;(fa=f[x])!=anc;rotate(x))
   {pushdown(f[fa]); //�游������´�
    pushdown(fa); //���׽�����´�
    if (f[fa]!=anc) (get(x)==get(fa)) ? rotate(fa) : rotate(x);
    //�游����븸�׽����ͬһ��,Ӧ�ȵ������׽��,���Ч��
   }
 if (!anc) root=x;
}

void build(int l,int r,int fa)//��splay 
{if (l>r) return;
 int mid=l+r>>1;
 if (mid<fa) ch[fa][0]=mid;
 else ch[fa][1]=mid;
 sz[mid]=1;
 f[mid]=fa;
 if(l==r) return;
 build(l,mid-1,mid);
 build(mid+1,r,mid);
 pushup(mid);
}

int findkth(int k)//���ҵ�k��Ԫ��
{int now=root;
 while(1)
   {if (rev[now]) pushdown(now);
    if (k<=sz[ch[now][0]] && ch[now][0])
      now=ch[now][0];
    else
      {k-=sz[ch[now][0]]+1;
       if (k==0) return now;
       else now=ch[now][1];
      }
   }
}

void init()
{n=read();
 a[1].pos=1,a[1].val=-oo;
 a[n+2].pos=n+2,a[n+2].val=oo;//ͷβ�������ڱ�,��ֹԽ�� 
 for(int i=2;i<=n+1;i++)
   {a[i].val=read();
    a[i].pos=i;
   }
 sort(a+1,a+n+3,cmp);//��Ȩֵ�����С����,Ȩֵ��ͬ��λ�ô�С�������� 
}

void rever(int L,int R)//������[L,R]��ת 
{int x=findkth(L-1),y=findkth(R+1);
 splay(x,0);
 splay(y,x);
 rev[ch[y][0]]^=1;
}

void work()
{build(1,n+2,0);
 root=n+3>>1;
 for(int i=2;i<=n+1;i++)
   {splay(a[i].pos,0);
    int ans=sz[ch[root][0]]+1;
    printf("%d ",ans-1);//��1����Ϊǰ����һ���ڱ�,���������һλ 
    rever(i,ans);//����[i,ans]��ת
   }
}

int main()
{
 init();
 work();
 return 0;  
}
