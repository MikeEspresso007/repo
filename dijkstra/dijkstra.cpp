#include <iostream>
#include <time.h>  
#include <float.h>
#include <iomanip>
#include <cstdlib> 

using namespace std;

// number of NODES_NUM
#define NODES_NUM 100

// function to calculate probability
double prob() 
{
    return (double)rand() / (double)RAND_MAX;
}

// class to create nPairDist using connectivity matrices representation
class GraphBase
{
    int num;
public:
    double ** nPairDist; // nodes pair shortestDist
    
    // 2D array constructor
    GraphBase(int nodes)
    {   
        num = nodes;
        
        nPairDist = new double*[num];

        for (int i = 0; i < num; ++i) 
        {
            nPairDist[i] = new double[num];  
        }
    }

    
    // initiate the connection between nodes by density
    void initialize(double density)
    {
        // Traverse the 2D array
        for (int i = 0; i < num; ++i) 
        {
            for (int j = i; j < num; ++j) 
            {
                // if the index is same, then no connection
                if (i == j)
                { 
                    nPairDist[i][j] = false;
                }
                else
                {
                    // create link between nodes pair, based on probability
                    // Higher density, means more connections.
                    double rWeight = (1.0 + 1) + (((double) rand()) / (double) RAND_MAX) * (10.0 - (1.0 + 1));
                    nPairDist[i][j] = nPairDist[j][i] = (prob() < density)*rWeight;
                }
            }
        }
    }
    
    void printGraph()
    {
        cout << "\n\nThis nPairDist has " << num << " nodes" << endl;
        for (int i = 0; i < num; i++)
        {
            cout << "from (" << i << ") to  ";
            for (int j = 0; j < num; j++)
            {
                if(nPairDist[i][j] !=0.0f )
                {
                   cout << "(" << j << ")-" << nPairDist[i][j] << " ";
                }        
            }   
            cout << endl;    
        } 
    }
};

// function to find minimal shortestDist
double minDistance(double * shortestDist, bool * nodesList)
{
    double min = DBL_MAX;
    int index;
    
    // scan the list of shortestDist and all nodes
    for (int v = 0; v < NODES_NUM; v++)
    {
        // find the minimal shortestDist to non-visisted NODES_NUM.
        if (    shortestDist[v] <= min    // if shortestDist to v is lower the minimal
            && nodesList[v] == false)     // check un-visisted NODES_NUM
        {
            min   = shortestDist[v];
            index = v;
        }
    }

    return index;
}

// function to calculate average path
double averagePathLen(double * shortestDist)
{
    double sum = 0;
    for (int d = 0; d < NODES_NUM; d++)
        sum += shortestDist[d];
    // as we only calculate the path from NODES_NUM 1, we divided it by nodes-1
    double avg = sum*1.0/(NODES_NUM-1);
    return avg;
}

// function to find the shortest path
double dijkstra(double ** nPairDist, int src)
{
    double  shortestDist[NODES_NUM];    // to record shortest shortestDist from 0 to correspoding NODES_NUM.
    bool    nodesList[NODES_NUM];       // to tick the visited nodes.

    // Initiase all shortestDist to infinity
    for (int i = 0; i < NODES_NUM; i++)
    {
        shortestDist[i]   = DBL_MAX;
        nodesList[i]  = false;  // visited = true, un-visited = false
    }

    // the shortestDist from the src always zero
    shortestDist[src] = 0;

    // Loop through all nodes to visit one by one, and record the shortest shortestDist to visit each of them.
    for (int c = 0; c < NODES_NUM-1; c++)
    {
        // Pick the NODES_NUM which has the shortest shortestDist to visit.
        int u = minDistance(shortestDist, nodesList);    
        
        // tick it as visited.
        nodesList[u] = true;

        //cout << "\r\nu=" << u << "     shortestDist[u]=" << shortestDist[u] ; 

        // loop through adjacent nodes
        for (int v = 0; v < NODES_NUM; v++)
        {
            if (      nPairDist[u][v]                               // if there is connection to U
                &&  !nodesList[v]                                   // if num is not visited yet
                &&    shortestDist[u] + nPairDist[u][v] < shortestDist[v])  // if there is shorter path, update it
            {            
                shortestDist[v] = shortestDist[u] + nPairDist[u][v];  //update minimum shortestDist from NODES_NUM 0 to corresponding NODES_NUM
            }    
        }

    }

    double avg = averagePathLen(shortestDist);
    return avg;
}



/* Main Program */
int main() 
{

    // set 2 significant numbers
    std::cout << std::setprecision(2) << std::fixed;
    srand(time(0));
    
    GraphBase graph1(NODES_NUM);
    

    // Monte Carlo simulation with different density
    double dens[] = {0.20, 0.50, 0.70}; // too low density, then no connection between start and end.
    int N = 100;
    
    cout << "Implement a Monte Carlo simulation that calculates the average shortest path in a graph with " << N << " samples" << endl;
    
    for (int i = 0; i < sizeof(dens)/sizeof(double); i++)
    {
        double sum = 0.0;
        double density = dens[i];
        
        for (int j = 0; j < N; j++)
        {
            // initialize the edges of the nPairDist
            graph1.initialize(density);
            //graph1.printGraph();

            double res = dijkstra(graph1.nPairDist, 0);
            //cout << "" << res << endl;

            sum += res;
        }

        cout << "When density is " << dens[i]*100 << "%, average shortest path is " <<  sum/N << endl;
    }
}