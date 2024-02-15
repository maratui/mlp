#include "graph_layer.h"

s21::GraphLayer::GraphLayer(unsigned nodes_count, unsigned inputs_count) {
  for (auto i = 0U; i < nodes_count; i++) {
    layer_.push_back(Node(inputs_count));
  }
}

std::list<s21::Node> &s21::GraphLayer::GetLayer() noexcept { return layer_; }

void s21::GraphLayer::SetEdgeWeights(
    const std::vector<std::vector<double>> &edge_weights) noexcept {
  auto i = 0U;

  for (auto node = layer_.begin();
       (node != layer_.end()) && (i < edge_weights.size()); ++node) {
    node->SetEdgeWeights(edge_weights[i]);

    i++;
  }
}

void s21::GraphLayer::SetNodeBiases(
    const std::vector<double> &node_biases) noexcept {
  auto i = 0U;

  for (auto node = layer_.begin();
       (node != layer_.end()) && (i < node_biases.size()); ++node) {
    node->SetNodeBias(node_biases[i]);

    i++;
  }
}

void s21::GraphLayer::GetNodesOutputValues(std::vector<double> &output_values) {
  output_values.clear();
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    output_values.push_back(node->GetNodeOutputValue());
  }
}

void s21::GraphLayer::GetNodesErrorValues(std::vector<double> &error_values) {
  error_values.clear();
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    error_values.push_back(node->GetNodeErrorValue());
  }
}

void s21::GraphLayer::GetEdgeWeights(
    std::vector<std::vector<double>> &edge_weights) {
  edge_weights.clear();
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    edge_weights.push_back(node->GetEdgeWeights());
  }
}

void s21::GraphLayer::GetNodeBiases(std::vector<double> &node_biases) {
  node_biases.clear();
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    node_biases.push_back(node->GetNodeBias());
  }
}

unsigned s21::GraphLayer::GetNodesCount() const noexcept {
  return layer_.size();
}

void s21::GraphLayer::ActivateLayer(
    const std::vector<double> &input_values) noexcept {
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    node->ActivateNode(input_values);
  }
}

void s21::GraphLayer::ModifyLayerDeltas(
    const std::vector<double> &input_values) noexcept {
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    node->ModifyNodeDeltas(input_values);
  }
}

void s21::GraphLayer::ModifyLayer() noexcept {
  for (auto node = layer_.begin(); node != layer_.end(); ++node) {
    node->ModifyNode();
  }
}
