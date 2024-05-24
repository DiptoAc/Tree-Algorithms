#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl;
#define endl '\n'
#define LLONG_MAX 1e16
const ll M =1e9+7;
const ll N =1e6+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=0;
ll LOG=20;
vector<ll>st(N),en(N),g[N];
vector<vector<ll>>parent(20,vector<ll>(N,1));
void dfs(ll v,ll p)
{
     st[v]=timer++;
     parent[0][v]=p;
     for(int i=1;i<20;i++){parent[i][v]=parent[i-1][parent[i-1][v]];}
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
int32_t main()
{
    fast
    ll i,j=1,k=1,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>q;
        for(i=2;i<=n;i++)
        {
            cin>>k;
            g[k].pb(i);
        }
        dfs(1,1);
        while(q--)
        {
            ll x,y;
            cin>>x>>y;
            cout<<lca(x,y)<<endl;
        }
    }
}
/***
LCA using binary lifting

Company Queries 2
***/
