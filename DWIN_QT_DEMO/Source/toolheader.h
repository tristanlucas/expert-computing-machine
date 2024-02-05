#ifndef TOOLHEADER_H
#define TOOLHEADER_H

#include <QWidget>

class MainWindow;
class QPushButton;
class ToolHeader : public QWidget
{
	Q_OBJECT

public:
	explicit ToolHeader(MainWindow *parent = 0);
	~ToolHeader();

	void Init();

protected:
	virtual void paintEvent(QPaintEvent *event);

private slots:
	void OnStartPageClicked(bool checked);
	void OnBaseTestClicked(bool checked);
	void OnComTestClicked(bool checked);
	void OnSqlTestClicked(bool checked);

private:
	void SetAllPropertyOff();

private:
	MainWindow* m_mainWnd;
	QPushButton* m_btnStartPage;
	QPushButton* m_btnBaseTest;
	QPushButton* m_btnComTest;
	QPushButton* m_btnSqlTest;
};

#endif // TOOLHEADER_H
