#ifndef IMAGERENDER_H
#define IMAGERENDER_H

#include <QWidget>
#include <QImage>

namespace Ui {
class ImageRender;
}

class ImageRender : public QWidget
{
    Q_OBJECT
    
public:
    explicit ImageRender(QWidget *parent = 0);
    ~ImageRender();

   void updateImage(QImage image);
    
protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    Ui::ImageRender *ui;

    QImage m_image;
    QImage m_imageScaled;
};

#endif // IMAGERENDER_H
