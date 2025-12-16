#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;



int main() {
    int nIntersections = 0;
    int nTrucks;
    int m1, m2;
    int nConnection;

    cin >> nIntersections >> nTrucks;
    cin >> m1 >> m2;
    cin >> nConnection;

    vector<int> L;
    queue<int> Q;
    vector<int> inDegree(nIntersections + 1);
    vector<vector<int>> adj(nIntersections + 1);
    vector<unordered_map<int, int>> dp(nIntersections + 1);

    for (int i = 1; i <= nConnection; i++) {
        int a, b;
        cin >> a >> b;
        inDegree[b]++;
        adj[a].push_back(b);
    }
 
    // Topological Sort using Kahn's Algorithm
    //caso esteja lento usar matriz de adjacencia
    for (int i = 1; i <= nIntersections; i++) {
        if (inDegree[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();
        L.push_back(current);

        for (int neighborId : adj[current]) {
            inDegree[neighborId]--;
            if (inDegree[neighborId] == 0) {
                Q.push(neighborId);
            }
        }
    }



    for (int i = (int)L.size() - 1; i >= 0 ; i--) {
        int topo = L[i];
        for (int j : adj[topo]) {
            dp[topo][j] = (dp[topo][j] + 1) % nTrucks;
            for (auto k = dp[j].begin(); k != dp[j].end(); ++k) {
                int key = k->first;
                int path = k->second;
                dp[topo][key] += path;
                if (dp[topo][key] >= nTrucks) {
                    dp[topo][key] %= nTrucks;
                }
            }        
        }
    }

      // Collect pairs per truck number
    vector<vector<pair<int,int>>> pares(nConnection + 1);
    for (int a = 1; a <= nIntersections; a++) {
        for (auto it = dp[a].begin(); it != dp[a].end(); ++it) {
            int b = it->first;
            int count = it->second;
            int num_cam = 1 + (count % nTrucks);
            if (num_cam >= m1 && num_cam <= m2 && a != b) {
                cout << a << ' ' << b << ' ' << count << '\n';
                pares[num_cam].push_back(make_pair(a, b));
            }
        }
    }

    // Sort pairs lexicographically per truck and print
    for (int t = m1; t <= m2; t++) {
        sort(pares[t].begin(), pares[t].end());
        cout << 'C' << t;
        for (size_t i = 0; i < pares[t].size(); i++) {
            cout << ' ' << pares[t][i].first << "," << pares[t][i].second;
        }
        cout << '\n';
    }
    return 0;
}