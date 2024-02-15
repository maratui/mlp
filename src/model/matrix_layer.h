#ifndef CPP7_MLP_MODEL_MATRIX_LAYER_H_
#define CPP7_MLP_MODEL_MATRIX_LAYER_H_

#include <cmath>
#include <random>
#include <vector>

namespace s21 {
class MatrixLayer {
 public:
  MatrixLayer() = delete;
  explicit MatrixLayer(unsigned nodes_count, unsigned inputs_count);

  void SetEdgeWeights(
      const std::vector<std::vector<double>> &edge_weights) noexcept;
  void SetNodeBiases(const std::vector<double> &node_biases) noexcept;
  void SetNodeErrorValue(const double &value, const unsigned i) noexcept;

  const std::vector<double> &GetNodesOutputValues() const noexcept;
  const std::vector<double> &GetNodesErrorValues() const noexcept;
  const std::vector<std::vector<double>> &GetEdgeWeights() const noexcept;
  const std::vector<double> &GetNodeBiases() const noexcept;
  unsigned GetNodesCount() const noexcept;

  void ActivateLayer(const std::vector<double> &input_values) noexcept;
  void ModifyLayerDeltas(const std::vector<double> &input_values) noexcept;
  void ModifyLayer() noexcept;

 private:
  static constexpr double kDistributionParameter = 0.5;
  static constexpr double kLearningRate = 0.1;

  double NodeSummationFunction(const std::vector<double> &input_values,
                               const std::size_t i) noexcept;
  double NodeActivationFunction(double z) noexcept;

  std::vector<double> node_output_values_;
  std::vector<double> node_error_values_;
  std::vector<double> node_biases_;
  std::vector<double> bias_deltas_;
  std::vector<std::vector<double>> edge_weights_;
  std::vector<std::vector<double>> weight_deltas_;
};
}  // namespace s21

#endif  // CPP7_MLP_MODEL_MATRIX_LAYER_H_
