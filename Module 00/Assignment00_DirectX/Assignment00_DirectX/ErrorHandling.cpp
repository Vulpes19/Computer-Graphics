#include "ErrorHandling.hpp"

DirectXException::DirectXException(HRESULT hr, const char* fileName, int line) : hr(hr), fileName(fileName), line(line)
{
	_com_error err(hr);
	errorMsg = err.ErrorMessage();
}

DirectXException::~DirectXException(void)
{}

const char* DirectXException::what(void) const noexcept
{
	size_t len = lstrlenW(errorMsg);
	char* ret = new char[len + 1];
	memcpy(ret, errorMsg, len);
	return(ret);
}

const char *DirectXException::getFile(void) const noexcept
{
	return (fileName);
}

HRESULT	DirectXException::getResult(void) const noexcept
{
	return (hr);
}

int	DirectXException::getLine(void) const noexcept
{
	return (line);
}