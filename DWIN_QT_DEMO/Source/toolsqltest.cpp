#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>
#include <QDebug>
#include "toolsqltest.h"
#include "tooldefs.h"
#include "tooltranslator.h"

ToolSqlTest::ToolSqlTest(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(40, 20, 40, 20);
	layout->setSpacing(20);

	QWidget* widget1 = new QWidget(this);
	widget1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QGridLayout* layout1 = new QGridLayout(widget1);
	layout1->setContentsMargins(0, 0, 0, 0);
	layout1->setSpacing(10);

	QLabel* label0 = new QLabel(widget1);
	label0->setText(ToolTranslator::Translate("Label_1000400"));
	label0->setFixedSize(80, 30);
	label0->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout1->addWidget(label0, 0, 0);

	m_dbPath = new QLineEdit(widget1);
#ifdef _WIN32
	m_dbPath->setText(tr("E:/sqlite.db"));
#else
	m_dbPath->setText(tr("/var/log/sqlite.db"));
#endif
	m_dbPath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_dbPath->setDisabled(true);
	layout1->addWidget(m_dbPath, 0, 1);

	QPushButton* btnStart = new QPushButton(this);
	btnStart->setText(ToolTranslator::Translate("Label_1000401"));
	btnStart->setFixedSize(80, 30);
	btnStart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout1->addWidget(btnStart, 0, 2);

	QLabel* label1 = new QLabel(widget1);
	label1->setText(ToolTranslator::Translate("Label_1000402"));
	label1->setFixedSize(80, 30);
	label1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout1->addWidget(label1, 1, 0, 1, 1);

	m_createResult = new QLineEdit(widget1);
	m_createResult->setText(ToolTranslator::Translate("Label_1000403"));
	m_createResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout1->addWidget(m_createResult, 1, 1, 1, 2);

	QLabel* label2 = new QLabel(widget1);
	label2->setText(ToolTranslator::Translate("Label_1000404"));
	label2->setFixedSize(80, 30);
	label2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout1->addWidget(label2, 2, 0, 1, 1);

	m_insertResult = new QLineEdit(widget1);
	m_insertResult->setText(ToolTranslator::Translate("Label_1000403"));
	m_insertResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout1->addWidget(m_insertResult, 2, 1, 1, 2);

	QLabel* label3 = new QLabel(widget1);
	label3->setText(ToolTranslator::Translate("Label_1000405"));
	label3->setFixedSize(80, 30);
	label3->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout1->addWidget(label3, 3, 0, 1, 1);

	m_deleteResult = new QLineEdit(widget1);
	m_deleteResult->setText(ToolTranslator::Translate("Label_1000403"));
	m_deleteResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	layout1->addWidget(m_deleteResult, 3, 1, 1, 2);

	layout->addWidget(widget1);

	QWidget* widget2 = new QWidget(this);
	widget2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout* layout2 = new QHBoxLayout(widget2);
	layout2->setContentsMargins(0, 0, 0, 0);
	layout2->setSpacing(10);

	QLabel* label4 = new QLabel(widget2);
	label4->setText(ToolTranslator::Translate("Label_1000406"));
	label4->setFixedSize(80, 30);
	label4->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	layout2->addWidget(label4);

	m_view = new QTableView(widget2);
	m_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	layout2->addWidget(m_view);

	layout->addWidget(widget2);
	setLayout(layout);

	connect(btnStart,SIGNAL(clicked(bool)),this,SLOT(OnStartSqlTest(bool)));
}

ToolSqlTest::~ToolSqlTest()
{
	//qDebug() << "ToolSqlTest destory.";

#ifdef QT_SQLITE_ENABLE
	m_db.close();
#endif
}

void ToolSqlTest::OnStartSqlTest(bool checked)
{
	Q_UNUSED(checked);

#ifdef QT_SQLITE_ENABLE
	m_db.close();

	m_createResult->setText(ToolTranslator::Translate("Label_1000013"));
	QCoreApplication::processEvents();

	QString dbFile = m_dbPath->text();
	{
		QFileInfo FileInfo(dbFile);
		if (FileInfo.isFile()) // 如果是文件
			QFile::remove(dbFile);
	}

	// 建立和SQlite数据库连接
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	// 设置数据库文件的名称
	m_db.setDatabaseName(dbFile);
	// 打开数据库
	if (!m_db.open())
	{
		m_createResult->setText(ToolTranslator::Translate("Label_1010002"));
		m_createResult->setProperty("status", "error");
		m_createResult->style()->polish(m_createResult);

		m_insertResult->setText(ToolTranslator::Translate("Label_1010002"));
		m_insertResult->setProperty("status", "error");
		m_insertResult->style()->polish(m_insertResult);

		m_deleteResult->setText(ToolTranslator::Translate("Label_1010002"));
		m_deleteResult->setProperty("status", "error");
		m_deleteResult->style()->polish(m_deleteResult);

		QCoreApplication::processEvents();
		return;
	}

	// 构建创建表的SQL语句
	QSqlQuery query;
	{
		QString sql = QString("CREATE TABLE t_student(id INT PRIMARY KEY NOT NULL,name TEXT NOT NULL,score REAL NOT NULL);");
		if (!query.exec(sql))
		{
			m_createResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_createResult->setProperty("status", "error");
			m_createResult->style()->polish(m_createResult);

			m_insertResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_insertResult->setProperty("status", "error");
			m_insertResult->style()->polish(m_insertResult);

			m_deleteResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_deleteResult->setProperty("status", "error");
			m_deleteResult->style()->polish(m_deleteResult);

			QCoreApplication::processEvents();
			return;
		}

		m_createResult->setText(ToolTranslator::Translate("Label_1010001"));
		m_createResult->setProperty("status", "ok");
		m_createResult->style()->polish(m_createResult);
		QCoreApplication::processEvents();
	}

	// 添加
	QStringList names;
	names << ToolTranslator::Translate("Label_1000407") 
		<< ToolTranslator::Translate("Label_1000408") 
		<< ToolTranslator::Translate("Label_1000409") 
		<< ToolTranslator::Translate("Label_1000410");
	QStringList scores;
	scores << "96" << "98" << "95" << "94";
	for (int i = 1; i < 5; i++)
	{
		QString sql = QString("INSERT INTO t_student VALUES(%1, '%2', %3);").arg(i).arg(names.at(i-1)).arg(scores.at(i-1));
		if (!query.exec(sql))
		{
			m_insertResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_insertResult->setProperty("status", "error");
			m_insertResult->style()->polish(m_insertResult);

			m_deleteResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_deleteResult->setProperty("status", "error");
			m_deleteResult->style()->polish(m_deleteResult);
			QCoreApplication::processEvents();
			return;
		}
	}
	m_insertResult->setText(ToolTranslator::Translate("Label_1010001"));
	m_insertResult->setProperty("status", "ok");
	m_insertResult->style()->polish(m_insertResult);
	QCoreApplication::processEvents();

	// 删除
	{
		QString sql = QString("DELETE FROM t_student WHERE id=%1;").arg(3);
		if (!query.exec(sql))
		{
			m_deleteResult->setText(ToolTranslator::Translate("Label_1010002"));
			m_deleteResult->setProperty("status", "error");
			m_deleteResult->style()->polish(m_deleteResult);
			QCoreApplication::processEvents();
			return;
		}
	}

	m_deleteResult->setText(ToolTranslator::Translate("Label_1010001"));
	m_deleteResult->setProperty("status", "ok");
	m_deleteResult->style()->polish(m_deleteResult);
	QCoreApplication::processEvents();

	//查询表
	{
		QString str = QString("SELECT * FROM t_student");
		m_model.setQuery(str);
		m_view->setModel(&m_model);
	}
#endif
}

