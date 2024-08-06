#include <iostream>
#include <vector>
using namespace std;

void dfs1(int i, vector<int>& order, vector<int>& visited, vector<vector<int> >& adj){
    // order vector gives reverse order of topological sort
    visited[i] = true;
    for(auto j : adj[i]){
        if(!visited[j])
            dfs1(j, order, visited, adj);
    }
    order.push_back(i);
}

void dfs2(int i, vector<vector<int> >& adj, int j, vector<int>& component){
    // cout << i << " * " << j << endl;
    component[i] = j;
    for(auto k: adj[i]){
        if(component[k] == -1)
            dfs2(k, adj, j, component);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    int num_nodes = 2*m+2;
    vector<vector<int> > adj(num_nodes); // (2*m) is +m and (2*m+1) is -m
    vector<vector<int> > adj_rev(num_nodes);
    string s1, a, s2, b;
    for(int i = 0; i < n; i++){
        cin >> s1 >> a >> s2 >> b;
        if(s1 == "+" && s2 == "+"){
            adj[2*stoi(a)+1].push_back(2*stoi(b));
            adj[2*stoi(b)+1].push_back(2*stoi(a));
            adj_rev[2*stoi(b)].push_back(2*stoi(a)+1);
            adj_rev[2*stoi(a)].push_back(2*stoi(b)+1);
        } else if(s1 == "-" && s2 == "+"){
            adj[2*stoi(a)].push_back(2*stoi(b));
            adj[2*stoi(b)+1].push_back(2*stoi(a)+1);
            adj_rev[2*stoi(b)].push_back(2*stoi(a));
            adj_rev[2*stoi(a)+1].push_back(2*stoi(b)+1);
        } else if(s1 == "+" && s2 == "-"){
            adj[2*stoi(a)+1].push_back(2*stoi(b)+1);
            adj[2*stoi(b)].push_back(2*stoi(a));
            adj_rev[2*stoi(b)+1].push_back(2*stoi(a)+1);
            adj_rev[2*stoi(a)].push_back(2*stoi(b));
        } else {
            adj[2*stoi(a)].push_back(2*stoi(b)+1);
            adj[2*stoi(b)].push_back(2*stoi(a)+1);
            adj_rev[2*stoi(b)+1].push_back(2*stoi(a));
            adj_rev[2*stoi(a)+1].push_back(2*stoi(b));
        }
    }

    vector<int> visited(num_nodes, 0);
    vector<int> order;
    for(int i = 2; i < num_nodes; i++){
        if(!visited[i])
            dfs1(i, order, visited, adj);
    }

    vector<int> component(num_nodes, -1);
    int j, node = 1;
    for(int i = order.size()-1; i >= 0; i--){
        node = order[i];
        // cout << i << " - " << order[i] << endl;
        if(component[node] == -1){
            dfs2(node, adj_rev, j, component);
            j++;
        }
    }

    vector<int> result(m+1, 0);
    bool flag = true;
    for(int i = 1; i <= m; i++){
        if(component[2*i] == component[2*i+1]){
            cout << "IMPOSSIBLE" << endl;
            flag = false;
            break;
        }
        if(component[2*i] > component[2*i+1]){
            result[i] = 1;
        }
    }

    if(flag){
        for(int i = 1; i <= m; i++){
            if(result[i]) cout << "+ ";
            else cout << "- ";
        }
        cout << endl;
    }

    return 0;
}