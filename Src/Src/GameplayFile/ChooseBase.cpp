#include "ChooseBase.h"

ChooseBase::ChooseBase( QuestionManager& questions,uint16_t numberOfPlayers)
	:m_numberOfPlayers{ numberOfPlayers }
{
	m_question = questions.randQTypeNumerical();
	std::cout << m_question;
}



void ChooseBase::CreateOrder(Player::Color player, int playerAnswer)
{
	int differenceBetweenPlayerAnswerAndQuestionAnswer = std::abs(playerAnswer - m_question.getAnswer());

	std::pair<int, Player::Color> toInsert;
	toInsert.first = differenceBetweenPlayerAnswerAndQuestionAnswer;
	toInsert.second = player;
	m_PlayerOrder.push(toInsert);
}

void ChooseBase::setBaseZone(Board& board)
{
	while (!m_PlayerOrder.empty())
	{
		std::shared_ptr<PlayerBase> player(std::make_shared < PlayerBase >(m_PlayerOrder.top().second));
		std::cout <<"Curent board format :"<< board;
		std::cout << *player <<"Player please choose a zone :";
		uint16_t index1, index2;
		uint16_t numPlayers = board.getNumberOfPlayers();
		std::cin >> index1 >> index2;
		std::string message = "Invalid parameters";
		if (numPlayers == 2)
		{

			try
			{
				if (index1 > 2 || index2 > 2)
				{
					throw(message);
				}
			}
			catch (std::string message)
			{
				std::cerr << "Error:" << message << "max is 2 2";
				return;
			}
		}
		else
		{
			if (numPlayers == 3)
			{
				try
				{
					if (index1 > 4 || index2 > 2)
					{
						throw(message);
					}

				}
				catch (std::string message)
				{
					std::cerr << "Error:" << message << "max is 4 2";
					return;
				}
			}

			else
			{
				if (numPlayers == 4)
				{
					try
					{
						if (index1 > 5 || index2 > 3)
						{
							throw(message);
						}

					}
					catch (std::string message)
					{
						std::cerr << "Error:" << message << "max is 5 3";
						return;
					}

				}
			}
		}

		if (board[{index1, index2}] == nullptr)
		{
			board[{index1, index2}] = player;

		}
		else
		{
			bool frag = false;
			int count = 0;
			while (frag == false && count < 2)
			{
				std::cout << "This base is already choose, please choose another :";
				std::cin >> index1 >> index2;
				if (board[{index1, index2}] == nullptr)
				{
					board[{index1, index2}] = player;
					frag = true;

				}
				else
					count++;
			}
			if (count == 2)
			{
				std::string message = "You are too stupid for this game broski, don't play";
				try
				{
					throw(message);

				}
				catch (std::string message)
				{
					std::cerr << message;
					return;
				}

			}
		}
		m_PlayerOrder.pop();
	}
}
