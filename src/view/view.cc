#include "view.h"

s21::View::View(Controller *controller) : controller_(controller) {
  setWindowTitle("Multilayer Perceptron");
  CreateConnectLearn();
  CreateConnectTest();
  CreateChart();
  CreateConnectSaveLoad();
  CreateConnectClass();
  CreateDraw();
  CreateGridLayout();
}

void s21::View::CreateConnectLearn() {
  learn_ = new Learn;

  connect(learn_->GetRunEpochsLearnButton(), SIGNAL(clicked()), this,
          SLOT(RunEpochsLearnButtonClicked()));
  connect(learn_->GetRunGroupsLearnButton(), SIGNAL(clicked()), this,
          SLOT(RunGroupsLearnButtonClicked()));
}

void s21::View::CreateConnectTest() {
  test_ = new Test;

  connect(test_->GetRunTestButton(), SIGNAL(clicked()), this,
          SLOT(RunTestButtonClicked()));
}

void s21::View::CreateChart() { chart_ = new Chart; }

void s21::View::CreateConnectSaveLoad() {
  save_perceptron_button_ = new Button("Сохранить веса перцептрона", false);
  load_perceptron_button_ = new Button("Загрузить веса перцептрона", false);

  connect(save_perceptron_button_, SIGNAL(clicked()), this,
          SLOT(SavePerceptronButtonClicked()));
  connect(load_perceptron_button_, SIGNAL(clicked()), this,
          SLOT(LoadPerceptronButtonClicked()));
}

void s21::View::CreateConnectClass() {
  class_ = new Class;

  connect(class_->GetLoadBMPImageButton(), SIGNAL(clicked()), this,
          SLOT(LoadBMPImageButtonClicked()));
  connect(class_->GetClassifyImageButton(), SIGNAL(clicked()), this,
          SLOT(ClassifyImageButtonClicked()));
}

void s21::View::CreateDraw() { draw_ = new Draw; }

void s21::View::CreateGridLayout() {
  grid_layout_ = new QGridLayout(this);
  grid_layout_->addWidget(learn_, 0, 0, 1, 1, Qt::AlignTop);
  grid_layout_->addWidget(test_, 1, 0, 1, 1, Qt::AlignBottom);
  grid_layout_->addWidget(chart_, 0, 1, 2, 2, Qt::AlignTop);
  grid_layout_->addWidget(save_perceptron_button_, 2, 1, 1, 1, Qt::AlignBottom);
  grid_layout_->addWidget(load_perceptron_button_, 2, 2, 1, 1, Qt::AlignBottom);
  grid_layout_->addWidget(draw_, 0, 3, 3, 1, Qt::AlignTop);
  grid_layout_->addWidget(class_, 0, 4, 3, 1, Qt::AlignTop);
  grid_layout_->setSizeConstraint(QLayout::SetFixedSize);
}

void s21::View::SetNetworkStrategy() {
  if (learn_->GetNetworkStrategy()->IsFirstRadioButtonChecked()) {
    controller_->SetMatrixNetworkStrategy();
  } else if (learn_->GetNetworkStrategy()->IsSecondRadioButtonChecked()) {
    controller_->SetGraphNetworkStrategy();
  }
}

void s21::View::EventLoop() {
  QEventLoop loop;
  QTimer::singleShot(100, &loop, SLOT(quit()));
  loop.exec();
}

void s21::View::RunEpochsLearnButtonClicked() {
  QString emnist_letters_train_path = "";
  QString emnist_letters_test_path = "";
  QString emnist_letters_mapping_path = "";
  unsigned hidden_layers_count = learn_->GetHiddenLayersCount();
  unsigned epochs_count = learn_->GetEpochsCount();

  emnist_letters_train_path = QFileDialog::getOpenFileName(
      this, "Open the train file", ".", "the train file (*train.csv)");
  emnist_letters_test_path = QFileDialog::getOpenFileName(
      this, "Open the test file", ".", "the test file (*test.csv)");
  emnist_letters_mapping_path = QFileDialog::getOpenFileName(
      this, "Open the mapping file", ".", "the mapping file (*.txt)");

  EventLoop();

  if (emnist_letters_train_path != "" && emnist_letters_test_path != "" &&
      emnist_letters_mapping_path != "") {
    test_->ClearTest();
    SetNetworkStrategy();

    controller_->LoadTrain(emnist_letters_train_path.toStdString(),
                           emnist_letters_mapping_path.toStdString());
    controller_->LoadTest(emnist_letters_test_path.toStdString(),
                          emnist_letters_mapping_path.toStdString());
    controller_->EpochsTrainNetwork(epochs_count, hidden_layers_count);

    chart_->CreateChart(controller_->GetTrainMeanSquaredErrors(),
                        controller_->GetTestMeanSquaredErrors());
  }
}

void s21::View::RunGroupsLearnButtonClicked() {
  QString emnist_letters_train_path = "";
  QString emnist_letters_mapping_path = "";
  unsigned hidden_layers_count = learn_->GetHiddenLayersCount();
  unsigned groups_count = learn_->GetGroupsCount();

  emnist_letters_train_path = QFileDialog::getOpenFileName(
      this, "Open the train file", ".", "the train file (*train.csv)");
  emnist_letters_mapping_path = QFileDialog::getOpenFileName(
      this, "Open the mapping file", ".", "the mapping file (*mapping.txt)");

  EventLoop();

  if (emnist_letters_train_path != "" && emnist_letters_mapping_path != "") {
    test_->ClearTest();
    SetNetworkStrategy();

    controller_->LoadTrain(emnist_letters_train_path.toStdString(),
                           emnist_letters_mapping_path.toStdString());
    controller_->GroupsTrainNetwork(groups_count, hidden_layers_count);

    chart_->CreateChart(controller_->GetTrainMeanSquaredErrors(),
                        controller_->GetTestMeanSquaredErrors());
  }
}

void s21::View::RunTestButtonClicked() {
  QString emnist_letters_test_path = "";
  QString emnist_letters_mapping_path = "";
  double sample_part = test_->GetSamplePart();

  emnist_letters_test_path = QFileDialog::getOpenFileName(
      this, "Open the test file", ".", "the test file (*test.csv)");
  emnist_letters_mapping_path = QFileDialog::getOpenFileName(
      this, "Open the mapping file", ".", "the mapping file (*mapping.txt)");

  EventLoop();

  if (emnist_letters_test_path != "" && emnist_letters_mapping_path != "") {
    controller_->LoadTest(emnist_letters_test_path.toStdString(),
                          emnist_letters_mapping_path.toStdString());
    controller_->TestNetwork(sample_part);

    auto test_results = controller_->GetTestResults();
    test_->SetAverageAccuracy(test_results.average_accuracy);
    test_->SetPrecision(test_results.precision);
    test_->SetRecall(test_results.recall);
    test_->SetFMeasure(test_results.f_measure);
    test_->SetTotalTime(test_results.total_time);
  }
}

void s21::View::LoadBMPImageButtonClicked() {
  QString bmp_image_path = "";

  bmp_image_path = QFileDialog::getOpenFileName(this, "Open the BMP image", ".",
                                                "the BMP image (*.bmp)");

  if (bmp_image_path != "") {
    QImage image(bmp_image_path);
    draw_->SetImage(image);
  }
}

void s21::View::ClassifyImageButtonClicked() {
  controller_->LoadImage(draw_->GetImage());
  class_->SetLetterLabel(controller_->ClassifyImage());
}

void s21::View::SavePerceptronButtonClicked() {
  QString perceptron_path = "";

  perceptron_path =
      QFileDialog::getSaveFileName(this, "Save the perceptron file", ".",
                                   "the perceptron file (perceptron*)");

  if (perceptron_path != "") {
    controller_->GetNetwork();
    controller_->SavePerceptron(perceptron_path.toStdString());
  }
}

void s21::View::LoadPerceptronButtonClicked() {
  QString perceptron_path = "";

  perceptron_path =
      QFileDialog::getOpenFileName(this, "Open the perceptron file", ".",
                                   "the perceptron file (perceptron*)");

  if (perceptron_path != "") {
    test_->ClearTest();
    chart_->ClearChart();
    SetNetworkStrategy();
    controller_->LoadPerceptron(perceptron_path.toStdString());
    controller_->SetNetwork();
  }
}
