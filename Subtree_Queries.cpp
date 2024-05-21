#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T>
using oset = tree<T, null_type, less<T>,rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long
#define int long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl;
#define endl '\n'
#define LLONG_MAX 1e16
const ll M =1e9+7;
const ll N =2e5+5;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m;
vector<ll>g[N],st,en,val;
void dfs(ll v,ll p,ll &tm) //This dfs function will set start and end time for every node.(All child will be among st-en)
{
    st[v]=++tm;
    for(auto c:g[v])
    {
        if(c==p){continue;}
        dfs(c,v,tm);
    }en[v]=tm;
}
struct BIT//Fenwick tree for finding time.
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
        for(int i=1;i<sz;i++)
        {
            add(v[i],i);
        }
    }
    void add(ll val, ll idx)
    {
        while(idx<sz)
        {
            bit[idx]+=val;
            idx+=(idx&-idx);
        }
    }
    ll sum(ll idx)
    {
        ll ans=0;
        while(idx>0)
        {
            ans+=bit[idx];
            idx-=(idx&-idx);
        }
        return ans;
    }
    ll sum(ll x,ll y)
    {
        return sum(y)-sum(x-1);
    }
};
int32_t main()
{
    fast
    ll i,j,k,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        ll tm=0;
        cin>>n>>q;
        st.resize(n+1);
        en.resize(n+1);
        val.resize(n+1);
        vector<ll>temp(n+1);
        for(i=1;i<=n;i++){cin>>temp[i];}
        for(i=1;i<n;i++)
        {
            ll x,y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs(1,0,tm);
        for(i=1;i<=n;i++)
        {
            val[st[i]]=temp[i];
        }
        BIT bit(val);
        while(q--)
        {
            ll x,y,z;
            cin>>x>>y;
            x--;
            if(x)
            {
                cout<<bit.sum(st[y],en[y])<<endl;;
            }
            else
            {
                cin>>z;
                bit.add(z-val[st[y]],st[y]);
                val[st[y]]=z;
            }
        }
    }
}
/***
This is a problem on Eular Tour or tree flatning.

https://cses.fi/problemset/task/1137/
***/
