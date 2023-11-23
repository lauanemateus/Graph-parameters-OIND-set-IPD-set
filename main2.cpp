// Código que mostra o número mínimo de vértices problemas caso um grafo não admita conjunto IPD

#include "biblioteca.hpp"

using namespace std;

int main(){
    int n,m,a,b, qtEdges, qt_K1=0, qt_K2;
    int ans_ipd = inf, ans_yoind = inf;
    vector<int>colour(n+1, 0);
    vector<vector<int>>ListAdj;
    vector<pair<int,int>>edges;

    cout<<"Grafo 1\n";
    ReadGraph(n, qtEdges, edges);   
    // ReadAdjMatrix(n, ListAdj, qtEdges);
    ListAdj = GerarListaAdjacencia(n, edges);

    ipd(1, n, ListAdj, colour, ans_ipd);
    fill(colour.begin(), colour.end(), 0);
    yoind(1, n, ListAdj, colour, ans_yoind);
    if(ans_ipd!=inf) cout<<"IPD(G) = " << ans_ipd<<"\n";
    else {
        cout<<"IPD(G) = impossivel\n";
        fill(colour.begin(), colour.end(), 0);
        pair<int,int> resp = find_almost_paired(1, n, ListAdj, colour);    
        cout<<"Quantidade de K1 = "<<resp.first<<"\n";
        cout<<"Quantidade de K2 = "<<resp.second<<"\n";
    }
    cout<<"Yoind(G) = " << ans_yoind<<"\n";
    return 0;
}