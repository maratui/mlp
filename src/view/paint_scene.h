#ifndef CPP7_MLP_VIEW_PAINTSCENE_H_
#define CPP7_MLP_VIEW_PAINTSCENE_H_

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace s21 {
class PaintScene : public QGraphicsScene {
  Q_OBJECT

 public:
  void SetImage(QImage &&image);

 private:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

  QPointF previousPoint;
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_PAINTSCENE_H_
