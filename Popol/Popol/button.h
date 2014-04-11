#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\image.h"
#include "Input.h"

class Button
{
	typedef void (*TODO)(HWND,UINT,WPARAM,LPARAM);
public :
	Button()
		: bMouseOver(false)
		, hOwner(NULL)
	{
	}
	void Attach(HWND hWnd)
	{
		hOwner = hWnd;
	}
	void SetImageOn(LPCTSTR szFileName, const Rect& rc)
	{
		imgOn.load(szFileName, rc);
	}
	void SetImageOff(LPCTSTR szFileName, const Rect& rc)
	{
		imgOff.load(szFileName, rc);
	}
	void SetButtonRect(const Rect& rc)
	{
		rcButton = rc;
	}
	void SetTransparent(COLORREF clr)
	{
		imgOn.SetTransparent(clr);
		imgOff.SetTransparent(clr);
	}
	void SetAction(TODO _action, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		action = _action;
		msg.hwnd = hWnd;
		msg.message = uMsg;
		msg.wParam = wParam;
		msg.lParam = lParam;
	}
	void Update(DWORD tick)
	{
		if (!hOwner) return;

		Point ptMouse = InputDevice.getPos();
		ptMouse = ptMouse.ToClient(hOwner);

		if (::PtInRect(&rcButton, ptMouse))
		{
			bMouseOver = true;

			if (InputDevice.OnClick(VK_LBUTTON))
			{
				if (action)
				{
					(*action)(msg.hwnd, msg.message, msg.wParam, msg.lParam);
				}
			}

		}
		else
		{
			bMouseOver = false;
		}
	}
	void Draw(HDC hdc)
	{
		if (!hOwner) return;

		if (bMouseOver)
			imgOn.Draw(hdc, rcButton);
		else 
			imgOff.Draw(hdc, rcButton);
	}


private :
	HWND hOwner;
	Image imgOn;
	Image imgOff;
	Rect rcButton;

	bool bMouseOver;

	TODO action;
	MSG msg;
};