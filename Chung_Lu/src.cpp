/*
* Chung-Lu graph
*
* Consider Graph G (n, W) with n vertices and weights W = (W1, W2, ..., Wn) >= 0
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

using std::cout;
using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a ChungLu Graph. 
/**
* @param G is assigned the generated graph.
* @param n is the number of nodes of the generated graph.
* @param weights is Array of weight of each node.
*/
void ChungLu(Graph &G, int n, Array<double> &weights) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	Array<node> v(n);
	double Wk = 0.0;

	for (int i = 0; i < n; i++) {
		v[i] = G.newNode();
		Wk += weights[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double p = std::min((weights[i] * weights[j] / Wk), 1.0);
			if (dist(rng) <= p) {
				G.newEdge(v[i], v[j]);
			}
		}
	}

}

//! Creates a ChungLu Graph with random weights. 
/**
* @param G is assigned the generated graph.
* @param n is the number of nodes of the generated graph.
*/
void ChungLuRandomWeights(Graph &G, int n) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	Array<node> v(n);
	NodeArray<double> weights(G, 0.0);
	double Wk = 0.0;

	for (int i = 0; i < n; i++) {
		v[i] = G.newNode();
		weights[i] = dist(rng);
		Wk += weights[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double p = std::min((weights[i] * weights[j] / Wk), 1.0);
			if (dist(rng) <= p) {
				G.newEdge(v[i], v[j]);
			}
		}
	}

}


int main(){
	//! TODO: tests
	Graph G;
	ChungLuRandomWeights(G, 100);

	Array<double> weights(0, 10);
	for (double &x : weights) {
		x = 4.0;
	}

	ChungLu(G, 10, weights);

	return 0;
}
/*
* Chung-Lu graph
*
* Consider Graph G (n, W) with n vertices and weights W = (W1, W2, ..., Wn) >= 0
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

using std::cout;
using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a ChungLu Graph. 
/**
* @param G is assigned the generated graph.
* @param n is the number of nodes of the generated graph.
* @param weights is Array of weight of each node.
*/
void ChungLu(Graph &G, int n, Array<double> &weights) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	Array<node> v(n);
	double Wk = 0.0;

	for (int i = 0; i < n; i++) {
		v[i] = G.newNode();
		Wk += weights[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double p = std::min((weights[i] * weights[j] / Wk), 1.0);
			if (dist(rng) <= p) {
				G.newEdge(v[i], v[j]);
			}
		}
	}

}

//! Creates a ChungLu Graph. 
/**
* @param G is assigned the generated graph.
* @param n is the number of nodes of the generated graph.
*/
void ChungLuRandomWeights(Graph &G, int n) {
	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	Array<node> v(n);
	NodeArray<double> weights(G, 0.0);
	double Wk = 0.0;

	for (int i = 0; i < n; i++) {
		v[i] = G.newNode();
		weights[i] = dist(rng);
		Wk += weights[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double p = std::min((weights[i] * weights[j] / Wk), 1.0);
			if (dist(rng) <= p) {
				G.newEdge(v[i], v[j]);
			}
		}
	}

}


int main(){
	//! TODO: tests
	Graph G;
	ChungLuRandomWeights(G, 100);

	Array<double> weights(0, 10);
	for (double &x : weights) {
		x = 4.0;
	}

	ChungLu(G, 10, weights);

	return 0;
}
