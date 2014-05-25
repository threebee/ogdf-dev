/*
 * Routing of Multipoint Connections, Bernard M.Waxman,
 * IEEE Journal On Selected Areas In Communications,
 * VOL. 6, NO. 9, December 1988
 *
 * Related Text :
 *
 * For the purpose of running these experiments, two simple random graph models
 * RG1 and RG2, which have some of the characteristics of an actual network,
 * were used. In RG1, n nodes are randomly distributed over a rectangular
 * coordinate grid. Each node is placed at a location with integer coordinates.
 * The Euclidean metric is then used to determine the distance between each pair
 * of nodes. In RG2, for each pair of nodes, a distance is chosen in (0, L] from
 * a uniform distribution. For both models, edges are introduced between pairs of
 * nodes u, v with a probability that dependes on the distance between them.
 * The edge probablity is given by
 *              p({ u, v }) = beta*exp(-d(u, v) / L*alpha)
 * where d(u, v) is the distance from node u to v, L is the maximum distance
 * between two nodes, and alpha and beta are parameters in the range(0, 1].
 * Larger values of beta result in graphs with higher edge densities, while
 * small values of alpha increase the densiy of short edges relative to longer
 * ones. Finally, we set the cost of an edge equal to the distance between its
 * endpoints.
 */

#include <iostream>
#include <cmath>
#include <random>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/NodeArray.h>
#include <ogdf/basic/geometry.h>

using std::minstd_rand;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using namespace ogdf;

//! Creates a Waxman graph[Model-1] by laying out nodes in a unit square.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param alpha is a parameter in the range(0, 1].
 * @param beta is a parameter in the range(0, 1].
 */
void randomWaxmanGraphUsingPlane(Graph &G, int n, double alpha, double beta) {
	OGDF_ASSERT(alpha > 0.0 && (alpha < (1.0 + std::numeric_limits<double>::epsilon())));
	OGDF_ASSERT(beta > 0.0 && (beta < (1.0 + std::numeric_limits<double>::epsilon())));

	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	NodeArray<DPoint> point(G, DPoint(0, 0));

	// setting random points in the plane
	for (node v : G.nodes) {
		point[v] = DPoint(dist(rng), dist(rng));
	}

	double maxDistance = 0.0;

	// obtaining maximum distance between points
	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = point[v].distance(point[w]);
			if (distance > maxDistance)
				maxDistance = distance;
		}
	}

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = point[v].distance(point[w]);
			double probability = alpha * exp(-distance / (beta * maxDistance));

			// connecting edges based on probability
			if (dist(rng) <= probability){
				G.newEdge(v, w);
			}
		}
	}

}

//! Creates a Waxman graph[Model-1] by laying out nodes in a user specified grid.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param alpha is a parameter in the range(0, 1].
 * @param beta is a parameter in the range(0, 1].
 * @param width is the width of the grid.
 * @param height is the height of the grid.
 */
void randomWaxmanGraphUsingGrid(Graph &G, int n, double alpha, double beta, int width, int height) {
	OGDF_ASSERT(alpha > 0.0 && (alpha < (1.0 + std::numeric_limits<double>::epsilon())));
	OGDF_ASSERT(beta > 0.0 && (beta < (1.0 + std::numeric_limits<double>::epsilon())));

	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);
	uniform_int_distribution<> distx(0, width);
	uniform_int_distribution<> disty(0, height);

	NodeArray<DPoint> point(G, DPoint(0, 0));

	// setting random points in the width*height grid.
	for (node v : G.nodes)
		point[v] = DPoint(distx(rng), disty(rng));

	double maxDistance = 0.0;

	// obtaining maximum distance between points
	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = point[v].distance(point[w]);
			if (distance > maxDistance)
				maxDistance = distance;
		}
	}

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = point[v].distance(point[w]);
			double probability = alpha * exp(-distance / (beta * maxDistance));

			// connecting edges based on probability
			if (dist(rng) <= probability) {
				G.newEdge(v, w);
			}
		}
	}

}

//! Creates a Waxman graph[Model-2] with randomly selected maxDistance.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param alpha is a parameter in the range(0, 1].
 * @param beta is a parameter in the range(0, 1].
 */
void randomWaxmanGraph(Graph &G, int n, double alpha, double beta) {
	OGDF_ASSERT(alpha > 0.0 && (alpha < (1.0 + std::numeric_limits<double>::epsilon())));
	OGDF_ASSERT(beta > 0.0 && (beta < (1.0 + std::numeric_limits<double>::epsilon())));

	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, 1);

	// randomly selecting maxDistance
	double maxDistance = dist(rng);

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) {
			double distance = dist(rng) * maxDistance;
			double probability = alpha * exp(-distance / (beta * maxDistance));

			// connecting edges based on probability
			if (dist(rng) <= probability) {
				G.newEdge(v, w);
			}
		}
	}

}

//! Creates a Waxman graph[Model-2] with user specified maxDistance.
/**
 * @param G is assigned the generated graph.
 * @param n is the number of nodes of the generated graph.
 * @param alpha is a parameter in the range(0, 1].
 * @param beta is a parameter in the range(0, 1].
 * @param maxDistance is the maximum distance between two nodes.
 */
void randomWaxmanGraphIntegral(Graph &G, int n, double alpha, double beta, double maxDistance) {
	OGDF_ASSERT(alpha > 0.0 && (alpha < (1.0 + std::numeric_limits<double>::epsilon())));
	OGDF_ASSERT(beta > 0.0 && (beta < (1.0 + std::numeric_limits<double>::epsilon())));

	G.clear();
	if (n == 0) return;

	minstd_rand rng(randomSeed());
	uniform_real_distribution<> dist(0, maxDistance);

	for (node v : G.nodes) {
		for (node w = v->succ(); w; w = w->succ()) { 
			double distance = dist(rng);
			double probability = alpha * exp(-distance / (beta * maxDistance));

			// connecting edges based on probability
			if (dist(rng) <= probability) {
				G.newEdge(v, w);
			}
		}
	}

}

int main(){
	//! TODO: tests
	Graph G;
	randomWaxmanGraphUsingPlane(G, 100, 0.5, 1.0);
	randomWaxmanGraphUsingGrid(G, 100, 0.5, 0.5, 10, 10);
	randomWaxmanGraph(G, 100, 0.5, 0.5);
	randomWaxmanGraphIntegral(G, 100, 0.5, 0.5, 10);

	return 0;
}
