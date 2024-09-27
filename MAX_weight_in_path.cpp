#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> random(1, 1000000);
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 1e16
const ll M =1e9+7;
const ll N =2e5+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=0;
ll LOG=20;
vector<ll>st(N),en(N),g[N],par(N),sz(N,1);
ll Find(ll x)
{
    if(par[x]==x){return x;}
    return par[x]=Find(par[x]);
}
void mrg(ll x, ll y)
{
    x=Find(x);
    y=Find(y);
    if(x==y){return;}
    if(sz[x]<sz[y]){swap(x,y);}
    sz[x]+=sz[y];
    par[y]=x;
}
map<pair<ll,ll>,ll>weight;
vector<vector<ll>>parent(20,vector<ll>(N,1)),dist(20,vector<ll>(N));
void dfs(ll v,ll p)
{
    st[v]=timer++;
    parent[0][v]=p;
    ll x=v,y=p;
    if(x>y){swap(x,y);}
    dist[0][v]=weight[{x,y}];

    for(int i=1;i<20;i++)
    {
        parent[i][v]=parent[i-1][parent[i-1][v]];
        dist[i][v]=max(dist[i-1][v],dist[i-1][parent[i-1][v]]);
    }
    for(auto c:g[v])
    {
        if(p==c){continue;}
        dfs(c,v);
    }en[v]=timer;
}
bool ancestor(ll u, ll v){return (st[u]<=st[v] && en[v]<=en[u]);}
ll lca(ll u, ll v)
{
    if(ancestor(u,v)){return u;}
    if(ancestor(v,u)){return v;}
    for(int i=19;i>=0;i--)
    {
        if(!ancestor(parent[i][u],v)){u=parent[i][u];}
    }return parent[0][u];
}

ll maximum(ll x, ll v)
{
    if(v==x){return 0;}
    ll ans=INT_MIN,i;
    for(i=19;i>=0;i--)
    {
        if(ancestor(x,parent[i][v]))
        {
            ans=max(ans,dist[i][v]);
            v=parent[i][v];
        }
    }
    return ans;
}
int32_t main()
{
    fast
    ll i,j=1,k=1,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>m;
        priority_queue<array<ll,3>,vector<array<ll,3>>,greater<array<ll,3>>>pq;
        vector<array<ll,3>>ques;
        for(i=1;i<=m;i++)
        {
            if(i<=n){par[i]=i;}
            ll x,y,z;
            cin>>x>>y>>z;
            if(x>y){swap(x,y);}
            ques.pb({x,y,z});
            weight[{x,y}]=z;
            pq.push({z,x,y});
        }
        ll min_tree=0;
        vector<array<ll,3>>tr;
        map<pair<ll,ll>,ll>ans;
        while(pq.size())
        {
            auto [z,x,y]=pq.top();
            pq.pop();
            ll a=Find(x);
            ll b=Find(y);
            if(a==b){continue;}
            min_tree+=z;
            tr.pb({x,y,z});
            mrg(a,b);
            g[x].pb(y);
            g[y].pb(x);
        }
        for(auto [x,y,z]:tr){ans[{x,y}]=min_tree;}
        dfs(1,1);
        for(auto [x,y,z]:ques)
        {
            if(ans[{x,y}]){cout<<min_tree<<endl;continue;}
            k=lca(x,y);
            cout<<min_tree-max(maximum(k,x),maximum(k,y))+z<<endl;

        }
    }
}



//https://codeforces.com/contest/609/problem/E
/*

In this problem, I used Binary Lifting to find the maximum weighted edge between the path of two nodes.

Logic:
1. Build a sparse table to store the weight of each edge (see the maximum function).
2. Find the LCA (Lowest Common Ancestor) of the two nodes.
3. For each node, find the maximum weighted edge from each of them to their LCA.
*/
