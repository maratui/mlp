#include "learn.h"

s21::Learn::Learn() {
  label_ = new Label("Обучение", false, kMargins);
  hidden_layers_count_ =
      new LabelLineEdit("Количество скрытых слоев:  ", "2", 1, false, kMargins);
  QString text[3] = {"Реализация перцептрона", "Матричный вид", "Графовый вид"};
  network_strategy_ = new TwoRadioButtons(text, 0, kMargins);
  epochs_count_ =
      new LabelLineEdit("Количество эпох обучения:  ", "3", 1, false, kMargins);
  run_epochs_learn_button_ = new Button("Запустить обучение с эпохами", false);
  groups_count_ = new LabelLineEdit("Количество групп обучения:  ", "5", 1,
                                    false, kMargins);
  run_groups_learn_button_ =
      new Button("Запустить обучение с кросс-валидацией", false);
  v_layout_ = new VBoxLayout(kMargins, this);

  hidden_layers_count_->SetRange(2U, 5U);
  epochs_count_->SetRange(2U, 9U);
  groups_count_->SetRange(2U, 9U);

  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  v_layout_->addWidget(hidden_layers_count_, 1, Qt::AlignTop);
  v_layout_->addWidget(network_strategy_, 2, Qt::AlignTop);
  v_layout_->addWidget(epochs_count_, 3, Qt::AlignTop);
  v_layout_->addWidget(run_epochs_learn_button_, 4, Qt::AlignTop);
  v_layout_->addWidget(groups_count_, 4, Qt::AlignTop);
  v_layout_->addWidget(run_groups_learn_button_, 5, Qt::AlignTop);

  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize s21::Learn::sizeHint() const {
  QSize size = QWidget::sizeHint();

  size.rwidth() = 300;

  return size;
}

s21::Button *s21::Learn::GetRunEpochsLearnButton() noexcept {
  return run_epochs_learn_button_;
}

s21::Button *s21::Learn::GetRunGroupsLearnButton() noexcept {
  return run_groups_learn_button_;
}

s21::TwoRadioButtons *s21::Learn::GetNetworkStrategy() noexcept {
  return network_strategy_;
}

unsigned s21::Learn::GetHiddenLayersCount() noexcept {
  return hidden_layers_count_->GetUnsignedValue();
}

unsigned s21::Learn::GetEpochsCount() noexcept {
  return epochs_count_->GetUnsignedValue();
}

unsigned s21::Learn::GetGroupsCount() noexcept {
  return groups_count_->GetUnsignedValue();
}
