#ifndef CPP7_MLP_CONTROLLER_CONTROLLER_H_
#define CPP7_MLP_CONTROLLER_CONTROLLER_H_

#include "../facade/facade.h"

namespace s21 {
class Controller {
 public:
  Controller() = delete;
  explicit Controller(Facade *facade);

  void SetMatrixNetworkStrategy();
  void SetGraphNetworkStrategy();

  void SavePerceptron(const std::string &perceptron_path);
  void GetNetwork();

  void LoadPerceptron(const std::string &perceptron_path);
  void SetNetwork() noexcept;

  void LoadTrain(const std::string &emnist_letters_train_path,
                 const std::string &emnist_letters_mapping_path);
  void EpochsTrainNetwork(const unsigned epochs_count,
                          const unsigned hidden_layers_count) noexcept;
  void GroupsTrainNetwork(const unsigned groups_count,
                          const unsigned hidden_layers_count) noexcept;
  const std::vector<double> &GetTrainMeanSquaredErrors() noexcept;
  const std::vector<double> &GetTestMeanSquaredErrors() noexcept;

  void LoadTest(const std::string &emnist_letters_test_path,
                const std::string &mapping_path);
  void TestNetwork(const double &sample_part) noexcept;
  const ExperimentResults &GetTestResults() noexcept;

  void LoadImage(const QImage &image);
  std::string &ClassifyImage() noexcept;

 private:
  Facade *facade_{};
};
}  // namespace s21

#endif  // CPP7_MLP_CONTROLLER_CONTROLLER_H_
