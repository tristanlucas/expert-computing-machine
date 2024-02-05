#include <QtSerialPort>
#include <QVBoxLayout>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include "mainwindow.h"
#include "toolheader.h"
#include "toolbody.h"

MainWindow::MainWindow(QWidget *parent)
	:  QMainWindow(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);

	m_central = new QWidget(this);
	m_central->setObjectName(QStringLiteral("centralWidget"));
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(m_central->sizePolicy().hasHeightForWidth());
	m_central->setSizePolicy(sizePolicy);
	m_layout = new QVBoxLayout(m_central);
	m_layout->setSpacing(0);
	m_layout->setContentsMargins(11, 11, 11, 11);
	m_layout->setObjectName(QStringLiteral("layout"));
	m_layout->setContentsMargins(0, 0, 0, 0);
	this->setCentralWidget(m_central);

#ifndef _WIN32
	QRect rect = QGuiApplication::primaryScreen()->availableGeometry();
	resize(rect.width(), rect.height());
#else
	resize(1024, 600);
#endif

	m_header = new ToolHeader(this);
	m_header->setObjectName(tr("headerWidget"));
	m_header->setFixedHeight(50);
	m_header->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_layout->addWidget(m_header);

	m_body = new ToolBody(this);
	m_body->setObjectName(tr("bodyWidget"));
	m_body->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_layout->addWidget(m_body);

	m_header->Init();
}

MainWindow::~MainWindow()
{

}

ToolBody* MainWindow::GetBody()
{
	return m_body;
}
