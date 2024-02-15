#include "graph_network.h"

void s21::GraphNetwork::ActivateNetwork(unsigned inputs_count,
                                        unsigned hidden_layers_count) {
  layers_.clear();
  layers_.push_back(GraphLayer(kNodesCount, inputs_count));
  for (auto l = 1U; (l < hidden_layers_count || l < kHiddenLayersMinCount) &&
                    (l < kHiddenLayersMaxCount);
       l++) {
    layers_.push_back(GraphLayer(kNodesCount, kNodesCount));
  }
  layers_.push_back(GraphLayer(kOutputsCount, kNodesCount));
}

void s21::GraphNetwork::GetNetwork(
    std::vector<std::vector<std::vector<double>>> &perceptron_edge_weights,
    std::vector<std::vector<double>> &perceptron_node_biases) {
  perceptron_edge_weights.clear();
  perceptron_node_biases.clear();
  for (auto layer = layers_.begin(); layer != layers_.end(); ++layer) {
    std::vector<std::vector<double>> edge_weights;
    std::vector<double> node_biases;

    layer->GetEdgeWeights(edge_weights);
    perceptron_edge_weights.push_back(edge_weights);
    layer->GetNodeBiases(node_biases);
    perceptron_node_biases.push_back(node_biases);
  }
}

void s21::GraphNetwork::SetNetwork(
    const std::vector<std::vector<std::vector<double>>>
        &perceptron_edge_weights,
    const std::vector<std::vector<double>> &perceptron_node_biases) noexcept {
  auto i = 0UL;

  for (auto layer = layers_.begin();
       (layer != layers_.end()) && (i < perceptron_edge_weights.size()) &&
       (i < perceptron_node_biases.size());
       ++layer) {
    layer->SetEdgeWeights(perceptron_edge_weights[i]);
    layer->SetNodeBiases(perceptron_node_biases[i]);

    i++;
  }
}

const std::list<s21::GraphLayer> &s21::GraphNetwork::GetLayers()
    const noexcept {
  return layers_;
}

void s21::GraphNetwork::CalculateLayersOutputValues() noexcept {
  std::vector<double> output_values = input_values_;

  for (auto layer = layers_.begin(); layer != layers_.end(); ++layer) {
    layer->ActivateLayer(output_values);
    layer->GetNodesOutputValues(output_values);
  }
}

void s21::GraphNetwork::CalculateOutputLayerErrorValues(
    unsigned emnist_letter_number) noexcept {
  auto back_layer = --(layers_.end());
  auto k = 0U;

  for (auto node = back_layer->GetLayer().begin();
       (node != back_layer->GetLayer().end()) && (k < kOutputsCount); ++node) {
    double o = node->GetNodeOutputValue();
    double t = 0.0;
    double error_value{};

    if (k == (emnist_letter_number - 1U)) {
      t = 1.0;
    }
    error_value = -o * (1.0 - o) * (t - o);
    node->SetNodeErrorValue(error_value);

    k++;
  }
  nodes_count_ = kOutputsCount;
  layers_.back().GetNodesErrorValues(nodes_error_values_);
  layers_.back().GetEdgeWeights(edge_weights_);
}

void s21::GraphNetwork::CalculateHiddenLayersErrorValues() noexcept {
  auto layer = --(--(layers_.end()));

  for (auto l = layers_.size() - 1UL; l > 0UL; l--) {
    auto j = 0U;

    for (auto node = layer->GetLayer().begin();
         (node != layer->GetLayer().end()); ++node) {
      double o = node->GetNodeOutputValue();
      double sum = 0.0;
      double error_value{};

      for (auto k = 0U;
           (k < nodes_error_values_.size()) && (k < edge_weights_.size()) &&
           (j < edge_weights_[k].size());
           k++) {
        sum += nodes_error_values_[k] * edge_weights_[k][j];
      }
      error_value = o * (1.0 - o) * sum;
      node->SetNodeErrorValue(error_value);

      j++;
    }
    nodes_count_ = layer->GetNodesCount();
    layer->GetNodesErrorValues(nodes_error_values_);
    layer->GetEdgeWeights(edge_weights_);

    --layer;
  }
}

void s21::GraphNetwork::ModifyNetworkDeltas() noexcept {
  std::vector<double> output_values = input_values_;

  for (auto layer = layers_.begin(); layer != layers_.end(); ++layer) {
    layer->ModifyLayerDeltas(output_values);
    layer->GetNodesOutputValues(output_values);
  }
}

void s21::GraphNetwork::ModifyNetwork() noexcept {
  for (auto layer = layers_.begin(); layer != layers_.end(); ++layer) {
    layer->ModifyLayer();
  }
}

std::vector<double> &s21::GraphNetwork::GetBackNodesOutputValues() {
  layers_.back().GetNodesOutputValues(nodes_output_values_);

  return nodes_output_values_;
}

bool s21::GraphNetwork::IsEmptyNetwork() noexcept { return layers_.empty(); }
