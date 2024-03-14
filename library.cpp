#include<bits/stdc++.h>
using namespace std;

const int inf = (int)1e9;
// considere IPD o mesmo que conjunto "dominante emparelhado induzido" mínimo
// considere OIND o mesmo que conjunto "dominante independente aberto" mínimo

// gera lista de adjacencia dados n vertices e as arestas, considerando vertices de 1 a n
vector<vector<int>> GerarListaAdjacencia(int n, vector<pair<int,int>>edges);

// verificar se o grafo possui um conjunto IPD válido dado o vetor colour
/* em cada posição do vetor colour pode ter o valor 1 (aquela aresta faz parte do conjunto IPD), 
valor 2 (aquela aresta é vizinha a algum vértice que faz parte do conjunto IPD),
ou valor 0, caso não seja uma aresta indicada pelo valor 1 e pelo valor 2
*/
// Assim, se um grafo algum vertice com valor 0 no vetor colour, significa que o conjunto IPD dado não é válido
int verifica_conj_ipd(int n, vector<int>&colour);

// funcao que encontra menor número de ipd válido para o grafo dado na entrada através da lista de adjacencia
// v é o vértice atual que a funcao esta trabalhando e n é o número de vértices total
void ipd(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour, int &ans);

// funcao que encontra menor número de OIND válido para o grafo dado na entrada através da lista de adjacencia
// v é o vértice atual que a funcao esta trabalhando e n é o número de vértices total
void OIND(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour, int &ans);

vector<pair<int,int>> GerarEdgesProdLexicografico (int n, vector<vector<int>> &ListAdj1, int m, vector<vector<int>> &ListAdj2, int &qtVertex);

void ReadGraph(int &n, int &qtEdges, vector<pair<int,int>>&edges);

void ReadAdjMatrix(int &n, vector<vector<int>> &ListAdj, int &qtEdges);

int ReadAdjMatrix2(int &n, vector<vector<int>> &ListAdj, int &qtEdges);

pair<int,int> find_almost_paired(int v, int n, vector<vector<int>> &ListAdj, vector<int> &colour);

pair<int,int> qt_K1_K2(int n, vector<int>&colour, vector<vector<int>> &ListAdj);
