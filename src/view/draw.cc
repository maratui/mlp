#include "draw.h"

s21::Draw::Draw() {
  label_ = new Label("Рисование", false, kMargins);
  paint_scene_ = new PaintScene();
  graphics_view_ = new QGraphicsView();
  clear_button_ = new Button("Очистить сцену рисования", false);

  v_layout_ = new VBoxLayout(kMargins, this);
  v_layout_->addWidget(label_, 0, Qt::AlignTop);
  v_layout_->addWidget(graphics_view_, 1);
  v_layout_->addWidget(clear_button_, 2);

  graphics_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  graphics_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  graphics_view_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  graphics_view_->setScene(paint_scene_);

  paint_scene_->setSceneRect(0, 0, graphics_view_->width(),
                             graphics_view_->height());

  image_ = QImage(graphics_view_->width(), graphics_view_->height(),
                  QImage::Format_ARGB32_Premultiplied);

  connect(clear_button_, SIGNAL(clicked()), this, SLOT(ClearButtonClicked()));

  setContentsMargins(kMargins, kMargins, kMargins, kMargins);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize s21::Draw::sizeHint() const {
  QSize size = QWidget::sizeHint();

  size.rwidth() = 600;
  size.rheight() = 600;

  return size;
}

void s21::Draw::SetImage(const QImage &image) {
  paint_scene_->SetImage(
      image.scaled(graphics_view_->width(), graphics_view_->height() - 40));
}

const QImage &s21::Draw::GetImage() {
  QPainter painter(&image_);

  image_.fill(Qt::white);
  paint_scene_->render(&painter);

  return image_;
}

void s21::Draw::ClearButtonClicked() { paint_scene_->clear(); }
