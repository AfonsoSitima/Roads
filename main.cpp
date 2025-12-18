#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>


using namespace std;
using namespace std::chrono;

int main(){
    ifstream fin("testes/teste.in");


    auto start = high_resolution_clock::now();

    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> in_degree;
    int n, m, m1, m2, k, a, b;
    fin >> n >> m >> m1 >> m2 >> k;


    vector<vector<int>>adj(n+1);
    vector<vector<int>> caminhos(n+1, vector<int>(n+1, 0));
    in_degree.resize(n+1);
    for(int i = k; i>0 ;i--){
        fin >> a >> b;
        adj[a].push_back(b);
        in_degree[b]++;
    }
    //O(n^2)
    vector<vector<pair<int,int>>> pares(m2+1);
    vector<int> order;
    order.reserve(n);

    queue<int> fila_temp;

    //O(V + E)     *n + k
    for(int i = 1; i <= n; i++){
        if(in_degree[i] == 0){
            fila_temp.push(i);
        }
    }
    while(!fila_temp.empty()){
        int u = fila_temp.front();
        fila_temp.pop();
        order.push_back(u);
        
        for(int v : adj[u]){
            in_degree[v]--;
            if(in_degree[v] == 0){
                fila_temp.push(v);
            }
        }
    }


    //O(V*(V + E))   *n*(n + k)
    for (int i = 1; i<= n;i++){
        caminhos[i][i] = 1;
        for (int y : order) {
            for(int ant : adj[y]){
                caminhos[i][ant] += caminhos[i][y];
                if (caminhos[i][ant] > m)
                    caminhos[i][ant] -= m;
                }
        }    
        for (int b = 1; b<=n;b++){
            if(i == b || caminhos[i][b] == 0) continue;
            int num_cam = 1 + caminhos[i][b]%m;
            if(num_cam>=m1 && num_cam<=m2){
                pares[num_cam].emplace_back(i,b);
            }
        }
    }

    //O(m2 - m1)
    for (int i = m1; i <= m2;i++){
        cout << 'C' << i;
        for(size_t j = 0; j < pares[i].size(); j++){
            cout << ' ' << pares[i][j].first << ',' << pares[i][j].second;
        }
        cout << '\n';
    }



    //o tempo total é O(V*(V + E))   *n*(n + k)


    auto end = high_resolution_clock::now();
    double elapsed = duration<double>(end - start).count();
    cout << "-----------------------" << "\n";
    cout << "N (vertice): " << n <<"\n";
    cout << "M (arestas): " << k <<"\n";
    cout << "Tempo: " << elapsed << " segundos\n";
    cout << "-----------------------" << "\n";

    fin.close();

    return 0;
    
}