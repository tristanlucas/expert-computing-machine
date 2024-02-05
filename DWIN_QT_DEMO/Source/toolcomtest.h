#ifndef TOOLCOMTEST_H
#define TOOLCOMTEST_H

#include <QWidget>

class QComboBox;
class QPushButton;
class QLineEdit;
class QTextEdit;
class QSerialPort;
class ToolComTest : public QWidget
{
	Q_OBJECT

public:
	explicit ToolComTest(QWidget *parent = 0);
	~ToolComTest();

private slots:
	void OnOpenCloseComPort(bool checked);
	void OnBtnSendClicked(bool checked);
	void OnSerialportRead();
	void OnSerialportWritten(qint64 bytes);

private:
	QComboBox* m_comList;
	QPushButton* m_btnOpen;
	QLineEdit* m_sendText;
	QTextEdit* m_recvText;
	QSerialPort* m_serialPort;
};

#endif // TOOLCOMTEST_H
