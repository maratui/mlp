#ifndef CPP7_MLP_FACADE_FACADE_H_
#define CPP7_MLP_FACADE_FACADE_H_

#include <string>
#include <vector>

#include "../model/graph_network.h"
#include "../model/matrix_network.h"
#include "file_reader.h"
#include "image_reader.h"
#include "test_results.h"

namespace s21 {
class Facade {
 public:
  void SavePerceptron(const std::string &perceptron_path);
  void LoadPerceptron(const std::string &perceptron_path);

  void LoadTrain(const std::string &train_path,
                 const std::string &mapping_path);
  void LoadTest(const std::string &test_path, const std::string &mapping_path);

  void LoadImage(const QImage &image);

  void SetMatrixNetworkStrategy();
  void SetGraphNetworkStrategy();

  void GetNetwork() noexcept;
  void SetNetwork() noexcept;

  void EpochsTrainNetwork(unsigned epochs_count,
                          unsigned hidden_layers_count) noexcept;
  void GroupsTrainNetwork(unsigned groups_count,
                          unsigned hidden_layers_count) noexcept;
  const std::vector<double> &GetTrainMeanSquaredErrors() noexcept;
  const std::vector<double> &GetTestMeanSquaredErrors() noexcept;

  void TestNetwork(const double &sample_part) noexcept;
  const ExperimentResults &GetTestResults() noexcept;

  std::string &ClassifyImage() noexcept;

 private:
  void SetEmnistLettersTrain(
      std::vector<std::vector<unsigned>> &emnist_letters_train,
      const unsigned i, const unsigned groups_count);
  void SetEmnistLettersTest(
      std::vector<std::vector<unsigned>> &emnist_letters_test, const unsigned i,
      const unsigned groups_count);

  FileReader file_reader_;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights_;
  std::vector<std::vector<double>> perceptron_node_biases_;
  std::vector<std::vector<unsigned>> emnist_letters_mapping_;
  std::vector<std::vector<unsigned>> emnist_letters_train_;
  std::vector<std::vector<unsigned>> emnist_letters_test_;

  ImageReader image_reader_;
  std::vector<unsigned> emnist_letter_;

  MatrixNetwork matrix_network_;
  GraphNetwork graph_network_;
  Network *network_ = &matrix_network_;

  std::vector<double> train_mean_squared_errors_;
  std::vector<double> test_mean_squared_errors_;
  TestResults test_results_;
  std::string letter_ = "";
};
}  // namespace s21

#endif  // CPP7_MLP_FACADE_FACADE_H_
