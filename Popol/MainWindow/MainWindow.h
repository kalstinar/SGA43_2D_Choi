#pragma once

#include <windows.h>
#include <tchar.h>
#include <map>
#include "BaseType.h"
#include "utility.h"


template<typename T>
class MainWindow
{
	typedef MainWindow Me;
	typedef Callable<LRESULT, T, LRESULT(T::*)(HWND,UINT,WPARAM,LPARAM)> Action;
	typedef std::map<UINT, Action> EventMapType;
	typedef typename EventMapType::iterator Handler;
public :
	MainWindow()
		: lpszWindowTitle(NULL)
		, dwStyle(WS_OVERLAPPEDWINDOW)
		, width(500), height(500)
	{
	}
	~MainWindow()
	{
	}
	BOOL Setup(HINSTANCE hInst)
	{
		LPCTSTR lpClassName = _T("MyMainWindow");

		hMainInst = hInst;
		WNDCLASSEX wcex;

		::ZeroMemory(&wcex, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);
		wcex.hInstance = hInst;
		wcex.lpfnWndProc = &MainWindow::WndProc;
		wcex.lpszClassName = lpClassName;
		wcex.lpszMenuName = NULL;
		wcex.style = CS_VREDRAW | CS_HREDRAW;

		if (!::RegisterClassEx(&wcex))
		{
			DWORD dwError = ::GetLastError();

			//ErrorMessageBox(dwError);
			return FALSE;
		}

		SetEventMap();

		int cx = ::GetSystemMetrics(SM_CXSCREEN);
		int cy = ::GetSystemMetrics(SM_CYSCREEN);

		cx = (cx-500)/2;
		cy = (cy-500)/2;

		hMainWnd = ::CreateWindowEx(0, lpClassName,
			((lpszWindowTitle)? lpszWindowTitle : _T("sample")),
			dwStyle,
			cx,
			cy,
			width,
			height,
			0,
			0,
			hInst,
			this);

		if (hMainWnd == NULL)
		{
			DWORD dwError = ::GetLastError();

			//ErrorMessageBox(dwError);
			return FALSE;
		}


		::ShowWindow(hMainWnd, SW_NORMAL);
		::UpdateWindow(hMainWnd);

		return TRUE;
	}
protected :
	void SetWindowTitle(LPCTSTR szTitle)
	{
		SafeDelete(lpszWindowTitle);
		strAlloc(&lpszWindowTitle, szTitle);
	}
	void SetWindowStyle(DWORD style)
	{
		dwStyle = style;
	}
	void SetWindowSize(const int& w, const int& h)
	{
		width = w;
		height = h;
	}

	virtual void SetEventMap()
	{
		AddEventHandler(WM_DESTROY, &Me::OnDestroy);
	}
	// 새로운 이벤트 처리기 등록.
	void AddEventHandler(UINT msg, Action act)
	{
		Handler it = eventmap.find(msg);
		if (it == eventmap.end())
		{
			eventmap.insert(std::make_pair(msg, act));
		}
	}
	// do update entire client screen.
	void Invalidate(BOOL bErase = TRUE)
	{
		RECT rc;
		::GetClientRect(hMainWnd, &rc);
		::InvalidateRect(hMainWnd, &rc, bErase);
	}

	LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Post WM_QUIT message to thread's message queue.
		::PostQuitMessage(0);
		return 0;
	}





	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		MainWindow* pWin;
		if (uMsg == WM_CREATE)
		{
			LPCREATESTRUCT lpcs;
			lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);

			pWin = reinterpret_cast<MainWindow*>(lpcs->lpCreateParams);

			// for 64bit compatible : LONG => PtrToUlong
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, PtrToUlong(pWin));

			return pWin->EventHandler(hWnd,uMsg,wParam,lParam);
		}
		else
		{
			pWin = reinterpret_cast<MainWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

			if (pWin)
			{
				return pWin->EventHandler(hWnd, uMsg, wParam, lParam);
			}
		}

		return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	LRESULT EventHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Handler it = eventmap.find(uMsg);
		if (it != eventmap.end())
		{
			return (it->second)(this, hWnd, uMsg, wParam, lParam);
		}

		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

protected :
	HINSTANCE hMainInst;
	HWND hMainWnd;

private :
	EventMapType eventmap;
	LPTSTR lpszWindowTitle;
	DWORD dwStyle;
	int width;
	int height;
};