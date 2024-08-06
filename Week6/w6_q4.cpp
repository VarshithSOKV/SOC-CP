#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
#define ll long long

bool dfs(vector<vector<int> >& adj, vector<int>& visited,
         vector<int>&parent, int start)
{
    stack<int> S;
    S.push(start);
    int v;
    // cout << "yes" << endl; 
    while(!S.empty()){
        v = S.top(); S.pop();
        if(visited[v]) return true;
        for(auto i: adj[v]){
            // cout << v << " - " << i << endl;
            if(parent[v] != i){
                S.push(i);
                parent[i] = v;
            }
        }
        visited[v] = 1;
    }
    return false;
}

int main()
{
    int t, n, a, max, min;
    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n;
        vector<vector<int> > adj(n+1);
        for(int j = 1; j <= n; j++){
            cin >> a;
            auto it = find(adj[j].begin(), adj[j].end(), a);
            if(it == adj[j].end()) adj[j].push_back(a);
            it = find(adj[a].begin(), adj[a].end(), j);
            if(it == adj[a].end()) adj[a].push_back(j);
        }
        int numcycles = 0, numsinglended = 0;
        vector<int> visited(n+1, 0);
        vector<int> parent(n+1, -1);
        for(int i = 1; i <= n; i++){
            if(adj[i].size() == 1) numsinglended++;
            if(!visited[i]){
                if(dfs(adj, visited, parent, i)){
                    numcycles++;
                }
            }
        }
        min = numcycles;
        if(numsinglended != 0) min++;
        max = numcycles + (numsinglended/2);

        cout << min << " " << max << endl;
    }

    return 0;
}