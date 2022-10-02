#include "WhalenException.h"
#include <sstream>

WhalenException::WhalenException(int line, const char* file) noexcept
	: line(line), file(file)
{

}

const char* WhalenException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WhalenException::GetType() const noexcept {
	return "Whalen Exception";

}

int WhalenException::GetLine() const noexcept {
	return line;
}

const std::string& WhalenException::GetFile() const noexcept {
	return file;
}

std::string  WhalenException::GetOriginString() const noexcept {
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}