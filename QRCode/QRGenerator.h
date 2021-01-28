#ifndef QRGENERATOR_H
#define QRGENERATOR_H

#include <QWidget>
#include <QImage>
#include "qrencode.h"
#include "ImageRender.h"

namespace Ui {
class QRGenerator;
}

class QRGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit QRGenerator(QWidget *parent = nullptr);
    ~QRGenerator();

    QImage& generateImage(QString info, int size);
    int getQRWidth() const;
    bool saveImage(QString name);

protected:
    void resizeEvent(QResizeEvent *e);
    QSize minimumSizeHint() const;

private slots:
    void on_pushButton_generate_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::QRGenerator *ui;

    QRcode *m_qrData;   // QRCode class pointer

    QImage *m_image;    // QImage of QRCode

    ImageRender m_scaledImgW;   // scaled image widget

    // Draw QImage
    void draw(QPainter &painter, int width, int height);

    // Update QRCode context info
    void setQRInfo(QString str);
};

#endif // QRGENERATOR_H
