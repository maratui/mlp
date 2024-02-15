#ifndef CPP7_MLP_VIEW_LABEL_LINE_EDIT_H_
#define CPP7_MLP_VIEW_LABEL_LINE_EDIT_H_

#include <QWidget>

#include "label.h"
#include "layout.h"
#include "line_edit.h"

namespace s21 {
class LabelLineEdit : public QWidget {
  Q_OBJECT

 public:
  explicit LabelLineEdit(const QString &text, const QString &default_value,
                         const int max_length, const bool read_only,
                         const unsigned margins);

  void SetRange(const unsigned &min, const unsigned &max) noexcept;
  void SetRange(const double &min, const double &max) noexcept;
  void SetValue(const QString &value) noexcept;
  void SetValue(const unsigned &value) noexcept;
  void SetValue(const double &value) noexcept;

  const unsigned &GetUnsignedValue() noexcept;
  const double &GetDoubleValue() noexcept;

 private:
  unsigned unsigned_value_{};
  unsigned min_unsigned_value_{};
  unsigned max_unsigned_value_{};
  double double_value_{};
  double min_double_value_{};
  double max_double_value_{};
  Label *label_{};
  LineEdit *line_edit_{};
  HBoxLayout *h_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_LABEL_LINE_EDIT_H_
