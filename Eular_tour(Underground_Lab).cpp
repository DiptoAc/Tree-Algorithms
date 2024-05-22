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
ll n,m;
vector<ll>g[N],vis(N),path;
void dfs(ll v)
{
    if(vis[v]){return;}
    vis[v]=1;
    path.pb(v);
    for(auto c:g[v])
    {
        if(vis[c]){continue;}
        dfs(c);
        path.pb(v);
    }
    path.pb(v);
}
int32_t main()
{
    fast
    ll i,j=1,k=1,p,q,tc=1,cs=0;//cin>>tc;
    while(tc--)
    {
        cin>>n>>m>>k;
        map<pair<ll,ll>,ll>mp;
        while(m--)
        {
            ll x,y;
            cin>>x>>y;
            if(x>y){swap(x,y);}
            if(mp[{x,y}]){continue;}
            mp[{x,y}]=1;
            g[x].pb(y);
            g[y].pb(x);
        }
        dfs(1);
        //for(auto it:path){cout<<it<<" ";}cout<<endl;
        ll lim=path.size()/k;
        ll mx=(2*n+k-1)/k;
        j=0;
        vector<ll>visited(n+1);
        for(i=1;i<=k;i++)
        {
            if(j==path.size()){cout<<"1 1"<<endl;continue;}
            vector<ll>temp={0};
            while(temp.size()<=mx)
            {
                if(path[j]!=temp.back())
                {
                    temp.pb(path[j]);
                    visited[path[j]]=1;
                }
                j++;
                if(j==path.size()){break;}
            }
            while(j<path.size())
            {
                if(visited[path[j]]){j++;}
                else{break;}
            }
            cout<<temp.size()-1<<" ";
            for(int bal=1;bal<temp.size();bal++)
            {
                cout<<temp[bal]<<" ";
            }cout<<endl;
        }
    }
}
/***
https://codeforces.com/contest/781/problem/C
Eular Tour Problem: Underground Lab.

Found from: Ultimate topic list by Shahjalal Shohag.
***/


