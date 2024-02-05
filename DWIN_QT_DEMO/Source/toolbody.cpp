#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include "toolbody.h"
#include "tooldefs.h"
#include "toolstartpage.h"
#include "toolbasetest.h"
#include "toolcomtest.h"
#include "toolsqltest.h"

ToolBody::ToolBody(QWidget *parent)
	: QWidget(parent)
	, m_curType(0)
	, m_curPage(0)
{
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	setLayout(m_layout);
}

ToolBody::~ToolBody()
{
}

void ToolBody::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ToolBody::OpenPage(int page)
{
	if (page == m_curType)
		return;

	if (m_curPage)
	{
		m_layout->removeWidget(m_curPage);
		delete m_curPage;
		m_curPage = 0;
		m_curType = 0;
	}

	switch (page)
	{
	case TOOL_START_PAGE:
		m_curPage = new ToolStartPage(this);
		m_curType = page;
		m_layout->addWidget(m_curPage);
		break;
	case TOOL_PAGE_BASE_TEST:
		m_curPage = new ToolBaseTest(this);
		m_curType = page;
		m_layout->addWidget(m_curPage);
		break;
	case TOOL_PAGE_COM_TEST:
		m_curPage = new ToolComTest(this);
		m_curType = page;
		m_layout->addWidget(m_curPage);
		break;
	case TOOL_PAGE_SQL_TEST:
		m_curPage = new ToolSqlTest(this);
		m_curType = page;
		m_layout->addWidget(m_curPage);
		break;
	default:
		break;
	}
}
