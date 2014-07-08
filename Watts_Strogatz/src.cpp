/**
 * Collective dynamics of 'small-world' networks
 * Duncan J. Watts & Steven H. Strogatz
 *
 * Link: http://labs.yahoo.com/files/w_s_NATURE_0.pdf
 *
 * Watts-Strogatz Model
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

//! Creates a Watts-Strogatz Graph. 
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes 
 * @param d is the minimum degree.
 * @param probability is probability of rewiring
 */
void randomWattsStrogatzGraph(Graph &G, int n, int k, double probability) {
	
	//! Atleast 3 nodes are required to make a ring
	OGDF_ASSERT(n > 2);
	OGDF_ASSERT(0 <= k && k <= n/2);
	OGDF_ASSERT(0 < probability + std::numeric_limits<double>::epsilon() && probability < 1);
	G.clear();

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	Array<node> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = G.newNode();
	}

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= k; j++) {
			
			//! maping -x to n-x
			int t = ((i - j) % n) < 0 ? (n + ((i - j) % n)) : ((i - j) % n);
				 
			//! no new edge exist between (v, w) and v!=w then make a edge between them
			if (G.searchEdge(v[i], v[t]) == nullptr && v[i] != v[t]) {
				G.newEdge(v[i], v[t]);
			}

			if (G.searchEdge(v[i], v[(i + j) % n]) == nullptr && v[i] != v[(i + j) % n]) {
				G.newEdge(v[i], v[(i + j) % n]);
			}
		}
	}

	edge f;
	for (edge e = G.firstEdge(); e; e = f) {
		f = e->succ();
		node u = e->source();
		node v = G.chooseNode();

		//! Choose a node until u != v
		while (u == v) {
			v = G.chooseNode();
		}
		
		//! If there already exists edge between (u, v) ignore and continue
		if (G.searchEdge(u, v) == nullptr) {
			continue;
		}
		else {
			if (dist(rng) < (probability + std::numeric_limits<double>::epsilon())) {
				G.delEdge(e);
				G.newEdge(u, v);
			}
		}
	}
}

int main(){
	//! TODO: tests
	Graph G;
	randomWattsStrogatzGraph(G, 100, 15, 0.5);
	std::cout << G.numberOfEdges() << endl;

	return 0;
}
