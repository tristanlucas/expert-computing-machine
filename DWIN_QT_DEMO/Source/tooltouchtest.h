#ifndef TOOLTOUCHTEST_H
#define TOOLTOUCHTEST_H

#include <QDialog>

class ToolTouchTest : public QDialog
{
	Q_OBJECT

public:
	explicit ToolTouchTest(QWidget *parent = 0);
	~ToolTouchTest();

private slots:
	void OnBtnClosed(bool checked);
};

#endif // TOOLTOUCHTEST_H
