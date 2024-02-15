#ifndef CPP7_MLP_MODEL_NETWORK_H_
#define CPP7_MLP_MODEL_NETWORK_H_

#include <algorithm>
#include <random>

namespace s21 {
class Network {
 public:
  virtual void ActivateNetwork(unsigned inputs_count,
                               unsigned hidden_layers_count) = 0;

  virtual void GetNetwork(
      std::vector<std::vector<std::vector<double>>> &perceptron_edge_weights,
      std::vector<std::vector<double>> &perceptron_node_biases) = 0;
  virtual void SetNetwork(const std::vector<std::vector<std::vector<double>>>
                              &perceptron_edge_weights,
                          const std::vector<std::vector<double>>
                              &perceptron_node_biases) noexcept = 0;

  void TrainNetwork(
      std::vector<std::vector<unsigned>> &emnist_letters_train) noexcept;

  unsigned ClassifyImage(const std::vector<unsigned> &emnist_letter) noexcept;

  const double &CalculateMeanSquaredError(
      const std::vector<std::vector<unsigned>> &emnist_letters) noexcept;

 protected:
  static constexpr double kNormalization = 255.0;
  static const unsigned kNodesCount = 50U;
  static const unsigned kOutputsCount = 26U;
  static const unsigned kHiddenLayersMinCount = 2U;
  static const unsigned kHiddenLayersMaxCount = 5U;
  static const unsigned kBatchSize = 16U;

  void NormalizeInputValues(const std::vector<unsigned> &input_values) noexcept;
  virtual void CalculateLayersOutputValues() noexcept = 0;
  virtual void CalculateOutputLayerErrorValues(
      unsigned emnist_letter_number) noexcept = 0;
  virtual void CalculateHiddenLayersErrorValues() noexcept = 0;
  virtual void ModifyNetworkDeltas() noexcept = 0;
  virtual void ModifyNetwork() noexcept = 0;
  virtual bool IsEmptyNetwork() noexcept = 0;
  virtual std::vector<double> &GetBackNodesOutputValues() = 0;

  unsigned nodes_count_{};
  std::vector<double> input_values_;
  std::vector<double> nodes_output_values_;
  std::vector<double> nodes_error_values_;
  std::vector<std::vector<double>> edge_weights_;

  double mean_squared_error_{};
};
}  // namespace s21

#endif  // CPP7_MLP_MODEL_NETWORK_H_
