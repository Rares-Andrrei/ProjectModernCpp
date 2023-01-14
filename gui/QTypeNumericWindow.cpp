#include "QTypeNumericWindow.h"
#include <qtimer.h>
QTypeNumericWindow::QTypeNumericWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_TimeRemaining = new QTimer(this);
	m_timer = new QTimer(this);

	connect(m_TimeRemaining, &QTimer::timeout, this, &QTypeNumericWindow::on_TimeRemaining_Timeout);
	connect(m_timer, &QTimer::timeout, this, &QTypeNumericWindow::on_Timer_Timeout);
	connect(ui.Delete, &QPushButton::pressed, this, &QTypeNumericWindow::on_Delete_pressed);
	connect(ui.Delete, &QPushButton::released, this, &QTypeNumericWindow::on_Delete_release);

	ui.TimeRemaining->setRange(0, 3000);
	ui.TimeRemaining->setValue(0);

	// nu sunt sigur daca trebuie ?
	ui.Answer->setClearButtonEnabled(false);
	ui.Answer->setEnabled(false);

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
	QString question = QString::fromLocal8Bit(m_GameInstance->getQuestionTypeNumerical());
	ui.Question->setWordWrap(true);
	ui.Question->setText(question);
	ui.Question->setFont(QFont("Arial", 25));
	ui.Question->setAlignment(Qt::AlignCenter);
	// Request :: ask the server fro a random question 
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

void QTypeNumericWindow::sendResponseToServerAndGetDuelStatus(const QString& response)
{
	// request :: send the response to the server and get the duel status W/L/Conqueror
	// make the changes to the specified zones
	std::vector<std::tuple<int, Color::ColorEnum, int, int>> updatedZones ;		// ZoneId , Color , score , NumberOfLives
	updatedZones.push_back(std::make_tuple(1, Color::ColorEnum::Red,100, 1));
	std::vector<std::pair<int, Color::ColorEnum>> UpdatedPlayersScores;		// Score , Color
	UpdatedPlayersScores.push_back(std::make_pair(2100, Color::ColorEnum::Red));
	UpdatedPlayersScores.push_back(std::make_pair(1900, Color::ColorEnum::Yellow));

	emit emitTieBreakerResults(updatedZones, UpdatedPlayersScores);
		
	//TD
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
		sendResponseToServerAndGetDuelStatus(ui.Answer->text());
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
		// REQUEST :: send the response  provided to the server
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
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(true);
	}
	ui.Answer->clear();
	ui.TimeRemaining->setValue(0);
	m_TimeRemaining->start(10);
}

void sendOrderToParent(const std::queue<std::pair<Color::ColorEnum, int>>& playerOrder) {}
