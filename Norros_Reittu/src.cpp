/**
 * On a conditionally Poissonean graph process
 * Link: http://citeseerx.ist.psu.edu/showciting?cid=233780  
 *
 * Norros-Reittu graph
 * Consider Graph G (n, W) with n vertices and degree sequence W = (W1, W2, ..., Wn) >= 0
 * In this model, an edge between two vertices i and j is independently present with probability
 *             P (i, j) = 1 – exp (-WiWj/ summation (Wk))
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

//! Creates a Norros-Reittu Graph. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param weights is degree sequence of Graph.
 */
void norrosReittuGraph(Graph &G, int n, Array<int> &weights) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	int Wk = 0;

	// adding n nodes to graph and summing degree sequence
	for (int i = 0; i < n; i++) {
		G.newNode();
		Wk += weights[i];
	}

	int i, j;
	node v, w;
	for (i = 0, v = G.firstNode(); v; v = v->succ(), i++) {
		for (j = 0, w = v->succ(); w; w = w->succ(), j++) {
			double probability = 1.0 - exp(-(weights[i] * weights[j]) / (double)Wk);
			if (dist(rng) < (probability + std::numeric_limits<double>::epsilon())) {
				G.newEdge(v, w);
			}
		}
	}

}

//! Creates a Norros-Reittu Graph with random degree sequence. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 */
void norrosReittuRandomWeightsGraph(Graph &G, int n) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	NodeArray<double> weights(G, 0.0);
	double Wk = 0.0;

	// adding n nodes to graph
	for (int i = 0; i < n; i++) {
		G.newNode();
	}

	// summing degree sequence
	for (node v : G.nodes) {
		weights[v] = dist(rng);
		Wk += weights[v];
	}

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double probability = 1.0 - exp(-(weights[v] * weights[w]) / Wk);
			if (dist(rng) <= (probability + std::numeric_limits<double>::epsilon())) {
				G.newEdge(v, w);
			}
		}
	}

}


int main(){
	//! TODO: tests
	Graph G;
	norrosReittuRandomWeightsGraph(G, 100);

	Array<int> weights(0, 10);
	for (int &x : weights) {
		x = 4;
	}

	norrosReittuGraph(G, 10, weights);

	return 0;
}
