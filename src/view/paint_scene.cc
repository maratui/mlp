#include "paint_scene.h"

void s21::PaintScene::SetImage(QImage &&image) {
  clear();

  for (auto i = 0; i < image.width(); i++) {
    for (auto j = 0; j < image.height(); j++) {
      if (qGray(image.pixel(i, j)) < 10) {
        addEllipse(i, j, 2, 2, QPen(Qt::NoPen), QBrush(Qt::black));
      }
    }
  }
}

void s21::PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  addEllipse(event->scenePos().x() - 30, event->scenePos().y() - 30, 60, 60,
             QPen(Qt::NoPen), QBrush(Qt::black));
  previousPoint = event->scenePos();
}

void s21::PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(),
          event->scenePos().y(),
          QPen(Qt::black, 60, Qt::SolidLine, Qt::RoundCap));
  previousPoint = event->scenePos();
}
