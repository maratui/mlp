#include "chart.h"

s21::Chart::Chart() {
  label_ =
      new Label("График изменения ошибок обучения и теста", false, kMargins);
  v_layout_ = new VBoxLayout(kMargins, this);

  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  ClearChart();

  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize s21::Chart::sizeHint() const {
  QSize size = QWidget::sizeHint();

  size.rwidth() = 500;

  return size;
}

void s21::Chart::CreateChart(
    const std::vector<double> &train_mean_squared_errors,
    const std::vector<double> &test_mean_squared_errors) {
  ClearChart();
  AddSeries(train_mean_squared_errors, test_mean_squared_errors);
  AddAxis(train_mean_squared_errors.size());
}

void s21::Chart::ClearChart() {
  if (chart_view_ != nullptr) {
    delete chart_view_;
  }
  chart_view_ = new QChartView();
  chart_ = new QChart();
  chart_->legend()->hide();
  chart_view_->setChart(chart_);
  v_layout_->addWidget(chart_view_, 1);
}

void s21::Chart::AddSeries(
    const std::vector<double> &train_mean_squared_errors,
    const std::vector<double> &test_mean_squared_errors) {
  train_series_ = new QLineSeries();
  test_series_ = new QLineSeries();

  for (auto i = 0UL; i < train_mean_squared_errors.size(); i++) {
    train_series_->append(i + 1, train_mean_squared_errors[i]);
  }
  train_series_->setPen(QPen(Qt::red));
  train_series_->setPointsVisible();

  for (auto i = 0UL; i < test_mean_squared_errors.size(); i++) {
    test_series_->append(i + 1, test_mean_squared_errors[i]);
  }
  test_series_->setPen(QPen(Qt::green));
  test_series_->setPointsVisible();

  chart_->addSeries(train_series_);
  chart_->addSeries(test_series_);
}

void s21::Chart::AddAxis(const std::size_t &x_range) {
  x_axis_ = new QValueAxis();
  y_axis_ = new QValueAxis();

  x_axis_->setRange(0, x_range + 1);
  x_axis_->setLabelFormat("%1d");
  x_axis_->setTickCount(x_range + 2);

  y_axis_->setTitleText("ошибка");
  y_axis_->setLabelFormat("%.4lf");
  y_axis_->setTickCount(5);

  chart_->addAxis(x_axis_, Qt::AlignBottom);
  chart_->addAxis(y_axis_, Qt::AlignLeft);

  train_series_->attachAxis(x_axis_);
  train_series_->attachAxis(y_axis_);
  test_series_->attachAxis(x_axis_);
  test_series_->attachAxis(y_axis_);
}
