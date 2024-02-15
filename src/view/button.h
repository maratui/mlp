#ifndef CPP7_MLP_VIEW_BUTTON_H_
#define CPP7_MLP_VIEW_BUTTON_H_

#include <QPushButton>

namespace s21 {
class Button : public QPushButton {
  Q_OBJECT

 public:
  Button() = delete;
  Button(const QString &text, const bool is_width_fixed);

  QSize sizeHint() const override;

 private:
  const unsigned kMargins = 3U;
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_BUTTON_H_
