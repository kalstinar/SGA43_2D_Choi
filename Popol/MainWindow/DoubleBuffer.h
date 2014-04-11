#pragma once

#include <windows.h>
#include "BaseType.h"

/////////////////////////////////////////////////////////
// 더블버퍼링을 위한 클래스
class DoubleBuffer
{
	typedef DoubleBuffer Me;
public :
	DoubleBuffer()
		: hMainWnd(NULL), hMainDC(NULL), hMemDC(NULL), hMemBitmap(NULL)
	{
	}
	~DoubleBuffer()
	{
		Detach();
	}

	// 더블버퍼링을 사용할 Window Handle 과 연결.
	void Attach(HWND hWnd)
	{
		// 인자가 잘못됐다면 끝.
		if (hWnd == NULL) return;

		// 이미 연결되어 있다면...
		if (hMainWnd)
			// 연결된 연결을 끊어버린다.
			Detach();

		// 새로운 연결을 시도하자.
		hMainWnd = hWnd;

		// 윈도우의 크기 획득.
		::GetClientRect(hMainWnd, &rcClient);

		// Draw 에서 사용할 destDC, srcDC, srcBitmap 를 만든다.
		hMainDC = ::GetDC(hMainWnd);
		hMemDC = ::CreateCompatibleDC(hMainDC);
		hMemBitmap = ::CreateCompatibleBitmap(hMainDC, rcClient.width(), rcClient.height());
		hOldMemBitmap = Select(hMemDC, hMemBitmap);
	}
	// Window Handle 과의 연결을 끊어버린다.
	void Detach()
	{
		if (hMemBitmap)
		{
			Select(hMemDC, hOldMemBitmap);
			::DeleteObject(hMemBitmap);
			hMemBitmap = NULL;
		}
		if (hMemDC)
		{
			::DeleteDC(hMemDC);
			hMemDC = NULL;
		}
		if (hMainDC)
		{
			::ReleaseDC(hMainWnd, hMainDC);
			hMainDC = NULL;
			hMainWnd = NULL;
		}
	}

	void Draw()
	{
		// 연결된 window handle 이 없거나, DC 가 없다면 아무것도 하지 않는다.
		if (!hMainWnd || !hMainDC || !hMemDC) return;

		::BitBlt(hMainDC, rcClient.left, rcClient.top,
			rcClient.width(), rcClient.height(),
			hMemDC, 0, 0,
			SRCCOPY);
	}

public :
	// operator overloading..
	Me& operator << (const COLORREF& clr)
	{
		::SetDCBrushColor(hMemDC, clr);
		::FillRect(hMemDC, &rcClient, (HBRUSH)::GetStockObject(DC_BRUSH));

		return *this;
	}

	operator HDC()
	{
		return hMemDC;
	}

private :
	HWND hMainWnd;				// DoubleBuffer 기능을 사용할 window handle
	HDC hMainDC;				// 연결된 window handle 의 DC
	HDC hMemDC;					// DoubleBuffer 를 위한 메모리 DC
	HBITMAP hMemBitmap;			// 메모리 DC 에서 사용할 Bitmap
	HBITMAP hOldMemBitmap;		// SelectObject 용도
	Rect rcClient;				// 연결된 window handle 의 크기.
};