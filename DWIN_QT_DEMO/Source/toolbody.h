#ifndef TOOLBODY_H
#define TOOLBODY_H

#include <QWidget>

class QVBoxLayout;
class ToolBody : public QWidget
{
	Q_OBJECT

public:
	explicit ToolBody(QWidget *parent = 0);
	~ToolBody();

	void OpenPage(int page);

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	QVBoxLayout* m_layout;
	int m_curType;
	QWidget* m_curPage;
};

#endif // TOOLHEADER_H
