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
const ll N=2e5+1;
const ll LOG=20;
void debug(vector<ll>&v){for(auto it:v){cout<<it<<" ";}cout<<endl;}
ll n,m;
vector<ll>g[N],sz(N),is_removed(N),min_dist(N,INF);
/*
g[] is the adjacency matrix.
sz[] is for storing subtree size.
is_removed[] tracks all decomposed nodes.
min_dist[] keeps the track of closest red node.
*/

vector<pair<ll,ll>>ancestor[N];
//{centroid,dist_form_the_centeroid}

ll get_size(ll cur=1,ll par=-1) //Finds the size of subtree for every node.
{
    sz[cur]=1;
    for(auto chi:g[cur])
    {
        if(chi==par || is_removed[chi]){continue;}
        sz[cur]+=get_size(chi,cur);
    }return sz[cur];
}
ll find_centroid(ll cur,ll tree_size, ll par=-1) //Returns the centroid of subtree
{
    for(auto chi:g[cur])
    {
        if(chi==par || is_removed[chi]){continue;}
        if(sz[chi]*2>tree_size)
        {
            return find_centroid(chi,tree_size,cur);
        }
    }return cur;
}

void get_dist(ll cur, ll centeroid, ll par, ll cur_sz)
{
    ancestor[cur].pb({centeroid,cur_sz});
    for(auto chi:g[cur])
    {
        if(chi==par || is_removed[chi]){continue;}
        get_dist(chi,centeroid,cur,cur_sz+1);
    }
}

void centeroid_decomp(ll cur)
{
    ll centeroid = find_centroid(cur,get_size(cur));

    for(auto chi:g[centeroid])
    {
        if(is_removed[chi]){continue;}
        get_dist(chi,centeroid,centeroid,1);
    }


    is_removed[centeroid]=1; //After updating ancestor(Using centeroid and dist), remove this centeroid.
    for(auto chi:g[centeroid])
    {
        if(is_removed[chi]){continue;}
        centeroid_decomp(chi); //Keep decomposing subtrees.
    }
}

void paint(ll node)  //Paint the node and update all centeroids.
{
    for(auto [anc,dist]:ancestor[node])
    {
        min_dist[anc]=min(min_dist[anc],dist);
    }min_dist[node]=0;
}

void query(ll node) //Check all centeroids and find the minimum distance.
{
    ll ans=min_dist[node];
    for(auto [anc,dist]:ancestor[node])
    {
        ans=min(ans,dist+min_dist[anc]);
    }
    cout<<ans<<endl;
}

int32_t main()
{
    fast
    ll i,j,k,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>q;
        for(i=1;i<n;i++)
        {
            ll x,y;cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        centeroid_decomp(1);
        paint(1); //First node is initially red.
        while(q--)
        {
            ll ops, x;
            cin>>ops>>x;
            if(--ops){query(x);}
            else{paint(x);}
        }
    }
}
/*
Problem name: Xenia and tree(Codeforces)
Topic name: Centeroid decomposition
*/
