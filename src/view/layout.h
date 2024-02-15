#ifndef CPP7_MLP_VIEW_LAYOUT_H_
#define CPP7_MLP_VIEW_LAYOUT_H_

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace s21 {
class GridLayout : public QGridLayout {
  Q_OBJECT

 public:
  explicit GridLayout(const unsigned margins, QWidget *parent);
};

class VBoxLayout : public QVBoxLayout {
  Q_OBJECT

 public:
  explicit VBoxLayout(const unsigned margins, QWidget *parent);
};

class HBoxLayout : public QHBoxLayout {
  Q_OBJECT

 public:
  explicit HBoxLayout(const unsigned margins, QWidget *parent);
};
}  // namespace s21

#endif  // CPP7_MLP_VIEW_LAYOUT_H_
