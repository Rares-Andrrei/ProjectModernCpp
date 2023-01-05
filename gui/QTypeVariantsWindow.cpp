#include "QTypeVariantsWindow.h"

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

	requestQuestion();
}

void QTypeVariantsWindow::advantageButtonEnabled()
{
	//daca avantajul a fost deja apasat o data sa dispara
	/*if (1 == 1)
		delete ui.fiftyFiftyAdvantajeButton;
	else*/
		ui.fiftyFiftyAdvantajeButton->setToolTip("50-50 : this advantage eliminates 2 variants");
}

QTypeVariantsWindow::QTypeVariantsWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	buttonsConnections();
	createTimeSlider();
	createAnswerVariants();
	advantageButtonEnabled();
}

QTypeVariantsWindow::~QTypeVariantsWindow()
{
}

void QTypeVariantsWindow::requestQuestion()
{
	ui.Question->setWordWrap(true);

	ui.Question->setFont(QFont("Arial", 25));
	ui.Question->setAlignment(Qt::AlignCenter);
	// Request :: ask the server for a random question and the 4 variants
	ui.Question->setText("This is a long message that will be displayed in a scrollable text edit widget.This is a long message that will be displayed in a scrollable text edit widget.");

	ui.VariantA->setText("A");
	ui.VariantB->setText("B");
	ui.VariantC->setText("C");
	ui.VariantD->setText("D");
}

void QTypeVariantsWindow::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
}

void QTypeVariantsWindow::showEvent(QShowEvent* event)
{
	m_timeRemaining->start(10);
	QWidget::showEvent(event);
}

void QTypeVariantsWindow::on_Variant1_clicked()
{
	variant = "a";
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant2_clicked()
{
	variant = "b";
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant3_clicked()
{
	variant = "c";
	on_Variant_clicked();
}

void QTypeVariantsWindow::on_Variant4_clicked()
{
	variant = "d";
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
	m_timeRemaining->stop();
	ui.TimeSlider->setEnabled(false);
	disableAllButtons();
	int value = ui.TimeSlider->value();
	if (variant == "")
		variant = "NULL"; // daca nu a ales un raspuns in timp util , este declarat ca fiind gresit
	// REQUEST :: send the response  provided to the server + the time 
	this->close();
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