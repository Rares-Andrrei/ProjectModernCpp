#include "QTypeVariantsWindow.h"

QTypeVariantsWindow::QTypeVariantsWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(m_timeRemaining, &QTimer::timeout, this, &QTypeVariantsWindow::on_TimeRemaining_Timeout);
	connect(ui.VariantA, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant1_clicked);
	connect(ui.VariantB, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant2_clicked);
	connect(ui.VariantC, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant3_clicked);
	connect(ui.VariantD, &QPushButton::clicked, this, &QTypeVariantsWindow::on_Variant4_clicked);
	ui.VariantA->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.VariantD->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	requestQuestion();
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
}

