#include "label_line_edit.h"

s21::LabelLineEdit::LabelLineEdit(const QString &text,
                                  const QString &default_value,
                                  const int max_length, const bool read_only,
                                  const unsigned margins) {
  label_ = new Label(text, true, 0);
  line_edit_ = new LineEdit(default_value, max_length, read_only, 0);

  h_layout_ = new HBoxLayout(0, this);
  h_layout_->addWidget(label_, 0, Qt::AlignLeft);
  h_layout_->addWidget(line_edit_, 1, Qt::AlignRight);

  setContentsMargins(margins, margins, margins, margins);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void s21::LabelLineEdit::SetRange(const unsigned &min,
                                  const unsigned &max) noexcept {
  min_unsigned_value_ = min;
  max_unsigned_value_ = max;
}
void s21::LabelLineEdit::SetRange(const double &min,
                                  const double &max) noexcept {
  min_double_value_ = min;
  max_double_value_ = max;
}

void s21::LabelLineEdit::SetValue(const QString &value) noexcept {
  line_edit_->setText(value);
}

void s21::LabelLineEdit::SetValue(const unsigned &value) noexcept {
  line_edit_->setText(QString::number(value));
}

void s21::LabelLineEdit::SetValue(const double &value) noexcept {
  line_edit_->setText(QString::number(value));
}

const unsigned &s21::LabelLineEdit::GetUnsignedValue() noexcept {
  unsigned_value_ = min_unsigned_value_;
  if (!line_edit_->text().isEmpty()) {
    try {
      int value = line_edit_->text().toInt();

      if (value >= 0) {
        unsigned_value_ = value;
      }
    } catch (...) {
    }
    if (unsigned_value_ < min_unsigned_value_) {
      unsigned_value_ = min_unsigned_value_;
    } else if (unsigned_value_ > max_unsigned_value_) {
      unsigned_value_ = max_unsigned_value_;
    }
  }
  SetValue(unsigned_value_);

  return unsigned_value_;
}

const double &s21::LabelLineEdit::GetDoubleValue() noexcept {
  double_value_ = min_double_value_;
  if (!line_edit_->text().isEmpty()) {
    try {
      double value = line_edit_->text().toDouble();

      double_value_ = value;
    } catch (...) {
    }
    if (double_value_ < min_double_value_) {
      double_value_ = min_double_value_;
    } else if (double_value_ > max_double_value_) {
      double_value_ = max_double_value_;
    }
  }
  SetValue(double_value_);

  return double_value_;
}
