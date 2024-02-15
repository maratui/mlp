#ifndef CPP7_MLP_MODEL_GRAPH_NETWORK_H_
#define CPP7_MLP_MODEL_GRAPH_NETWORK_H_

#include "graph_layer.h"
#include "network.h"

namespace s21 {
class GraphNetwork : public Network {
 public:
  void ActivateNetwork(unsigned inputs_count,
                       unsigned hidden_layers_count) override;

  void GetNetwork(
      std::vector<std::vector<std::vector<double>>> &perceptron_edge_weights,
      std::vector<std::vector<double>> &perceptron_node_biases) override;
  void SetNetwork(const std::vector<std::vector<std::vector<double>>>
                      &perceptron_edge_weights,
                  const std::vector<std::vector<double>>
                      &perceptron_node_biases) noexcept override;

 protected:
  const std::list<GraphLayer> &GetLayers() const noexcept;

 private:
  void CalculateLayersOutputValues() noexcept override;
  void CalculateOutputLayerErrorValues(
      unsigned emnist_letter_number) noexcept override;
  void CalculateHiddenLayersErrorValues() noexcept override;
  void ModifyNetworkDeltas() noexcept override;
  void ModifyNetwork() noexcept override;
  bool IsEmptyNetwork() noexcept override;
  std::vector<double> &GetBackNodesOutputValues() override;

  std::list<GraphLayer> layers_;
};
}  // namespace s21

#endif  // CPP7_MLP_MODEL_GRAPH_NETWORK_H_
