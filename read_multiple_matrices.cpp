// Esse código é para ler entradas de várias matriz de adjacência que não possuem numero de vertices indicado
// Mostra o conjunto IPD, ou o mínimo de vértices problemas caso um grafo não admita conjunto IPD
// Mostra o conjunto OIND

#include "library.hpp"

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, qtEdges;
    int ans_ipd = inf, ans_OIND = inf;
    int returnReadMatrix2;

    vector<int>colour;
    vector<vector<int>>ListAdj;
    vector<pair<int,int>>edges;
    set<pair<int, int>> arestas;

    while(true){
        // initializing 
        ListAdj.clear(), edges.clear(), arestas.clear(), colour.clear();
        ans_ipd = inf, ans_OIND = inf;
        
        // calling the function for read the matrix and make the List of Adjacency 
        returnReadMatrix2 = ReadAdjMatrix2(n, ListAdj, qtEdges);

        colour.resize(n+1, 0);

        if(n!=0){
            for(int i=1; i<=n; i++){
                for(auto u:ListAdj[i]){
                    arestas.insert({i, u});
                }
            }
            cout<<"Número de vértices = "<<n<<"\n";
            cout<<"Número de arestas: "<<qtEdges<<"\n";
            cout<<"Lista de Adjacencia:\n";
            for(auto u:arestas){
                if(u.first<u.second) cout<<u.first<<" "<<u.second<<"\n";
            }
            
            ipd(1, n, ListAdj, colour, ans_ipd);
            fill(colour.begin(), colour.end(), 0);
            OIND(1, n, ListAdj, colour, ans_OIND);
            if(ans_ipd!=inf) cout<<"IPD(G) = " << ans_ipd<<"\n";
            else {
                cout<<"IPD(G) = impossivel\n";
                fill(colour.begin(), colour.end(), 0);
                pair<int,int> resp = find_almost_paired(1, n, ListAdj, colour);    
                cout<<"Quantidade de K1 = "<<resp.first<<"\n";
                cout<<"Quantidade de K2 = "<<resp.second<<"\n";
            }
            cout<<"OIND(G) = " << ans_OIND<<"\n";
            cout<<"\n";
        }
        if(returnReadMatrix2 == 0){
            return 0;
        }
    }
    return 0;
}
