#ifndef CPP7_MLP_FACADE_FILE_READER_H_
#define CPP7_MLP_FACADE_FILE_READER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class FileReader {
 public:
  void ReadEmnistLettersFile(std::vector<std::vector<unsigned>> &emnist_letters,
                             const std::string &path, char delim = ',');

  void WritePerceptronWeightsToFile(
      const std::vector<std::vector<std::vector<double>>> &edge_weights,
      const std::vector<std::vector<double>> &node_biases,
      const std::string &path);
  void ReadPerceptronWeightsFile(
      std::vector<std::vector<std::vector<double>>> &edge_weights,
      std::vector<std::vector<double>> &node_biases, const std::string &path);

 private:
  void WritePerceptronWeights(
      const unsigned &layers_size,
      const std::vector<std::vector<std::vector<double>>> &edge_weights,
      std::ofstream &out);
  void WritePerceptronBiases(
      const unsigned &layers_size,
      const std::vector<std::vector<double>> &node_biases, std::ofstream &out);
  void ReadPerceptronWeights(
      const unsigned &layers_size,
      std::vector<std::vector<std::vector<double>>> &edge_weights,
      std::ifstream &in);
  void ReadPerceptronBiases(const unsigned &layers_size,
                            std::vector<std::vector<double>> &node_biases,
                            std::ifstream &in);
};
}  // namespace s21

#endif  // CPP7_MLP_FACADE_FILE_READER_H_
