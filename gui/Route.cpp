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
	m_logger.logg(Logger::Level::Info, "leave lobby is succesful", response.status_code);
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
		m_logger.logg(Logger::Level::Info, "get question type numerical is succesful", response.status_code,"\n", response.text);
		return response.text;
	}
	else
	{
		m_logger.logg(Logger::Level::Error,"get question type numerical is failed", response.status_code);
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
		m_logger.logg(Logger::Level::Info, "get variants is succesful", response.status_code,"\n", questionData[0],"\n", questionData[1],"\n", questionData[2],"\n", questionData[3]);
		return questionData;
		
	}
	else
	{
		m_logger.logg(Logger::Level::Error, "Get variants is failed", response.status_code);
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
	m_logger.logg(Logger::Level::Info, "send response numerical et1 is succesful",resp);
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
	//m_logger.logg(Logger::Level::Info, "players queue is succesful","\n","player color",players.front().first, "\n","player score" ,players.front().second);
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

std::tuple<Color::ColorEnum, Color::ColorEnum, int> Route::getDuelingPlayersAndZone(Color::ColorEnum attacker, int zoneId)
{
	cpr::Url url{ "http://localhost:18080/duelParticipants" };
	cpr::Payload payload{
			{ "gameID", std::to_string(m_gameId)},
			{ "sessionKeyIter", m_sessionKey},
			{ "attacker", std::to_string(Color::ColorToInt(attacker))},
			{ "regionId", std::to_string(zoneId)}
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
	std::tuple<Color::ColorEnum, Color::ColorEnum, int> data;
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		data = std::make_tuple(Color::getColor(resData["color1"].i()), Color::getColor(resData["color2"].i()), resData["zoneId"].i());
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
		Color::ColorEnum colorAttacker = Color::getColor(resData["attackerColor"].i());
		std::string colorAttackerString = Color::ColorToString(colorAttacker);
		m_logger.logg(Logger::Level::Info, "get attacker color is succesful","\n","color attacker: ",colorAttackerString);
		return Color::getColor(resData["attackerColor"].i());
	}
	return Color::ColorEnum::None;
}

DuelManager Route::sendResponseEt2(Color::ColorEnum color, int response, int time)
{
	cpr::Url url{ "http://localhost:18080/sendResponseEt2" }; //cand trimiti variantele time nu conteaza pi oricat
	cpr::Payload payload{
			{ "sessionKey", m_sessionKey},
			{ "gameID", std::to_string(m_gameId)},
			{"color", std::to_string(Color::ColorToInt(color))},
			{"response", std::to_string(response)},
			{"time", std::to_string(time)},
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
	DuelManager duel;
	if (aux != "")
	{
		crow::json::rvalue resData = crow::json::load(aux);
		std::string duelStatus = resData["duelStatus"].s();
		if (duelStatus == "lifeTaken")
		{
			int ZoneId = resData["baseId"].i();
			int lives = resData["lives"].i();
			int score = resData["score"].i();
			Color::ColorEnum color = Color::getColor(resData["color"].i());
			Color::ColorEnum attacker = Color::getColor(resData["attacker"].i());
			Color::ColorEnum defender = Color::getColor(resData["defender"].i());
			duel.setLifeTaken(ZoneId, lives, score, color, attacker, defender);
			duel.setDuelStatus(DuelManager::duelStatus::lifeTaken);
			m_logger.logg(Logger::Level::Info, "life taken",ZoneId,score,lives);
			return duel;
		}
		else if (duelStatus == "Lose")
		{
			duel.setDuelStatus(DuelManager::duelStatus::Lose);
			m_logger.logg(Logger::Level::Info, "lose");
			return duel;
		}
		else if (duelStatus == "Draw")
		{
			duel.setDuelStatus(DuelManager::duelStatus::Draw);
			Color::ColorEnum attacker = Color::getColor(resData["attacker"].i());
			Color::ColorEnum defender = Color::getColor(resData["defender"].i());
			duel.setTieBreakerParticipants({ attacker, defender });
			m_logger.logg(Logger::Level::Info, "draw next to tie breaker");
			return duel;
		}
		else if (duelStatus == "Win")
		{
			std::vector<std::tuple<int, Color::ColorEnum, int>> zonesData;
			// Id , color , score
			int zoneNr = resData["zoneNr"].i();
			for (int i = 0; i < zoneNr; i++)
			{
				int score = resData["zoneScore" + std::to_string(i)].i();
				int id = resData["zoneId" + std::to_string(i)].i();
				Color::ColorEnum color = Color::getColor(resData["zoneColor" + std::to_string(i)].i());
				zonesData.push_back(std::make_tuple(id, color, score));
			}
			duel.setDuelStatus(DuelManager::duelStatus::Win);
			duel.setWinChanges(zonesData);
			m_logger.logg(Logger::Level::Info, "win");
			return duel;
		}
		else if (duelStatus == "None")
		{
			duel.setDuelStatus(DuelManager::duelStatus::None);
			return duel;
		}
	}
	return duel;
}

std::string Route::getQuestionTypeNumericalEt2()
{
	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/getQuestionTypeNumericalEt2" },
		cpr::Payload{
			{ "gameID", std::to_string(m_gameId)}
		});
	if (response.status_code == 200)
	{
		m_logger.logg(Logger::Level::Info, "get question type numerical et2 is succesful", response.status_code);
		return response.text;
	}
	else
	{
		m_logger.logg(Logger::Level::Error, "get question type numerical is failed", response.status_code);
		return "";
	}
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
		m_logger.logg(Logger::Level::Info, "valid", response.status_code);
		return value == "true";
	}
	else
	{
		m_logger.logg(Logger::Level::Warning,"invalid",response.status_code);
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
		m_logger.logg(Logger::Level::Info, "valid", response.status_code);
		return value == "true";
	}
	else
	{
		m_logger.logg(Logger::Level::Info, "invalid", response.status_code);
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
		m_logger.logg(Logger::Level::Info, "valid", response.status_code);
		return value == "true";
	}
	else
	{
		m_logger.logg(Logger::Level::Info, "invalid", response.status_code);
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
		m_logger.logg(Logger::Level::Info, "valid", response.status_code);
		return value == "true";
	}
	else
	{
		m_logger.logg(Logger::Level::Info, "invalid", response.status_code);
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
		m_logger.logg(Logger::Level::Info, "valid", response.status_code);
		return value == "true";
	}
	else
	{
		m_logger.logg(Logger::Level::Info, "invalid", response.status_code);
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
		auto zoneColorDll = Color::ColorToString(zoneColor);
		m_logger.logg(Logger::Level::Info, "zoneInfo update", response.status_code, zoneId,zoneColorDll,zoneScore,zoneLifes);
		return zoneInfo;
	}
	else
	{
		std::tuple<int, Color::ColorEnum, int, int> zoneInfo= std::make_tuple(0, Color::ColorEnum::None, 0, 0);
		m_logger.logg(Logger::Level::Warning, "-",0,"None",0,0);
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
		m_logger.logg(Logger::Level::Info, "update players info is successful", response.status_code);
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
	m_logger.logg(Logger::Level::Info, "lobby type", type, "is succesful", lambda);
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
	m_logger.logg(Logger::Level::Info, "getMatchHistoryRoute is succesful ", response.status_code);
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
		m_logger.logg(Logger::Level::Warning, "Other");
		return CredentialErrors::Other;
	}
	int resp = resData["error"].i();
	switch (resp)
	{
	case static_cast<int>(CredentialErrors::AlreadyConnected):
		m_logger.logg(Logger::Level::Warning, "Already Connected");
		return CredentialErrors::AlreadyConnected;
	case static_cast<int>(CredentialErrors::IncorrectAccount):
		m_logger.logg(Logger::Level::Warning, "Incorrect Account");
		return CredentialErrors::IncorrectAccount;
	case static_cast<int>(CredentialErrors::IncorrectPassword):
		m_logger.logg(Logger::Level::Warning, "Incorrect Password");
		return CredentialErrors::IncorrectPassword;
	case static_cast<int>(CredentialErrors::Valid):
		m_sessionKey = resData["sessionKey"].s();
		setNickname = QString::fromLocal8Bit(std::string(resData["nickname"].s()));
		m_logger.logg(Logger::Level::Info, "Valid");
		return CredentialErrors::Valid;
	default:
		m_logger.logg(Logger::Level::Warning, "Other");
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
		m_logger.logg(Logger::Level::Warning, "Other");
		return CredentialErrors::Other;
	}
	int resp = std::stoi(response.text);
	switch (resp)
	{
	case static_cast<int>(CredentialErrors::NameSize):
		m_logger.logg(Logger::Level::Warning, "NameSize");
		return CredentialErrors::NameSize;
	case static_cast<int>(CredentialErrors::UsernameSize):
		m_logger.logg(Logger::Level::Warning, "UsernameSize");
		return CredentialErrors::UsernameSize;
	case static_cast<int>(CredentialErrors::PasswordSize):
		m_logger.logg(Logger::Level::Warning, "PasswordSize");
		return CredentialErrors::PasswordSize;
	case static_cast<int>(CredentialErrors::UserTaken):
		m_logger.logg(Logger::Level::Warning, "UserTaken");
		return CredentialErrors::UserTaken;
	case static_cast<int>(CredentialErrors::NameTaken):
		m_logger.logg(Logger::Level::Warning, "NameTaken");
		return CredentialErrors::NameTaken;
	case static_cast<int>(CredentialErrors::Valid):
		m_logger.logg(Logger::Level::Info, "Valid");
		return CredentialErrors::Valid;

	default:
		m_logger.logg(Logger::Level::Warning, "Other");
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
		m_logger.logg(Logger::Level::Info, "Logout successful",response.status_code);
		return true;
	}
	else {
		m_logger.logg(Logger::Level::Error, "Logout unsuccesful", response.status_code);
		return false;
	}
}

std::pair<std::array<int, 4>, std::array<int, 3>> Route::useFourCloseAdvantage(const std::string& stage)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/useAdvantage" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey},
			{ "advantageType", "fourClose"},
			{ "gameID", std::to_string(m_gameId)},
			{ "stage", stage}
		}
	);
	std::array<int, 4> answers;
	std::array<int, 3 > zoneData;
	if (response.text != "")
	{
		m_logger.logg(Logger::Level::Info, "Use four close advantage fail", response.status_code);
		return std::make_pair(answers, zoneData);
	}
	else
	{
		crow::json::rvalue json = crow::json::load(response.text);
		answers[0] = json["r1"].i();
		answers[1] = json["r2"].i();
		answers[2] = json["r3"].i();
		answers[3] = json["r4"].i();
		zoneData[0] = json["zone"].i();
		zoneData[1] = json["score"].i();
		zoneData[2] = json["color"].i();
		m_logger.logg(Logger::Level::Info, "Use four close advantages is successful ", response.status_code);
		m_logger.logg(Logger::Level::Info, "Response: " + response.text);
		
	}
	return std::make_pair(answers, zoneData);
}

std::pair<int, std::array<int, 3 >> Route::useSugestionAdvantage(const std::string& stage)
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/useAdvantage" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey},
			{ "advantageType", "sugestion"},
			{ "gameID", std::to_string(m_gameId)},
			{ "stage", stage}
		}
	);
	int answer = 0;
	std::array<int, 3 > zoneData;
	if (response.text != "")
	{
		m_logger.logg(Logger::Level::Info, "Use sugestion advantage fail", response.status_code);
		return std::make_pair(answer, zoneData);
	}
	else
	{
		crow::json::rvalue json = crow::json::load(response.text);
		zoneData[0] = json["zone"].i();
		zoneData[1] = json["score"].i();
		zoneData[2] = json["color"].i();
		answer = json["r"].i();
		
	}
	return std::make_pair(answer, zoneData);
}

std::pair<std::array<std::string, 2>, std::array<int, 3 >> Route::useFiftyAdvantage()
{
	auto response = cpr::Post(
		cpr::Url{ "http://localhost:18080/useAdvantage" },
		cpr::Payload{
			{ "sessionKey", m_sessionKey},
			{ "advantageType", "50-50"},
			{ "gameID", std::to_string(m_gameId)},
			{ "stage", "ET2"}
		}
	);
	crow::json::rvalue resData = crow::json::load(response.text);
	std::array<std::string, 2> options;
	std::array<int, 3 > zoneData;
	if (response.text != "")
	{
		m_logger.logg(Logger::Level::Info, "Use fifty advantage fail", response.status_code);
		return std::make_pair(options, zoneData);
	}
	else
	{
		crow::json::rvalue json = crow::json::load(response.text);
		zoneData[0] = json["zone"].i();
		zoneData[1] = json["score"].i();
		zoneData[2] = json["color"].i();
		options[0] = json["r1"].s();
		options[1] = json["r2"].s();
		m_logger.logg(Logger::Level::Info, "Use four clase advantage successful", response.status_code);
	}
	return std::make_pair(options, zoneData);
}