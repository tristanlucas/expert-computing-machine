#include <QDebug>
#include <QFile>
#include "tooltranslator.h"

ToolTranslator* ToolTranslator::s_translator = nullptr;

ToolTranslator::ToolTranslator()
{
}

ToolTranslator::~ToolTranslator()
{
}

int ToolTranslator::Init()
{
	QFile file(":/language/chinese.ini");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return -1;

	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line.isEmpty())
			continue;

		if (line.at(0) == '#') // 跳过注释行
			continue;

		int pos = line.indexOf('=');
		if (pos >= 0)
		{
			m_labels.insert(line.left(pos), line.right(line.length()-pos-1));
		}
	}
	return 0;
}

ToolTranslator& ToolTranslator::GetTranslator()
{
	if (!s_translator)
	{
		s_translator = new ToolTranslator();
		s_translator->Init();
	}
	return *s_translator;
}

void ToolTranslator::ReleaseTranslator()
{
	if (s_translator)
	{
		delete s_translator;
		s_translator = nullptr;
	}
}

QString ToolTranslator::Translate(QString text)
{	
	return ToolTranslator::GetTranslator().DoTranslate(text);
}

QString ToolTranslator::DoTranslate(QString& text)
{
	if (m_labels.contains(text))
	{
		return m_labels[text];
	}
	return text; // 不存在时返回原字符串
}