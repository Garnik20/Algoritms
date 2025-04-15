#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// === Edge definition ===
template <typename VertexType>
struct Edge {
  VertexType from;
  VertexType to;
  int weight;

  int GetWeight() const { return weight; }

  bool operator<(const Edge &other) const { return weight < other.weight; }
};

// === Graph interface ===
template <typename VertexType, typename EdgeType>
class IGraph {
 public:
  virtual size_t GetVertexCount() const = 0;
  virtual size_t GetEdgeCount() const = 0;
  virtual std::vector<EdgeType> GetAllEdges() const = 0;
  virtual ~IGraph() = default;
};

// === Graph implementation (for Kruskal) ===
template <typename VertexType, typename EdgeType>
class EdgeListGraph : public IGraph<VertexType, EdgeType> {
 public:
  EdgeListGraph(size_t vertex_count) : vertex_count(vertex_count) {}

  void AddEdge(const EdgeType &edge) { edges.push_back(edge); }

  size_t GetVertexCount() const override { return vertex_count; }

  size_t GetEdgeCount() const override { return edges.size(); }

  std::vector<EdgeType> GetAllEdges() const override { return edges; }

 private:
  size_t vertex_count;
  std::vector<EdgeType> edges;
};

// === Kruskal's Algorithm ===
template <typename VertexType, typename EdgeType>
int64_t Kruskal(const IGraph<VertexType, EdgeType> &graph) {
  std::vector<EdgeType> edges = graph.GetAllEdges();
  std::sort(edges.begin(), edges.end());

  std::vector<VertexType> parent(graph.GetVertexCount());
  std::vector<int> rank(graph.GetVertexCount(), 0);

  for (VertexType v = 0; v < graph.GetVertexCount(); ++v)
    parent[v] = v;

  auto find_set = [&](VertexType v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  };

  auto union_sets = [&](VertexType a, VertexType b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (rank[a] < rank[b])
        std::swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b])
        rank[a]++;
    }
  };

  int64_t total_weight = 0;
  for (const auto &edge : edges) {
    if (find_set(edge.from) != find_set(edge.to)) {
      total_weight += edge.GetWeight();
      union_sets(edge.from, edge.to);
    }
  }

  return total_weight;
}

template <typename VertexType, typename EdgeType>
void Input(EdgeListGraph<VertexType, EdgeType>& graph, size_t m) {
  
  
  for (size_t i = 0; i < m; ++i) {
    VertexType u, v, w;
    std::cin >> u >> v >> w;
    graph.AddEdge(EdgeType{u - 1, v - 1, w}); // 0-indexed
  }
}

// === Main ===
int main() {
  using Vertex = int32_t;
  using E = Edge<Vertex>;
  size_t n, m;
  std::cin >> n >> m;
  EdgeListGraph<Vertex, E> graph(n);

  Input(graph, m);

  int64_t result = Kruskal(graph);
  std::cout << result << '\n';
  return 0;
}
