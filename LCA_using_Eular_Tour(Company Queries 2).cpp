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
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
const ll M =1e9+7;
const ll N =2e5+1;
ll n,m,o=1;
vector<ll>g[N],depth(N),path,st(N,-1),en(N),path_depth;
vector<pair<ll,ll>>v,tr;
void dfs(ll v,ll p)
{
    st[v]=path.size();
    path.pb(v);
    depth[v]=depth[p]+1;
    for(auto c:g[v])
    {
        if(c==p){continue;}
        dfs(c,v);
        en[v]=path.size();
        path.pb(v);
    }
}
pair<ll,ll>mx={LLONG_MAX,LLONG_MAX};
void build(ll node, ll low, ll high)
{
    if(low==high)
    {
        tr[node]=v[low];
        return;
    }
    ll mid=(low+high)>>1;

    build(2*node,low,mid);;
    build(2*node+1,mid+1,high);

    tr[node]=min(tr[2*node],tr[2*node+1]);
}

pair<ll,ll>query(ll node, ll low, ll high, ll x, ll y)
{
    if(low>y || high<x){return mx;}
    if(x<=low && high<=y){return tr[node];}

    ll mid=(low+high)>>1;

    return min(query(2*node,low,mid,x,y),query(2*node+1,mid+1,high,x,y));
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
        path.pb(1);
        dfs(1,1);
        path_depth.resize(path.size());
        for(i=0;i<path.size();i++)
        {
            path_depth[i]=depth[path[i]];
            v.pb({path_depth[i],path[i]});
        }
        tr.resize(4*v.size());
        //debug(path);debug(path_depth);
        k=path.size()-1;
        build(1,1,k);
        while(q--)
        {
            ll x,y;
            cin>>x>>y;
            x=st[x];
            y=st[y];
            if(x>y){swap(x,y);}
            cout<<query(1,1,k,x,y).second<<endl;
        }

    }
}
/***
CSES: Company Queries 2
https://cses.fi/problemset/task/1688/
LCA Using Eular tour.

Logic:- The node with the lowest depth between the 2 queried node is the LCA.

Step 1: Flatten the tree.
Step 2: Build segment tree of sparse table to find the node with min depth in range.
Step 3: Print min depth node of that range.
***/
