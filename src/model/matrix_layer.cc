#include "matrix_layer.h"

s21::MatrixLayer::MatrixLayer(unsigned nodes_count, unsigned inputs_count) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> weight_dis(-kDistributionParameter,
                                              kDistributionParameter);

  for (auto j = 0U; j < nodes_count; j++) {
    node_error_values_.push_back(0.0);
    node_output_values_.push_back(0.0);
    node_biases_.push_back(0.0);
    bias_deltas_.push_back(0.0);
  }

  for (auto i = 0U; i < nodes_count; i++) {
    std::vector<double> weights_vector;
    std::vector<double> delta_weights_vector;

    for (auto j = 0U; j < inputs_count; j++) {
      weights_vector.push_back(weight_dis(gen));
      delta_weights_vector.push_back(0.0);
    }
    edge_weights_.push_back(weights_vector);
    weight_deltas_.push_back(delta_weights_vector);
  }
}

void s21::MatrixLayer::SetEdgeWeights(
    const std::vector<std::vector<double>> &edge_weights) noexcept {
  edge_weights_ = edge_weights;
}

void s21::MatrixLayer::SetNodeBiases(
    const std::vector<double> &node_biases) noexcept {
  node_biases_ = node_biases;
}

void s21::MatrixLayer::SetNodeErrorValue(const double &value,
                                         const unsigned i) noexcept {
  node_error_values_[i] = value;
}

const std::vector<double> &s21::MatrixLayer::GetNodesOutputValues()
    const noexcept {
  return node_output_values_;
}

const std::vector<double> &s21::MatrixLayer::GetNodesErrorValues()
    const noexcept {
  return node_error_values_;
}

const std::vector<std::vector<double>> &s21::MatrixLayer::GetEdgeWeights()
    const noexcept {
  return edge_weights_;
}

const std::vector<double> &s21::MatrixLayer::GetNodeBiases() const noexcept {
  return node_biases_;
}

unsigned s21::MatrixLayer::GetNodesCount() const noexcept {
  return node_output_values_.size();
}

void s21::MatrixLayer::ActivateLayer(
    const std::vector<double> &input_values) noexcept {
  for (auto i = 0UL; (i < node_output_values_.size()) &&
                     (i < edge_weights_.size()) && (i < node_biases_.size());
       i++) {
    double z = NodeSummationFunction(input_values, i);

    node_output_values_[i] = NodeActivationFunction(z);
  }
}

void s21::MatrixLayer::ModifyLayerDeltas(
    const std::vector<double> &input_values) noexcept {
  for (auto i = 0UL;
       (i < weight_deltas_.size()) && (i < node_error_values_.size()) &&
       (i < bias_deltas_.size());
       i++) {
    for (auto j = 0UL;
         (j < weight_deltas_[i].size()) && (j < input_values.size()); j++) {
      weight_deltas_[i][j] += node_error_values_[i] * input_values[j];
    }
    bias_deltas_[i] += node_error_values_[i];
  }
}

void s21::MatrixLayer::ModifyLayer() noexcept {
  for (auto i = 0U; (i < edge_weights_.size()) && (i < weight_deltas_.size()) &&
                    (i < node_biases_.size()) && (i < bias_deltas_.size());
       i++) {
    for (auto j = 0U;
         (j < edge_weights_[i].size()) && (j < weight_deltas_[i].size()); j++) {
      edge_weights_[i][j] -= kLearningRate * weight_deltas_[i][j];
      weight_deltas_[i][j] = 0.0;
    }
    node_biases_[i] -= kLearningRate * bias_deltas_[i];
    bias_deltas_[i] = 0.0;
  }
}

double s21::MatrixLayer::NodeSummationFunction(
    const std::vector<double> &input_values, const std::size_t i) noexcept {
  double sum = 0.0;

  for (auto j = 0UL; (j < input_values.size()) && (j < edge_weights_[i].size());
       j++) {
    sum += input_values[j] * edge_weights_[i][j];
  }

  return sum;
}

double s21::MatrixLayer::NodeActivationFunction(double z) noexcept {
  return (1.0 / (1.0 + exp(-z)));
}
