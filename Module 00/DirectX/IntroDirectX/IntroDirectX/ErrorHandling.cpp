#include "ErrorHandling.hpp"

DirectXexcp::DirectXexcp(HRESULT res, const char* fileName, int line) : std::runtime_error("DirectX error"), res(res), fileName(fileName), line(line)
{
	_com_error	err(res);
	errorMsg = err.ErrorMessage();
}

DirectXexcp::~DirectXexcp(void)
{}

const char* DirectXexcp::what(void) const noexcept
{
	size_t len = lstrlenW(errorMsg);
	char* ret = new char[len + 1];
	memcpy(ret, errorMsg, len);
	return (ret);
}

HRESULT	DirectXexcp::getHResult(void) const noexcept
{
	return (res);
}

const char	*DirectXexcp::GetFile(void) const noexcept
{
	return (fileName);
}

int		DirectXexcp::getLine(void) const noexcept
{
	return (line);
}