#include "biblioteca.hpp"

using namespace std;

int main(){
    int n,m,a,b, qtEdges1, qtEdges2, qtVertexProd=0;
    int ans_ipd = inf, ans_yoind = inf;
    vector<int>colour(n+1, 0);
    vector<vector<int>>ListAdj1, ListAdj2, ListProd;
    vector<pair<int,int>>edges1, edges2, edgesProd;

    cout<<"Grafo 1\n";
    // ReadGraph(n, qtEdges1, edges1);   
    ReadAdjMatrix(n, ListAdj1, qtEdges1);

    // ListAdj1 = GerarListaAdjacencia(n, edges1);

    ipd(1, n, ListAdj1, colour, ans_ipd);
    fill(colour.begin(), colour.end(), 0);
    yoind(1, n, ListAdj1, colour, ans_yoind);
    if(ans_ipd!=inf) cout<<"IPD(G) = " << ans_ipd<<"\n";
    else cout<<"IPD(G) = impossivel\n";
    cout<<"Yoind(G) = " << ans_yoind<<"\n";
    cout<<"\n";

    fill(colour.begin(), colour.end(), 0);
    ans_ipd=ans_yoind=inf;

    cout<<"Grafo 2\n";
    // ReadGraph(m, qtEdges2, edges2);   
    ReadAdjMatrix(m, ListAdj2, qtEdges2);
    // ListAdj2 = GerarListaAdjacencia(m, edges2);

    ipd(1, m, ListAdj2, colour, ans_ipd);
    fill(colour.begin(), colour.end(), 0);
    yoind(1, m, ListAdj2, colour, ans_yoind);
    if(ans_ipd!=inf) cout<<"IPD(H) = " << ans_ipd<<"\n";
    else cout<<"IPD(H) = impossivel\n";
    cout<<"Yoind(H) = " << ans_yoind<<"\n";
    cout<<"\n";

    fill(colour.begin(), colour.end(), 0);
    ans_ipd=ans_yoind=inf;

    edgesProd = GerarEdgesProdLexicografico(n, ListAdj1, m, ListAdj2, qtVertexProd);
    ListProd = GerarListaAdjacencia(qtVertexProd, edgesProd);

    ipd(1, qtVertexProd, ListProd, colour, ans_ipd);
    fill(colour.begin(), colour.end(), 0);
    yoind(1, qtVertexProd, ListProd, colour, ans_yoind);
    if(ans_ipd!=inf) cout<<"IPD(GxH) = " << ans_ipd<<"\n";
    else cout<<"IPD(GxH) = impossivel\n";
    cout<<"Yoind(GxH) = " << ans_yoind<<"\n";

    return 0;
}