#include "two_radio_buttons.h"

s21::TwoRadioButtons::TwoRadioButtons(const QString *text, const int checked,
                                      const unsigned margins) {
  label_ = new Label(text[0], true, 0);
  first_radio_button_ = CreateQRadioButton(text[1], (checked == 0));
  second_radio_button_ = CreateQRadioButton(text[2], (checked == 1));

  v_layout_ = new VBoxLayout(0, this);
  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  v_layout_->addWidget(first_radio_button_, 1, Qt::AlignTop);
  v_layout_->addWidget(second_radio_button_, 2, Qt::AlignTop);

  setContentsMargins(margins, margins, margins, margins);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

bool s21::TwoRadioButtons::IsFirstRadioButtonChecked() noexcept {
  return first_radio_button_->isChecked();
}
bool s21::TwoRadioButtons::IsSecondRadioButtonChecked() noexcept {
  return second_radio_button_->isChecked();
}

QRadioButton *s21::TwoRadioButtons::CreateQRadioButton(const QString &text,
                                                       const bool checked) {
  QRadioButton *radio_button = new QRadioButton;

  radio_button->setText(text);
  radio_button->setChecked(checked);

  return radio_button;
}
