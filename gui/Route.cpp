#include "Route.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <iostream>
#include <sstream>
#include <QCoreApplication>

std::string Route::getSessionKey()
{
	return m_sessionKey;
}

bool Route::leaveLobby()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/eliminatePlayerFromQueue" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		});
	return response.status_code == 200;
}

std::string Route::getQuestionTypeNumerical()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/getQuestionTypeNumerical" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)}
		});
	if (response.status_code == 200)
	{
		return response.text;
	}
	else
	{
		return "";
	}
}

std::array<std::string, 5> Route::getQuestionTypeVariants()
{
	std::array<std::string, 5> questionData;
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/getQuestionTypeVariants" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)}
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		questionData[0] = resData["question"].s();
		questionData[1] = resData["var1"].s();
		questionData[2] = resData["var2"].s();
		questionData[3] = resData["var3"].s();
		questionData[4] = resData["var4"].s();
		return questionData;
	}
	else
	{
		return questionData = { "", "", "", "", "" };
	}
}

std::queue<std::pair<Color::ColorEnum, int>> Route::sendResponseNumericalEt1(int resp, int time, Color::ColorEnum color)
{
	std::queue<std::pair<Color::ColorEnum, int>> players;
	cpr::Url url{ "http://localhost:18080/sendNumericalResponseEt1" };
	cpr::Payload payload{
			{ "sessionKey", m_sessionKey},
			{ "gameID", std::to_string(m_gameId)},
			{ "color", std::to_string(Color::ColorToInt(color))},
			{ "response", std::to_string(resp)},
			{ "time", std::to_string(time)}
	};
	auto lambda = [](cpr::Response response) {
		return response.text;
	};

	auto future_text = cpr::PostCallback(lambda, url, payload);

	while (future_text.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
	{
		QCoreApplication::processEvents();
	}
	auto aux = future_text.get();
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		for (int i = 1; i <= resData["playerNr"].i(); i++)
		{
			Color::ColorEnum c = Color::getColor(resData["playerColor" + std::to_string(i)].i());
			int s = resData["playerScore" + std::to_string(i)].i();
			players.push({ c, s });
		}
	}
	return players; //logica de pe gui va decide de cate ori se va apela fucntia de alegere teritoriu, daca playerul curent trebuie a aaleaga va trimite culoarea si teritoriul ales daca nu se va trimite un string gol, ca raspuns la ruta de alegere teritoriu se va returna harta actualizata.
}

std::pair<int, Color::ColorEnum> Route::chooseRegion(int id, Color::ColorEnum color)
{
	cpr::Url url{ "http://localhost:18080/chooseRegion" };
	cpr::Payload payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "color", std::to_string(Color::ColorToInt(color))},
			{ "regionId", std::to_string(id)}
	};
	auto lambda = [](cpr::Response response) {
		return response.text;
	};

	auto future_text = cpr::PostCallback(lambda, url, payload);
	while (future_text.wait_for(std::chrono::microseconds(10)) != std::future_status::ready)
	{
		QCoreApplication::processEvents();
	}
	auto aux = future_text.get();
	std::pair<int, Color::ColorEnum> data;
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		data.first = resData["zoneId"].i();
		data.second = Color::getColor(resData["zoneColor"].i());
	}
	return data;
}

Color::ColorEnum Route::getAttackerColor()
{
	cpr::Url url{ "http://localhost:18080/requestDuerlTurn" };
	cpr::Payload payload{
			{ "sessionKey", m_sessionKey},
			{ "gameID", std::to_string(m_gameId)},
	};
	auto lambda = [](cpr::Response response) {
		return response.text;
	};

	auto future_text = cpr::PostCallback(lambda, url, payload);
	while (future_text.wait_for(std::chrono::microseconds(10)) != std::future_status::ready)
	{
		QCoreApplication::processEvents();
	}
	auto aux = future_text.get();
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		return Color::getColor(resData["attackerColor"].i());
	}
	return Color::ColorEnum::None;
}

bool Route::checkValidBasePosition(int ZoneId)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/checkValidBasePosition" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "regionId", std::to_string(ZoneId)}
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		std::string value = resData["valid"].s();
		return value == "true";
	}
	else
	{
		return false;
	}
}

bool Route::checkValidRegionPosition(int ZoneId, const Color::ColorEnum& color)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/checkValidRegionPosition" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "color", std::to_string(Color::ColorToInt(color))},
			{ "regionId", std::to_string(ZoneId)}
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		std::string value = resData["valid"].s();
		return value == "true";
	}
	else
	{
		return false;
	}
}

bool Route::checkValidAttackMove(int ZoneId, const Color::ColorEnum& color)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/checkValidAttackMove" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "color", std::to_string(Color::ColorToInt(color))},
			{ "regionId", std::to_string(ZoneId)}
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		std::string value = resData["valid"].s();
		return value == "true";
	}
	else
	{
		return false;
	}
}

bool Route::checkIfBoardIsFull()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/checkIfBoardIsFull" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		std::string value = resData["valid"].s();
		return value == "true";
	}
	else
	{
		return false;
	}
}

bool Route::checkIfPlayerCanUseAdvantages(const Color::ColorEnum& color)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/checkIfPlayerCanUseAdvantages" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "color", std::to_string(Color::ColorToInt(color))},

		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		std::string value = resData["valid"].s();
		return value == "true";
	}
	else
	{
		return false;
	}
}

std::tuple<int, Color::ColorEnum, int, int> Route::updateZoneInfo(int ZoneId)
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/updateZoneInfo" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "regionId", std::to_string(ZoneId)}
		});
	if (response.status_code == 200)
	{
		std::tuple<int, Color::ColorEnum, int, int> zoneInfo;
		auto& [zoneId, zoneColor, zoneScore, zoneLifes] = zoneInfo;
		crow::json::rvalue resData = crow::json::load(response.text);
		zoneId = resData["zoneId"].i();
		zoneColor = Color::getColor(resData["zoneColor"].i());
		zoneScore = resData["zoneScore"].i();
		zoneLifes = resData["zoneLifes"].i();

		return zoneInfo;
	}
	else
	{
		return std::make_tuple(0, Color::ColorEnum::None, 0, 0);
	}
}

std::vector<std::pair<Color::ColorEnum, int>> Route::updatePlayersInfo()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/updatePlayerInfo" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)},
		});
	std::vector<std::pair<Color::ColorEnum, int>> playersInfo;
	crow::json::rvalue resData = crow::json::load(response.text);

	if (response.status_code == 200)
	{
		for (int i = 1; i <= resData["playerNr"].i(); i++)
		{
			Color::ColorEnum c = Color::getColor(resData["playerColor" + std::to_string(i)].i());
			int s = resData["playerScore" + std::to_string(i)].i();
			playersInfo.push_back(std::make_pair(c, s));
		}
	}
	return playersInfo;

}

void Route::enterLobby(int type, std::vector<std::shared_ptr<PlayerQString>>& players)
{
	cpr::Url url{ "http://localhost:18080/enterLobby" };

	cpr::Payload payload{
			{ "sessionKey", m_sessionKey},
			{ "lobbyType", std::to_string(type)}
	};

	auto lambda = [](cpr::Response response) {
		return response.text;
	};

	auto future_text = cpr::PostCallback(lambda, url, payload);

	while (future_text.wait_for(std::chrono::microseconds(10)) != std::future_status::ready)
	{
		QCoreApplication::processEvents();
	}
	auto aux = future_text.get();
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		m_gameId = resData["lobbyID"].i();
		int playerNr = resData["playerNr"].i();
		for (int i = 1; i < playerNr; i++)
		{
			int color = resData["playerColor" + std::to_string(i)].i();
			std::string name = resData["playerName" + std::to_string(i)].s();
			int score = resData["playerScore" + std::to_string(i)].i();
			std::shared_ptr<PlayerQString> player = std::make_shared<PlayerQString>(QString::fromLocal8Bit(name));
			auto colorr = Color::getColor(color);
			player->setColor(colorr);
			players.emplace_back(std::move(player));
		}
	}
}

std::list<std::array<std::string, 5>> Route::getMatchHistoryRoute()
{
	std::list<std::array<std::string, 5>> matches;
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/getMatchHistory" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		});
	if (response.status_code == 200)
	{
		crow::json::rvalue resData = crow::json::load(response.text);
		int matchesNr = resData["MatchesNr"].i();
		for (int i = 0; i < matchesNr; i++)
		{
			matches.push_back(std::array<std::string, 5>{
				resData["Date" + std::to_string(i)].s(),
					resData["Place1" + std::to_string(i)].s(),
					resData["Place2" + std::to_string(i)].s(),
					resData["Place3" + std::to_string(i)].s(),
					resData["Place4" + std::to_string(i)].s()}
			);
		}
	}
	return matches;
}

CredentialErrors Route::login(std::string username, std::string password, QString& setNickname)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/login" },
		cpr::Payload{
			{ "username", username},
			{ "password", password}
		}
	);
	crow::json::rvalue resData = crow::json::load(response.text);
	if (response.text == "")
	{
		return CredentialErrors::Other;
	}
	int resp = resData["error"].i();
	switch (resp)
	{
	case static_cast<int>(CredentialErrors::AlreadyConnected):
		return CredentialErrors::AlreadyConnected;
	case static_cast<int>(CredentialErrors::IncorrectAccount):
		return CredentialErrors::IncorrectAccount;
	case static_cast<int>(CredentialErrors::IncorrectPassword):
		return CredentialErrors::IncorrectPassword;
	case static_cast<int>(CredentialErrors::Valid):
		m_sessionKey = resData["sessionKey"].s();
		setNickname = QString::fromLocal8Bit(std::string(resData["nickname"].s()));
		return CredentialErrors::Valid;
	default:
		return CredentialErrors::Other;
	}
}

CredentialErrors Route::signUp(std::string username, std::string password, std::string name)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/signUp" },
		cpr::Payload{
			{ "username", username},
			{ "password", password},
			{"name", name}
		}
	);
	if (response.text == "")
	{
		return CredentialErrors::Other;
	}
	int resp = std::stoi(response.text);
	switch (resp)
	{
	case static_cast<int>(CredentialErrors::NameSize):
		return CredentialErrors::NameSize;
	case static_cast<int>(CredentialErrors::UsernameSize):
		return CredentialErrors::UsernameSize;
	case static_cast<int>(CredentialErrors::PasswordSize):
		return CredentialErrors::PasswordSize;
	case static_cast<int>(CredentialErrors::UserTaken):
		return CredentialErrors::UserTaken;
	case static_cast<int>(CredentialErrors::NameTaken):
		return CredentialErrors::NameTaken;
	case static_cast<int>(CredentialErrors::Valid):
		return CredentialErrors::Valid;

	default:
		return CredentialErrors::Other;
	}
}

bool Route::logOut()
{
	auto response = cpr::Put(
		cpr::Url{ "http://localhost:18080/logOut" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey}
		}
	);
	if (response.status_code == 200 || response.status_code == 202) {
		return true;
	}
	else {
		return false;
	}
}
