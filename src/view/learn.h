#ifndef CPP7_MLP_VIEW_LEARN_H_
#define CPP7_MLP_VIEW_LEARN_H_

#include <QWidget>

#include "button.h"
#include "label.h"
#include "label_line_edit.h"
#include "layout.h"
#include "two_radio_buttons.h"

namespace s21 {
class Learn : public QWidget {
  Q_OBJECT

 public:
  Learn();

  QSize sizeHint() const override;

  Button *GetRunEpochsLearnButton() noexcept;
  Button *GetRunGroupsLearnButton() noexcept;
  TwoRadioButtons *GetNetworkStrategy() noexcept;
  unsigned GetHiddenLayersCount() noexcept;
  unsigned GetEpochsCount() noexcept;
  unsigned GetGroupsCount() noexcept;

 private:
  const unsigned kMargins = 3U;

  Label *label_{};
  LabelLineEdit *hidden_layers_count_{};
  TwoRadioButtons *network_strategy_{};
  LabelLineEdit *epochs_count_{};
  Button *run_epochs_learn_button_{};
  LabelLineEdit *groups_count_{};
  Button *run_groups_learn_button_{};
  VBoxLayout *v_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_LEARN_H_
