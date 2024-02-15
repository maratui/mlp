#include "controller.h"

s21::Controller::Controller(Facade *facade) : facade_(facade) {}

void s21::Controller::SetMatrixNetworkStrategy() {
  facade_->SetMatrixNetworkStrategy();
}
void s21::Controller::SetGraphNetworkStrategy() {
  facade_->SetGraphNetworkStrategy();
}

void s21::Controller::SavePerceptron(const std::string &perceptron_path) {
  facade_->SavePerceptron(perceptron_path);
}
void s21::Controller::GetNetwork() { facade_->GetNetwork(); }

void s21::Controller::LoadPerceptron(const std::string &perceptron_path) {
  facade_->LoadPerceptron(perceptron_path);
}
void s21::Controller::SetNetwork() noexcept { facade_->SetNetwork(); }

void s21::Controller::LoadTrain(
    const std::string &emnist_letters_train_path,
    const std::string &emnist_letters_mapping_path) {
  facade_->LoadTrain(emnist_letters_train_path, emnist_letters_mapping_path);
}

void s21::Controller::EpochsTrainNetwork(
    const unsigned epochs_count, const unsigned hidden_layers_count) noexcept {
  facade_->EpochsTrainNetwork(epochs_count, hidden_layers_count);
}

void s21::Controller::GroupsTrainNetwork(
    const unsigned groups_count, const unsigned hidden_layers_count) noexcept {
  facade_->GroupsTrainNetwork(groups_count, hidden_layers_count);
}

const std::vector<double>
    &s21::Controller::GetTrainMeanSquaredErrors() noexcept {
  return facade_->GetTrainMeanSquaredErrors();
}

const std::vector<double>
    &s21::Controller::GetTestMeanSquaredErrors() noexcept {
  return facade_->GetTestMeanSquaredErrors();
}

void s21::Controller::LoadTest(const std::string &emnist_letters_test_path,
                               const std::string &mapping_path) {
  facade_->LoadTest(emnist_letters_test_path, mapping_path);
}

void s21::Controller::TestNetwork(const double &sample_part) noexcept {
  facade_->TestNetwork(sample_part);
}

const s21::ExperimentResults &s21::Controller::GetTestResults() noexcept {
  return facade_->GetTestResults();
}

void s21::Controller::LoadImage(const QImage &image) {
  facade_->LoadImage(image);
}

std::string &s21::Controller::ClassifyImage() noexcept {
  return facade_->ClassifyImage();
}
