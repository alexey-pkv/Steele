#ifndef STEELE_STEELEEXCEPTION_H
#define STEELE_STEELEEXCEPTION_H


#include <exception>
#include <string>
#include <sstream>


namespace Steele
{
	class SteeleException : public std::exception
	{
	private:
		std::string m_msg;
		
		
	public:
		template<class ... T>
		explicit SteeleException(T&& ... args)
		{
			std::stringstream ss{};
			
			((ss << std::forward<T>(args) << " "), ...);
			
			m_msg = ss.str();
		}
		
		template<class ... T>
		explicit SteeleException(const T& ... args)
		{
			m_msg = std::string(std::forward<T>(args)...);
		}
		
		
	public:
		SteeleException() = default;
		~SteeleException() override = default;
		
		explicit SteeleException(std::string&& msg);
		explicit SteeleException(const std::string& msg);
		explicit SteeleException(const char* msg);
		
		
	public:
		const char* what() const noexcept override;
	};
}


#endif