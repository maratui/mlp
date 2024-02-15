#include "test_results.h"

void s21::TestResults::Begin(const std::size_t &output_count) {
  experiment_results_.average_accuracy = 0.0;
  experiment_results_.precision = 0.0;
  experiment_results_.recall = 0.0;
  experiment_results_.f_measure = 0.0;
  begin_ = std::chrono::high_resolution_clock::now();

  for (auto i = 0UL; i < output_count; i++) {
    std::vector<unsigned> unsigned_vector;

    for (auto j = 0UL; j < output_count; j++) {
      unsigned_vector.push_back(0U);
    }
    confusion_.push_back(unsigned_vector);
  }
}

void s21::TestResults::SetConfusion(const std::size_t &row,
                                    const std::size_t &col) noexcept {
  confusion_[row][col] += 1U;
}

void s21::TestResults::End(const std::size_t &tests_count,
                           unsigned passed_tests) noexcept {
  auto output_count = confusion_.size();
  auto end = std::chrono::high_resolution_clock::now();

  experiment_results_.total_time =
      std::chrono::duration<double>(end - begin_).count();

  experiment_results_.average_accuracy =
      (double)passed_tests / (double)tests_count;

  experiment_results_.precision = 0.0;
  experiment_results_.recall = 0.0;
  for (auto i = 0UL; i < output_count; i++) {
    double row_sum = 0.0;
    double col_sum = 0.0;

    for (auto j = 0UL; j < output_count; j++) {
      row_sum += confusion_[i][j];
      col_sum += confusion_[j][i];
    }
    if (row_sum > 1.0e-6) {
      experiment_results_.precision += (double)confusion_[i][i] / row_sum;
    }
    if (col_sum > 1.0e-6) {
      experiment_results_.recall += (double)confusion_[i][i] / col_sum;
    }
  }
  experiment_results_.precision /= (double)output_count;
  experiment_results_.recall /= (double)output_count;

  if ((experiment_results_.precision + experiment_results_.recall) > 0.0) {
    experiment_results_.f_measure =
        2.0 * experiment_results_.precision * experiment_results_.recall /
        (experiment_results_.precision + experiment_results_.recall);
  }
}

const s21::ExperimentResults &s21::TestResults::GetTestResults() noexcept {
  return experiment_results_;
}
