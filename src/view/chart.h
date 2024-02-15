#ifndef CPP7_MLP_VIEW_CHART_H_
#define CPP7_MLP_VIEW_CHART_H_

#include <QWidget>
#include <QtCharts>
#include <vector>

#include "label.h"
#include "layout.h"

namespace s21 {
class Chart : public QWidget {
  Q_OBJECT

 public:
  Chart();

  QSize sizeHint() const override;

  void CreateChart(const std::vector<double> &train_mean_squared_errors,
                   const std::vector<double> &test_mean_squared_errors);

  void ClearChart();

 private:
  static const unsigned kMargins = 3U;

  void AddSeries(const std::vector<double> &train_mean_squared_errors,
                 const std::vector<double> &test_mean_squared_errors);
  void AddAxis(const std::size_t &x_range);

  Label *label_{};
  VBoxLayout *v_layout_{};
  QChartView *chart_view_{};
  QChart *chart_{};
  QLineSeries *train_series_{};
  QLineSeries *test_series_{};
  QValueAxis *x_axis_{};
  QValueAxis *y_axis_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_CHART_H_
