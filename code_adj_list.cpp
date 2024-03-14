/* This code is for reading a graph in the form of an adjacency list like this:
    n m
    v1 v2
    v3 v4
    ...
    vi vj
*/

// Consider that IPD is the induced paired dominating set of a graph
// Consider that OIND is open independent dominating set
// We are interested in the minimum cardinality of the IPD and OIND set
// The code shows the IPD set, or the minimum number of vertices problems in case a graph does not admit an IPD set
// The code shows the OIND set

#include "library.hpp"

using namespace std;

int main(){

    int n, qtEdges;
    int ans_ipd = inf, ans_OIND = inf;
    int returnReadMatrix2;

    vector<int>colour;
    vector<vector<int>>ListAdj;
    vector<pair<int,int>>edges;

    // initializing 
    ListAdj.clear(), edges.clear(), colour.clear();
    ans_ipd = inf, ans_OIND = inf;
        
    cout<<"Describe the graph according to the exemple:\n\n"<<"3 3          (vertex number and edges number)\n";
    cout <<"1 2          (edge connecting the vertex 1 and 2)\n"<<"3 1          (edge connecting the vertex 3 and 1)\n\n";

    ReadGraph(n, qtEdges,edges);  // function that will read the graph in the form of an adjacency list and add the edges into pairs of vertices in the vector edges
    ListAdj = GerarListaAdjacencia(n, edges); // function that will create the adjacency list in the ListAdj vector since the edges vector is already ready
    colour.resize(n+1, 0); // coloring vector that will be used in the ipd, OIND, find_almost_paired functions
    // the vector colour must be reset every time we call one of the ipd, OIND, find_almost_paired functions
    
    ipd(1, n, ListAdj, colour, ans_ipd); // calling the function that will find the minimum number of the induced paired dominating set cardinality of the graph
    // the result is saved in ans_ipd

    fill(colour.begin(), colour.end(), 0); // reseting colour
    OIND(1, n, ListAdj, colour, ans_OIND); // calling the function that will find the minimum number of the open independent dominating set cardinality of the graph
    // the result is saved in ans_OIND

    if(ans_ipd!=inf) cout<<"IPD(G) = " << ans_ipd<<"\n"; // if there is an induced paired dominating set we will print its minimum cardinality
    else { // otherwise, we will find a almost induced paired dominating set, that is, a set that allows isolated vertices, but we want a set with the smallest number of isolated vertices
        cout<<"IPD(G) = impossible\n";
        fill(colour.begin(), colour.end(), 0); // reseting solour
        pair<int,int> resp = find_almost_paired(1, n, ListAdj, colour);  // calling the function that will find the minimum number of the almost induced paired dominating set cardinality
        cout<<"Quantity of K1 = "<<resp.first<<"\n"; // K1 saves the number of isolated vertices 
        cout<<"Quantity of K2 = "<<resp.second<<"\n"; // K2 saves the number of vertices that belongs to the almost induced paired dominating set and have exactly another neighbor that also belongs
    }
    cout<<"OIND(G) = " << ans_OIND<<"\n"; // if there is an open independent dominating set we will print its minimum cardinality
    cout<<"\n";
    
    return 0;
}
