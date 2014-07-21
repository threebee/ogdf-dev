/**
 * B. Bollobás, A probabilistic proof of an asymptotic formula for the number
 * of labelled regular graphs. European J. Combin. 1 (1980), no. 4, 311-316.
 *
 * Algorithm for Pairing Model:
 * 1. Begin with a set of n vertices.
 * 2. Create a new set of nk points, distributing them across n buckets,
 *	  such that each bucket contains k points.
 * 3. Take each point and pair it randomly with another one,
 *    until ½nk pairs are obtained (i.e., a perfect matching).
 * 4. Collapse the points, so that each bucket (and thus the points it contains)
 *    maps onto a single vertex of the original graph. Retain all edges between
 *    points as the edges of the corresponding vertices.
 * 5. Check if the resulting graph is simple. That is to say, make sure that none
 *    of the vertices have loops (i.e., self-connections) or multiple edges 
 *    (i.e., more than one connection to the same vertex). If the graph is not
 *    simple, restart.
 */

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <algorithm>

#include <ogdf/basic/Graph.h> 
#include <ogdf/basic/NodeArray.h>
#include <ogdf/basic/geometry.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>

using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a Random Regular Graph. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes 
 * @param k is number of points in each bucket.
 */
void randomRegularGraphI(Graph &G, int n, int k) {
	OGDF_ASSERT(n >= 0);
	OGDF_ASSERT(n*k % 2 == 0);

	G.clear();

	Array<node> vis(n);

	for (int i = 0; i < n; i++) {
		vis[i] = G.newNode();
	}

	Array<int> nodeMapper(n*k);
	Array<bool> paired(n*k);

	for (int points = 0; points < n*k; points++) {
		nodeMapper[points] = (int)floor(points / k);
		paired[points] = false;
	}

	for (int i = 0; i < n*k;) {
		int u, v;
		u = nodeMapper[i];

		while (paired[i]) {
			i++;
			if (!(i < n*k)) break;
			u = nodeMapper[i];
		}

		if (!(i < n*k)) break;

		int value = (rand() % (n*k - i + 1)) + i;

		v = nodeMapper[value];
		while (paired[value]) {
			value = (rand() % (n*k - i + 1)) + i;
			v = nodeMapper[value];
		}

		paired[i] = true;
		paired[value] = true;

		G.newEdge(vis[u], vis[v]);
	}
}

void randomRegularGraph(Graph &G, int n, int k) {
	//! Due to point 5 in algorithm this might take forever :P
	do {
		randomRegularGraphI(G, n, k);
	} while (!isSimple(G));
}


int main(){

	//! TODO: tests
	Graph G;
	randomRegularGraph(G, 7, 4);
	std::cout << G.numberOfEdges() << endl;
	
	return 0;
}
