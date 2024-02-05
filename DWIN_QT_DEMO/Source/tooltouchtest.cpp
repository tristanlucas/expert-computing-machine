#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QFileInfo>
#include "tooltouchtest.h"
#include "tooltranslator.h"

#define TOUCH_TEST_ITEMS_ROWS		9
#define TOUCH_TEST_ITEMS_COLUMNS	9

ToolTouchTest::ToolTouchTest(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	this->setObjectName("toolTouchTest");

#ifndef _WIN32
	QRect rect = QGuiApplication::primaryScreen()->availableGeometry();
	resize(rect.width(), rect.height());
#else
	resize(1024, 600);
#endif

	QGridLayout* layout = new QGridLayout(this);
	layout->setContentsMargins(2, 2, 2, 2);
	layout->setSpacing(2);

	for (int row = 0; row < TOUCH_TEST_ITEMS_ROWS; row++)
	{
		for (int column = 0; column < TOUCH_TEST_ITEMS_COLUMNS; column++)
		{
			QPushButton* btn = new QPushButton(this);
			btn->setText(tr("%1").arg(row*TOUCH_TEST_ITEMS_COLUMNS+column+1));
			btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			layout->addWidget(btn, row, column);

			if (row == TOUCH_TEST_ITEMS_ROWS/2 && column == TOUCH_TEST_ITEMS_COLUMNS/2)
			{
				btn->setText(ToolTranslator::Translate("Label_1000600"));
				connect(btn,SIGNAL(clicked(bool)),this,SLOT(OnBtnClosed(bool)));
			}
		}
	}
	setLayout(layout);
}

ToolTouchTest::~ToolTouchTest()
{
	//qDebug() << "ToolTouchTest destory.";
}

void ToolTouchTest::OnBtnClosed(bool checked)
{
	Q_UNUSED(checked);
	this->close();
}

