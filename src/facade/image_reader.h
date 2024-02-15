#ifndef CPP7_MLP_FACADE_IMAGE_READER_H_
#define CPP7_MLP_FACADE_IMAGE_READER_H_

#include <QImage>
#include <vector>

namespace s21 {
class ImageReader {
 public:
  void ReadEmnistLetterImage(std::vector<unsigned> &emnist_letter,
                             const QImage &image);

 private:
  const unsigned kSizeNormalization = 28U;
  const unsigned kColorNormalization = 255U;

  QImage image_;
};
}  // namespace s21

#endif  // CPP7_MLP_FACADE_IMAGE_READER_H_
