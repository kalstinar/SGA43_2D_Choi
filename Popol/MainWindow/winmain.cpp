#include "ClockApp.h"

INT
WINAPI
_tWinMain(HINSTANCE hInst,
		  HINSTANCE,
		  LPTSTR,
		  INT)
{
	ClockApp app;

	app.Setup(hInst);

	MSG msg;

	while (true)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;
	}

	return msg.wParam;
}

