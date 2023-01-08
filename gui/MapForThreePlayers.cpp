#include "MapForThreePlayers.h"

MapForThreePlayers::MapForThreePlayers(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	t_checkFinishState = std::make_unique<QTimer>();
	t_checkFinishState->setInterval(500);
	connect(t_checkFinishState.get(), SIGNAL(timeout()), SLOT(on_CheckFinishState_Timeout()));
}

MapForThreePlayers::~MapForThreePlayers()
{}

void MapForThreePlayers::setNumberOfInterractions(int numberOfInterractions)
{
	
	m_numberOfInterractions = numberOfInterractions;
}

void MapForThreePlayers::setPlayer(const std::shared_ptr<PlayerQString>& player)
{
	m_player = player;
}

void MapForThreePlayers::setGameInstance(const std::shared_ptr<Route>& GameInstance)
{
	m_GameInstance = GameInstance;
}

QColor MapForThreePlayers::getColor(const Color::ColorEnum& color)
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
void MapForThreePlayers::showEvent(QShowEvent* event)
{
	t_checkFinishState->start();
}
	void MapForThreePlayers::on_zona1_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona1->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona1->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}
	void MapForThreePlayers::on_zona2_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona2->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona2->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona3_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona3->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona3->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona4_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona4->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona4->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona5_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona5->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona5->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona6_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona6->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona6->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona7_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona7->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona7->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona8_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona8->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona8->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona9_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona9->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona9->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona10_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona10->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona10->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona11_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona11->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona11->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona12_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona12->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona12->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona13_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona13->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona13->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona14_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona14->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona14->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_zona15_clicked()
	{
		if (m_validateMove == true)
		{
			m_validateMove = true;
			m_numberOfInterractions--;
			ui.zona15->setAutoFillBackground(true);
			QPalette pal = QPalette(getColor(m_player->getColor()));
			ui.zona15->setPalette(pal);
		}
		else {
			QMessageBox::information(this, "Error", "You can't move here");
		}
	}

	void MapForThreePlayers::on_CheckFinishState_Timeout()
	{
		if (m_numberOfInterractions == 0)// sau  server ul zice ca tabla e plina)
		{
			t_checkFinishState->stop();
			this->hide();
			//emit signal  sa se stie sa se treaca la urmatoarea faza 
		}
	}
