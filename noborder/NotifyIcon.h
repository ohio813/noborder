#pragma once
#include <Windows.h>
#include <wchar.h>
#include <string>
#include <stdexcept>
#include <assert.h>

class NotifyIcon {
	typedef void(*EventHandler)(NotifyIcon & self, UINT msg);

	UINT const			m_id;
	std::wstring const	m_className;
	UINT const			m_taskbarCreatedMsg;
	HWND			m_hwnd;
	HICON			m_hicon;
	std::wstring	m_tipText;
	bool			m_isVisible;
	EventHandler	m_eventHandler;

	BOOL MyShell_NotifyIcon(
		NOTIFYICONDATAW &,
		bool const & forceAdd) const;
	void Update(
		bool const & forceAdd = false) const;
	void UpdateBalloon(
		std::wstring const & text,
		std::wstring const & title,
		DWORD const & infoFlag) const;

public:
	NotifyIcon(UINT const id, std::wstring const & className);
	~NotifyIcon();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	NotifyIcon& Init();
	HWND GetHwnd() const;

	bool IsVisible() const;
	NotifyIcon& SetVisible(bool const &);

	bool HasIcon() const;
	NotifyIcon& SetIcon(HICON const &);

	std::wstring const & GetTip() const;
	NotifyIcon& SetTip(std::wstring const &);	

	NotifyIcon& SetEventHandler(EventHandler const &);

	enum class BalloonIcon {
		None, Info, Warning, Error
	};
	
	NotifyIcon& ShowBalloon(
		std::wstring const & text,
		std::wstring const & title,
		BalloonIcon const & = BalloonIcon::Info);
	NotifyIcon& HideBalloon();

};
