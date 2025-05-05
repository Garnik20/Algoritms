#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// === Edge definition ===
template <typename VertexT, typename WeightT = size_t>
struct Edge {
 public:
  using WeightType = WeightT;
  Edge(const VertexT& from, const VertexT& to, WeightT weight = 1)
      : vertices_(from, to), weight_(weight) {}

  const VertexT& GetStart() const { return vertices_.first; }
  const VertexT& GetTarget() const { return vertices_.second; }
  WeightT GetWeight() const { return weight_; }

  bool operator<(const Edge& other) const { return weight_ < other.weight_; }

 private:
  std::pair<VertexT, VertexT> vertices_;
  WeightT weight_;
};

// === DSU (Disjoint Set Union) ===
template <typename VertexType>
class DSU {
 public:
  DSU(size_t size) : parent(size), rank(size, 0) {
    for (size_t i = 0; i < size; ++i) {
      parent[i] = i;
    }
  }

  VertexType find_set(VertexType v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(VertexType a, VertexType b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (rank[a] < rank[b]) std::swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b]) ++rank[a];
    }
  }

 private:
  std::vector<VertexType> parent;
  std::vector<int> rank;
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

  void AddEdge(const EdgeType& edge) { edges_.push_back(edge); }

  size_t GetVertexCount() const override { return vertex_count_; }

  size_t GetEdgeCount() const override { return edges_.size(); }

  std::vector<EdgeType> GetAllEdges() const override { return edges_; }

 private:
  size_t vertex_count_;
  std::vector<EdgeType> edges_;
};

// === Kruskal's Algorithm ===
template <typename Graph>
int64_t Kruskal(const Graph& graph) {
  using EdgeType = typename Graph::EdgeType;
  using VertexType = decltype(std::declval<EdgeType>().GetStart());

  std::vector<EdgeType> edges = graph.GetAllEdges();
  std::sort(edges.begin(), edges.end());

  DSU<VertexType> dsu(graph.GetVertexCount());
  int64_t total_weight = 0;

  for (const auto& edge : edges) {
    if (dsu.find_set(edge.GetStart()) != dsu.find_set(edge.GetTarget())) {
      total_weight += edge.GetWeight();
      dsu.union_sets(edge.GetStart(), edge.GetTarget());
    }
  }

  return total_weight;
}

template <typename Graph>
void Input(Graph& graph, size_t edge_count) {
  using EdgeType = typename Graph::EdgeType;
  using VertexType = decltype(std::declval<EdgeType>().GetStart());
  
  for (size_t count = 0; count < edge_count; ++count) {
    VertexType u_vert;
    VertexType v_vert;
    typename EdgeType::WeightType w_vert;
    std::cin >> u_vert >> v_vert >> w_vert;
    graph.AddEdge(EdgeType{u_vert - 1, v_vert - 1, w_vert});
  }
}

// === Main ===
int main() {
  using Vertex = int32_t;
  using Weight = int64_t;
  using E = Edge<Vertex, Weight>;
  using Graph = EdgeListGraph<Vertex, E>;

  size_t count;
  size_t edge_count;
  std::cin >> count >> edge_count;
  Graph graph(count);

  Input(graph, edge_count);

  int64_t result = Kruskal(graph);
  std::cout << result << '\n';
  return 0;
}