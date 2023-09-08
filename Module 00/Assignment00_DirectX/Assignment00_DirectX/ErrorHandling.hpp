#pragma once

#include <stdexcept>
#include "DirectX.hpp"
#include <comdef.h>

class DirectXException : public std::exception
{
	public:
		DirectXException(HRESULT, const char *, int);
		~DirectXException(void) noexcept;
		const char* what(void) const noexcept override;
		HRESULT		getResult(void) const noexcept;
		const char* getFile(void) const noexcept;
		int			getLine(void) const noexcept;
	private:
		HRESULT hr;
		const char* fileName;
		int line;
		LPCTSTR errorMsg;
};