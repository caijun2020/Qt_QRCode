#ifndef QRPARSER_H
#define QRPARSER_H

#include <QWidget>
#include <QImage>
#include "ImageRender.h"

namespace Ui {
class QRParser;
}

class QRParser : public QWidget
{
    Q_OBJECT

public:
    explicit QRParser(QWidget *parent = nullptr);
    ~QRParser();

    QString deCodeFromFile(const QString &fileName);
    QString deCodeFromQImage(const QImage &img);

protected:
    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *obj, QEvent *e);

private slots:
    void on_pushButton_browse_clicked();

private:
    Ui::QRParser *ui;

    QImage *m_image;    // QImage of QRCode
    ImageRender m_scaledImgW;   // scaled image widget

    void updateImage(QString file);
};

#endif // QRPARSER_H
