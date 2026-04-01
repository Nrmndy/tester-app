#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "src/cable.h"
#include "src/cable_viewer.h"

using namespace domain;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();

private:
    Ui::MainWindow *ui;

    std::optional<Cable> cable_;

    util::CableViewer viewer_;
};
#endif // MAINWINDOW_H
