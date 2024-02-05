#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>
#include <QProcess>
#ifndef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

#include "toolbasetest.h"
#include "tooldefs.h"
#include "mainwindow.h"
#include "tooltouchtest.h"
#include "tooltranslator.h"
extern MainWindow* g_mainwnd;

ToolBaseTest::ToolBaseTest(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout* layout = new QGridLayout(this);
	layout->setContentsMargins(40, 20, 40, 20);
	layout->setSpacing(20);

	QLabel* label5 = new QLabel(this);
	label5->setText(ToolTranslator::Translate("Label_1000008"));
	label5->setFixedSize(80, 30);
	label5->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(label5, 1, 0);

	QLineEdit* touchInfo = new QLineEdit(this);
	touchInfo->setText(ToolTranslator::Translate("Label_1000009"));
	touchInfo->setFixedHeight(30);
	touchInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(touchInfo, 1, 1);

	QPushButton* btnTouchTest = new QPushButton(this);
	btnTouchTest->setObjectName(tr("btnTouchTest"));
	btnTouchTest->setText(ToolTranslator::Translate("Label_1000003"));
	btnTouchTest->setFixedSize(100, 30);
	btnTouchTest->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(btnTouchTest, 1, 2);

	QWidget* widget = new QWidget(this);
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(widget, 2, 0, 1, 3);

	setLayout(layout);

	connect(btnTouchTest,SIGNAL(clicked(bool)),this,SLOT(OnBtnTouchTestClicked(bool)));

}

ToolBaseTest::~ToolBaseTest()
{
	//qDebug() << "ToolBaseTest destory.";
}

void ToolBaseTest::OnBtnTouchTestClicked(bool checked)
{
	Q_UNUSED(checked);

	ToolTouchTest* pDialog = new ToolTouchTest();
	pDialog->setWindowModality(Qt::ApplicationModal);
	pDialog->show();
	pDialog->exec();

	delete pDialog;
}
