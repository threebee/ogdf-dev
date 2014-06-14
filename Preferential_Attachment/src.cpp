/**
 * Emergence of Scaling in Random Networks
 * Albert-Laszlo Barabasi and Reka Albert
 *
 * Preferential Attachment Graph
 * Related Text:
 * Starting with a small number (m0) of vertices, at every time step we add a new
 * vertex with m(<= m0) edges that link the new vertex to m different vertices
 * already present in the system. To incorporate preferential attachment, we
 * assume that the probability that a new vertex will be connected to vertex i
 * depends on the connectivity k_i of that vertex, so that
 *         P(k_i) = k_i/ summation(K_j)
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

//! Creates a Preferential Attachment Graph. 
/**
* @param G is assigned the generated graph.
* @param n is the number of nodes to be added to graph.
* @param m is the minimum degree of new node.
*/
void preferentialAttachmentGraph(Graph &G, int n, int d) {
	OGDF_ASSERT(1 <= d && d <= G.numberOfNodes());

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	for (int i = 0; i < n; i++) {
		node w = G.newNode();
		while (w->degree() < d) {
			node v = G.chooseNode();
			if (v != w && G.searchEdge(w,v) == nullptr) {
				double probability = (v->degree() / (double)(2 * G.numberOfEdges()));
				if (dist(rng) < (probability + std::numeric_limits<double>::epsilon())) {
					G.newEdge(v, w);
				}
			}
		}
	}
}

int main(){
	//! TODO: tests
	Graph G;
	node x = G.newNode();
	node y = G.newNode();
	G.newEdge(x, y);
	preferentialAttachmentGraph(G, 100, 2);
	std::cout << G.numberOfEdges() << endl;

	return 0;
}
