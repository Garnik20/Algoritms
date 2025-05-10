#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// === Edge definition ===
template <typename VertexT, typename WeightT = size_t>
struct Edge {
 public:
  using VertexType = VertexT;
  using WeightType = WeightT;
  Edge(VertexT from, VertexT to, WeightT weight = 1)
      : vertices_(from, to), weight_(weight) {}

  VertexT GetStart() const { return vertices_.first; }
  VertexT GetTarget() const { return vertices_.second; }
  WeightT GetWeight() const { return weight_; }

  bool operator<(const Edge& other) const { return weight_ < other.weight_; }

 private:
  std::pair<VertexT, VertexT> vertices_;
  WeightT weight_;
};

// === DSU (Disjoint Set Union) ===
template <typename VertexType>
class Dsu {
 public:
  explicit Dsu(size_t size) : parent_(size), rank_(size, 0) {
    for (size_t i = 0; i < size; ++i) {
      parent_[i] = static_cast<VertexType>(i);
    }
  }

  VertexType FindSet(VertexType vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet(parent_[vertex]);
  }

  void UnionSets(VertexType first, VertexType second) {
    first = FindSet(first);
    second = FindSet(second);
    if (first != second) {
      if (rank_[first] < rank_[second]) {
        std::swap(first, second);
      }
      parent_[second] = first;
      if (rank_[first] == rank_[second]) {
        ++rank_[first];
      }
    }
  }

 private:
  std::vector<VertexType> parent_;
  std::vector<int> rank_;
};

// === Graph interface ===
template <typename VertexType, template <typename> class EdgeTemplate>
class IGraph {
 public:
  using VertexT = VertexType;
  using EdgeT = EdgeTemplate<VertexType>;
  using WeightT = typename EdgeT::WeightType;

  virtual size_t GetVertexCount() const = 0;
  virtual size_t GetEdgeCount() const = 0;
  virtual std::vector<EdgeT> GetAllEdges() const = 0;
  virtual ~IGraph() = default;
};

// === Graph implementation ===
template <typename VertexType, template <typename> class EdgeTemplate>
class EdgeListGraph : public IGraph<VertexType, EdgeTemplate> {
 public:
  using EdgeT = typename IGraph<VertexType, EdgeTemplate>::EdgeT;

  explicit EdgeListGraph(size_t vertex_count) : vertex_count_(vertex_count) {}

  void AddEdge(const EdgeT& edge) { edges_.push_back(edge); }

  size_t GetVertexCount() const override { return vertex_count_; }

  size_t GetEdgeCount() const override { return edges_.size(); }

  std::vector<EdgeT> GetAllEdges() const override { return edges_; }

 private:
  size_t vertex_count_;
  std::vector<EdgeT> edges_;
};

// === Kruskal's Algorithm ===
template <typename Graph>
int64_t Kruskal(const Graph& graph) {
  using EdgeType = typename Graph::EdgeT;
  using VertexType = typename Graph::VertexT;

  std::vector<EdgeType> edges = graph.GetAllEdges();
  std::sort(edges.begin(), edges.end());

  Dsu<VertexType> dsu(graph.GetVertexCount());
  int64_t total_weight = 0;

  for (const auto& edge : edges) {
    if (dsu.FindSet(edge.GetStart()) != dsu.FindSet(edge.GetTarget())) {
      total_weight += edge.GetWeight();
      dsu.UnionSets(edge.GetStart(), edge.GetTarget());
    }
  }

  return total_weight;
}

template <typename Graph>
void Input(Graph& graph, size_t edge_count) {
  using EdgeType = typename Graph::EdgeT;
  using VertexType = typename EdgeType::VertexType;
  using WeightType = typename Graph::WeightT;

  for (size_t count = 0; count < edge_count; ++count) {
    VertexType u_vert;
    VertexType v_vert;
    WeightType w_vert;
    std::cin >> u_vert >> v_vert >> w_vert;
    graph.AddEdge(EdgeType{u_vert - 1, v_vert - 1, w_vert});
  }
}

// === Main ===
int main() {
  using Vertex = int32_t;
  using Weight = int64_t;
  template <typename T>
  using EdgeTemplate = Edge<T, Weight>;
  using Graph = EdgeListGraph<Vertex, EdgeTemplate>;

  size_t count;
  size_t edge_count;
  std::cin >> count >> edge_count;
  Graph graph(count);

  Input(graph, edge_count);

  int64_t result = Kruskal(graph);
  std::cout << result << '\n';
  return 0;
}