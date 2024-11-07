#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
//uniform_int_distribution<int> dist(1, 1000000);
#define ll long long 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 2e9
const ll M=1e9+7;
const ll N=1e4+1;
const ll LOG=15;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=0,chainNo=0,pos=0;
vector<vector<ll>>parent(LOG,vector<ll>(N));
vector<ll>st(N),en(N),seg_t(2*N),chainHead(N),topOfChain(N),baseArr(N),id(N),sz(N,1);
vector<pair<ll,ll>>g[10001];
vector<array<ll,33>>arr;

void build() // 1 index based segment tree.
{
    for(int i=1;i<=n;i++){seg_t[i+n]=baseArr[i];}
    for(int i=n;i>=1;i--)
    {
        seg_t[i]=max(seg_t[(i<<1)],seg_t[(i<<1)+1]);
    }
}

void update(ll pos, ll val)
{
    seg_t[pos+n]=baseArr[pos]=val;

    for(int i=((pos+n)>>1);i>1;i>>=1)
    {
        seg_t[i]=max(seg_t[(i<<1)],seg_t[(i<<1)+1]);
    }

}
ll query(ll L, ll R)
{
    ll ans=0;
    L+=n;
    R+=n;
    while(L<=R)
    {
        if(L&1) //Suppose L is 11. 11/2 = 5 contains value of 10 and 11. But, 10 is not in range. Therefore ++;
        {
            ans=max(seg_t[L++],ans);
        }
        if(!(R&1)) //Suppose R is 20. 20/2 = 10 contains value of 20 and 21. But, 21 is out of range. There --;
        {
            ans=max(seg_t[R--],ans);
        }
        L>>=1;
        R>>=1;
    }
    return ans;
}

bool is_ancestor(ll par, ll chi)
{
    return st[par]<=st[chi] && en[chi]<=en[par];
}
ll lca(ll x, ll y)
{
    if(is_ancestor(x,y)){return x;}
    if(is_ancestor(y,x)){return y;}
    for(int i=LOG-1;i>=0;i--)
    {
        int now=parent[i][x];
        if(is_ancestor(now,y)){continue;}
        x=now;
    }
    return parent[0][x];
}

//This dfs finds (1)starting and ending time. (2) Parent's of nodes. (3)Size of each subtree.
void dfs(ll cur, ll par)
{
    st[cur]=++timer;
    parent[0][cur]=par;
    for(auto [chi,d]:g[cur])
    {
        if(chi==par){continue;}
        dfs(chi, cur);
        sz[cur]+=sz[chi];
    }
    en[cur]=++timer;
}
// This function assigns 2^n th parent.
void initialize()
{
    for(int i=1;i<LOG;i++)
    {
        for(int j=1;j<=n;j++)
        {
            parent[i][j]=parent[i-1][parent[i-1][j]];
        }
    }
}

void heavy_light(ll cur, ll par, ll cst)
{
    if(!chainHead[chainNo]) //Starting of new chain. So, cur is a head(top element of this chain)
    {
        chainHead[chainNo]=cur;
    }
    topOfChain[cur]=chainHead[chainNo]; //Cur element টা যেই চেইনে আছে। সেই চেইনের টপ এলিমেন্ট topOfChain এ আছে।
    id[cur]=++pos;
    baseArr[id[cur]]=cst;

    ll hvy_nd=0,mx=0,hvy_cst=0;
    for(auto [chi,cost]:g[cur])
    {
        if(chi==par){continue;}
        if(sz[chi]>mx)
        {
            hvy_nd=chi;
            mx=sz[chi];
            hvy_cst=cost;
        }
    }
    if(hvy_nd==0){return;} //Means this is the leaf node

    heavy_light(hvy_nd,cur,hvy_cst); //Continue building chain. Therefore chainNo doesn't change.

    for(auto [chi,cost]:g[cur])
    {
        if(chi==par || chi==hvy_nd){continue;}
        chainNo++; // Before starting a new chain. Increase the chainNo.
        heavy_light(chi,cur,cost);
    }
}

ll path_max(ll par, ll chi)
{
    ll ans=0;
    while(chi!=par)
    {
        if(par==topOfChain[chi]) //Parent is the top element of current chain.
        {
            ans=max(ans,query(id[par]+1,id[chi]));
            break;
        }
        if(is_ancestor(par,topOfChain[chi])) //Parent is not in chain.
        {
            ans=max(ans,query(id[topOfChain[chi]],id[chi]));
            chi=parent[0][topOfChain[chi]];
        }
        else //Parent is a part of chain. But parent is not the top element of chain.
        {
            ans=max(ans,query(id[par]+1,id[chi]));
            break;
        }
    }return ans;
}
void clean() //Clean everything for next test case.
{
    arr.clear();
    for(int i=0;i<=n;i++)
    {
        g[i].clear();
        baseArr[i]=id[i]=st[i]=en[i]=timer=pos=chainNo=chainHead[i]=seg_t[i]=0;
        sz[i]=1;
    }
    for(int i=n+1;i<=2*n;i++)
    {
        seg_t[i]=0;
    }
}

int32_t main()
{
    fast
    ll i,j,k,q,tc=1,cs=0;cin>>tc;
    while(tc--)
    {
        cin.ignore();
        cin>>n;
        arr.pb({0,0,0});
        for(i=1;i<n;i++)
        {
            ll x, y, d;
            cin>>x>>y>>d;
            g[x].pb({y,d});
            g[y].pb({x,d});
            arr.pb({x,y,d});
        }
        dfs(1,1);initialize();heavy_light(1,1,0);
        build();
        string str;
        while(cin>>str)
        {
            if(str=="DONE"){break;}
            else if(str=="QUERY")
            {
                ll x,y,a;
                cin>>x>>y;
                a=lca(x,y);
                x=path_max(a,x);
                y=path_max(a,y);
                cout<<max(x,y)<<endl;
            }
            else
            {
                ll x,y,index,val;
                cin>>index>>val;
                x=arr[index][0];
                y=arr[index][1];
                arr[index][2]=val;
                if(parent[0][y]!=x){swap(x,y);}
                update(id[y],val);
            }
        }
        clean();
    }
}
/*
Topic name. Heavy_Light_Decomposition
Promble name: QTREE (SPOJ)
*/
