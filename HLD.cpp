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
#define ll int
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define ok cout<<"ok"<<endl<<flush;
#define endl '\n'
#define INF 2e9
const ll M=1e9+7;
const ll N=2e5+1;
const ll LOG=18;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,timer=0,lcaTimer=0;
vector<ll>g[N],sz(N,1);
ll v[N],id[N],depth[N],st[N],en[N],tp[N],arr[N],loop_tr[2*N];
ll p[LOG][N]; //This is the sparse table that stores parents.
void loop_build()
{
    ll i;
    for(i=1;i<=n;i++)
    {
        loop_tr[n+i]=arr[i];
    }
    for(i=n;i>1;i--)
    {
        loop_tr[i]=max(loop_tr[2*i],loop_tr[2*i+1]);
    }
}

void loop_update(ll idx, ll val)
{
    loop_tr[idx+n]=val;
    arr[idx]=val;
    for(ll i=(n+idx)/2;i>1;i/=2)
    {
        loop_tr[i]=max(loop_tr[2*i],loop_tr[2*i+1]);
    }

}
ll loop_query(ll L, ll R)
{
    ll ans=0;
    L+=n;
    R+=n;
    while(L<=R)
    {
        if(L%2==1)
        {
            ans=max(ans,loop_tr[L++]);
        }
        if(R%2==0)
        {
            ans=max(ans,loop_tr[R--]);
        }
        L>>=1;
        R>>=1;
    }return ans;
}

void dfs(ll cur ,ll par) //This dfs sets start time, end time , depth and parents.
{
    st[cur]=++lcaTimer;
    depth[cur]=depth[par]+1;
    p[0][cur]=par;
    for(auto child:g[cur])
    {
        if(child==par){continue;}
        dfs(child,cur);
        sz[cur]+=sz[child];
    }
    en[cur]=++lcaTimer;
}
bool is_ancestor(ll par, ll chi)  //Is ancestor function to find lca
{
    return (st[par]<=st[chi] && en[chi]<=en[par]);
}
ll lca(ll a, ll b)  //Lca using eular tour
{
    if(is_ancestor(a,b)){return a;}
    if(is_ancestor(b,a)){return b;}
    for(ll i=LOG-1;i>=0;i--)
    {
        ll temp=p[i][a];
        if(!is_ancestor(temp,b))
        {
            a=temp;
        }
    }
    return p[0][a];
}

void dfs_hld(ll cur, ll par, ll top)  //Sets the top element of every heavy segment. Always starts dfs from heavy element. Therefore all elements of single element stays in a line.
{
    id[cur]=++timer;
    tp[cur]=top;
    arr[id[cur]]=v[cur];

    ll h_chi=0, mx_sz=0;
    for(auto chi:g[cur])
    {
        if(chi==par){continue;}
        if(mx_sz<sz[chi])
        {
            mx_sz=sz[chi];
            h_chi=chi;
        }
    }

    if(h_chi == 0){return;}
    dfs_hld(h_chi,cur,top);
    for(auto chi:g[cur])
    {
        if(chi==par || chi==h_chi){continue;}
        dfs_hld(chi,cur,chi);
    }
}

ll path_max(ll par, ll chi)
{
    ll mx=0;
    while(chi!=par)
    {
        if(chi==tp[chi])//If the node is single, return it's value.
        {
            mx=max(mx,v[chi]);
            chi=p[0][chi];
        }
        else if(depth[tp[chi]]>depth[par])//
        {
            //mx=max(query(id[tp[chi]],id[chi]),mx);
            mx=max(loop_query(id[tp[chi]],id[chi]),mx);
            chi=p[0][tp[chi]];
        }
        else//
        {
            //mx=max(mx,query(id[par],id[chi]));
            mx=max(mx,loop_query(id[par],id[chi]));
            break;
        }
    }
    return mx;
}
int32_t main()
{
    fast
    ll i,j,k,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>q;
        for(i=1;i<=n;i++){cin>>v[i];}
        for(i=1;i<n;i++)
        {
            ll x,y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs(1,0);
        en[0]=INF;
        for(i=1;i<LOG;i++)
        {
            for(j=1;j<=n;j++)
            {
                ll t = p[i-1][j];
                p[i][j] = p[i-1][t];
            }
        }
        dfs_hld(1,0,1);
        //build();
        loop_build();
        //for(i=1;i<=n;i++){cout<<id[i]<<" ";}cout<<" (id)"<<endl;for(i=1;i<=n;i++){cout<<tp[i]<<" ";}cout<<" tp"<<endl;for(i=1;i<=n;i++){cout<<sz[i]<<" ";}cout<<" sz"<<endl;
        while(q--)
        {
            ll x,y,z;
            cin>>z>>x>>y;z--;
            if(z)
            {
                //Output
                ll t=lca(x,y);
                cout<<max({path_max(t,x),path_max(t,y),v[t]})<<" ";
            }
            else
            {
                //update
                v[x]=y;
                loop_update(id[x],v[x]);
            }
        }
    }
}
/*
https://cses.fi/problemset/task/2134/
Path queries 2
This is the code of HLD


This code gets tle if normal segment tree is used instead of 
loop segment tree
*/
