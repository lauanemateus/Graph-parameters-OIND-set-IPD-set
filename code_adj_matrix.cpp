/* This code is for reading a graph in the form of an adjacency matrix like this:
    n
    101001
    101000
    ...
    111000

    The Matrix is a quadratic matrix with n rows and n colums
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
        
    cout<<"Describe the graph according to the exemple:\n\n"<<"3          (vertex number)\n";
    cout <<"011\n100\n100\n\n";

    ReadAdjMatrix(n, ListAdj, qtEdges);  // function that will read the graph in the form of an adjacency matrix and create the vector ListAdj that saves the graph as a adjacency list
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