#include "label.h"

s21::Label::Label(const QString &text, const bool alignleft,
                  const unsigned margins) {
  setText(text);
  if (alignleft)
    setAlignment(Qt::AlignLeft);
  else
    setAlignment(Qt::AlignCenter);

  setContentsMargins(margins, margins, margins, margins);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QSize s21::Label::sizeHint() const {
  QSize size = QLabel::sizeHint();

  size.rheight() = 30;

  return size;
}
