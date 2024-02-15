#include "line_edit.h"

s21::LineEdit::LineEdit(const QString &text, const unsigned max_length,
                        const bool read_only, const unsigned margins)
    : max_length_(max_length) {
  setText(text);
  setAlignment(Qt::AlignCenter);
  setMaxLength(max_length_);
  setReadOnly(read_only);

  setContentsMargins(margins, margins, margins, margins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize s21::LineEdit::sizeHint() const {
  QSize size = QLineEdit::sizeHint();

  size.rwidth() = max_length_ * 10;
  size.rheight() = 30;

  return size;
}
