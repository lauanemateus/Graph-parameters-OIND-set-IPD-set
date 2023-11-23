#include<bits/stdc++.h>
using namespace std;

const int inf = (int)1e9;

// considere IPD o mesmo que "dominante emparelhado induzido"

// gera lista de adjacencia dados n vertices e as arestas, considerando vertices de 1 a n
vector<vector<int>> GerarListaAdjacencia(int n, vector<pair<int,int>>edges){
    vector<vector<int>> ListAdj(n+1);
    int a, b;
    for (int i = 0; i < edges.size(); i++)
    {
        a=edges[i].first, b=edges[i].second;
        ListAdj[a].push_back(b);
        // cout<<"adiciondo "<<b<<" em "<<a<<"\n";
    }
    return ListAdj;
}

// verificar se o grafo possui um conjunto IPD válido dado o vetor colour
/* em cada posição do vetor colour pode ter o valor 1 (aquela aresta faz parte do conjunto IPD), 
valor 2 (aquela aresta é vizinha a algum vértice que faz parte do conjunto IPD),
ou valor 0, caso não seja uma aresta indicada pelo valor 1 e pelo valor 2
*/
// Assim, se um grafo algum vertice com valor 0 no vetor colour, significa que o conjunto IPD dado não é válido
int verifica_conj_ipd(int n, vector<int>&colour){
    int cont=0;
    bool ok=1;
    for(int i = 1; i <= n; i++){
        if(colour[i]==0) {
            ok=0;  
        }
        if(colour[i]==1) cont++;
    }
    if(!ok) return inf;
    return cont;
}

int ans=inf; // ans com valor suficientemente grande;
long long chamadas=0;

// funcao que encontra menor número de ipd válido para o grafo dado na entrada através da lista de adjacencia e da matriz de adjacencia
// v é o vértice atual que a funcao esta trabalhando e n é o número de vértices total
void solve(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour){
    if(v==n+1){
        ans=min(ans, verifica_conj_ipd(n, colour));
        return;
    }

    // se colour[v]==1 é pq o vértice v faz - no estado atual - parte do conjunto IPD (conjunto dominante emparelhado induzido)
    // se colour[v]==2 é pq o vértice v não pode fazer parte do conjunto S, por causa da definição de conjunto IPD
    if(colour[v]){
        solve(v+1,  n, ListAdj, colour);
        return;
    }

    //caso em que vamos, se possível, adicionar v e um de seus vizinhos no conjunto IPD
    // aqui, terão vários subcasos, dependendo da quantidade de vizinhos
    colour[v]=1;
    // cout<<"v="<<v<< " eh 1\n";
    int u, w, ni,nj; 
    for (int i = 0; i < ListAdj[v].size(); i++)
    {
        u = ListAdj[v][i]; // vizinho de v
        if(colour[u]) continue;
        colour[u]=1;
        vector<int>aux;
        for (int j = 0; j < ListAdj[v].size(); j++)
        {
            w = ListAdj[v][j];
            if(colour[w]==0){
                colour[w]=2;
                aux.push_back(w);
            }
        }
        for (int j = 0; j < ListAdj[u].size(); j++)
        {
            w = ListAdj[u][j];
            if(colour[w]==0){
                colour[w]=2;
                aux.push_back(w);
            }
        }
        solve(v+1,  n, ListAdj, colour);
        colour[u]=0;
        for (int j = 0; j < aux.size(); j++)
        {
            colour[aux[j]]=0;
        } 
    }
    // voltando v ao estado anterior
    colour[v]=0;

    //caso em que nao vamos adicionar v no conjunto IPD
    solve(v+1,  n, ListAdj, colour);
    
}

int main(){
    int n, m,a,b;
    cin>>n>>m;

    vector<int>colour(n+1, 0);
    vector<vector<int>>ListAdj;
    vector<pair<int,int>>edges;

    for (int i = 0; i < m; i++)
    {
        cin>>a>>b;
        edges.push_back({a,b});
        edges.push_back({b,a});
    }   

    ListAdj = GerarListaAdjacencia(n, edges);
    solve(1, n, ListAdj, colour);
    cout<<ans<<"\n";
    // cout<<"chamadas="<<chamadas<<"\n";
    return 0;
}