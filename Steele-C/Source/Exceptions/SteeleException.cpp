#include "Exceptions/SteeleException.h"


Steele::SteeleException::SteeleException(std::string&& msg):
	m_msg(std::move(msg))
{
	
}

Steele::SteeleException::SteeleException(const std::string& msg) : 
	m_msg(msg)
{
	
}

Steele::SteeleException::SteeleException(const char *msg) : 
	m_msg(msg)
{
	
}

const char* Steele::SteeleException::what() const noexcept
{
	return m_msg.c_str();
}
