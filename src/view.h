#pragma once

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QList>
#include <QMainWindow>
#include <QPainter>
#include <QSettings>
#include <QTimer>

#include "3rdparty/giflib/gif_lib.h"
#include "main.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace viewer {
class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_11_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_pushButton_save_image_clicked();
  void on_pushButton_gif_clicked();
  void on_horizontalSlider_actionTriggered(int action);
  void on_horizontalSlider_2_actionTriggered(int action);
  void on_horizontalSlider_3_actionTriggered(int action);
  void on_horizontalSlider_4_actionTriggered(int action);
  void on_horizontalSlider_5_actionTriggered(int action);
  void on_horizontalSlider_6_actionTriggered(int action);
  void on_horizontalSlider_7_actionTriggered(int action);
  void on_horizontalSlider_8_actionTriggered(int action);
  void on_horizontalSlider_9_actionTriggered(int action);
  void RecordGif();

 private:
  std::unique_ptr<Ui::View> ui;
  TestQt win;
  int x_value, y_value, z_value, scale_value, x_rotate_value, y_rotate_value,
      z_rotate_value;
  int projection, edge_type, edge_th, edge_color, v_type, v_color, v_th,
      field_color;
  bool check_file_conf;

  void WriteToFile();
  void ChangeColors();
  void ChangesFromFile();

  std::vector<QImage> frames_;  // Хранение кадров
  std::unique_ptr<QTimer> timer_;
  int frame_count_ = 0;  // Количество записанных кадров
  int max_frames_ = 50;
};
}  // namespace viewer