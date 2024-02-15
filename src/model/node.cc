#include "node.h"

s21::Node::Node(unsigned inputs_count) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-kDistributionParameter,
                                       kDistributionParameter);

  node_error_value_ = 0.0;
  node_output_value_ = 0.0;
  node_bias_ = dis(gen);
  bias_delta_ = 0.0;

  for (auto j = 0U; j < inputs_count; j++) {
    edge_weights_.push_back(dis(gen));
    weight_deltas_.push_back(0.0);
  }
}

void s21::Node::SetEdgeWeights(
    const std::vector<double> &edge_weights) noexcept {
  edge_weights_ = edge_weights;
}

void s21::Node::SetNodeBias(const double &node_bias) noexcept {
  node_bias_ = node_bias;
}

void s21::Node::SetNodeErrorValue(const double &value) noexcept {
  node_error_value_ = value;
}

const double &s21::Node::GetNodeOutputValue() const noexcept {
  return node_output_value_;
}

const double &s21::Node::GetNodeErrorValue() const noexcept {
  return node_error_value_;
}

const std::vector<double> &s21::Node::GetEdgeWeights() const noexcept {
  return edge_weights_;
}

const double &s21::Node::GetNodeBias() const noexcept { return node_bias_; }

void s21::Node::ActivateNode(const std::vector<double> &input_values) noexcept {
  double z = NodeSummationFunction(input_values);

  node_output_value_ = NodeActivationFunction(z);
}

void s21::Node::ModifyNodeDeltas(
    const std::vector<double> &input_values) noexcept {
  for (auto j = 0U; (j < weight_deltas_.size()) && (j < input_values.size());
       j++) {
    weight_deltas_[j] += node_error_value_ * input_values[j];
  }
  bias_delta_ += node_error_value_;
}

void s21::Node::ModifyNode() noexcept {
  for (auto j = 0U; (j < edge_weights_.size()) && (j < weight_deltas_.size());
       j++) {
    edge_weights_[j] -= kLearningRate * weight_deltas_[j];
    weight_deltas_[j] = 0.0;
  }
  node_bias_ -= kLearningRate * bias_delta_;
  bias_delta_ = 0.0;
}

double s21::Node::NodeSummationFunction(
    const std::vector<double> &input_values) noexcept {
  double sum = 0.0;

  for (auto j = 0UL; (j < input_values.size()) && (j < edge_weights_.size());
       j++) {
    sum += input_values[j] * edge_weights_[j];
  }

  return sum;
}

double s21::Node::NodeActivationFunction(double z) noexcept {
  return (1.0 / (1.0 + exp(-z)));
}
