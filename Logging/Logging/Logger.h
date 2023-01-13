#pragma once
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif
#include<iostream>
#include<chrono>
class LOGGER_API Logger
{
public:
	enum class Level
	{
		Info,
		Warning,
		Error
	};

public:
	Logger(std::ostream& os, Level minimumLevel = Level::Info);

	void log(const char* message, Level level);
	void log(const std::string& message, Level level);
	template<class... T>
	void logg(Level level, T... messages)
	{
		std::string newString;

		switch (level)
		{
		case Logger::Level::Info:
			newString = "Info";
		case Logger::Level::Warning:
			newString = "Warning";
		case Logger::Level::Error:
			newString = "Error";
		default:
			newString = "";
		}
		if (static_cast<int>(level) < static_cast<int>(minimumLevel))
			return;
		getCurrentTime();
		os  << newString << "] ";
		((os << messages), ...);
		os << std::endl;
	}
	void setMinimumLogLevel(Level level);
	

private:
	std::ostream& os;
	Level minimumLevel;
	void getCurrentTime();
	
	
};


