#pragma once

#include "WhalenWin.h"
#include "WhalenException.h"
#include <d3d11.h>
#include <wrl.h>
#include "DxgiInfoManager.h"

class Graphics {
public:
	class Exception : public WhalenException {
		using WhalenException::WhalenException;

	};
	class HrException : public Exception {
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class DeviceRemovedException : public HrException {
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;

	};

public:
	Graphics( HWND hWnd );
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept {
		const float color[] = { red, green, blue, 1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), color);
	}

private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapchain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};