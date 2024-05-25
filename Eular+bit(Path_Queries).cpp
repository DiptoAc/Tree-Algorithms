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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
const ll M =1e9+7;
const ll N =3e5+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=0;
vector<ll>g[N],st(N),en(N),path={0},vec;
void dfs(ll v=1, ll p=0)
{
    path.pb(v);
    st[v]=path.size();
    //st[v]=++timer;
    for(auto c:g[v])
    {
        if(c==p){continue;}
        dfs(c,v);
    }
    path.pb(v);
    en[v]=path.size();
    //en[v]=++timer;
}
struct BIT
{
    ll sz;
    vector<ll>bit;
    BIT(ll sz)
    {
        this->sz=sz;
        bit.resize(sz);
    }
    BIT(vector<ll>v):BIT(v.size())
    {
        for(int i=1;i<v.size();i++)
        {
            add(i,v[i]);
        }
    }
    void add(ll idx, ll val)
    {
        while(idx<sz)
        {
            bit[idx]+=val;
            idx+=idx&-idx;
        }
    }
    ll sum(ll idx)
    {
        ll ans=0;
        while(idx>0)
        {
            ans+=bit[idx];
            idx-=idx&-idx;
        }return ans;
    }
};
int32_t main()
{
    fast
    ll i,j=1,k=1,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>q;
        vector<ll>weight(n);
        for(auto &it:weight){cin>>it;}
        m=n-1;
        while(m--)
        {
            ll x,y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs();
        //debug(path);
        vec.resize(path.size());
        for(i=0;i<n;i++)
        {
            vec[st[i+1]]=weight[i];
            vec[en[i+1]]=-weight[i];
        }
        //debug(vec);
        BIT bt(vec);
        while(q--)
        {
            ll x,y,z;
            cin>>x>>y;
            if(--x)
            {
                cout<<bt.sum(st[y])<<endl;
            }
            else
            {
                cin>>z;
                bt.add(st[y],-weight[y-1]+z);
                bt.add(en[y],weight[y-1]-z);
                weight[y-1]=z;
            }
        }
    }
}
/***
CSES: Path Queries
Eular tour + Bit
***/
