#ifndef CPP7_MLP_TESTS_TESTS_H_
#define CPP7_MLP_TESTS_TESTS_H_

#include <gtest/gtest.h>

#include "../facade/file_reader.h"
#include "../model/graph_network.h"
#include "../model/matrix_network.h"

namespace s21 {
class MatrixNetworkTester : protected MatrixNetwork {
 public:
  using MatrixNetwork::ActivateNetwork;
  using MatrixNetwork::ClassifyImage;
  using MatrixNetwork::GetLayers;
  using MatrixNetwork::SetNetwork;
  using MatrixNetwork::TrainNetwork;
};

class GraphNetworkTester : protected GraphNetwork {
 public:
  using GraphNetwork::ActivateNetwork;
  using GraphNetwork::ClassifyImage;
  using GraphNetwork::GetLayers;
  using GraphNetwork::SetNetwork;
  using GraphNetwork::TrainNetwork;
};
}  // namespace s21

#endif  // CPP7_MLP_TESTS_TESTS_H_
