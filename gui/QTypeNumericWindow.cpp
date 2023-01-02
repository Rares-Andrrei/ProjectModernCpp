#include "QTypeNumericWindow.h"
#include <qtimer.h>
QTypeNumericWindow::QTypeNumericWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//connect(m_timer, &QTimer::timeout,this, &QTypeNumericWindow::on_Timer_Timeout);
	ui.TimeRemaining->setRange(0, 100);
	ui.TimeRemaining->setValue(0);
	ui.Answer->setClearButtonEnabled(true);

	// Use a stylesheet to customize the appearance of the slider
	ui.TimeRemaining->setStyleSheet("QSlider {"
		"  background: transparent;"
		"  height: 10px;"
		"  border: 0px solid #777;"
		"  border-radius: 5px;"
		"}"
		"QSlider::groove:horizontal {"
		"  background: #777;"
		"  height: 8px;"
		"  border: 0px solid #777;"
		"  border-radius: 4px;"
		"}"
		"QSlider::handle:horizontal {"
		"  background: #eee;"
		"  width: 20px;"
		"  margin-top: -3px;"
		"  margin-bottom: -3px;"
		"  border: 1px solid #777;"
		"  border-radius: 10px;"
		"  image: url(:/images/handle.png);"
		"}"
		"QSlider::groove:horizontal { background: green; }");
	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [&]() {
		int value = ui.TimeRemaining->value();
	if (value < ui.TimeRemaining->maximum())
	{
		ui.TimeRemaining->setValue(value + 1);
		update();
	}
	else {
		timer.stop();
		// REQUEST :: send the response  provided to the server
	}
		});
	timer.start(1000);
	requestQuestion();

	//TD:  Clasa custom pentru button , pentru a simplifica codul
	ui.Number0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Number9->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.Delete->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QTypeNumericWindow::~QTypeNumericWindow()
{}

void QTypeNumericWindow::requestQuestion()
{
	ui.Question->setWordWrap(true);
	ui.Question->setText("This is a long message that will be displayed in a scrollable text edit widget.This is a long message that will be displayed in a scrollable text edit widget.");
	ui.Question->setFont(QFont("Arial", 25));
	ui.Question->setAlignment(Qt::AlignCenter);
	// Request :: ask the server fro a random question 
	// se the Question label to the given one
}

void QTypeNumericWindow::on_Number0_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "0");
}
void QTypeNumericWindow::on_Number1_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "1");
}
void QTypeNumericWindow::on_Number2_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "2");
}
void QTypeNumericWindow::on_Number3_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "3");
}
void QTypeNumericWindow::on_Number4_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "4");
}
void QTypeNumericWindow::on_Number5_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "5");
}
void QTypeNumericWindow::on_Number6_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "6");
}
void QTypeNumericWindow::on_Number7_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "7");
}
void QTypeNumericWindow::on_Number8_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "8");
}
void QTypeNumericWindow::on_Number9_clicked()
{
	ui.Answer->setText(ui.Answer->text() + "9");
}
void QTypeNumericWindow::on_Delete_clicked()
{
	ui.Answer->setText(ui.Answer->text().left(ui.Answer->text().length() - 1));
}
void QTypeNumericWindow::on_Enter_clicked()
{
	// Request :: send the response  provided to the server
}

//void QTypeNumericWindow::on_Delete_pressed()
//{
//	m_timer->start(100);
//}
//void QTypeNumericWindow::on_Delete_release()
//{
//	m_timer->stop();
//}
//void QTypeNumericWindow::on_Timer_Timeout()
//{
//	if (ui.Answer->text().length() > 0)
//		ui.Answer->setText(ui.Answer->text().left(ui.Answer->text().length() - 1));
//}