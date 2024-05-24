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
const ll N =2e5+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=1;
vector<ll>g[N],depth,path={0},st,path_depth,tr;
void dfs(ll v=1,ll p=1)
{

    st[v]=timer++;
    path.pb(v);
    depth[v]=depth[p]+1;
    for(auto c:g[v])
    {
        if(c==p){continue;}
        dfs(c,v);
        path.pb(v);
        timer++;
    }
}
void build(ll node=1, ll low=1, ll high=path.size()-1)
{
    if(low==high)
    {
        tr[node]=path_depth[low];
        return;
    }
    ll mid=(low+high)>>1;
    build(2*node,low,mid);
    build(2*node+1,mid+1,high);
    tr[node]=min(tr[2*node],tr[2*node+1]);
}

ll query(ll node,ll low, ll high, ll x, ll y)
{
    if(y<low || x>high){return M;}
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
        st.resize(n+1);
        depth.resize(n+1);
        m=n-1;
        while(m--)
        {
            ll x,y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs();
        path_depth.resize(path.size());
        for(i=0;i<2*n;i++){path_depth[i]=depth[path[i]];}
        tr.resize(4*path.size());
        build();
        while(q--)
        {
            ll x,y;
            cin>>x>>y;
            ll a,b;
            a=st[x];
            b=st[y];
            if(a>b){swap(a,b);}
            ll ans=query(1,1,path.size()-1,a,b);
            cout<<depth[x]+depth[y]-2*ans<<endl;
        }
    }
}
/***
https://cses.fi/problemset/task/1135
Problem name: Distance Queries
Topic name: Eular Tour

Logic: Find LCA, find the depth of x,y and LCA(x,y);
Now ans= depth[x]+depth[y]-2*depth[lca];
***/
