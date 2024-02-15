#include "image_reader.h"

void s21::ImageReader::ReadEmnistLetterImage(
    std::vector<unsigned> &emnist_letter, const QImage &image) {
  image_ = image.scaled(kSizeNormalization, kSizeNormalization);

  emnist_letter.clear();
  emnist_letter.push_back(0U);
  for (auto i = 0U; i < kSizeNormalization; i++) {
    for (auto j = 0U; j < kSizeNormalization; j++) {
      auto rgb = image_.pixel(i, j);
      emnist_letter.push_back(kColorNormalization - (unsigned)qGray(rgb));
    }
  }
}
