#include "file_reader.h"

void s21::FileReader::ReadEmnistLettersFile(
    std::vector<std::vector<unsigned>> &emnist_letters, const std::string &path,
    char delim) {
  std::ifstream in(path);

  emnist_letters.clear();

  if (in.is_open()) {
    std::string line = "";

    while (std::getline(in, line)) {
      std::vector<unsigned> unsigned_vector;
      std::istringstream line_iss(line);
      std::string num_str = "";
      unsigned unsigned_num{};

      while (std::getline(line_iss, num_str, delim)) {
        std::istringstream num_str_iss(num_str);
        num_str_iss >> unsigned_num;
        unsigned_vector.push_back(unsigned_num);
      }
      emnist_letters.push_back(unsigned_vector);
    }
  }
  in.close();
}

void s21::FileReader::WritePerceptronWeightsToFile(
    const std::vector<std::vector<std::vector<double>>> &edge_weights,
    const std::vector<std::vector<double>> &node_biases,
    const std::string &path) {
  std::ofstream out(path);

  if (out.is_open()) {
    unsigned layers_size = edge_weights.size();

    out << layers_size << "\n";
    WritePerceptronWeights(layers_size, edge_weights, out);
    WritePerceptronBiases(layers_size, node_biases, out);
  }
  out.close();
}

void s21::FileReader::ReadPerceptronWeightsFile(
    std::vector<std::vector<std::vector<double>>> &edge_weights,
    std::vector<std::vector<double>> &node_biases, const std::string &path) {
  std::ifstream in(path);

  edge_weights.clear();
  node_biases.clear();

  if (in.is_open()) {
    unsigned layers_size{};

    in >> layers_size;
    ReadPerceptronWeights(layers_size, edge_weights, in);
    ReadPerceptronBiases(layers_size, node_biases, in);
  }
  in.close();
}

void s21::FileReader::WritePerceptronWeights(
    const unsigned &layers_size,
    const std::vector<std::vector<std::vector<double>>> &edge_weights,
    std::ofstream &out) {
  for (auto i = 0U; i < layers_size; i++) {
    unsigned nodes_size = edge_weights[i].size();

    out << nodes_size << "\n";
    for (auto row = 0U; row < nodes_size; ++row) {
      unsigned weights_size = edge_weights[i][row].size();

      out << weights_size << "\n";
      for (auto col = 0U; col < weights_size; ++col) {
        double value = edge_weights[i][row][col];

        out << value << " ";
      }
      out << "\n";
    }
  }
}

void s21::FileReader::WritePerceptronBiases(
    const unsigned &layers_size,
    const std::vector<std::vector<double>> &node_biases, std::ofstream &out) {
  for (auto i = 0U; i < layers_size; i++) {
    unsigned biases_size = node_biases[i].size();

    out << biases_size << "\n";
    for (auto row = 0U; row < biases_size; ++row) {
      double value = node_biases[i][row];

      out << value << " ";
    }
    out << "\n";
  }
}

void s21::FileReader::ReadPerceptronWeights(
    const unsigned &layers_size,
    std::vector<std::vector<std::vector<double>>> &edge_weights,
    std::ifstream &in) {
  for (auto i = 0U; i < layers_size; i++) {
    std::vector<std::vector<double>> nodes_vector;
    unsigned nodes_size{};

    in >> nodes_size;
    for (auto row = 0U; row < nodes_size; ++row) {
      std::vector<double> weights_vector;
      unsigned weights_size{};

      in >> weights_size;
      for (auto col = 0U; col < weights_size; ++col) {
        double value{};

        in >> value;
        weights_vector.push_back(value);
      }
      nodes_vector.push_back(weights_vector);
    }
    edge_weights.push_back(nodes_vector);
  }
}

void s21::FileReader::ReadPerceptronBiases(
    const unsigned &layers_size, std::vector<std::vector<double>> &node_biases,
    std::ifstream &in) {
  for (auto i = 0U; i < layers_size; i++) {
    std::vector<double> biases_vector;
    unsigned biases_size{};

    in >> biases_size;
    for (auto row = 0U; row < biases_size; ++row) {
      double value{};

      in >> value;
      biases_vector.push_back(value);
    }
    node_biases.push_back(biases_vector);
  }
}
