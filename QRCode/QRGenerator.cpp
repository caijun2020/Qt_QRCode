#include "QRGenerator.h"
#include "ui_QRGenerator.h"
#include <QPainter>
#include <QDebug>

QRGenerator::QRGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRGenerator),
    m_qrData(NULL),
    m_image(NULL)
{
    ui->setupUi(this);

    m_scaledImgW.setParent(ui->label_image);

    generateImage("Hello QR Code", 400);
}

QRGenerator::~QRGenerator()
{
    delete ui;

    if(m_qrData != NULL)
    {
        QRcode_free(m_qrData);
    }

    if(m_image != NULL)
    {
        delete m_image;
        m_image = NULL;
    }
}

void QRGenerator::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    QWidget *pWidget = static_cast<QWidget*>(this->parent());

    if(pWidget != NULL)
    {
        this->resize(pWidget->size());
        //qDebug() << "QRGenerator::resizeEvent() pWidget->size()=" << pWidget->size();
        m_scaledImgW.resize(ui->label_image->size());
    }
}

int QRGenerator::getQRWidth() const
{
    if(m_qrData != NULL)
    {
        return m_qrData->width;
    }
    else
    {
        return 0;
    }
}

void QRGenerator::setQRInfo(QString str)
{
    if(m_qrData != NULL)
    {
        QRcode_free(m_qrData);
    }

    m_qrData = QRcode_encodeString(str.toStdString().c_str(),
                             1,
                             QR_ECLEVEL_L,
                             QR_MODE_8,
                             1);
}

QSize QRGenerator::minimumSizeHint() const
{
    QSize s;

    if(m_qrData != NULL)
    {
        int qr_width = m_qrData->width > 0 ? m_qrData->width : 1;
        s = QSize(qr_width, qr_width);
    }
    else
    {
        s = QSize(50, 50);
    }

    return s;
}

bool QRGenerator::saveImage(QString fileName)
{
    bool ret = false;

    if(!fileName.isEmpty() && m_image != NULL)
    {
        ret = m_image->save(fileName);
    }

    return ret;
}

void QRGenerator::draw(QPainter &painter, int width, int height)
{
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    const int qr_width = m_qrData->width > 0 ? m_qrData->width : 1;
    double scale_x = width / qr_width;
    double scale_y = height / qr_width;
    for(int y = 0; y < qr_width; y ++)
    {
        for(int x = 0; x < qr_width; x++)
        {
            unsigned char b = m_qrData->data[y * qr_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
}


QImage& QRGenerator::generateImage(QString info, int size)
{
    if(m_image != NULL)
    {
        delete m_image;
        m_image = NULL;
    }

    // Create a QImage
    m_image = new QImage(size, size, QImage::Format_Mono);

    // Set QRCode info
    setQRInfo(info);

    QPainter painter(m_image);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, size, size);

    if(m_qrData != NULL)
    {
        draw(painter, size, size);

        m_scaledImgW.updateImage(*m_image);
    }

    return *m_image;
}

void QRGenerator::on_pushButton_generate_clicked()
{
    generateImage(ui->textEdit_input->toPlainText(), 300);
}

void QRGenerator::on_pushButton_save_clicked()
{
    saveImage("QR.jpg");
}
