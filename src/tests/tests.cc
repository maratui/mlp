#include "tests.h"

TEST(TestMLP, LoadPerceptron) {
  s21::FileReader file_reader;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights;
  std::vector<std::vector<double>> perceptron_node_biases;

  file_reader.ReadPerceptronWeightsFile(perceptron_edge_weights,
                                        perceptron_node_biases,
                                        "tests/perceptrons/perceptron_2m_g5");

  EXPECT_EQ(3, perceptron_edge_weights.size());
  EXPECT_EQ(50, perceptron_edge_weights[0].size());
  EXPECT_EQ(784, perceptron_edge_weights[0][0].size());
  EXPECT_EQ(50, perceptron_edge_weights[1].size());
  EXPECT_EQ(50, perceptron_edge_weights[1][0].size());
  EXPECT_EQ(26, perceptron_edge_weights[2].size());
  EXPECT_EQ(50, perceptron_edge_weights[2][0].size());

  EXPECT_EQ(3, perceptron_node_biases.size());
  EXPECT_EQ(50, perceptron_node_biases[0].size());
  EXPECT_EQ(50, perceptron_node_biases[1].size());
  EXPECT_EQ(26, perceptron_node_biases[2].size());
}

TEST(TestMLP, LoadTrain) {
  s21::FileReader file_reader;
  std::vector<std::vector<unsigned>> emnist_letters_train;
  std::vector<std::vector<unsigned>> emnist_letters_mapping;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_train, "tests/emnist_letters/emnist-letters-train.csv");
  file_reader.ReadEmnistLettersFile(
      emnist_letters_mapping, "tests/emnist_letters/emnist-letters-mapping.txt",
      ' ');

  EXPECT_EQ(26, emnist_letters_mapping.size());
  EXPECT_EQ(3395, emnist_letters_train.size());

  EXPECT_EQ(3, emnist_letters_mapping[0].size());
  EXPECT_EQ(785, emnist_letters_train[0].size());
}

TEST(TestMLP, LoadTest) {
  s21::FileReader file_reader;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_test, "tests/emnist_letters/emnist-letters-test.csv");

  EXPECT_EQ(799, emnist_letters_test.size());
  EXPECT_EQ(785, emnist_letters_test[0].size());
}

TEST(TestMLP, SetMatrixNetwork) {
  s21::FileReader file_reader;
  s21::MatrixNetworkTester network_tester;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights;
  std::vector<std::vector<double>> perceptron_node_biases;

  file_reader.ReadPerceptronWeightsFile(perceptron_edge_weights,
                                        perceptron_node_biases,
                                        "tests/perceptrons/perceptron_2m_g5");
  unsigned inputs_count = perceptron_edge_weights[0][0].size();
  unsigned hidden_layers_count = perceptron_edge_weights.size() - 1UL;

  network_tester.ActivateNetwork(inputs_count, hidden_layers_count);
  network_tester.SetNetwork(perceptron_edge_weights, perceptron_node_biases);

  EXPECT_EQ(3, network_tester.GetLayers().size());
  EXPECT_EQ(50, network_tester.GetLayers().front().GetNodesCount());
  EXPECT_EQ(26, network_tester.GetLayers().back().GetNodesCount());
}

TEST(TestMLP, SetGraphNetwork) {
  s21::FileReader file_reader;
  s21::GraphNetworkTester network_tester;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights;
  std::vector<std::vector<double>> perceptron_node_biases;

  file_reader.ReadPerceptronWeightsFile(perceptron_edge_weights,
                                        perceptron_node_biases,
                                        "tests/perceptrons/perceptron_2m_g5");
  unsigned inputs_count = perceptron_edge_weights[0][0].size();
  unsigned hidden_layers_count = perceptron_edge_weights.size() - 1UL;

  network_tester.ActivateNetwork(inputs_count, hidden_layers_count);
  network_tester.SetNetwork(perceptron_edge_weights, perceptron_node_biases);

  EXPECT_EQ(3, network_tester.GetLayers().size());
  EXPECT_EQ(50, network_tester.GetLayers().front().GetNodesCount());
  EXPECT_EQ(26, network_tester.GetLayers().back().GetNodesCount());
}

TEST(TestMLP, MatrixClassifyImage) {
  s21::FileReader file_reader;
  s21::MatrixNetworkTester network_tester;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights;
  std::vector<std::vector<double>> perceptron_node_biases;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadPerceptronWeightsFile(perceptron_edge_weights,
                                        perceptron_node_biases,
                                        "tests/perceptrons/perceptron_2m_g5");
  if (!perceptron_edge_weights.empty()) {
    unsigned inputs_count = perceptron_edge_weights[0][0].size();
    unsigned hidden_layers_count = perceptron_edge_weights.size() - 1UL;

    network_tester.ActivateNetwork(inputs_count, hidden_layers_count);
    network_tester.SetNetwork(perceptron_edge_weights, perceptron_node_biases);
  }

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/H.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/P.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/S.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/V.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));
}

TEST(TestMLP, GraphClassifyImage) {
  s21::FileReader file_reader;
  s21::GraphNetworkTester network_tester;
  std::vector<std::vector<std::vector<double>>> perceptron_edge_weights;
  std::vector<std::vector<double>> perceptron_node_biases;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadPerceptronWeightsFile(perceptron_edge_weights,
                                        perceptron_node_biases,
                                        "tests/perceptrons/perceptron_2m_g5");
  if (!perceptron_edge_weights.empty()) {
    unsigned inputs_count = perceptron_edge_weights[0][0].size();
    unsigned hidden_layers_count = perceptron_edge_weights.size() - 1UL;

    network_tester.ActivateNetwork(inputs_count, hidden_layers_count);
    network_tester.SetNetwork(perceptron_edge_weights, perceptron_node_biases);
  }

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/H.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/P.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/S.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));

  file_reader.ReadEmnistLettersFile(emnist_letters_test,
                                    "tests/emnist_letters/V.csv");
  EXPECT_EQ(emnist_letters_test[0][0],
            network_tester.ClassifyImage(emnist_letters_test[0]));
}

TEST(TestMLP, TrainMatrixNetwork) {
  const unsigned kEpochs = 1U;
  const unsigned kHiddenLayersCount = 2U;

  s21::FileReader file_reader;
  s21::MatrixNetworkTester network_tester;
  std::vector<std::vector<unsigned>> emnist_letters_train;
  std::vector<std::vector<unsigned>> emnist_letters_mapping;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_train, "tests/emnist_letters/emnist-letters-train.csv");
  file_reader.ReadEmnistLettersFile(
      emnist_letters_mapping, "tests/emnist_letters/emnist-letters-mapping.txt",
      ' ');
  file_reader.ReadEmnistLettersFile(
      emnist_letters_test, "tests/emnist_letters/emnist-letters-test.csv");

  if (!emnist_letters_train.empty()) {
    unsigned inputs_count = emnist_letters_train[0].size() - 1UL;
    std::size_t tests_count{};
    unsigned passed_tests{};

    network_tester.ActivateNetwork(inputs_count, kHiddenLayersCount);
    for (auto i = 0U; i < kEpochs; i++) {
      network_tester.TrainNetwork(emnist_letters_train);
    }

    EXPECT_EQ(3, network_tester.GetLayers().size());
    EXPECT_EQ(50, network_tester.GetLayers().front().GetNodesCount());
    EXPECT_EQ(26, network_tester.GetLayers().back().GetNodesCount());

    tests_count = emnist_letters_test.size();
    for (auto i = 0UL; i < tests_count; i++) {
      if (emnist_letters_test[i][0] ==
          network_tester.ClassifyImage(emnist_letters_test[i])) {
        passed_tests++;
      }
    }
    EXPECT_EQ(tests_count, passed_tests);
  }
}

TEST(TestMLP, TrainGraphNetwork) {
  const unsigned kEpochs = 1U;
  const unsigned kHiddenLayersCount = 2U;

  s21::FileReader file_reader;
  s21::GraphNetworkTester network_tester;
  std::vector<std::vector<unsigned>> emnist_letters_train;
  std::vector<std::vector<unsigned>> emnist_letters_mapping;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_train, "tests/emnist_letters/emnist-letters-train.csv");
  file_reader.ReadEmnistLettersFile(
      emnist_letters_mapping, "tests/emnist_letters/emnist-letters-mapping.txt",
      ' ');
  file_reader.ReadEmnistLettersFile(
      emnist_letters_test, "tests/emnist_letters/emnist-letters-test.csv");

  if (!emnist_letters_train.empty()) {
    unsigned inputs_count = emnist_letters_train[0].size() - 1UL;
    std::size_t tests_count{};
    unsigned passed_tests{};

    network_tester.ActivateNetwork(inputs_count, kHiddenLayersCount);
    for (auto i = 0U; i < kEpochs; i++) {
      network_tester.TrainNetwork(emnist_letters_train);
    }

    EXPECT_EQ(3, network_tester.GetLayers().size());
    EXPECT_EQ(50, network_tester.GetLayers().front().GetNodesCount());
    EXPECT_EQ(26, network_tester.GetLayers().back().GetNodesCount());

    tests_count = emnist_letters_test.size();
    for (auto i = 0UL; i < tests_count; i++) {
      if (emnist_letters_test[i][0] ==
          network_tester.ClassifyImage(emnist_letters_test[i])) {
        passed_tests++;
      }
    }
    EXPECT_EQ(tests_count, passed_tests);
  }
}

TEST(TestMLP, TestMatrixNetwork) {
  const unsigned kEpochs = 1U;
  const unsigned kHiddenLayersCount = 2U;

  s21::FileReader file_reader;
  s21::MatrixNetworkTester network_tester;
  std::vector<std::vector<unsigned>> emnist_letters_train;
  std::vector<std::vector<unsigned>> emnist_letters_mapping;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_train, "tests/emnist_letters/emnist-letters-train.csv");
  file_reader.ReadEmnistLettersFile(
      emnist_letters_mapping, "tests/emnist_letters/emnist-letters-mapping.txt",
      ' ');
  file_reader.ReadEmnistLettersFile(
      emnist_letters_test, "tests/emnist_letters/emnist-letters-test.csv");

  if (!emnist_letters_train.empty()) {
    unsigned inputs_count = emnist_letters_train[0].size() - 1UL;
    std::size_t tests_count{};
    unsigned passed_tests{};

    network_tester.ActivateNetwork(inputs_count, kHiddenLayersCount);
    for (auto i = 0U; i < kEpochs; i++) {
      network_tester.TrainNetwork(emnist_letters_train);
    }

    tests_count = emnist_letters_test.size();
    for (auto i = 0UL; i < tests_count; i++) {
      if (emnist_letters_test[i][0] ==
          network_tester.ClassifyImage(emnist_letters_test[i])) {
        passed_tests++;
      }
    }
    EXPECT_EQ(tests_count, passed_tests);
  }
}

TEST(TestMLP, TestGraphNetwork) {
  const unsigned kEpochs = 1U;
  const unsigned kHiddenLayersCount = 2U;

  s21::FileReader file_reader;
  s21::GraphNetworkTester network_tester;
  std::vector<std::vector<unsigned>> emnist_letters_train;
  std::vector<std::vector<unsigned>> emnist_letters_mapping;
  std::vector<std::vector<unsigned>> emnist_letters_test;

  file_reader.ReadEmnistLettersFile(
      emnist_letters_train, "tests/emnist_letters/emnist-letters-train.csv");
  file_reader.ReadEmnistLettersFile(
      emnist_letters_mapping, "tests/emnist_letters/emnist-letters-mapping.txt",
      ' ');
  file_reader.ReadEmnistLettersFile(
      emnist_letters_test, "tests/emnist_letters/emnist-letters-test.csv");

  if (!emnist_letters_train.empty()) {
    unsigned inputs_count = emnist_letters_train[0].size() - 1UL;
    std::size_t tests_count{};
    unsigned passed_tests{};

    network_tester.ActivateNetwork(inputs_count, kHiddenLayersCount);
    for (auto i = 0U; i < kEpochs; i++) {
      network_tester.TrainNetwork(emnist_letters_train);
    }

    tests_count = emnist_letters_test.size();
    for (auto i = 0UL; i < tests_count; i++) {
      if (emnist_letters_test[i][0] ==
          network_tester.ClassifyImage(emnist_letters_test[i])) {
        passed_tests++;
      }
    }
    EXPECT_EQ(tests_count, passed_tests);
  }
}
