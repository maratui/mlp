QT          += widgets charts

CONFIG      += c++17

INCLUDEPATH += \
  model \
  facade \
  controller \
  view

SOURCES     += \
  ../model/node.cc \
  ../model/graph_layer.cc \
  ../model/graph_network.cc \
  ../model/matrix_layer.cc \
  ../model/matrix_network.cc \
  ../model/network.cc \
  ../facade/file_reader.cc \
  ../facade/image_reader.cc \
  ../facade/test_results.cc \
  ../facade/facade.cc \
  ../controller/controller.cc \
  ../view/layout.cc \
  ../view/label.cc \
  ../view/line_edit.cc \
  ../view/button.cc \
  ../view/label_line_edit.cc \
  ../view/two_radio_buttons.cc \
  ../view/learn.cc \
  ../view/test.cc \
  ../view/chart.cc \
  ../view/class.cc \
  ../view/paint_scene.cc \
  ../view/draw.cc \
  ../view/view.cc \
  ../view/main.cc

HEADERS     += \
  ../model/node.h \
  ../model/graph_layer.h \
  ../model/graph_network.h \
  ../model/matrix_layer.h \
  ../model/matrix_network.h \
  ../model/network.h \
  ../facade/file_reader.h \
  ../facade/image_reader.h \
  ../facade/test_results.h \
  ../facade/facade.h \
  ../controller/controller.h \
  ../view/layout.h \
  ../view/label.h \
  ../view/line_edit.h \
  ../view/button.h \
  ../view/label_line_edit.h \
  ../view/two_radio_buttons.h \
  ../view/learn.h \
  ../view/test.h \
  ../view/chart.h \
  ../view/class.h \
  ../view/paint_scene.h \
  ../view/draw.h \
  ../view/view.h
