#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QApplication>
#include <QDesktopWidget>
#include <QStandardPaths>
#include <QDateTime>
#include <QTimer>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    move((QApplication::desktop()->width() - width())/2, (QApplication::desktop()->height() - height())/2);
    setAttribute(Qt::WA_TranslucentBackground, true);
    //ui->statusBar->showMessage(QString::number(x()) + "," + QString::number(y()) + "     " + QString::number(width()) + "," + QString::number(height()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCaptureFullscreen_clicked()
{
    showMinimized();
    QEventLoop eventloop;
    QTimer::singleShot(500, &eventloop, SLOT(quit()));
    eventloop.exec();
    if(ui->checkBox->checkState() == Qt::Checked){
        QTimer::singleShot(12000, &eventloop, SLOT(quit()));
        eventloop.exec();
    }
    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    QApplication::clipboard()->setPixmap(pixmap, QClipboard::Clipboard);
    QDateTime time = QDateTime::currentDateTime();
    QString filename = time.toString("yyyyMMddhhmmss") + ".jpg";
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/" + filename;
    pixmap.save(path,0,100);
}

void MainWindow::on_btnCaptureWindow_clicked()
{
    showMinimized();
    QEventLoop eventloop;
    QTimer::singleShot(500, &eventloop, SLOT(quit()));
    eventloop.exec();
    if(ui->checkBox->checkState() == Qt::Checked){
        QTimer::singleShot(10000, &eventloop, SLOT(quit()));
        eventloop.exec();
    }
    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),x(),y(), frameGeometry().width(), frameGeometry().height());
    QApplication::clipboard()->setPixmap(pixmap, QClipboard::Clipboard);
    QDateTime time = QDateTime::currentDateTime();
    QString filename = time.toString("yyyyMMddhhmmss") + ".jpg";
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/" + filename;
    pixmap.save(path,0,100);
}

void MainWindow::resizeEvent(QResizeEvent *size)
{
    float r = (float) frameGeometry().width() / frameGeometry().height();
    QString sr = QString("%1").arg(r);
    ui->statusBar->showMessage(QString::number(x()) + "," + QString::number(y()) + "     " + QString::number(frameGeometry().width()) + "," + QString::number(frameGeometry().height()) + "     " + sr);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    ui->statusBar->showMessage(QString::number(x()) + "," + QString::number(y()) + "     " + QString::number(frameGeometry().width()) + "," + QString::number(frameGeometry().height()));
}
