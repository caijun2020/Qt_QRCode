#include "QRParser.h"
#include "ui_QRParser.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QUrl>
#include <QDebug>
#include "QZXing.h"


QRParser::QRParser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRParser),
    m_image(NULL)
{
    ui->setupUi(this);

    m_scaledImgW.setParent(ui->label_image);

    // Enable drag&drop for label_image
    ui->label_image->installEventFilter(this);
    ui->label_image->setAcceptDrops(true);

}

QRParser::~QRParser()
{
    delete ui;

    if(m_image != NULL)
    {
        delete m_image;
        m_image = NULL;
    }
}

void QRParser::resizeEvent(QResizeEvent *e)
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

bool QRParser::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->label_image)
    {
        if(e->type() == QEvent::DragEnter)
        {
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(e);
            dee->acceptProposedAction();

            return true;
        }
        else if(e->type() == QEvent::Drop)
        {
            QDropEvent *de = dynamic_cast<QDropEvent *>(e);
            QList<QUrl> urls = de->mimeData()->urls();

            if(urls.isEmpty())
            {
                return true;
            }

            QString path = urls.first().toLocalFile();
            deCodeFromFile(path);

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return QRParser::eventFilter(obj, e);
    }
}

void QRParser::on_pushButton_browse_clicked()
{
    QString defaultLocalDir = ui->lineEdit_imageSource->text();

    QString fileName = QFileDialog::getOpenFileName( this,
                                                     tr("Select the image of 2D-Code"),
                                                     defaultLocalDir,
                                                     tr("Image files (*.jpg *jpeg *.png *.bmp *.gif)"));

    if (!fileName.isEmpty())
    {
        QString codeText = deCodeFromFile(fileName);
    }
}


void QRParser::updateImage(QString file)
{
    if(m_image != NULL)
    {
        delete m_image;
        m_image = NULL;
    }

    // Create a QImage
    m_image = new QImage(file);

    m_scaledImgW.updateImage(*m_image);
}

QString QRParser::deCodeFromQImage(const QImage &img)
{
    QZXing decoder;
    decoder.setDecoder(QZXing::DecoderFormat_Aztec |
                       QZXing::DecoderFormat_CODABAR |
                       QZXing::DecoderFormat_CODE_39 |
                       QZXing::DecoderFormat_CODE_93 |
                       QZXing::DecoderFormat_EAN_8 |
                       QZXing::DecoderFormat_ITF |
                       QZXing::DecoderFormat_MAXICODE |
                       QZXing::DecoderFormat_PDF_417 |
                       QZXing::DecoderFormat_RSS_14 |
                       QZXing::DecoderFormat_RSS_EXPANDED |
                       QZXing::DecoderFormat_UPC_A |
                       QZXing::DecoderFormat_UPC_E |
                       QZXing::DecoderFormat_UPC_EAN_EXTENSION |
                       QZXing::DecoderFormat_CODE_128_GS1 |
                       QZXing::DecoderFormat_QR_CODE |
                       QZXing::DecoderFormat_DATA_MATRIX |
                       QZXing::DecoderFormat_EAN_13 |
                       QZXing::DecoderFormat_CODE_128
                       );

    QString result = decoder.decodeImage(img);

    return result;
}

QString QRParser::deCodeFromFile(const QString &fileName)
{
    // Update image view
    updateImage(fileName);

    // Decode 2D code to QString
    QString codeText = deCodeFromQImage(*m_image);

    // Update LineEdit
    ui->lineEdit_imageSource->setText(fileName);

    // Update decode result
    if(!codeText.isEmpty())
    {
        ui->textEdit_result->setPlainText(codeText);
    }
    else
    {
        ui->textEdit_result->setPlainText("");
        qDebug() << tr("Parse failed!");
    }

    return codeText;
}
