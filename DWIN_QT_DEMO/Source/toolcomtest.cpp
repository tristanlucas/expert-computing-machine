#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QtSerialPort>
#include <QMessageBox>
#include "toolcomtest.h"
#include "tooldefs.h"
#include "tooltranslator.h"

ToolComTest::ToolComTest(QWidget *parent)
  : QWidget(parent)
  , m_serialPort(0)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 20, 40, 20);
    layout->setSpacing(20);

    QWidget* widget1 = new QWidget(this);
    widget1->setFixedHeight(30);
    widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* layout1 = new QHBoxLayout(widget1);
    layout1->setContentsMargins(0, 0, 0, 0);
    layout1->setSpacing(10);

    QLabel* label1 = new QLabel(widget1);
    label1->setText(ToolTranslator::Translate("Label_1000300"));
    label1->setFixedSize(80, 30);
    label1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout1->addWidget(label1);

    m_comList = new QComboBox(widget1);
    QStringList portlist;
    portlist << "COM1" << "COM2" << "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8";
    m_comList->addItems(portlist);
    m_comList->setCurrentIndex(1);
    m_comList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout1->addWidget(m_comList);

    m_btnOpen = new QPushButton(widget1);
    m_btnOpen->setObjectName(tr("btnOpenCom"));
    m_btnOpen->setText(ToolTranslator::Translate("Label_1000301"));
    m_btnOpen->setFixedWidth(100);
    m_btnOpen->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout1->addWidget(m_btnOpen);

    layout->addWidget(widget1);

    QWidget* widget2 = new QWidget(this);
    widget2->setFixedHeight(30);
    widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* layout2 = new QHBoxLayout(widget2);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->setSpacing(10);

    QLabel* label2 = new QLabel(widget2);
    label2->setText(ToolTranslator::Translate("Label_1000302"));
    label2->setFixedSize(80, 30);
    label2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout2->addWidget(label2);

    m_sendText = new QLineEdit(widget2);
    m_sendText->setText(tr("Hello DWIN!"));
    m_sendText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout2->addWidget(m_sendText);

    QPushButton* btnSend = new QPushButton(widget2);
    btnSend->setObjectName(tr("btnSendCom"));
    btnSend->setText(ToolTranslator::Translate("Label_1000303"));
    btnSend->setFixedWidth(100);
    btnSend->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout2->addWidget(btnSend);

    layout->addWidget(widget2);

    QWidget* widget3 = new QWidget(this);
    widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout* layout3 = new QHBoxLayout(widget3);
    layout3->setContentsMargins(0, 0, 0, 0);
    layout3->setSpacing(10);

    QLabel* label3 = new QLabel(widget3);
    label3->setText(ToolTranslator::Translate("Label_1000304"));
    label3->setFixedSize(80, 30);
    label3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout3->addWidget(label3);

	QFont font;
	font.setPixelSize(22);
    m_recvText = new QTextEdit(widget3);
	m_recvText->setFont(font);
    m_recvText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout3->addWidget(m_recvText);

    layout->addWidget(widget3);
    setLayout(layout);

    connect(m_btnOpen,SIGNAL(clicked(bool)),this,SLOT(OnOpenCloseComPort(bool)));
    connect(btnSend,SIGNAL(clicked(bool)),this,SLOT(OnBtnSendClicked(bool)));
}

ToolComTest::~ToolComTest()
{
    //qDebug() << "ToolComTest destory.";
    if (m_serialPort)
    {
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = 0;
    }
}

void ToolComTest::OnOpenCloseComPort(bool checked)
{
    Q_UNUSED(checked);

    if (m_serialPort) // 关闭
    {
        disconnect(m_serialPort,SIGNAL(readyRead()),this,SLOT(OnSerialportRead()));

        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = 0;

        m_btnOpen->setText(ToolTranslator::Translate("Label_1000301"));
    }
    else // 打开
    {
        m_serialPort = new QSerialPort(this);
#ifdef _WIN32
        QString device = tr("COM%1").arg(m_comList->currentIndex()+1);
#else
        QString device = tr("/dev/ttyS%1").arg(m_comList->currentIndex()+1); // 注：不同类型屏，设备名可能不一样
#endif
        qDebug() << QString("Open device:%1").arg(device);
        m_serialPort->setPortName(device);
        if (!m_serialPort->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this, ToolTranslator::Translate("Label_1010000")
				, tr("[%1] %2").arg(device).arg(ToolTranslator::Translate("Label_1000306")));
            delete m_serialPort;
            m_serialPort = 0;
            return;
        }

        m_serialPort->setBaudRate(QSerialPort::Baud115200);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        m_serialPort->clear();

        connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(OnSerialportRead()));

        m_btnOpen->setText(ToolTranslator::Translate("Label_1000305"));
    }
}

void ToolComTest::OnBtnSendClicked(bool checked)
{
    Q_UNUSED(checked);

    if (!m_serialPort || !m_serialPort->isOpen())
        return;

    m_serialPort->write(m_sendText->text().toStdString().data());
    m_serialPort->write("\n");
}

void ToolComTest::OnSerialportRead()
{
    QByteArray text = m_serialPort->readAll();
    m_recvText->moveCursor(QTextCursor::End);
    m_recvText->insertPlainText(text);
}

void ToolComTest::OnSerialportWritten(qint64 bytes)
{
    Q_UNUSED(bytes);
}

