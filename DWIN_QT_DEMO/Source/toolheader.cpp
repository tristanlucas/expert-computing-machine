#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include "toolheader.h"
#include "mainwindow.h"
#include "toolbody.h"
#include "tooldefs.h"
#include "tooltranslator.h"

ToolHeader::ToolHeader(MainWindow *parent)
	: QWidget((QWidget*)parent)
	, m_mainWnd(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	QWidget* logo = new QWidget(this);
	logo->setObjectName(tr("logoWidget"));
	logo->setFixedSize(80, 50);
	logo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout->addWidget(logo);

	layout->addSpacing(10);

	m_btnStartPage = new QPushButton(this);
	m_btnStartPage->setObjectName(tr("btnStartPage"));
	m_btnStartPage->setText(ToolTranslator::Translate("Label_1000100"));
	m_btnStartPage->setFixedWidth(100);
	m_btnStartPage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_btnStartPage->setProperty("status", "off");
	layout->addWidget(m_btnStartPage);

	m_btnBaseTest = new QPushButton(this);
	m_btnBaseTest->setObjectName(tr("btnBaseTest"));
	m_btnBaseTest->setText(ToolTranslator::Translate("Label_1000101"));
	m_btnBaseTest->setFixedWidth(100);
	m_btnBaseTest->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_btnBaseTest->setProperty("status", "off");
	layout->addWidget(m_btnBaseTest);

	m_btnComTest = new QPushButton(this);
	m_btnComTest->setObjectName(tr("btnComTest"));
	m_btnComTest->setText(ToolTranslator::Translate("Label_1000102"));
	m_btnComTest->setFixedWidth(100);
	m_btnComTest->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_btnComTest->setProperty("status", "off");
	layout->addWidget(m_btnComTest);

	m_btnSqlTest = new QPushButton(this);
	m_btnSqlTest->setObjectName(tr("btnSqlTest"));
	m_btnSqlTest->setText(ToolTranslator::Translate("Label_1000103"));
	m_btnSqlTest->setFixedWidth(100);
	m_btnSqlTest->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_btnSqlTest->setProperty("status", "off");
	layout->addWidget(m_btnSqlTest);

	layout->addStretch(1);
	setLayout(layout);

	connect(m_btnStartPage,SIGNAL(clicked(bool)),this,SLOT(OnStartPageClicked(bool)));
	connect(m_btnBaseTest,SIGNAL(clicked(bool)),this,SLOT(OnBaseTestClicked(bool)));
	connect(m_btnComTest,SIGNAL(clicked(bool)),this,SLOT(OnComTestClicked(bool)));
	connect(m_btnSqlTest,SIGNAL(clicked(bool)),this,SLOT(OnSqlTestClicked(bool)));
}

ToolHeader::~ToolHeader()
{
}

void ToolHeader::Init()
{
	OnStartPageClicked(true);
}

void ToolHeader::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ToolHeader::OnStartPageClicked(bool checked)
{
	Q_UNUSED(checked);
	//qDebug() << "start page clicked.";
	m_mainWnd->GetBody()->OpenPage(TOOL_START_PAGE);

	SetAllPropertyOff();
	m_btnStartPage->setProperty("status", "on");
	m_btnStartPage->style()->polish(m_btnStartPage);
}

void ToolHeader::OnBaseTestClicked(bool checked)
{
	Q_UNUSED(checked);
	//qDebug() << "base test clicked.";
	m_mainWnd->GetBody()->OpenPage(TOOL_PAGE_BASE_TEST);

	SetAllPropertyOff();
	m_btnBaseTest->setProperty("status", "on");
	m_btnBaseTest->style()->polish(m_btnBaseTest);
}

void ToolHeader::OnComTestClicked(bool checked)
{
	Q_UNUSED(checked);
	//qDebug() << "com test clicked.";
	m_mainWnd->GetBody()->OpenPage(TOOL_PAGE_COM_TEST);

	SetAllPropertyOff();
	m_btnComTest->setProperty("status", "on");
	m_btnComTest->style()->polish(m_btnComTest);
}

void ToolHeader::OnSqlTestClicked(bool checked)
{
	Q_UNUSED(checked);
	//qDebug() << "sql test clicked.";
	m_mainWnd->GetBody()->OpenPage(TOOL_PAGE_SQL_TEST);

	SetAllPropertyOff();
	m_btnSqlTest->setProperty("status", "on");
	m_btnSqlTest->style()->polish(m_btnSqlTest);
}

void ToolHeader::SetAllPropertyOff()
{
	if (m_btnStartPage->property("status") == "on")
	{
		m_btnStartPage->setProperty("status", "off");
		m_btnStartPage->style()->polish(m_btnStartPage);
	}

	if (m_btnBaseTest->property("status") == "on")
	{
		m_btnBaseTest->setProperty("status", "off");
		m_btnBaseTest->style()->polish(m_btnBaseTest);
	}

	if (m_btnComTest->property("status") == "on")
	{
		m_btnComTest->setProperty("status", "off");
		m_btnComTest->style()->polish(m_btnComTest);
	}

	if (m_btnSqlTest->property("status") == "on")
	{
		m_btnSqlTest->setProperty("status", "off");
		m_btnSqlTest->style()->polish(m_btnSqlTest);
	}
}
