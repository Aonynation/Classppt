//By YinYueRan 
#include<cstdio>
const int N=300002;
struct LCT{
    int val[N],fa[N],ch[N][2],rev[N],s[N],st[N],top;
    bool nroot(int x){
        return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
    }
    int Get(int x){
        return ch[fa[x]][1]==x;
    }
    void swap(int &x,int &y){
        int t=x;x=y;y=t;
    }
    void Pushup(int x){
        s[x]=val[x]^s[ch[x][0]]^s[ch[x][1]];
    }
    void Change(int x){
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    void Pushdown(int x){
        if(rev[x]){
            Change(ch[x][0]);
            Change(ch[x][1]);
            rev[x]=0;
        }
    }
    void Rotate(int x){
        int y=fa[x],z=fa[y],w=Get(x);
        fa[ch[y][w]=ch[x][w^1]]=y;
        if(nroot(y))
            ch[z][Get(y)]=x;
        fa[x]=z;
        fa[ch[x][w^1]=y]=x;
        Pushup(y);
    }
    void Splay(int x){
        int y=x;
        st[top=1]=y;
        while(nroot(y))
            st[++top]=y=fa[y];
        while(top)
            Pushdown(st[top--]);
        while(nroot(x)){
            y=fa[x];
            if(nroot(y))
                Rotate(Get(x)==Get(y)?y:x);
            Rotate(x);
        }
        Pushup(x);
    }
    void Access(int x){
        for(int y=0;x;x=fa[y=x])
            Splay(x),ch[x][1]=y,Pushup(x);
    }
    void Makeroot(int x){
        Access(x);
        Splay(x);
        Change(x);
    }
    int Findroot(int x){
        Access(x);
        Splay(x);
        while(ch[x][0])
            Pushdown(x),x=ch[x][0];
        Splay(x);
        return x;
    }
    void Split(int x,int y){
        Makeroot(x);
        Access(y);
        Splay(y);
    }
    void Link(int x,int y){
        Makeroot(x);
        if(Findroot(y)!=x)
            fa[x]=y;
    }
    void Cut(int x,int y){
        Makeroot(x);
        if(Findroot(y)==x&&fa[y]==x&&!ch[y][0]){
            ch[x][1]=fa[y]=0;
            Pushup(x);
        }
    }
}T;

inline int read()
{int x=0,f=1;char ch=getchar();
 while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
 while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
 return x*f;
}

int n,m,i,op,x,y;
int main()
{
    n=read();m=read();
    for(i=1;i<=n;i++)
        T.val[i]=read();
    while(m--){
        op=read();x=read();y=read();
        if(op==0)T.Split(x,y),printf("%d\n",T.s[y]);
        if(op==1)T.Link(x,y);
        if(op==2)T.Cut(x,y);
        if(op==3)T.Splay(x),T.val[x]=y;
    }
}
