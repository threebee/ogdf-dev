#include "bandit/bandit.h"
#include "ogdf/basic/Graph.h"
#include "ogdf/basic/graph_generators.h"
#include "ogdf/basic/simple_graph_alg.h"

using namespace ogdf;
using namespace bandit;

go_bandit([](){
	describe("randomWaxmanGraphUsingPlane", [&](){
		for(int n = 1; n < 100; n++) {
			it(string("generates a graph with " + to_string(n) + " nodes").c_str(), [&](){
				Graph G;
				randomWaxmanGraphUsingPlane(G, n, 0.5, 0.5);
				AssertThat(G.numberOfNodes(), Equals(n));
				G.clear();
				randomWaxmanGraphUsingPlane(G, n, 0.0, 0.5);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingPlane(G, n, 0.5, 0.0);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingPlane(G, n, -0.5, 0.5);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingPlane(G, n, 0.5, 1.1);
				AssertThat(G.numberOfNodes(), Equals(0));
			});
		}
	});

	describe("randomWaxmanGraphUsingGrid", [&](){
		for(int n = 1; n < 100; n++) {
			it(string("generates a graph with " + to_string(n) + " nodes").c_str(), [&](){
				Graph G;
				randomWaxmanGraphUsingGrid(G, n, 0.5, 0.5, 10, 10);
				AssertThat(G.numberOfNodes(), Equals(n));
				G.clear();
				randomWaxmanGraphUsingGrid(G, n, 0.0, 0.5, 10, 10);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingGrid(G, n, 0.5, 0.0, 10, 10);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingGrid(G, n, -0.5, 0.5, 10, 10);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphUsingGrid(G, n, 0.5, 1.1, 10, 10);
				AssertThat(G.numberOfNodes(), Equals(0));
			});
		}
	});

	describe("randomWaxmanGraph", [&](){
		for(int n = 1; n < 100; n++) {
			it(string("generates a graph with " + to_string(n) + " nodes").c_str(), [&](){
				Graph G;
				randomWaxmanGraph(G, n, 0.5, 0.5);
				AssertThat(G.numberOfNodes(), Equals(n));
				G.clear();
				randomWaxmanGraph(G, n, 0.0, 0.5);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraph(G, n, 0.5, 0.0);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraph(G, n, -0.5, 0.5);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraph(G, n, 0.5, 1.1);
				AssertThat(G.numberOfNodes(), Equals(0));
			});
		}
	});

	describe("randomWaxmanGraphIntegral", [&](){
		for(int n = 1; n < 100; n++) {
			it(string("generates a graph with " + to_string(n) + " nodes").c_str(), [&](){
				Graph G;
				randomWaxmanGraphIntegral(G, n, 0.5, 0.5, L);
				AssertThat(G.numberOfNodes(), Equals(n));
				G.clear();
				randomWaxmanGraphIntegral(G, n, 0.0, 0.5, L);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphIntegral(G, n, 0.5, 0.0, L);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphIntegral(G, n, -0.5, 0.5, L);
				AssertThat(G.numberOfNodes(), Equals(0));
				G.clear();
				randomWaxmanGraphIntegral(G, n, 0.5, 1.1, L);
				AssertThat(G.numberOfNodes(), Equals(0));
			});
		}
	});
});
