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
const ll N =4e5+1;
ll n,m,o=1;
vector<ll>v,tr,lazy,g[N],st,en;
void dfs(ll v,ll p,ll &tm)
{
    st[v]=++tm;
    for(auto c:g[v])
    {
        if(c==p){continue;}
        dfs(c,v,tm);
    }
    en[v]=tm;
}
void push_down(ll node, ll low, ll high)
{
    if(lazy[node])
    {
        tr[node]=lazy[node];
        if(low!=high)
        {
            lazy[2*node]=lazy[node];
            lazy[2*node+1]=lazy[node];
        }
        lazy[node]=0;
    }
}
void build(ll node, ll low, ll high)
{
    if(low==high)
    {
        tr[node]|=(o<<v[low]);
        return;
    }
    ll mid= (low+high)>>1;
    build(2*node,low,mid);
    build(2*node+1,mid+1,high);
    tr[node]=(tr[2*node] | tr[2*node+1]);
}
void update(ll node, ll low, ll high, ll x, ll y, ll val)
{
    push_down(node,low,high);
    if(high<x || low>y){return;}
    if(x<=low && high<=y)
    {
        lazy[node]=(o<<val);
        push_down(node,low,high);
        return;
    }
    ll mid=(low+high)>>1;
    update(2*node,low,mid,x,y,val);
    update(2*node+1,mid+1,high,x,y,val);
    tr[node]=(tr[2*node] | tr[2*node+1]);
}
ll query(ll node, ll low, ll high, ll x, ll y)
{
    push_down(node,low,high);
    if(high<x || low>y){return 0;}
    if(x<=low && high<=y){return tr[node];}

    ll mid=(low+high)>>1;

    return query(2*node,low,mid,x,y) | query(2*node+1,mid+1,high,x,y);
}
int32_t main()
{
    fast
    ll i,j=1,k=1,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        ll tm=0;
        cin>>n>>q;
        vector<ll>temp(n+1);
        v.resize(n+1);
        st.resize(n+1);
        en.resize(n+1);
        tr.resize(4*n+1);
        lazy.resize(4*n+1);
        for(i=1;i<=n;i++){cin>>temp[i];}
        m=n-1;
        while(m--)
        {
            ll x,y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs(1,0,tm);
        for(i=1;i<=n;i++){v[st[i]]=temp[i];}
        build(1,1,n);
        while(q--)
        {
            ll x,y;
            cin>>x;x--;
            if(x)
            {
                cin>>x;
                cout<<__builtin_popcountll(query(1,1,n,st[x],en[x]))<<endl;
                //cout<<st[x]<<" st/en "<<en[x]<<endl;
                //debug(tr);
            }
            else
            {
                cin>>x>>y;
                update(1,1,n,st[x],en[x],y);
            }
        }
    }
}
/***
Codeforces: New Year Tree
Topic Name: Eular Tour.
Found from: Ultimate Topic List by Shahjalal Shohag.

Leaning Outcome:
1) Use a push down function for lazy propagation.
2) In eular tour, it's must to reorder elements according to starting time.
3) In lazy propagation:- in every function, Relax the lazy first. Then do whatever you wanna do.
***/
