#ifndef CPP7_MLP_VIEW_CLASS_H_
#define CPP7_MLP_VIEW_CLASS_H_

#include <QWidget>

#include "button.h"
#include "label.h"
#include "layout.h"

namespace s21 {
class Class : public QWidget {
  Q_OBJECT

 public:
  Class();

  QSize sizeHint() const override;

  void SetLetterLabel(const std::string &letter) noexcept;
  Button *GetLoadBMPImageButton() noexcept;
  Button *GetClassifyImageButton() noexcept;

 private:
  const unsigned kMargins = 3U;

  Label *label_{};
  QLabel *letter_label_{};
  Button *load_bmp_image_button_{};
  Button *classify_image_button_{};
  VBoxLayout *v_layout_{};
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_CLASS_H_
