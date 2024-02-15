#ifndef CPP7_MLP_VIEW_TWO_RADIO_BUTTONS_H_
#define CPP7_MLP_VIEW_TWO_RADIO_BUTTONS_H_

#include <QRadioButton>
#include <QWidget>

#include "label.h"
#include "layout.h"

namespace s21 {
class TwoRadioButtons : public QWidget {
  Q_OBJECT

 public:
  TwoRadioButtons() = delete;
  explicit TwoRadioButtons(const QString *text, const int checked,
                           const unsigned margins);

  bool IsFirstRadioButtonChecked() noexcept;
  bool IsSecondRadioButtonChecked() noexcept;

 private:
  QRadioButton *CreateQRadioButton(const QString &text, const bool checked);

  Label *label_{};
  QRadioButton *first_radio_button_{};
  QRadioButton *second_radio_button_{};
  VBoxLayout *v_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_TWO_RADIO_BUTTONS_H_
