#include <iostream>
#include <vector>
using namespace std;

int func(vector<int>& dp,vector<vector<int> >& adj,  int i){
    if(dp[i] != -1) return dp[i];
    dp[i] = 0;
    for(auto j: adj[i]){
        // cout << i << " - " << j << endl;
        dp[i] = max(dp[i], func(dp, adj, j));
    }
    dp[i] += 1;
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
    int result = -1;
    for(int i = 1; i <= n; i++){
        result = max(result, func(dp, adj, i));
    }
    cout << (result - 1) << endl;

    return 0;
}