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
#define INF 1e16
const ll M =1e9+7;
const ll N =1e6+1;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m,source,now;
vector<pair<ll,ll>>g[N],rev_g[N],clean_graph[N];
vector<ll>vis(N),cst(N),dp(N,-1),now_component(N);
queue<ll>qu;
stack<ll>stk;
//DFS traversal to store the visit order(Kosaraju's algorithm)
void sccDFS(ll vertex)
{
    vis[vertex]=1;
    for(auto [child,mashroom]:g[vertex])
    {
        if(vis[child]){continue;}
        sccDFS(child);
    }
    stk.push(vertex);
}

//Reverse traversal to find the components.(Clear the elements of detected component form both reverse graph and normal graph)
void SCC(ll vertex,vector<ll>&v)
{
    vis[vertex]=1;
    v.pb(vertex);
    for(auto [child,mashroom]:rev_g[vertex])
    {
        if(vis[child]){continue;}
        SCC(child,v);
    }return;;
}

//Dp, that finds the max weight
ll finalDFS(ll vertex=source)
{
    if(dp[vertex]!=-1){return dp[vertex];}
    ll ans=0;
    for(auto [child,mashroom]:g[vertex])
    {
        ans=max(ans,finalDFS(child)+mashroom);
    }return dp[vertex]=ans+cst[vertex];
}

ll calculate(ll mashroom)
{
    ll temp=((ll)sqrtl(1+8*mashroom)-1)/2;
    return mashroom*temp-(temp*(temp+1)*(temp+2))/(ll)6+mashroom;
}
int32_t main()
{
    fast
    ll i,j,k,p,q,tc=1,cs=0;
    while(tc--)
    {
        cin>>n>>m;
        for(i=0;i<m;i++)
        {
            ll x,y,c;
            cin>>x>>y>>c;
            g[x].pb({y,c});
            rev_g[y].pb({x,c});
        }
        cin>>source;
        for(i=1;i<=n;i++)
        {
            if(vis[i]){continue;}
            sccDFS(i);
        }
        vector<pair<ll,ll>>temp;
        for(i=1;i<=n;i++){vis[i]=0;}
        now =0;
        while(stk.size())
        {
            ll t=stk.top();stk.pop();
            if(vis[t]){continue;}
            now++;
            vector<ll>v;
            SCC(t,v);
            for(auto component:v){now_component[component]=now;}
            for(auto component:v)
            {
                for(auto [child,mashroom]:g[component])
                {
                    if(now_component[child]==now)
                    {
                        cst[now]+=calculate(mashroom);
                    }
                    else{clean_graph[component].pb({child,mashroom});}
                }
                g[component].clear();
                rev_g[component].clear();
            }
        }
        for(i=1;i<=n;i++){g[i].clear();}
        for(i=1;i<=n;i++)
        {
            auto t=clean_graph[i];
            for(auto [child,mashroom]:t)
            {
                g[now_component[i]].pb({now_component[child],mashroom});
            }
        }
        source=now_component[source];
        for(i=1;i<=now;i++){vis[i]=0;}
        cout<<finalDFS()<<endl;
    }
}
/*
https://codeforces.com/contest/894/problem/E
Codeforces: Ralph and mashrooms.

Implementation of casaraju's algorithm.

Solving takeaway
When compressing a graph-
It's better to create a new graph than altering the previous one.



Logic:
1) Find the every SCC and regard a set of scc's as one node. And keep all mashroom in the node.
2) Compress the graph. 
3) Run dp for maximum weight
*/
