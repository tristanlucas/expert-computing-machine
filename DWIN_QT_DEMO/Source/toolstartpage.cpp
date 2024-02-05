#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>
#include "toolstartpage.h"
#include "tooltranslator.h"

#define TOOL_VERSION "V1.1 Build 2022-08-10"

ToolStartPage::ToolStartPage(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout* layout = new QGridLayout(this);
	layout->setContentsMargins(40, 40, 40, 40);
	layout->setSpacing(10);

	QLabel* label1 = new QLabel(this);
	label1->setText(ToolTranslator::Translate("Label_1000200"));
	label1->setFixedSize(80, 30);
	label1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(label1, 0, 0);

	QLabel* label2 = new QLabel(this);
	label2->setText(QString::fromUtf8(TOOL_VERSION));
	label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(label2, 0, 1);

	QLabel* label3 = new QLabel(this);
	label3->setText(ToolTranslator::Translate("Label_1000201"));
	label3->setFixedSize(80, 30);
	label3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(label3, 1, 0);

	QLabel* label4 = new QLabel(this);
	label4->setText(ToolTranslator::Translate("Label_1000202"));
	label4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	layout->addWidget(label4, 1, 1);

	QWidget* widget = new QWidget(this);
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout->addWidget(widget, 2, 0, 1, 3);

	setLayout(layout);
}

ToolStartPage::~ToolStartPage()
{
	//qDebug() << "ToolStartPage destory.";
}

