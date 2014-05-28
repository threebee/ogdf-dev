/**
 * The average distances in random graphs with given expected degrees
 * Link: http://www.pnas.org/content/99/25/15879.short
 *
 * The Similarity between Stochastic Kronecker and Chung-Lu Graph Models
 * Link: http://arxiv.org/pdf/1110.4925.pdf
 *
 * Chung Lu Graph
 * Consider Graph G (n, W) with n vertices and degree sequence W = (W1, W2, ..., Wn) >= 0
 * In this model, an edge between two vertices i and j is independently present with probability
 * P (i, j) = min ((WiWj/ summation (Wk)), 1)
 *
 */

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include <ogdf/basic/Graph.h> 
#include <ogdf/basic/NodeArray.h>
#include <ogdf/basic/geometry.h>

using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a ChungLu Graph.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param weights is degree sequence of Graph.
 */
void chungLuGraph(Graph &G, int n, Array<int> &weights) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	int Wk = 0;

	// adding n nodes to graph and summing degree sequence
	for (int i = 0; i < n; i++){
		G.newNode();
		Wk += weights[i];
	}

	int i, j;
	node v, w;
	for (i = 0, v = G.firstNode(); v; v = v->succ(), i++) {
		for (j = 0, w = v->succ(); w; w = w->succ(), j++) {
			double probability = std::min((weights[i] * weights[j]) / (double)Wk, 1.0);
			if (dist(rng) < (probability + std::numeric_limits<double>::epsilon())) {
				G.newEdge(v, w);
			}
		}
	}

}

//! Creates a ChungLu Graph with random degree sequence.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 */
void chungLuRandomWeightsGraph(Graph &G, int n) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	NodeArray<double> weights(G, 0.0);
	double Wk = 0.0;
	
	// adding n nodes to graph
	for (int i = 0; i < n; i++){
		G.newNode();
	}

	// summing degree sequence
	for (node v : G.nodes) {
		weights[v] = dist(rng);
		Wk += weights[v];
	}
	
	for (node v: G.nodes) {
		for (node  w = v->succ(); w; w = w->succ()) {
			double probability = std::min((weights[v] * weights[w] / Wk), 1.0);
			if (dist(rng) < (probability + std::numeric_limits<double>::epsilon())) {
				G.newEdge(v, w);
			}
		}
	}

}


int main(){
	//! TODO: tests
	Graph G;
	chungLuRandomWeightsGraph(G, 100);

	Array<int> weights(0, 10);
	for (int &x : weights) {
		x = 4;
	}

	chungLuGraph(G, 10, weights);

	return 0;
}
