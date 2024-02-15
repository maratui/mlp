#ifndef CPP7_MLP_MODEL_NODE_H_
#define CPP7_MLP_MODEL_NODE_H_

#include <cmath>
#include <random>
#include <vector>

namespace s21 {
class Node {
 public:
  Node() = delete;
  explicit Node(unsigned inputs_count);

  void SetEdgeWeights(const std::vector<double> &edge_weights) noexcept;
  void SetNodeBias(const double &node_bias) noexcept;
  void SetNodeErrorValue(const double &value) noexcept;

  const double &GetNodeOutputValue() const noexcept;
  const double &GetNodeErrorValue() const noexcept;
  const std::vector<double> &GetEdgeWeights() const noexcept;
  const double &GetNodeBias() const noexcept;

  void ActivateNode(const std::vector<double> &input_values) noexcept;
  void ModifyNodeDeltas(const std::vector<double> &input_values) noexcept;
  void ModifyNode() noexcept;

 private:
  static constexpr double kDistributionParameter = 0.5;
  static constexpr double kLearningRate = 0.1;

  double NodeSummationFunction(
      const std::vector<double> &input_values) noexcept;
  double NodeActivationFunction(double z) noexcept;

  double node_output_value_{};
  double node_error_value_{};
  double node_bias_{};
  double bias_delta_{};
  std::vector<double> edge_weights_;
  std::vector<double> weight_deltas_;
};
}  // namespace s21

#endif  // CPP7_MLP_MODEL_NODE_H_
