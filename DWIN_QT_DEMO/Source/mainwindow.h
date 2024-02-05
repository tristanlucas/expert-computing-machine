#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>

class ToolHeader;
class ToolBody;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	ToolBody* GetBody();

private:
	QWidget* m_central;
	QVBoxLayout* m_layout;
	ToolHeader* m_header;
	ToolBody* m_body;
};

#endif // MAINWINDOW_H
