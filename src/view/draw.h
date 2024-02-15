#ifndef CPP7_MLP_VIEW_DRAW_H_
#define CPP7_MLP_VIEW_DRAW_H_

#include <QGraphicsView>
#include <QWidget>

#include "button.h"
#include "label.h"
#include "layout.h"
#include "paint_scene.h"

namespace s21 {
class Draw : public QWidget {
  Q_OBJECT

 public:
  Draw();

  QSize sizeHint() const override;

  void SetImage(const QImage &image);
  const QImage &GetImage();

 private slots:
  void ClearButtonClicked();

 private:
  const unsigned kMargins = 3U;

  Label *label_{};
  PaintScene *paint_scene_{};
  QGraphicsView *graphics_view_{};
  Button *clear_button_{};
  VBoxLayout *v_layout_{};

  QImage image_;
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_DRAW_H_
