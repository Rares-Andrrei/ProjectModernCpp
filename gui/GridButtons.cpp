#include "GridButtons.h"

GridButtons::GridButtons(int rows, int columns, QWidget* parent)
	: QWidget(parent)
{
	layout = new QGridLayout(this);
	buttons.resize(rows * columns);
	numberOfColumns = columns;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int index = i * columns + j;
			buttons[index] = new QPushButton("Zone " + QString::number(i * numberOfColumns + j), this);
			layout->addWidget(buttons[index], i, j);
			connect(buttons[index], &QPushButton::clicked, this, [this, i, j]() { handleButtonClick(i, j); });
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
	qDeleteAll(buttons);
	delete layout;
}

void GridButtons::setButtonColor(int index, const Color::ColorEnum& color)
{
	buttons[index]->setAutoFillBackground(true);
	QPalette pal = QPalette(getColor(color));
	buttons[index]->setPalette(pal);
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