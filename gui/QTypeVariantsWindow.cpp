#include "QTypeVariantsWindow.h"
#include "Route.h"
#include <array>

QTypeVariantsWindow::QTypeVariantsWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	buttonsConnections();
	createTimeSlider();
	createAnswerVariants();
	advantageButtonEnabled();
}

void QTypeVariantsWindow::buttonsConnections()
{
	m_timeRemaining = new QTimer(this);

	connect(m_timeRemaining, &QTimer::timeout, this, &QTypeVariantsWindow::on_TimeRemaining_Timeout);
	connect(ui.VariantA, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant1_clicked);
	connect(ui.VariantB, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant2_clicked);
	connect(ui.VariantC, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant3_clicked);
	connect(ui.VariantD, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant4_clicked);

	connect(ui.fiftyFiftyAdvantajeButton, SIGNAL(clicked()), SLOT(onFiftyFiftyButtonClicked()));
}

void QTypeVariantsWindow::createTimeSlider()
{
	ui.TimeSlider->setRange(0, 3000);
	ui.TimeSlider->setValue(0);
	ui.TimeSlider->setStyleSheet("QSlider {"
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
		"QSlider::groove:horizontal { background-color: rgb(42, 103, 174); }");
}

void QTypeVariantsWindow::createAnswerVariants()
{
	ui.VariantA->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantD->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void QTypeVariantsWindow::advantageButtonEnabled()
{
	//daca avantajul a fost deja apasat o data sa dispara
	/*if (1 == 1)
		delete ui.fiftyFiftyAdvantajeButton;
	else*/
	ui.fiftyFiftyAdvantajeButton->setToolTip("50-50 : this advantage eliminates 2 variants");
}

void QTypeVariantsWindow::resetTheWindow()
{
	enableAllButtons();
	for (auto& button : findChildren<QPushButton*>())
		button->setStyleSheet("QPushButton { background-color: white; }");
	ui.TimeSlider->setValue(0);
	variant = -1;
}

QTypeVariantsWindow::~QTypeVariantsWindow()
{
}

void QTypeVariantsWindow::requestQuestion()
{
	std::array<std::string, 5> question = m_GameInstance->getQuestionTypeVariants();
	ui.Question->setWordWrap(true);

	ui.Question->setFont(QFont("Arial", 25));
	ui.Question->setAlignment(Qt::AlignCenter);

	ui.Question->setText(QString::fromLocal8Bit(question[0]));

	ui.VariantA->setText(QString::fromLocal8Bit(question[1]));
	ui.VariantB->setText(QString::fromLocal8Bit(question[2]));
	ui.VariantC->setText(QString::fromLocal8Bit(question[3]));
	ui.VariantD->setText(QString::fromLocal8Bit(question[4]));
}

void QTypeVariantsWindow::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
}

void QTypeVariantsWindow::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
}

void QTypeVariantsWindow::sendResponseToServer(int response)
{
	auto duelStatus = m_GameInstance->sendResponseEt2(m_player->getColor(), response, 0);
	if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Lose)
	{
		emit emitAttackerLost();
		this->hide();
		return;
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::lifeTaken)
	{
		auto attackInfo = duelStatus.getUpdatedBase();
		// emit signal to update the life of the attacked base ?
		emit emitLifeTakenDisplayAnotherQuestion({ std::get<3>(attackInfo), std::get<4>(attackInfo) });
		this->hide();
		return;
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Win) 
	{
		auto updatedZones = duelStatus.getUpdatedZones();
		emit emitUpdatedZonesAfterWin(updatedZones);
		this->hide();
		return;
	}
	else if (duelStatus.getDuelStatus() == DuelManager::duelStatus::Draw)
	{
		auto tieBreakterParticipants = duelStatus.getTieBreakerParticipants();
		emit emitTieBreakerParticipants(tieBreakterParticipants);
	}
}

void QTypeVariantsWindow::showEvent(QShowEvent* event)
{
	resetTheWindow();
	m_timeRemaining->start(10);
	QWidget::showEvent(event);
}

void QTypeVariantsWindow::on_Variant1_clicked()
{
	variant = 0;
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant2_clicked()
{
	variant = 1;
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant3_clicked()
{
	variant = 2;
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant4_clicked()
{
	variant = 3;
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant_clicked()
{
	auto button = qobject_cast<QPushButton*>(QObject::sender());
	if (m_Variant)
	{
		m_Variant->setStyleSheet("QPushButton { background-color: white; }");
	}
	button->setStyleSheet("QPushButton { background-color: green; }");

	m_Variant = button;
}

void QTypeVariantsWindow::on_Enter_clicked()
{
	sendResponseToServer(variant);
}

void QTypeVariantsWindow::on_TimeRemaining_Timeout()
{
	int value = ui.TimeSlider->value();
	if (value < ui.TimeSlider->maximum())
	{
		ui.TimeSlider->setValue(value + 1);
	}
	else {
		m_timeRemaining->stop();
		on_Enter_clicked();
	}
}

void QTypeVariantsWindow::onFiftyFiftyButtonClicked()
{
	//trebuie vazut daca avantajul poate fi folosit
	   //- daca jucatorul are destule puncte pentru a lua avantajul
	   //- daca avantajul a mai fost sau nu folosit

	delete ui.VariantC;
	delete ui.VariantD;

	ui.VariantA->setFixedSize(470, 170);
	ui.VariantB->setFixedSize(470, 170);

	//dupa ce a fost folosit avantajul sa dispara
	delete ui.fiftyFiftyAdvantajeButton;
}

void QTypeVariantsWindow::disableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(false);
	}
}

void QTypeVariantsWindow::enableAllButtons()
{
	for (const auto& button : findChildren<QAbstractButton*>())
	{
		button->setEnabled(true);
	}
}
