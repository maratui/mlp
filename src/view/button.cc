#include "button.h"

s21::Button::Button(const QString &text, const bool is_width_fixed) {
  setText(text);
  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  if (is_width_fixed) {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  } else {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  }
}

QSize s21::Button::sizeHint() const {
  QSize size = QPushButton::sizeHint();

  size.rheight() = 40;

  return size;
}
