#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > el(m, vector<int>(2, 0)); // el = edge list
    for(int i = 0; i < m; i++) cin >> el[i][0] >> el[i][1];
    vector<vector<int> > adj(n+1);
    for(int i = 0; i < m; i++){
        adj[el[i][0]].push_back(el[i][1]);
        adj[el[i][1]].push_back(el[i][0]);
    }
    vector<vector<int> > gi(k, vector<int>(2, 0)); // gi = gaurd info
    for(int i = 0; i < k; i++) cin >> gi[i][0] >> gi[i][1];

    vector<int> d(n+1, -1);
    vector<int> visited(n+1, 0);
    priority_queue<pair<int, int> > Q; // first element max heap
    for(int i = 0; i < k; i++){
        d[gi[i][0]] = gi[i][1];
        Q.push(make_pair(gi[i][1], gi[i][0]));
    }
    pair<int, int> v;
    int temp;
    while(!Q.empty()){
        v = Q.top();
        Q.pop();
        if(visited[v.second]) continue;
        temp = adj[v.second].size();
        for(int i = 0; i < temp; i++){
            d[adj[v.second][i]] = max(d[adj[v.second][i]], v.first-1);
            if(!visited[adj[v.second][i]]) Q.push(make_pair(d[adj[v.second][i]], adj[v.second][i]));
        }
        visited[v.second] = 1;
    }

    vector<int> final;
    for(int i = 1; i <= n; i++){
        if(d[i] >= 0) final.push_back(i);
    }
    sort(final.begin(), final.end());

    temp = final.size();
    cout << temp << endl;
    for(int i = 0; i < temp; i++){
        cout << final[i] << " ";
    }
    cout << endl;

    return 0;
}