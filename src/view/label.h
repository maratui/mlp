#ifndef CPP7_MLP_VIEW_LABEL_H_
#define CPP7_MLP_VIEW_LABEL_H_

#include <QLabel>

namespace s21 {
class Label : public QLabel {
  Q_OBJECT

 public:
  Label(const QString &text, const bool alignleft, const unsigned margins);

  QSize sizeHint() const override;
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_LABEL_H_
