#ifndef TOOLBASETEST_H
#define TOOLBASETEST_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>

class QVBoxLayout;
class ToolBaseTest : public QWidget
{
	Q_OBJECT

public:
	explicit ToolBaseTest(QWidget *parent = 0);
	~ToolBaseTest();

private slots:
	void OnBtnTouchTestClicked(bool checked);

private:
};

#endif // TOOLBASETEST_H
