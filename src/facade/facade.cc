#include "facade.h"

void s21::Facade::SavePerceptron(const std::string &perceptron_path) {
  file_reader_.WritePerceptronWeightsToFile(
      perceptron_edge_weights_, perceptron_node_biases_, perceptron_path);
}

void s21::Facade::LoadPerceptron(const std::string &perceptron_path) {
  file_reader_.ReadPerceptronWeightsFile(
      perceptron_edge_weights_, perceptron_node_biases_, perceptron_path);
}

void s21::Facade::LoadTrain(const std::string &train_path,
                            const std::string &mapping_path) {
  file_reader_.ReadEmnistLettersFile(emnist_letters_train_, train_path);
  file_reader_.ReadEmnistLettersFile(emnist_letters_mapping_, mapping_path,
                                     ' ');
}

void s21::Facade::LoadTest(const std::string &test_path,
                           const std::string &mapping_path) {
  file_reader_.ReadEmnistLettersFile(emnist_letters_test_, test_path);
  file_reader_.ReadEmnistLettersFile(emnist_letters_mapping_, mapping_path,
                                     ' ');
}

void s21::Facade::LoadImage(const QImage &image) {
  image_reader_.ReadEmnistLetterImage(emnist_letter_, image);
}

void s21::Facade::SetMatrixNetworkStrategy() { network_ = &matrix_network_; }
void s21::Facade::SetGraphNetworkStrategy() { network_ = &graph_network_; }

void s21::Facade::GetNetwork() noexcept {
  perceptron_edge_weights_.clear();
  perceptron_node_biases_.clear();
  network_->GetNetwork(perceptron_edge_weights_, perceptron_node_biases_);
}

void s21::Facade::SetNetwork() noexcept {
  if (!perceptron_edge_weights_.empty()) {
    unsigned inputs_count = perceptron_edge_weights_[0][0].size();
    unsigned hidden_layers_count = perceptron_edge_weights_.size() - 1UL;

    network_->ActivateNetwork(inputs_count, hidden_layers_count);
    network_->SetNetwork(perceptron_edge_weights_, perceptron_node_biases_);
  }
}

void s21::Facade::EpochsTrainNetwork(unsigned epochs_count,
                                     unsigned hidden_layers_count) noexcept {
  train_mean_squared_errors_.clear();
  test_mean_squared_errors_.clear();

  if (!emnist_letters_train_.empty()) {
    unsigned inputs_count = emnist_letters_train_[0].size() - 1UL;

    network_->ActivateNetwork(inputs_count, hidden_layers_count);
    for (auto i = 0U; i < epochs_count; i++) {
      network_->TrainNetwork(emnist_letters_train_);
      train_mean_squared_errors_.push_back(
          network_->CalculateMeanSquaredError(emnist_letters_train_));
      test_mean_squared_errors_.push_back(
          network_->CalculateMeanSquaredError(emnist_letters_test_));
    }
  }
}

void s21::Facade::GroupsTrainNetwork(unsigned groups_count,
                                     unsigned hidden_layers_count) noexcept {
  train_mean_squared_errors_.clear();
  test_mean_squared_errors_.clear();

  if (!emnist_letters_train_.empty()) {
    unsigned inputs_count = emnist_letters_train_[0].size() - 1UL;

    network_->ActivateNetwork(inputs_count, hidden_layers_count);
    for (auto i = 0U; i < groups_count; i++) {
      std::vector<std::vector<unsigned>> emnist_letters_train;
      std::vector<std::vector<unsigned>> emnist_letters_test;

      SetEmnistLettersTrain(emnist_letters_train, i, groups_count);
      SetEmnistLettersTest(emnist_letters_test, i, groups_count);
      network_->TrainNetwork(emnist_letters_train);
      train_mean_squared_errors_.push_back(
          network_->CalculateMeanSquaredError(emnist_letters_train));
      test_mean_squared_errors_.push_back(
          network_->CalculateMeanSquaredError(emnist_letters_test));
    }
  }
}

void s21::Facade::SetEmnistLettersTrain(
    std::vector<std::vector<unsigned>> &emnist_letters_train, const unsigned i,
    const unsigned groups_count) {
  emnist_letters_train = emnist_letters_train_;
  unsigned group_size = emnist_letters_train.size() / groups_count;
  auto begin = emnist_letters_train.begin() + (i * group_size);

  if (i < (groups_count - 1U)) {
    emnist_letters_train.erase(begin, begin + group_size);
  } else if (i > 0U) {
    emnist_letters_train.erase(begin, emnist_letters_train.end());
  }
}

void s21::Facade::SetEmnistLettersTest(
    std::vector<std::vector<unsigned>> &emnist_letters_test, const unsigned i,
    const unsigned groups_count) {
  unsigned group_size = emnist_letters_train_.size() / groups_count;
  auto begin = emnist_letters_train_.begin() + (i * group_size);

  if (i < (groups_count - 1U)) {
    emnist_letters_test.insert(emnist_letters_test.end(), begin,
                               begin + group_size);
  } else {
    emnist_letters_test.insert(emnist_letters_test.end(), begin,
                               emnist_letters_train_.end());
  }
}

const std::vector<double> &s21::Facade::GetTrainMeanSquaredErrors() noexcept {
  return train_mean_squared_errors_;
}
const std::vector<double> &s21::Facade::GetTestMeanSquaredErrors() noexcept {
  return test_mean_squared_errors_;
}

void s21::Facade::TestNetwork(const double &sample_part) noexcept {
  auto output_count = emnist_letters_mapping_.size();
  auto tests_count = (std::size_t)(emnist_letters_test_.size() * sample_part);
  unsigned passed_tests{};

  test_results_.Begin(output_count);
  for (auto i = 0UL; i < tests_count; i++) {
    auto prediction = network_->ClassifyImage(emnist_letters_test_[i]);
    auto expection = emnist_letters_test_[i][0];

    if (prediction == expection) {
      passed_tests++;
    }
    test_results_.SetConfusion(prediction - 1, expection - 1);
  }
  if (tests_count > 0) {
    test_results_.End(tests_count, passed_tests);
  }
}

const s21::ExperimentResults &s21::Facade::GetTestResults() noexcept {
  return test_results_.GetTestResults();
}

std::string &s21::Facade::ClassifyImage() noexcept {
  unsigned letter_kay = network_->ClassifyImage(emnist_letter_);

  letter_ = "";
  for (auto i = 0UL; (letter_ == "") && (i < emnist_letters_mapping_.size());
       i++) {
    if (emnist_letters_mapping_[i][0] == letter_kay) {
      letter_.push_back(emnist_letters_mapping_[i][1]);
      letter_.push_back(emnist_letters_mapping_[i][2]);
    }
  }

  return letter_;
}
