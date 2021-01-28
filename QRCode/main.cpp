#include "MainWindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>


#define USE_SYS_QTEXTCODEC

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef USE_SYS_QTEXTCODEC
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);

#if 1
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#endif

#endif

    MainWindow w;
    w.show();

    int width = QApplication::desktop( )->width( ) * 1/2;
    int height = QApplication::desktop( )->height( ) * 1/2;
    w.resize(width, height);
    w.move((QApplication::desktop( )->width( ) - width) / 2, (QApplication::desktop( )->height( ) - height) / 3);

    return a.exec();
}
