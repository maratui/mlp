#include "test.h"

s21::Test::Test() {
  label_ = new Label("Тестирование", false, kMargins);
  sample_part_label_edit_ =
      new LabelLineEdit("Часть выборки:  ", "0.5", 5, false, kMargins);
  average_accuracy_label_edit_ =
      new LabelLineEdit("Средняя точность:  ", "", 5, true, kMargins);
  precision_label_edit_ =
      new LabelLineEdit("Прецизионность:  ", "", 5, true, kMargins);
  recall_label_edit_ = new LabelLineEdit("Полнота:  ", "", 5, true, kMargins);
  f_measure_label_edit_ = new LabelLineEdit("f-мера:  ", "", 5, true, kMargins);
  total_time_label_edit_ =
      new LabelLineEdit("Затраченное время:  ", "", 5, true, kMargins);
  run_test_button_ = new Button("Запустить тест", false);
  v_layout_ = new VBoxLayout(kMargins, this);

  sample_part_label_edit_->SetRange(0.0, 1.0);

  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  v_layout_->addWidget(sample_part_label_edit_, 1, Qt::AlignTop);
  v_layout_->addWidget(average_accuracy_label_edit_, 2, Qt::AlignTop);
  v_layout_->addWidget(precision_label_edit_, 3, Qt::AlignTop);
  v_layout_->addWidget(recall_label_edit_, 4, Qt::AlignTop);
  v_layout_->addWidget(f_measure_label_edit_, 5, Qt::AlignTop);
  v_layout_->addWidget(total_time_label_edit_, 6, Qt::AlignTop);
  v_layout_->addWidget(run_test_button_, 7, Qt::AlignTop);

  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize s21::Test::sizeHint() const {
  QSize size = QWidget::sizeHint();

  size.rwidth() = 300;

  return size;
}

void s21::Test::ClearTest() {
  average_accuracy_label_edit_->SetValue("");
  precision_label_edit_->SetValue("");
  recall_label_edit_->SetValue("");
  f_measure_label_edit_->SetValue("");
  total_time_label_edit_->SetValue("");
}

const double &s21::Test::GetSamplePart() {
  return sample_part_label_edit_->GetDoubleValue();
}
s21::Button *s21::Test::GetRunTestButton() { return run_test_button_; }

void s21::Test::SetAverageAccuracy(const double &average_accuracy) noexcept {
  average_accuracy_label_edit_->SetValue(average_accuracy);
}
void s21::Test::SetPrecision(const double &precision) noexcept {
  precision_label_edit_->SetValue(precision);
}
void s21::Test::SetRecall(const double &recall) noexcept {
  recall_label_edit_->SetValue(recall);
}
void s21::Test::SetFMeasure(const double &f_measure) noexcept {
  f_measure_label_edit_->SetValue(f_measure);
}
void s21::Test::SetTotalTime(const double &total_time) noexcept {
  total_time_label_edit_->SetValue(total_time);
}
