#pragma once

#include <exception>
#include <stdexcept>
#include <Windows.h>
#include <comdef.h>

class DirectXexcp : public std::runtime_error
{
public:
	DirectXexcp(HRESULT, const char*, int);
	virtual ~DirectXexcp(void) noexcept;
	const char* what(void) const noexcept override;
	HRESULT		getHResult(void) const noexcept;
	const char* GetFile(void) const noexcept;
	int			getLine(void) const noexcept;
private:
	HRESULT		res;
	const char	*fileName;
	int			line;
	LPCTSTR		errorMsg;
};