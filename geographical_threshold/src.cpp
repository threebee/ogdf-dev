/**
 * Giant Component and Connectivity in Geographical Threshold Graphs
 * Milan Bradonjic, Aric Hagberg, andAllon G. Percus
 *
 * Geographical-threshold graph
 * Related text:
 * The Geographical Threshold Graph model is constructed from of a set of n 
 * nodes placed independently in R^d  according to a Poisson point-wise
 * process. A non-negative weight w_i, taken randomly and independently from
 * a probability distribution function f(w):R+ -> R+, is assigned to each node
 * v_i for i belong [n]. Let F(x) = integration(0, x)(f(w)) dw be the
 * cumulative density function. For two nodes i and j at distance r, the
 * edge (i, j) exists if and only if the following connectivity relation is
 * satisfied: G(w_i, w_j)h(r) ≥ θ_n, where θ_n is a given threshold parameter
 * that depends on the size of the network. The function h(r) is assumed to be
 * decreasing in r. We use h(r) = r^(−α), for some positive α.
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
 * @param lambda is the exponential distribution
 * @param dimension is the dimension of nodes to layed out.
 */
void randomGeographicalThresholdGraph(Graph &G, int n, double alpha, double theta, double lambda = 1.0, int dimension = 2) {
	OGDF_ASSERT(n >= 0);
	OGDF_ASSERT(alpha > 0 && theta > 0 && lambda > 0);
	
	G.clear();
	if (n == 0) return;

	// exponential generator for laying out points
	default_random_engine generator;
	exponential_distribution<double> distribution(lambda);

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

			if ((weight(v) + weight(w)) > (theta*pow(distance, alpha))) {
				G.newEdge(v, w);
			}
		}
	}

}


//! Creates a Geographical Threshold Graph with given weights. 
/**
 * @param G is assigned the generated graph.
 * @param weights is array of weight assigned to nodes.
 * @param alpha is the model parameter.
 * @param theta is the threshold parameter.
 * @param lambda is the exponential distribution
 * @param dimension is the dimension of nodes to layed out.
 */
void randomGeographicalThresholdWeightsGraph(Graph &G, Array<int> &weights, double alpha, double theta, double lambda = 1.0, int dimension = 2) {
	OGDF_ASSERT(alpha > 0 && theta > 0 && lambda > 0);

	G.clear();
	if (weights.size() == 0) return;

	// exponential generator for laying out points
	default_random_engine generator;
	exponential_distribution<double> distribution(lambda);

	// uniform generator for assigning weights
	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	NodeArray<Array<double>> cord(G, Array<double>(dimension));
	double maxWeight = 0.0;

	// adding n nodes to graph and calculating max weight
	for (int i = 0; i < weights.size(); i++) {
		G.newNode();
		if (maxWeight > weights[i]) {
			maxWeight = weights[i];
		}
	}

	// using exponential distribution to generate random points
	for (node v : G.nodes) {
		for (int i = 0; i < dimension; i++){
			cord[v][i] = distribution(generator);
		}
	}

	int i, j;
	node v, w;
	for (i = 0, v = G.firstNode(); v; v = v->succ(), i++) {
		for (j = i + 1, w = v->succ(); w; w = w->succ(), j++) {
			double distance = 0.0;
			for (int k = 0; k < dimension; k++) {
				distance += (cord[v][k] - cord[w][k])*(cord[v][k] - cord[w][k]);
			}
			distance = sqrt(distance);

			if ((weights[i]/maxWeight + weights[j]/maxWeight) > theta*pow(distance, alpha)) {
				G.newEdge(v, w);
			}
		}
	}

}

int main(){
	//! TODO: tests
	Graph G;
	randomGeographicalThresholdGraph(G, 10, 2, 2, 4);

	Array<int> weights(0, 4);
	for (int &x : weights) {
		x = 4;
	}

	G.clear();
	randomGeographicalThresholdWeightsGraph(G, weights, 2, 2, 4);

	return 0;
}
