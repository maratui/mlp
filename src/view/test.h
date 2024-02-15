#ifndef CPP7_MLP_VIEW_TEST_H_
#define CPP7_MLP_VIEW_TEST_H_

#include <QWidget>

#include "button.h"
#include "label.h"
#include "label_line_edit.h"
#include "layout.h"

namespace s21 {
class Test : public QWidget {
  Q_OBJECT

 public:
  Test();

  QSize sizeHint() const override;

  void ClearTest();

  const double &GetSamplePart();
  Button *GetRunTestButton();

  void SetAverageAccuracy(const double &average_accuracy) noexcept;
  void SetPrecision(const double &precision) noexcept;
  void SetRecall(const double &recall) noexcept;
  void SetFMeasure(const double &f_measure) noexcept;
  void SetTotalTime(const double &total_time) noexcept;

 private:
  const unsigned kMargins = 3U;

  Label *label_{};
  LabelLineEdit *sample_part_label_edit_{};
  LabelLineEdit *average_accuracy_label_edit_{};
  LabelLineEdit *precision_label_edit_{};
  LabelLineEdit *recall_label_edit_{};
  LabelLineEdit *f_measure_label_edit_{};
  LabelLineEdit *total_time_label_edit_{};
  Button *run_test_button_{};
  VBoxLayout *v_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_TEST_H_
