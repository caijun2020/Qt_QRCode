#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_QRCodeGenW(new QRGenerator),
    m_QRCodeParseW(new QRParser)
{
    ui->setupUi(this);

    m_QRCodeGenW->setParent(ui->frame_QRGen);
    m_QRCodeParseW->setParent(ui->frame_QRParse);

    // Set Window Title
    this->setWindowTitle(tr("QR-Code Generator"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_QRCodeGenW;
    delete m_QRCodeParseW;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    m_QRCodeGenW->resize(ui->frame_QRGen->size());
    m_QRCodeParseW->resize(ui->frame_QRParse->size());
}

