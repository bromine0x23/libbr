#include "../test.hpp"
#include <libbr/container.hpp>

using namespace BR;

/*
 * run dijkstra on graph:
 *            v
 *    | 0| 1| 2| 3| 4|
 *   0|  |10| 5|  |  |
 *   1|  |  | 2| 1|  |
 * u 2|  | 3|  | 9| 2|
 *   3|  |  |  |  | 4|
 *   4| 7|  |  | 6|  |
 *
 * expected result:
 *           u
 *   | 0| 1| 2| 3| 4|
 * d | 0| 8| 5| 9| 7|
 */
TEST(Container, Dijkstra) {
	List< Tuple<int, int> > edges[5];
	edges[0].emplace_back(1, 10);
	edges[0].emplace_back(2, 5);
	edges[1].emplace_back(2, 2);
	edges[1].emplace_back(3, 1);
	edges[2].emplace_back(1, 3);
	edges[2].emplace_back(3, 9);
	edges[2].emplace_back(4, 2);
	edges[3].emplace_back(4, 4);
	edges[4].emplace_back(0, 7);
	edges[4].emplace_back(3, 6);

	int dist[5];
	for (int & d : dist) {
		d = 0x7FFFFFFF;
	}
	auto dijkstra_compare = [&dist](int lhs, int rhs) {
		return dist[lhs] < dist[rhs] || (dist[lhs] == dist[rhs] && lhs < rhs);
	};

	int source = 0;
	dist[source] = 0;
	TreeSet<int, decltype(dijkstra_compare)> queue({0, 1, 2, 3, 4}, dijkstra_compare);
	for (; !queue.empty();) {
		int u = *queue.begin();
		queue.erase(u);
		for (auto & edge : edges[u]) {
			int v = edge.get<0>();
			int w = edge.get<1>();
			if (dist[u] + w < dist[v]) {
				queue.erase(v);
				dist[v] = dist[u] + w;
				queue.insert(v);
			}
		}
	}

	EXPECT_EQ(0, dist[0]);
	EXPECT_EQ(8, dist[1]);
	EXPECT_EQ(5, dist[2]);
	EXPECT_EQ(9, dist[3]);
	EXPECT_EQ(7, dist[4]);
}