#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include "toolutility.h"
#include "tooldefs.h"

QSize ToolUtility::GetMainWindowSize()
{
#ifndef WIN32
	QRect rect = QGuiApplication::primaryScreen ()->availableGeometry() ;
	return QSize(rect.width(), rect.height());
#else
	return QSize(1280, 800);
#endif
}
