#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define ll long long
#define MOD 1000000007


void dfs(vector<vector<int> >& adj, vector<int>& visited,
            vector<int>& parent, int start, int end)
{
    stack<int> S;
    S.push(start);
    int v;
    while(!S.empty()){
        v = S.top(); S.pop();
        if(visited[v]) continue;
        if(v == end){
            return;
        }
        for(auto i: adj[v]){
            S.push(i);
            parent[i] = v;
        }
        visited[v] = 1;
    }
}

int func(vector<int>& dp,vector<vector<int> >& adj,  int i){
    if(dp[i] != -1) return dp[i];
    dp[i] = 0;
    for(auto j: adj[i]){
        // cout << i << " - " << j << endl;
        dp[i] += func(dp, adj, j);
        dp[i] %= MOD;
    }
    return dp[i];
}

int main()
{
    int n, m; cin >> n >> m;
    vector<vector<int> > adj(n+1);
    int input_var1, input_var2;
    for(int i = 0; i < m; i++){
        cin >> input_var1 >> input_var2;
        adj[input_var1].push_back(input_var2);
    }

    vector<int> dp(n+1, -1); // dp[i] how many ways you can reach i to n
    dp[n] = 1;
    cout << func(dp, adj, 1) << endl;

    return 0;
}