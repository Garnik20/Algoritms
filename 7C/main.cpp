#include <algorithm>
#include <functional>
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
  EdgeListGraph(size_t vertex_count) : vertex_count_(vertex_count) {}

  void AddEdge(const EdgeType &edge) { edges_.push_back(edge); }

  size_t GetVertexCount() const override { return vertex_count_; }

  size_t GetEdgeCount() const override { return edges_.size(); }

  std::vector<EdgeType> GetAllEdges() const override { return edges_; }

 private:
  size_t vertex_count_;
  std::vector<EdgeType> edges_;
};

// === Kruskal's Algorithm ===
template <typename VertexType, typename EdgeType>
int64_t Kruskal(const IGraph<VertexType, EdgeType> &graph) {
  std::vector<EdgeType> edges = graph.GetAllEdges();
  std::sort(edges.begin(), edges.end());

  std::vector<VertexType> parent(graph.GetVertexCount());
  std::vector<int> rank(graph.GetVertexCount(), 0);

  for (VertexType vert = 0; vert < graph.GetVertexCount(); ++vert) {
    parent[vert] = vert;
  }

  std::function<VertexType(VertexType)> find_set;

  find_set = [&](VertexType vert) -> VertexType {
    if (vert == parent[vert]) {
      return vert;
    }
    return parent[vert] = find_set(parent[vert]);
  };

  auto union_sets = [&](VertexType vert_a, VertexType vert_b) {
    vert_a = find_set(vert_a);
    vert_b = find_set(vert_b);
    if (vert_a != vert_b) {
      if (rank[vert_a] < rank[vert_b]) {
        std::swap(vert_a, vert_b);
      }
      parent[vert_b] = vert_a;
      if (rank[vert_a] == rank[vert_b]) {
        rank[vert_a]++;
      }
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
void Input(EdgeListGraph<VertexType, EdgeType>& graph, size_t edge_count) {
  
  
  for (size_t count = 0; count < edge_count; ++count) {
    VertexType u_vert;
    VertexType v_vert;
    VertexType w_vert;
    std::cin >> u_vert >> v_vert >> w_vert;
    graph.AddEdge(EdgeType{u_vert - 1, v_vert - 1, w_vert}); // 0-indexed
  }
}

// === Main ===
int main() {
  using Vertex = int32_t;
  using E = Edge<Vertex>;
  size_t count;
  size_t edge_count;
  std::cin >> count >> edge_count;
  EdgeListGraph<Vertex, E> graph(count);

  Input(graph, edge_count);

  int64_t result = Kruskal(graph);
  std::cout << result << '\n';
  return 0;
}
