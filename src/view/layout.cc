#include "layout.h"

s21::GridLayout::GridLayout(const unsigned margins, QWidget *parent)
    : QGridLayout(parent) {
  setContentsMargins(margins, margins, margins, margins);
  setSpacing(0);
}

s21::VBoxLayout::VBoxLayout(const unsigned margins, QWidget *parent)
    : QVBoxLayout(parent) {
  setContentsMargins(margins, margins, margins, margins);
  setSpacing(3);
}

s21::HBoxLayout::HBoxLayout(const unsigned margins, QWidget *parent)
    : QHBoxLayout(parent) {
  setContentsMargins(margins, margins, margins, margins);
  setSpacing(0);
}
