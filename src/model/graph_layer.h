#ifndef CPP7_MLP_MODEL_GRAPH_LAYER_H_
#define CPP7_MLP_MODEL_GRAPH_LAYER_H_

#include <list>

#include "node.h"

namespace s21 {
class GraphLayer {
 public:
  GraphLayer() = delete;
  explicit GraphLayer(unsigned nodes_count, unsigned inputs_count);

  std::list<Node> &GetLayer() noexcept;

  void SetEdgeWeights(
      const std::vector<std::vector<double>> &edge_weights) noexcept;
  void SetNodeBiases(const std::vector<double> &node_biases) noexcept;

  void GetNodesOutputValues(std::vector<double> &output_values);
  void GetNodesErrorValues(std::vector<double> &error_values);
  void GetEdgeWeights(std::vector<std::vector<double>> &edge_weights);
  void GetNodeBiases(std::vector<double> &node_biases);
  unsigned GetNodesCount() const noexcept;

  void ActivateLayer(const std::vector<double> &input_values) noexcept;
  void ModifyLayerDeltas(const std::vector<double> &input_values) noexcept;
  void ModifyLayer() noexcept;

 private:
  std::list<Node> layer_;
};
}  // namespace s21

#endif  // CPP7_MLP_MODEL_GRAPH_LAYER_H_
