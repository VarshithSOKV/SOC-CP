#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool flag;

void dfs(int j, int n, vector<vector<int> >& adj, vector<int>& visited, vector<int>& parent){
    stack<int> S;
    S.push(j);
    int v, temp, temp1, temp2;

    while(!S.empty()){
        v = S.top();
        S.pop();
        visited[v] = 1;

        for(auto i: adj[v]){
            if(parent[v] != i && visited[i]){
                flag = false;
                temp1 = i;
                parent[i] = v;
                temp2 = parent[i];
            } else if(parent[v] != i) {
                S.push(i);
                parent[i] = v;
            }
        }

        if(!flag) break;
    }
    if(!flag){
        vector<int> final;
        final.push_back(temp1);
        while(temp2 != temp1){
            final.push_back(temp2);
            temp2 = parent[temp2];
        }
        final.push_back(temp1);
        temp1 = final.size();
        cout << temp1 << endl;
        for(auto i : final){
            cout << i << " ";
        }
        cout << endl;
        return;
    }
}

int main(){
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    flag = true;
    vector<int> visited(n+1, 0), parent(n+1, -1);
    for(int j = 1; j <= n; j++){
        if(!visited[j]) dfs(j, n, adj, visited, parent);
        if(!flag) break;
    }
    if(flag){
       cout << "IMPOSSIBLE" << endl;     
    }

    return 0;
}