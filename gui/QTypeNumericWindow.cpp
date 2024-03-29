#include "QTypeNumericWindow.h"
#include <qtimer.h>
QTypeNumericWindow::QTypeNumericWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_TimeRemaining = std::make_unique<QTimer>(new QTimer(this));
	m_timer = std::make_unique<QTimer>(new QTimer(this));

	connect(m_TimeRemaining.get(), &QTimer::timeout, this, &QTypeNumericWindow::on_TimeRemaining_Timeout);
	connect(m_timer.get(), &QTimer::timeout, this, &QTypeNumericWindow::on_Timer_Timeout);
	connect(ui.Delete, &QPushButton::pressed, this, &QTypeNumericWindow::on_Delete_pressed);
	connect(ui.Delete, &QPushButton::released, this, &QTypeNumericWindow::on_Delete_release);

	ui.TimeRemaining->setRange(0, 1500);
	ui.TimeRemaining->setValue(0);

	ui.Answer->setEnabled(false);

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
	QString question = QString::fromLocal8Bit(m_GameInstance->getQuestionTypeNumerical());
	ui.Question->setWordWrap(true);
	ui.Question->setText(question);
	ui.Question->setFont(QFont("Arial", 25));
	ui.Question->setAlignment(Qt::AlignCenter);
}

void QTypeNumericWindow::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
}

void QTypeNumericWindow::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
}

void QTypeNumericWindow::setDuelPhase()
{
	m_gamePhase = GamePhase::Duels;
}

void QTypeNumericWindow::sendResponseToServerAndGetDuelStatus(int response, int time, const Color::ColorEnum& color)
{
	auto duelStatus = m_GameInstance->sendResponseEt2(color, response, time);

	emit emitTieBreakerDuelStatus(duelStatus);
}

void QTypeNumericWindow::showEvent(QShowEvent* event)
{
	resetTheWindow();
	QWidget::showEvent(event);
}

void QTypeNumericWindow::on_Number0_clicked()
{
	if (ui.Answer->text().size() == 0)
		ui.Answer->setText(ui.Answer->text() + "0");
	else if (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0')
		ui.Answer->setText(ui.Answer->text() + "0");
}

void QTypeNumericWindow::on_Number1_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "1");
}

void QTypeNumericWindow::on_Number2_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "2");
}

void QTypeNumericWindow::on_Number3_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "3");
}

void QTypeNumericWindow::on_Number4_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "4");
}

void QTypeNumericWindow::on_Number5_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "5");
}

void QTypeNumericWindow::on_Number6_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "6");
}

void QTypeNumericWindow::on_Number7_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "7");
}

void QTypeNumericWindow::on_Number8_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "8");
}

void QTypeNumericWindow::on_Number9_clicked()
{
	if (ui.Answer->text().size() == 0 || (ui.Answer->text().size() > 0 && ui.Answer->text()[0] != '0'))
		ui.Answer->setText(ui.Answer->text() + "9");
}

void QTypeNumericWindow::on_Delete_clicked()
{
	ui.Answer->setText(ui.Answer->text().left(ui.Answer->text().length() - 1));
}

void QTypeNumericWindow::on_Enter_clicked()
{
	m_TimeRemaining->stop();
	disableAllButtons();
	ui.TimeRemaining->setEnabled(false);
	int value = ui.TimeRemaining->value();
	int answer = ui.Answer->text().toInt();
	if (ui.Answer->text().size() == 0)
	{
		answer = INT_MAX;
	}
	if(m_gamePhase != GamePhase::Duels)
	{
		auto Ordervector = m_GameInstance->sendResponseNumericalEt1(answer, value, m_player->getColor());
		emit sendOrderToParent(Ordervector);
	}
	else
	{
		sendResponseToServerAndGetDuelStatus(answer, value, m_player->getColor());
	}
}

void QTypeNumericWindow::on_Delete_pressed()
{
	m_timer->start(100);
}

void QTypeNumericWindow::on_Delete_release()
{
	m_timer->stop();
}

void QTypeNumericWindow::on_Timer_Timeout()
{
	if (ui.Answer->text().length() > 0)
	{
		ui.Answer->setText(ui.Answer->text().left(ui.Answer->text().length() - 1));
	}
	else {
		m_timer->stop();
	}
}

void QTypeNumericWindow::on_TimeRemaining_Timeout()
{
	int value = ui.TimeRemaining->value();
	if (value < ui.TimeRemaining->maximum())
	{
		ui.TimeRemaining->setValue(value + 1);
	}
	else {
		m_TimeRemaining->stop();
		on_Enter_clicked();
	}
}

void QTypeNumericWindow::disableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(false);
	}
}

void QTypeNumericWindow::enableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(true);
	}
}

void QTypeNumericWindow::resetTheWindow()
{
	ui.Answer->clear();
	ui.TimeRemaining->setValue(0);
	m_TimeRemaining->start(10);
}

void QTypeNumericWindow::showWindow()
{
	this->show();
}