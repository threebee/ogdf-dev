/**
 * Efficient generation of large random networks
 * Vladimir Batagelj and Ulrik Brandes
 *
 * Bipartite Preferential Attachment Graph
 */

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include <ogdf/basic/Graph.h> 
#include <ogdf/basic/NodeArray.h>
#include <ogdf/basic/geometry.h>
#include <ogdf/basic/graph_generators.h>

using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a Bipartite Preferential Attachment Graph. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes in each of sets.
 * @param d is the minimum degree.
 */
void randomBipartitePrefrentialGraph(Graph &G, int n, int d) {
	OGDF_ASSERT(1 <= d && d <= n);
	G.clear();

	Array<int> M1(2*n*d), M2(2*n*d);
	Array<node> v(2*n*d);
	for (int i = 0; i < 2 * n*d; i++) {
		v[i] = G.newNode();
	}

	for (int i = 0; i < M1.size(); i++) {
		M1[i] = 0;
		M2[i] = 0;
	}

	for (int v = 0; v < n; v++) {
		for (int i = 0; i < d; i++) {
			M1[2 * (v*d + 1)] = v;
			M2[2 * (v*d + 1)] = n + v;

			minstd_rand rng(randomSeed());
			int x = 2 * (v*d + i) - 1;
			
			//! v = 0, i = 0 leads to x = -1 
			if (x < 0) x = 0;
			
			uniform_int_distribution<> dist(0, x);
			
			int r = dist(rng);
			
			if (r % 2 == 0)
				M1[2 * (v*d + i) + 1] = M2[r];
			else
				M1[2 * (v*d + i) + 1] = M1[r];

			r = dist(rng);

			if (r % 2 == 0)
				M2[2 * (v*d + i) + 1] = M1[r];
			else
				M2[2 * (v*d + i) + 1] = M2[r];
		}
	}

	for (int i = 0; i < n*d; i++) {
		if (M1[2 * i] != M1[2 * i + 1]) {
			G.newEdge(v[M1[2 * i]], v[M1[2 * i + 1]]);
		}

		if (M2[2 * i] != M2[2 * i + 1]) {
			G.newEdge(v[M2[2 * i]], v[M2[2 * i + 1]]);
		}
	}
}

int main(){
	//! TODO: tests
	Graph G;
	node x = G.newNode();
	node y = G.newNode();
	G.newEdge(x, y);
	randomBipartitePrefrentialGraph(G, 100, 50);
	std::cout << G.numberOfEdges() << endl;
	return 0;
}
