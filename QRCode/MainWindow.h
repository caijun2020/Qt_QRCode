#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QRGenerator.h"
#include "QRParser.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    Ui::MainWindow *ui;

    QRGenerator *m_QRCodeGenW;
    QRParser *m_QRCodeParseW;
};
#endif // MAINWINDOW_H
