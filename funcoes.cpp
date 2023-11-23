#include "biblioteca.hpp"

using namespace std;

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
int verifica_conj(int n, vector<int>&colour){
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

pair<int,int> qt_K1_K2(int n, vector<int>&colour, vector<vector<int>> &ListAdj){
    int qt_K1=0, qt_K2=0;
    bool ok=1;
    for(int i = 1; i <= n; i++){
        if(colour[i]==0) {
            ok=0;  
        }
        if(colour[i]==1){
            bool mark=0;
            for(auto u:ListAdj[i]){
                if(colour[u]==1){
                    mark=1;
                    break;
                }
            }
            if(mark) qt_K2++;
            else qt_K1++;
        }
    }
    if(!ok) return {inf, inf};
    return {qt_K1, qt_K2};
}

int ans=inf; // ans com valor suficientemente grande;
long long chamadas=0;

// funcao que encontra menor número de ipd válido para o grafo dado na entrada através da lista de adjacencia 
// v é o vértice atual que a funcao esta trabalhando e n é o número de vértices total
void ipd(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour, int &ans){
    if(v==n+1){
        ans=min(ans, verifica_conj(n, colour));
        return;
    }

    // se colour[v]==1 é pq o vértice v faz - no estado atual - parte do conjunto IPD (conjunto dominante emparelhado induzido)
    // se colour[v]==2 é pq o vértice v não pode fazer parte do conjunto S, por causa da definição de conjunto IPD
    if(colour[v]){
        ipd(v+1,  n, ListAdj, colour,ans);
        return;
    }

    //caso em que vamos, se possível, adicionar v e um de seus vizinhos no conjunto IPD
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
        ipd(v+1,  n, ListAdj, colour, ans);
        colour[u]=0;
        for (int j = 0; j < aux.size(); j++)
        {
            colour[aux[j]]=0;
        } 
    }
    // voltando v ao estado anterior
    colour[v]=0;

    //caso em que nao vamos adicionar v no conjunto IPD
    ipd(v+1,  n, ListAdj, colour, ans);
    
}

// funcao que encontra menor número de yoind válido para o grafo dado na entrada através da lista de adjacencia 
// v é o vértice atual que a funcao esta trabalhando e n é o número de vértices total
void yoind(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour, int &ans){
    if(v==n+1){
        ans=min(ans, verifica_conj(n, colour));
        return;
    }

    // se colour[v]==1 é pq o vértice v faz - no estado atual - parte do conjunto yoind (conjunto dominante emparelhado induzido)
    // se colour[v]==2 é pq o vértice v não pode fazer parte do conjunto S, por causa da definição de conjunto yoind
    if(colour[v]){
        yoind(v+1,  n, ListAdj, colour,ans);
        return;
    }

    vector<int>aux;
    int u, w; 

    //caso em que vamos, se possível, adicionar v e um de seus vizinhos no conjunto yoind
    colour[v]=1;

    // caso em que v faz parte de um K1
    for (int i = 0; i < ListAdj[v].size(); i++)
    {
        u=ListAdj[v][i];
        if(colour[u]==0){
            aux.push_back(u);
            colour[u]=2;
        }
    }
    yoind(v+1, n, ListAdj, colour, ans);

    // voltando ao estado anterir
    for (int j = 0; j < aux.size(); j++)
    {
        colour[aux[j]]=0;
    } 
    aux.clear();
    
    // caso em que v faz parte de um K2
    for (int i = 0; i < ListAdj[v].size(); i++)
    {
        u = ListAdj[v][i]; // vizinho de v
        if(colour[u]) continue;
        colour[u]=1;
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
        yoind(v+1,  n, ListAdj, colour, ans);
        colour[u]=0;
        for (int j = 0; j < aux.size(); j++)
        {
            colour[aux[j]]=0;
        } 
    }
    // voltando v ao estado anterior
    colour[v]=0;

    //caso em que nao vamos adicionar v no conjunto yoind
    yoind(v+1,  n, ListAdj, colour, ans);
    
}

pair<int,int> find_almost_paired(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour){
    // ans.firt é a qt de K1 e ans.second é a qtd de K2
    pair<int,int> ans = {inf,inf}, resp_atual;
    if(v==n+1){
        resp_atual=qt_K1_K2(n, colour, ListAdj);
        if(resp_atual.first<ans.first || 
            (resp_atual.first == ans.first && resp_atual.second<ans.second)) ans=resp_atual;
        return ans;
    }

    // se colour[v]==1 é pq o vértice v faz - no estado atual - parte do conjunto yoind (conjunto dominante emparelhado induzido)
    // se colour[v]==2 é pq o vértice v não pode fazer parte do conjunto S, por causa da definição de conjunto yoind
    if(colour[v]){
        return find_almost_paired(v+1,  n, ListAdj, colour);
    }

    vector<int>aux;
    int u, w; 

    //caso em que vamos, se possível, adicionar v e um de seus vizinhos no conjunto yoind
    colour[v]=1;

    // caso em que v faz parte de um K1
    for (int i = 0; i < ListAdj[v].size(); i++)
    {
        u=ListAdj[v][i];
        if(colour[u]==0){
            aux.push_back(u);
            colour[u]=2;
        }
    }
    ans = find_almost_paired(v+1,  n, ListAdj, colour);

    // voltando ao estado anterir
    for (int j = 0; j < aux.size(); j++)
    {
        colour[aux[j]]=0;
    } 
    aux.clear();
    
    // caso em que v faz parte de um K2
    for (int i = 0; i < ListAdj[v].size(); i++)
    {
        u = ListAdj[v][i]; // vizinho de v
        if(colour[u]) continue;
        colour[u]=1;
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
        resp_atual = find_almost_paired(v+1,  n, ListAdj, colour);
        if(resp_atual.first<ans.first || 
            (resp_atual.first == ans.first && resp_atual.second<ans.second)) ans=resp_atual;
        colour[u]=0;
        for (int j = 0; j < aux.size(); j++)
        {
            colour[aux[j]]=0;
        } 
    }
    // voltando v ao estado anterior
    colour[v]=0;

    //caso em que nao vamos adicionar v no conjunto yoind
    resp_atual = find_almost_paired(v+1,  n, ListAdj, colour);
    if(resp_atual.first<ans.first || 
            (resp_atual.first == ans.first && resp_atual.second<ans.second)) ans=resp_atual;

    return ans;
    
}

vector<pair<int,int>> GerarEdgesProdLexicografico (int n, vector<vector<int>> &ListAdj1, int m, vector<vector<int>> &ListAdj2, int &qtVertex){
    vector<pair<pair<int,int>, pair<int,int>>>edges;
    vector<pair<int,int>> ans;
    int u;
    for(int v=1; v<=m; v++){
        for(int i=0; i<ListAdj2[v].size(); i++){
            u=ListAdj2[v][i];
            // v-u sao vizinhos no grafo 2, logo vamos gerar 1v-1u, 2v-2u, ... , nv, nu
            for(int k=1; k<=n; k++){
                edges.push_back({{k, v}, {k, u}});
            }
        }
    }
    for(int v=1; v<=n; v++){
        for(int i=0; i<ListAdj1[v].size(); i++){
            u=ListAdj1[v][i];
            // v-u sao vizinhos no grafo 1, logo vamos gerar v1-u1, v1-u2, ... , v1, um
            for(int k=1; k<=m; k++){
                for (int w = 1; w <= m; w++)
                {
                    edges.push_back({{v, k}, {u, w}});
                }
            }
        }
    }
    map<pair<int, int>, int> id;
    int idX=0;
    for(auto p:edges){
        if(id.find(p.first)==id.end()){
            id[p.first] = ++idX;
        }
        if(id.find(p.second)==id.end()){
            id[p.second] = ++idX;
        }
        ans.push_back({id[p.first], id[p.second]});
    }
    qtVertex=idX;
    return ans;
}

void ReadAdjMatrix(int &n, vector<vector<int>> &ListAdj, int &qtEdges){
    // this function read connected graph givin the adjacency matrix

    /* exemple:
    0111100
    1011011
    1100111
    1100111
    1011011
    0111101
    0111110
    */

    cin>>n;
    string s;
    qtEdges=0;
    ListAdj.resize(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin>>s;
        for (int j = 1; j <= n; j++)
        {
            if(s[j-1]=='1'){
                ListAdj[i].push_back(j);
                qtEdges++;
            }
        }
    }
    qtEdges/=2;
}

// this function read the number of vertices, the number of edges and ,for each edge, it is read the neighbors a-b
void ReadGraph(int &n, int &qtEdges, vector<pair<int,int>>&edges){
    cin>>n>>qtEdges;
    int a, b;
    for (int i = 0; i < qtEdges; i++)
    {
        cin>>a>>b;
        edges.push_back({a,b});
        edges.push_back({b,a});
    } 
}