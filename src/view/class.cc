#include "class.h"

s21::Class::Class() {
  label_ = new Label("Классификация", false, kMargins);
  load_bmp_image_button_ = new Button("Загрузить BMP изображение", false);
  classify_image_button_ = new Button("Классифицировать изображение", false);
  letter_label_ = new QLabel();
  v_layout_ = new VBoxLayout(kMargins, this);

  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  v_layout_->addWidget(load_bmp_image_button_, 1, Qt::AlignTop);
  v_layout_->addWidget(classify_image_button_, 2, Qt::AlignTop);
  v_layout_->addWidget(letter_label_, 3, Qt::AlignTop);

  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

QSize s21::Class::sizeHint() const {
  QSize size = QWidget::sizeHint();

  size.rwidth() = 250;

  return size;
}

void s21::Class::SetLetterLabel(const std::string &letter) noexcept {
  QFont font;

  font.setPointSize(100);
  letter_label_->setFont(font);
  letter_label_->setAlignment(Qt::AlignCenter);
  letter_label_->setText(QString::fromStdString(letter));
}

s21::Button *s21::Class::GetLoadBMPImageButton() noexcept {
  return load_bmp_image_button_;
}

s21::Button *s21::Class::GetClassifyImageButton() noexcept {
  return classify_image_button_;
}
