#include "mainwindow.h"
#include "src/config_file_parser.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , viewer_(new util::CableViewer(this))
{
    ui->setupUi(this);
    resize(800, 600);

    // Slot Actions
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    // Открываем системный файловый менеджер
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Открыть файл соединений",
        "",
        "Text Files (*.txt);;All Files (*)"
    );

    if (fileName.isEmpty()) return;

    cable_.reset();
    cable_ = util::ConfigFileParser::parseWireFile(fileName);

    if (cable_) {
        ui->lbl_file_name->setText(fileName);
        ui->lbl_connections_value->setText(QString::number(cable_->GetConnectionsCount()));
        ui->lbl_circuits_value->setText(QString::number(cable_->GetCircuitsCount()));
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть или обработать файл");
    }

    ui->w_scheme->setCable(cable_.value());
}
