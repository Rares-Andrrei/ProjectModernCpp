#pragma once

#include <qgridlayout.h>
#include <qsignalmapper.h>
#include <qpushbutton.h>
#include <memory>
#include "ui_GridButtons.h"
#include <qmessagebox.h>
#include <qwidget.h>
#include "../Color/Color/Color.h"
#include <qstring.h>

class GridButtons : public QWidget
{
	Q_OBJECT

public:
	GridButtons(int rows, int columns, QWidget* parent = nullptr);
	~GridButtons();

	void setButtonColor(int index, const Color::ColorEnum& color);
	void setSizeAndAlignment(int percentHeight, int percentWidth);
	void setCustomName(int index, QString name, int score, int numberOfLives = 0);

signals:
	void sendButtonIndexClicked(int index);

private slots:
	void handleButtonClick(int row, int column);

private:
	int numberOfColumns;
	std::shared_ptr<QGridLayout> layout;
	QVector<std::shared_ptr<QPushButton>> buttons;

	QColor getColor(const Color::ColorEnum& color);
};
