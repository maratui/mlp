#ifndef CPP7_MLP_VIEW_LINE_EDIT_H_
#define CPP7_MLP_VIEW_LINE_EDIT_H_

#include <QLineEdit>

namespace s21 {
class LineEdit : public QLineEdit {
  Q_OBJECT

 public:
  LineEdit(const QString &default_value, const unsigned max_length,
           const bool read_only, const unsigned margins);

  QSize sizeHint() const override;

 private:
  int max_length_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_LINE_EDIT_H_
