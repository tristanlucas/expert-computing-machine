#ifndef TOOLSQLTEST_H
#define TOOLSQLTEST_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>

#ifndef _WIN32
#define QT_SQLITE_ENABLE
#endif

#ifdef QT_SQLITE_ENABLE
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#endif

class ToolSqlTest : public QWidget
{
	Q_OBJECT

public:
	explicit ToolSqlTest(QWidget *parent = 0);
	~ToolSqlTest();

private slots:
	void OnStartSqlTest(bool checked);

private:
	QLineEdit* m_dbPath;
	QLineEdit* m_createResult;
	QLineEdit* m_insertResult;
	QLineEdit* m_deleteResult;
	QTableView* m_view;

#ifdef QT_SQLITE_ENABLE
	QSqlDatabase m_db; //������qt�����ݿ�����
	QSqlQueryModel m_model; //����ͱ���select���
#endif
};

#endif // TOOLSQLTEST_H
