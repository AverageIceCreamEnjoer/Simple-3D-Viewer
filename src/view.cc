#include "view.h"

#include <gif_lib.h>

#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QtWidgets>
#include <filesystem>

#include "./ui_mainwindow.h"

namespace viewer {

std::string getExecutablePath() {
  // Получаем путь к исполняемому файлу
  QString exePath = QCoreApplication::applicationFilePath();

  // Получаем директорию исполняемого файла
  QDir exeDir = QFileInfo(exePath).absoluteDir();
  std::string path = exeDir.absolutePath().toStdString();
  std::string toRemove = "/install";
  if (path.find(toRemove) != std::string::npos)
    path.erase(path.find(toRemove), toRemove.length());
  return path;
}

View::View(QWidget* parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  namespace fs = std::filesystem;
  std::string path = getExecutablePath() + "/obj/";
  for (const auto& entry : fs::directory_iterator(path)) {
    std::string temp = entry.path().string();
    QString temp2 = QString::fromStdString(temp);
    ui->comboBox->addItem(temp2);
  }
  ui->comboBox_3->addItems({"green", "blue", "red", "yellow", "black"});
  ui->comboBox_2->addItems({"green", "blue", "red", "yellow", "black"});
  ui->comboBox_4->addItems({"white", "blue", "red", "yellow", "black"});
  ui->verticalLayout_2->addWidget(&win);
  x_value = 0, y_value = 0, z_value = 0, scale_value = 50, x_rotate_value = 0,
  y_rotate_value = 0, z_rotate_value = 0;
  projection = 1, edge_type = 0, edge_th = 0, edge_color = 0, v_type = 0,
  v_color = 0, v_th = 0, field_color = 0;
  ui->horizontalSlider_3->setValue(50);
  ui->horizontalSlider_4->setValue(50);
  ui->horizontalSlider_5->setValue(50);
  ui->horizontalSlider_6->setValue(50);
  ui->horizontalSlider_7->setValue(50);
  ui->horizontalSlider_8->setValue(50);
  ui->horizontalSlider_9->setValue(50);
  check_file_conf = true;
}

View::~View() { delete ui; }

void View::write_to_file() {
  std::ofstream out(getExecutablePath() + "/build/models.txt",
                    std::ios_base::out);
  out << projection << "\n";
  out << edge_type << "\n";
  out << edge_th << "\n";
  out << edge_color << "\n";
  out << v_type << "\n";
  out << v_color << "\n";
  out << v_th << "\n";
  out << field_color << "\n";
  out.close();
}

void View::change_colors() {
  std::string color = ui->comboBox_3->currentText().toStdString();
  if (color == "blue") {
    win.edge_color(0, 0, 128);
    edge_color = 1;
  } else if (color == "red") {
    win.edge_color(128, 0, 0);
    edge_color = 2;
  } else if (color == "yellow") {
    win.edge_color(255, 255, 0);
    edge_color = 3;
  } else if (color == "black") {
    win.edge_color(0, 0, 0);
    edge_color = 4;
  } else {
    win.edge_color(0, 128, 0);
    edge_color = 0;
  }
  color = ui->comboBox_2->currentText().toStdString();
  if (color == "blue") {
    win.vertex_color(0, 0, 128);
    v_color = 1;
  } else if (color == "red") {
    win.vertex_color(128, 0, 0);
    v_color = 2;
  } else if (color == "yellow") {
    win.vertex_color(255, 255, 0);
    v_color = 3;
  } else if (color == "black") {
    win.vertex_color(0, 0, 0);
    v_color = 4;
  } else {
    win.vertex_color(0, 128, 0);
    v_color = 0;
  }
  color = ui->comboBox_4->currentText().toStdString();
  if (color == "blue") {
    win.field_color(0, 0, 128);
    field_color = 1;
  } else if (color == "red") {
    win.field_color(128, 0, 0);
    field_color = 2;
  } else if (color == "yellow") {
    field_color = 3;
    win.field_color(255, 255, 0);
  } else if (color == "black") {
    field_color = 4;
    win.field_color(0, 0, 0);
  } else {
    field_color = 0;
    win.field_color(71, 72, 74);
  }
}

void View::changes_from_file() {
  std::string from_conf;
  std::ifstream in(getExecutablePath() + "/build/models.txt");
  if (std::getline(in, from_conf) && check_file_conf) {
    if (std::stoi(from_conf) == 1) {
      win.central_proj();
      projection = 1;
    } else {
      win.parallel_proj();
      projection = 0;
    }

    std::getline(in, from_conf);
    if (std::stoi(from_conf) == 0) {
      win.EdgeMode_false();
      edge_type = 0;
    } else {
      win.EdgeMode_true();
      edge_type = 1;
    }

    std::getline(in, from_conf);
    ui->horizontalSlider_2->setValue(std::stoi(from_conf));
    win.edge_size(std::stoi(from_conf));
    edge_th = std::stoi(from_conf);

    std::getline(in, from_conf);
    ui->comboBox_3->setCurrentIndex(std::stoi(from_conf));
    edge_color = std::stoi(from_conf);

    std::getline(in, from_conf);
    v_type = std::stoi(from_conf);
    win.vertex_mode(std::stoi(from_conf));

    std::getline(in, from_conf);
    ui->comboBox_2->setCurrentIndex(std::stoi(from_conf));
    v_color = std::stoi(from_conf);

    std::getline(in, from_conf);
    ui->horizontalSlider->setValue(std::stoi(from_conf));
    win.vertex_size(std::stoi(from_conf));
    v_th = std::stoi(from_conf);

    std::getline(in, from_conf);
    ui->comboBox_4->setCurrentIndex(std::stoi(from_conf));
    field_color = std::stoi(from_conf);
  }
  change_colors();
  in.close();
}

void View::on_pushButton_14_clicked() {
  std::string path = getExecutablePath() + "/obj/";
  bool check_file = false;
  QString obj = ui->textEdit->toPlainText();
  if (!((obj.toStdString()).empty())) {
    std::ifstream file(obj.toStdString());
    if (file.is_open() && obj.endsWith(".obj")) {
      check_file = win.change_obj(obj.toStdString());
      if (check_file) {
        std::string info = "Model name: " + obj.toStdString() + "\n" +
                           "Number vertex: " + std::to_string(win.getVertex()) +
                           "\n" +
                           "Number edges: " + std::to_string(win.getFace());
        ui->textBrowser->setText(QString::fromStdString(info));
      }
    } else {
      std::ifstream file(ui->comboBox->currentText().toStdString(),
                         std::ios_base::in);
      if (file.is_open() &&
          !((ui->comboBox->currentText().toStdString()).empty()) &&
          ui->comboBox->currentText().endsWith(".obj")) {
        check_file = win.change_obj(ui->comboBox->currentText().toStdString());
        if (check_file) {
          std::string info =
              "Model name: " + ui->comboBox->currentText().toStdString() +
              "\n" + "Number vertex: " + std::to_string(win.getVertex()) +
              "\n" + "Number edges: " + std::to_string(win.getFace());
          ui->textBrowser->setText(QString::fromStdString(info));
        }
      } else {
        std::string info = "No such file";
        ui->textBrowser->setText(QString::fromStdString(info));
      }
    }
  } else {
    std::ifstream file(ui->comboBox->currentText().toStdString(),
                       std::ios_base::in);
    if (file.is_open() &&
        !((ui->comboBox->currentText().toStdString()).empty()) &&
        ui->comboBox->currentText().endsWith(".obj")) {
      check_file = win.change_obj(ui->comboBox->currentText().toStdString());
      if (check_file) {
        std::string info =
            "Model name: " + ui->comboBox->currentText().toStdString() + "\n" +
            "Number vertex: " + std::to_string(win.getVertex()) + "\n" +
            "Number edges: " + std::to_string(win.getFace());
        ui->textBrowser->setText(QString::fromStdString(info));
      }
    } else {
      std::string info = "No such file";
      ui->textBrowser->setText(QString::fromStdString(info));
    }
  }
  if (check_file) {
    changes_from_file();
  } else {
    change_colors();
    x_value = 0, y_value = 0, z_value = 0, scale_value = 50, x_rotate_value = 0,
    y_rotate_value = 0, z_rotate_value = 0;
  }
  ui->horizontalSlider_3->setValue(50);
  ui->horizontalSlider_4->setValue(50);
  ui->horizontalSlider_5->setValue(50);
  ui->horizontalSlider_6->setValue(50);
  ui->horizontalSlider_6->setValue(50);
  ui->horizontalSlider_7->setValue(50);
  ui->horizontalSlider_8->setValue(50);
  ui->horizontalSlider_9->setValue(50);
  write_to_file();
  check_file_conf = false;
  win.update_view();
}

void View::on_pushButton_7_clicked() {
  win.parallel_proj();
  projection = 0;
  write_to_file();
}

void View::on_pushButton_8_clicked() {
  win.central_proj();
  projection = 1;
  write_to_file();
}

void View::on_pushButton_9_clicked() {
  win.EdgeMode_true();
  edge_type = 1;
  write_to_file();
}

void View::on_pushButton_10_clicked() {
  win.EdgeMode_false();
  edge_type = 0;
  write_to_file();
}

void View::on_pushButton_11_clicked() {
  win.vertex_mode(-1);
  v_type = -1;
  write_to_file();
}

void View::on_pushButton_12_clicked() {
  win.vertex_mode(0);
  v_type = 0;
  write_to_file();
}

void View::on_pushButton_13_clicked() {
  win.vertex_mode(1);
  v_type = 1;
  write_to_file();
}

void View::on_horizontalSlider_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider->value();
  win.vertex_size(curr_value);
  v_th = curr_value;
  write_to_file();
}

void View::on_horizontalSlider_2_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_2->value();
  win.edge_size(curr_value);
  edge_th = curr_value;
  write_to_file();
}

void View::on_horizontalSlider_3_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_3->value();
  curr_value -= 50;
  win.X_move(((double)((curr_value - x_value))) / 50);
  x_value = curr_value;
}

void View::on_horizontalSlider_4_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_4->value();
  curr_value -= 50;
  win.Y_move(((double)((curr_value - y_value))) / 50);
  y_value = curr_value;
}

void View::on_horizontalSlider_5_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_5->value();
  curr_value -= 50;
  win.Z_move(((double)((curr_value - z_value))) / 50);
  z_value = curr_value;
}

void View::on_horizontalSlider_6_actionTriggered(int action) {
  win.change_scale(((double)(50)) / scale_value);
  int curr_value = ui->horizontalSlider_6->value();
  if (curr_value == 0) {
    curr_value++;
  }
  win.change_scale(((double)(curr_value)) / 50);
  scale_value = curr_value;
  win.update_view();
}

void View::on_horizontalSlider_7_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_7->value();
  curr_value -= 50;
  win.X_rotate(((double)((curr_value - x_rotate_value))) / 10);
  x_rotate_value = curr_value;
}

void View::on_horizontalSlider_8_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_8->value();
  curr_value -= 50;
  win.Y_rotate(((double)((curr_value - y_rotate_value))) / 10);
  y_rotate_value = curr_value;
}

void View::on_horizontalSlider_9_actionTriggered(int action) {
  int curr_value = ui->horizontalSlider_9->value();
  curr_value -= 50;
  win.Z_rotate(((double)((curr_value - z_rotate_value))) / 10);
  z_rotate_value = curr_value;
}

void View::on_pushButton_save_image_clicked() {
  QString str = QFileDialog::getSaveFileName(0, "Сохранить изображение",
                                             "/mnt/c/Users/user/Pictures/",
                                             "*.png ;; *.jpg ;; *.bmp");

  if (!str.isEmpty()) {
    if (!str.endsWith(".png") && !str.endsWith(".jpg") &&
        !str.endsWith(".bmp")) {
      str += ".png";
    }
  }

  if (!str.isEmpty()) {
    win.Save_image(str);
  }
}

void View::on_pushButton_gif_clicked() {
  ui->label_record->setText("Record is on!");
  frames_.clear();
  frame_count_ = 0;

  // Настраиваем таймер
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &View::RecordGif);
  timer_->start(100);  // Записываем кадры каждые 100 мс (10 FPS)
}

void View::RecordGif() {
  QImage frame;
  win.getFrame(&frame);
  int width = win.getWidth();
  int height = win.getHeight();

  frames_.push_back(frame);

  frame_count_++;

  if (frame_count_ >= max_frames_) {  // Если записано нужное количество кадров
    timer_->stop();

    // Выбор пути сохранения GIF
    QString path = QFileDialog::getSaveFileName(0, "Сохранить изображение",
                                                "~/gif1.gif", "*.gif");
    if (path.isEmpty()) {
      qWarning("Путь сохранения GIF не выбран.");
      return;
    }

    // Создаем временную директорию для сохранения кадров
    QDir tempDir("temp_frames");
    if (!tempDir.exists()) {
      if (!tempDir.mkpath(".")) {
        qWarning("Не удалось создать временную директорию.");
        return;
      }
    }

    // Сохраняем кадры во временные файлы
    QString tempFilePath = tempDir.filePath("frame_%1.png");
    QVector<QString> tempFiles;
    for (int i = 0; i < frames_.size(); ++i) {
      QString frameFilePath = tempFilePath.arg(i);
      if (!frames_[i].save(frameFilePath)) {
        qWarning() << "Failed to save frame to" << frameFilePath;
        return;
      }
      tempFiles.append(frameFilePath);
    }

    // Проверка наличия команды convert
    QProcess checkProcess;
    checkProcess.start("convert", QStringList() << "--version");
    checkProcess.waitForFinished();
    if (checkProcess.exitCode() != 0) {
      qWarning(
          "ImageMagick convert command not found. Please install ImageMagick.");
      return;
    }

    // Используем ImageMagick для создания GIF-анимации
    QStringList args;
    args << "-delay" << "50" << "-loop" << "0" << "-dispose"
         << "Background";  // Увеличиваем задержку до 50 (0.5 секунды)
    for (const QString& file : tempFiles) {
      args << file;
    }
    args << path;

    QProcess process;
    process.start("convert", args);
    process.waitForFinished();

    if (process.exitCode() != 0) {
      qWarning() << "ImageMagick convert failed with exit code"
                 << process.exitCode();
      qWarning() << "Standard error:" << process.readAllStandardError();
      return;
    }

    // Удаляем временные файлы
    for (const QString& frameFilePath : tempFiles) {
      QFile::remove(frameFilePath);
    }

    // Удаляем временную директорию
    tempDir.removeRecursively();

    frames_.clear();
    frame_count_ = 0;

    ui->label_record->setText("Record completed!");
  }
}

}  // namespace viewer
