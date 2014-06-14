/**
 * Giant Component and Connectivity in Geographical Threshold Graphs
 * Milan Bradonjic, Aric Hagberg, andAllon G. Percus
 *
 * Geographical-threshold graph
 */

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include <ogdf/basic/Graph.h> 
#include <ogdf/basic/NodeArray.h>
#include <ogdf/basic/geometry.h>

using std::minstd_rand;
using std::default_random_engine;
using std::exponential_distribution;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a Geographical Threshold Graph. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param alpha is the model parameter.
 * @param theta is the threshold parameter.
 * @param dimension is the dimension of nodes to layed out.
 */
void randomGeographicalThresholdGraph(Graph &G, int n, double alpha, double theta, int dimension=2) {
	OGDF_ASSERT(n >= 0 && alpha > 0 && theta > 0);

	G.clear();
	if (n == 0) return;

	// exponential generator for laying out points
	default_random_engine generator;
	exponential_distribution<double> distribution(1.0);
	
	// uniform generator for assigning weights
	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	NodeArray<Array<double>> cord(G, Array<double>(dimension));
	NodeArray<double> weight(G, 0.0);

	// adding n nodes to graph
	for (int i = 0; i < n; i++) {
		G.newNode();
	}

	// setting random weights for nodes
	for (node v : G.nodes) {
		weight[v] = dist(rng);
	}

	// using exponential distribution to generate random points
	for (node v : G.nodes) {
		for (int i = 0; i < dimension; i++){
			cord[v][i] = distribution(generator);
		}
	}

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = 0.0;
			for (int i = 0; i < dimension; i++) {
				distance += (cord[v][i] - cord[w][i])*(cord[v][i] - cord[w][i]);
			}
			distance = sqrt(distance);

			if ((weight(v) + weight(w)) > (theta*pow(distance,alpha))) {
				G.newEdge(v, w);
			}
		}
	}

}

int main(){
	//! TODO: tests
	//! TODO: user specified weights version of geographicalThresholdGraph
	Graph G;
	randomGeographicalThresholdGraph(G, 100, 2, 2, 4);
	std::cout << G.numberOfEdges() << endl;

	return 0;
}
