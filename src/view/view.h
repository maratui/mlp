#ifndef CPP7_MLP_VIEW_VIEW_H_
#define CPP7_MLP_VIEW_VIEW_H_

#include <QEventLoop>
#include <QFileDialog>
#include <QTimer>
#include <QWidget>

#include "../controller/controller.h"
#include "chart.h"
#include "class.h"
#include "draw.h"
#include "learn.h"
#include "test.h"

namespace s21 {
class View : public QWidget {
  Q_OBJECT

 public:
  View() = delete;
  explicit View(Controller *controller);

 private slots:
  void RunEpochsLearnButtonClicked();
  void RunGroupsLearnButtonClicked();
  void RunTestButtonClicked();
  void LoadBMPImageButtonClicked();
  void ClassifyImageButtonClicked();
  void SavePerceptronButtonClicked();
  void LoadPerceptronButtonClicked();

 private:
  void CreateConnectLearn();
  void CreateConnectTest();
  void CreateChart();
  void CreateConnectSaveLoad();
  void CreateConnectClass();
  void CreateDraw();
  void CreateGridLayout();
  void SetNetworkStrategy();
  void EventLoop();

  Controller *controller_{};
  Learn *learn_{};
  Test *test_{};
  Chart *chart_{};
  Class *class_{};
  Draw *draw_{};
  Button *save_perceptron_button_{};
  Button *load_perceptron_button_{};
  QGridLayout *grid_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_VIEW_H_
