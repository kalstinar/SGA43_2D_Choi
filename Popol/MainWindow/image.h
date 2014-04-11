#pragma once

#include <windows.h>

////////////////////////////////////////////////////////////////////////////
// 이미지를 읽어들이고 그리는 작업을 편리하도록 만든 클래스.

class Image
{
public :
	Image()
		: hBitmap(NULL)
		, clrTransparent(RGB(0,0,0))
		, bUseTransparent(false)
	{
	}
	~Image()
	{
		release();
	}

public :
	// 이미지 파일명으로 읽어들이고 그릴 때 지정된 부분만 그리도록 부분도 설정.
	BOOL load(LPCTSTR szFileName, const Rect& rc)
	{
		// 이미 읽어들인 이미지가 있다면...
		if (hBitmap)
			// 해제를 하고..
			release();

		// 지정된 이미지를 읽어들인다.
		hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
		if (hBitmap == NULL)
			return FALSE;

		// 그려질 부분도 설정한다.
		rcBitmap = rc;

		return TRUE;
	}
	// 이미지 파일명만으로 이미지를 읽어들인다.
	// 그리는 부분은 이미지 전체.
	BOOL load(LPCTSTR szFileName)
	{
		// 이미 읽어들인 이미지가 있다면...
		if (hBitmap)
			// 해제를 하고...
			release();

		// 지정된 이미지를 읽어들이고...
		hBitmap = (HBITMAP)::LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_SHARED);
		if (hBitmap == NULL)
			return FALSE;

		// 따로 지정된 그릴 부분이 없으니 이미지 전체를 설정.
		BITMAP bm;
		::GetObject(hBitmap, sizeof(BITMAP), &bm);
		rcBitmap = Rect(Point(0,0), Point(bm.bmWidth, bm.bmHeight));

		return TRUE;
	}
	void release()
	{
		// 이미지 핸들이 유효하다면...
		if (hBitmap)
		{
			// 해제한다..
			::DeleteObject(hBitmap);
			hBitmap = NULL;
		}
	}
	// 그리기..
	void Draw(HDC hdc, const Rect& rcDest, DWORD rop = SRCCOPY)
	{
		HDC hBitmapDC = ::CreateCompatibleDC(hdc);
		HBITMAP hOldBitmap = Select(hBitmapDC, hBitmap);

		// 투명처리를 사용한다면...
		if (bUseTransparent)
		{
			::GdiTransparentBlt(hdc,									// 그려질 DC
								rcDest.left, rcDest.top,				// 그려질 위치
								rcDest.width(), rcDest.height(),		// 그려질 크기
								hBitmapDC,								// 이미지 DC
								rcBitmap.left, rcBitmap.top,			// 이미지 부분 위치
								rcBitmap.width(), rcBitmap.height(),	// 이미지 부분 크기
								clrTransparent);						// 투명처리할 색
		}
		else
		{
			::BitBlt(hdc,									// 그려질 DC
					 rcDest.left, rcDest.top,				// 그려질 위치
					 rcDest.width(), rcDest.height(),		// 그려질 크기
					 hBitmapDC,								// 이미지 DC
					 rcBitmap.left, rcBitmap.top,			// 이미지 부분 위치
					 rop);									// 이미지를 그리는 방법.
		}

		Select(hBitmapDC, hOldBitmap);
		::DeleteDC(hBitmapDC);
	}
	// 투명처리를 하기 위한 설정..
	void SetTransparent(COLORREF clr)
	{
		clrTransparent = clr;
		bUseTransparent = true;
	}
	// 그려질 부분의 크기를 반환.
	Rect getRect()
	{
		return rcBitmap;
	}

	// 이미지 핸들 자체를 필요로 하는 경우에 호출됨.
	operator HBITMAP ()
	{
		return hBitmap;
	}
	// getRect 를 편하게 쓰기 위해 선언...
	operator Rect ()
	{
		return rcBitmap;
	}

private :
	HBITMAP hBitmap;
	Rect rcBitmap;

	COLORREF clrTransparent;
	bool bUseTransparent;
};