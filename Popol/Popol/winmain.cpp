#include "MoveApp.h"

INT
WINAPI
_tWinMain(HINSTANCE hInst,
		  HINSTANCE, LPTSTR, INT)
{
	MoveApp app;

	app.Setup(hInst);

	MSG msg;

	DWORD dt = 1;
	DWORD st = ::GetTickCount();

	while (true)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
			break;

		InputDevice.Update(dt);

		app.Input(dt);
		app.Update(dt);
		app.Render(dt);

		dt = ::GetTickCount() - st;
		st = ::GetTickCount();

	}

	return msg.wParam;
}
