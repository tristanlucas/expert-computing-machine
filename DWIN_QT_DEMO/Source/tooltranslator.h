#ifndef TOOLTRANSLATOR_H
#define TOOLTRANSLATOR_H

#include <QString>
#include <QMap>

class ToolTranslator
{
public:
	static ToolTranslator& GetTranslator();
	static void ReleaseTranslator();

	static QString Translate(QString text);

private:
	ToolTranslator();
	~ToolTranslator();

	int Init();

	QString DoTranslate(QString& text);

private:
	static ToolTranslator* s_translator;
	QMap<QString, QString> m_labels;
};

#endif // TOOLTRANSLATOR_H
