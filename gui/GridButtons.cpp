#include "GridButtons.h"

GridButtons::GridButtons(int rows, int columns, QWidget* parent)
	: QWidget(parent)
{
	layout = std::make_shared<QGridLayout>(this);
	buttons.resize(rows * columns);
	numberOfColumns = columns;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int index = i * columns + j;
			buttons[index] = std::make_shared<QPushButton>("Zone " + QString::number(i * numberOfColumns + j), this);
			layout->addWidget(buttons[index].get(), i, j);
			connect(buttons[index].get(), &QPushButton::clicked, this, [this, i, j]() { handleButtonClick(i, j); });
			buttons[index]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			buttons[index]->setStyleSheet("background:transparent ;"
				"border:2px solid black;"
				"border-radius: 15px;"
			);
		}
	}
}

GridButtons::~GridButtons()
{
}

void GridButtons::setButtonColor(int index, const Color::ColorEnum& color)
{
	buttons[index]->setAutoFillBackground(true);
	QPalette pal = QPalette(getColor(color));
	buttons[index]->setPalette(pal);
}
void GridButtons::setSizeAndAlignment(int percentHeight, int percentWidth)
{
	int height = this->parentWidget()->height() * percentHeight / 100;
	int width = this->parentWidget()->width() * percentWidth / 100;
	setFixedSize(width, height);
	layout->setAlignment(this, Qt::AlignVCenter | Qt::AlignHCenter);
}
void GridButtons::setCustomName(int index, QString name, int score, int numberOfLives)
{
	QString buttonText = name + "\n" + QString::number(score) + "\n";
	for (int i = 0; i < numberOfLives; i++)
	{
		buttonText += "🏰";
	}
	buttons[index]->setText(buttonText);
}
void GridButtons::handleButtonClick(int row, int column)
{
	int index = row * numberOfColumns + column;
	Q_EMIT sendButtonIndexClicked(index);
}

QColor GridButtons::getColor(const Color::ColorEnum& color)
{
	switch (color)
	{
	case Color::ColorEnum::None:
		return QColorConstants::Black;
		break;
	case Color::ColorEnum::Red:
		return QColorConstants::Red;
		break;
	case Color::ColorEnum::Green:
		return QColorConstants::Green;
		break;
	case Color::ColorEnum::Blue:
		return QColorConstants::Blue;
		break;
	case Color::ColorEnum::Yellow:
		return QColorConstants::Yellow;
		break;
	default:
		return QColorConstants::White;
		break;
	}
}