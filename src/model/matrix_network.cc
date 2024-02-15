#include "matrix_network.h"

void s21::MatrixNetwork::ActivateNetwork(unsigned inputs_count,
                                         unsigned hidden_layers_count) {
  layers_.clear();
  layers_.push_back(MatrixLayer(kNodesCount, inputs_count));
  for (auto l = 1U; (l < hidden_layers_count || l < kHiddenLayersMinCount) &&
                    (l < kHiddenLayersMaxCount);
       l++) {
    layers_.push_back(MatrixLayer(kNodesCount, kNodesCount));
  }
  layers_.push_back(MatrixLayer(kOutputsCount, kNodesCount));
}

void s21::MatrixNetwork::GetNetwork(
    std::vector<std::vector<std::vector<double>>> &perceptron_edge_weights,
    std::vector<std::vector<double>> &perceptron_node_biases) {
  perceptron_edge_weights.clear();
  perceptron_node_biases.clear();
  for (auto i = 0UL; i < layers_.size(); i++) {
    perceptron_edge_weights.push_back(layers_[i].GetEdgeWeights());
    perceptron_node_biases.push_back(layers_[i].GetNodeBiases());
  }
}

void s21::MatrixNetwork::SetNetwork(
    const std::vector<std::vector<std::vector<double>>>
        &perceptron_edge_weights,
    const std::vector<std::vector<double>> &perceptron_node_biases) noexcept {
  for (auto i = 0UL;
       (i < layers_.size()) && (i < perceptron_edge_weights.size()) &&
       (i < perceptron_node_biases.size());
       i++) {
    layers_[i].SetEdgeWeights(perceptron_edge_weights[i]);
    layers_[i].SetNodeBiases(perceptron_node_biases[i]);
  }
}

const std::vector<s21::MatrixLayer> &s21::MatrixNetwork::GetLayers()
    const noexcept {
  return layers_;
}

void s21::MatrixNetwork::CalculateLayersOutputValues() noexcept {
  std::vector<double> output_values = input_values_;

  for (auto i = 0UL; i < layers_.size(); i++) {
    layers_[i].ActivateLayer(output_values);
    output_values = layers_[i].GetNodesOutputValues();
  }
}

void s21::MatrixNetwork::CalculateOutputLayerErrorValues(
    unsigned emnist_letter_number) noexcept {
  std::vector<double> output_values;

  output_values = layers_.back().GetNodesOutputValues();
  for (auto k = 0UL;
       (k < layers_.back().GetNodesCount()) && (k < output_values.size());
       k++) {
    double o = output_values[k];
    double t = 0.0;
    double error_value{};

    if (k == (emnist_letter_number - 1U)) {
      t = 1.0;
    }
    error_value = -o * (1.0 - o) * (t - o);
    layers_.back().SetNodeErrorValue(error_value, k);
  }
  nodes_count_ = kOutputsCount;
  nodes_error_values_ = layers_.back().GetNodesErrorValues();
  edge_weights_ = layers_.back().GetEdgeWeights();
}

void s21::MatrixNetwork::CalculateHiddenLayersErrorValues() noexcept {
  for (auto l = layers_.size() - 1UL; l > 0UL; l--) {
    std::vector<double> output_values;

    output_values = layers_[l - 1UL].GetNodesOutputValues();
    for (auto j = 0UL;
         (j < layers_[l - 1UL].GetNodesCount()) && (j < output_values.size());
         j++) {
      double o = output_values[j];
      double sum = 0.0;
      double error_value{};

      for (auto k = 0U; k < nodes_count_; k++) {
        sum += nodes_error_values_[k] * edge_weights_[k][j];
      }
      error_value = o * (1.0 - o) * sum;
      layers_[l - 1UL].SetNodeErrorValue(error_value, j);
    }
    nodes_count_ = layers_[l - 1UL].GetNodesCount();
    nodes_error_values_ = layers_[l - 1UL].GetNodesErrorValues();
    edge_weights_ = layers_[l - 1UL].GetEdgeWeights();
  }
}

void s21::MatrixNetwork::ModifyNetworkDeltas() noexcept {
  std::vector<double> output_values = input_values_;

  for (auto l = 0UL; l < layers_.size(); l++) {
    layers_[l].ModifyLayerDeltas(output_values);
    output_values = layers_[l].GetNodesOutputValues();
  }
}

void s21::MatrixNetwork::ModifyNetwork() noexcept {
  for (auto l = 0UL; l < layers_.size(); l++) {
    layers_[l].ModifyLayer();
  }
}

std::vector<double> &s21::MatrixNetwork::GetBackNodesOutputValues() {
  nodes_output_values_ = layers_.back().GetNodesOutputValues();

  return nodes_output_values_;
}

bool s21::MatrixNetwork::IsEmptyNetwork() noexcept { return layers_.empty(); }
