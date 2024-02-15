#include "network.h"

void s21::Network::TrainNetwork(
    std::vector<std::vector<unsigned>> &emnist_letters_train) noexcept {
  std::random_device rd;
  std::mt19937 gen(rd());

  for (auto i = 0; i < 2; i++) {
    std::shuffle(emnist_letters_train.begin(), emnist_letters_train.end(), gen);

    for (auto j = 0UL; j < emnist_letters_train.size(); j++) {
      NormalizeInputValues(emnist_letters_train[j]);
      CalculateLayersOutputValues();
      CalculateOutputLayerErrorValues(emnist_letters_train[j][0]);
      CalculateHiddenLayersErrorValues();
      ModifyNetworkDeltas();
      if ((j + 1) % kBatchSize == 0) {
        ModifyNetwork();
      }
    }
    ModifyNetwork();
  }
}

unsigned s21::Network::ClassifyImage(
    const std::vector<unsigned> &emnist_letter) noexcept {
  unsigned result{};

  if (!IsEmptyNetwork()) {
    std::vector<double> output_values;
    double max{};

    NormalizeInputValues(emnist_letter);
    CalculateLayersOutputValues();
    output_values = GetBackNodesOutputValues();
    max = output_values[0];
    result = 0U;
    for (auto i = 1UL; i < output_values.size(); i++) {
      if (max < output_values[i]) {
        max = output_values[i];
        result = i;
      }
    }
    result++;
  }

  return result;
}

const double &s21::Network::CalculateMeanSquaredError(
    const std::vector<std::vector<unsigned>> &emnist_letters) noexcept {
  std::size_t n = 0UL;

  mean_squared_error_ = 0.0;
  for (auto i = 0UL; i < emnist_letters.size(); i++) {
    std::vector<double> output_values;

    NormalizeInputValues(emnist_letters[i]);
    CalculateLayersOutputValues();
    output_values = GetBackNodesOutputValues();
    for (auto k = 0U; k < output_values.size(); k++) {
      double o = output_values[k];
      double t = 0.0;

      if (k == (emnist_letters[i][0] - 1U)) {
        t = 1.0;
      }
      mean_squared_error_ += (t - o) * (t - o);
      n += 1UL;
    }
  }
  mean_squared_error_ /= (double)n;

  return mean_squared_error_;
}

void s21::Network::NormalizeInputValues(
    const std::vector<unsigned> &input_values) noexcept {
  input_values_.clear();
  for (auto i = 1UL; i < input_values.size(); i++) {
    double value = input_values[i] / kNormalization;
    input_values_.push_back(value);
  }
}
