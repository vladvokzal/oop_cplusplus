#ifndef ERRORS
#define ERRORS

#include <string>
#include <exception>


class ErrorParametr : public std::exception
{

public:
	
	ErrorParametr(const std::string& message) : msg(message) {}
	
	const char* what() const throw() override
	{
		return msg.c_str();
	}

private:

	const std::string msg;
};

class ErrorGameOver : public std::exception
{

public:

	ErrorGameOver(const std::string& message) : msg(message) {}

	const char* what() const throw() override
	{
		return msg.c_str();
	}

private:

	const std::string msg;
};


#endif // !ERRORS