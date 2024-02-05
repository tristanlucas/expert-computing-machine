#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "tooltranslator.h"

MainWindow* g_mainwnd;
int main(int argc, char *argv[])
{
	//qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

	QApplication a(argc, argv);

	QFile qss(":/qss/style.qss");
	if( qss.open(QFile::ReadOnly))
	{
		QString style = QLatin1String(qss.readAll());
		a.setStyleSheet(style);
		qss.close();
	}

	ToolTranslator::GetTranslator();

	g_mainwnd = new MainWindow();
	g_mainwnd->show();

	return a.exec();
}
