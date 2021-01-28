#include "ImageRender.h"
#include "ui_ImageRender.h"
#include <QPainter>
#include <QRgb>
#include <QDebug>

ImageRender::ImageRender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageRender)
{
    ui->setupUi(this);
    this->move(0, 0);
}

ImageRender::~ImageRender()
{
    delete ui;
}

void ImageRender::updateImage(QImage image)
{
    m_image = image;
    m_imageScaled = image;

    this->update();

    // If image is valid
    if(!image.isNull())
    {
        this->resize(image.width(), image.height());
        qDebug() << "ImageRender::updateImage image.size=" << image.size();
    }
}

void ImageRender::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter paint(this);

    if(!m_imageScaled.isNull())
    {
        // Draw the image in left corner of widget
        //paint.drawImage(QPoint(0, 0), m_imageScaled);

        // Draw the image in the central of widget
        paint.drawImage(QPoint((this->width() - m_imageScaled.width())/2, (this->height() - m_imageScaled.height())/2), m_imageScaled);
    }
    else
    {
        paint.drawText(QPoint(this->width()/2, this->height()/2), tr("Invalid image data!"));
    }

    paint.end();
}

void ImageRender::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    QWidget *pWidget = static_cast<QWidget*>(this->parent());

    if(pWidget != NULL)
    {
        this->resize(pWidget->size());
        //qDebug() << "ImageRender::resizeEvent() pWidget->size()=" << pWidget->size();
    }

    if(!m_image.isNull())
    {
        // Keep the original width&height ratio of image
        m_imageScaled = m_image.scaled(this->size(), Qt::KeepAspectRatio);
        this->update();
    }
}
