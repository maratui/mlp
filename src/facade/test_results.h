#ifndef CPP7_MLP_FACADE_TEST_RESULTS_H_
#define CPP7_MLP_FACADE_TEST_RESULTS_H_

#include <chrono>
#include <vector>

namespace s21 {
struct ExperimentResults {
  double average_accuracy;
  double precision;
  double recall;
  double f_measure;
  double total_time;
};

class TestResults {
 public:
  void Begin(const std::size_t &output_count);
  void SetConfusion(const std::size_t &row, const std::size_t &col) noexcept;
  void End(const std::size_t &tests_count, unsigned passed_tests) noexcept;

  const ExperimentResults &GetTestResults() noexcept;

 private:
  std::chrono::high_resolution_clock::time_point begin_{};
  std::vector<std::vector<unsigned>> confusion_{};
  ExperimentResults experiment_results_{};
};
}  // namespace s21

#endif  // CPP7_MLP_FACADE_TEST_RESULTS_H_
