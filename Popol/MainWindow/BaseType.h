#pragma once

#include <windows.h>
#include <cmath>

// Win32 API 에서 자주 사용하는 구조체인
// POINT, RECT, SIZE 를 좀더 사용하기 편하도록 재정의함.

struct Point;
struct Rect;
struct Size;

struct Point : public POINT
{
	Point(const LONG& _x = 0, const LONG& _y = 0)
	{
		x = _x;
		y = _y;
	}
	// 두 위치의 차이를 반환하는 연산자
	Point operator - (const Point& o)
	{
		return Point(x-o.x, y-o.y);
	}
	// 두 위치의 거리를 반환하는 연산자.
	float operator ^ (const Point& o)
	{
		return sqrt(float((x-o.x)*(x-o.x) + (y-o.y)*(y-o.y)));
	}
	Point ToScreen(HWND hWnd)
	{
		Point tmp(*this);
		::ClientToScreen(hWnd, &tmp);
		return tmp;
	}
	Point ToClient(HWND hWnd)
	{
		Point tmp(*this);
		::ScreenToClient(hWnd, &tmp);
		return tmp;
	}
};

struct Size : public SIZE
{
	Size(const LONG& _cx = 0, const LONG& _cy = 0)
	{
		cx = _cx;
		cy = _cy;
	}
};

struct Rect : public RECT
{
	Rect()
	{
		left = top = right = bottom = 0;
	}
	Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
	Rect(const Point& c, const Size& s)
	{
		left = c.x - s.cx/2;
		top = c.y - s.cy/2;
		right = left + s.cx;
		bottom = top + s.cy;
	}
	Rect(const Point& lt, const LONG& w, const LONG& h)
	{
		left = lt.x;
		top = lt.y;
		right = left + w;
		bottom = top + h;
	}
	Rect(const Point& lt, const Point& rb)
	{
		left = lt.x;
		top = lt.y;
		right = rb.x;
		bottom = rb.y;
	}
	Point lefttop()
	{
		return Point(left, top);
	}
	Point rightbottom()
	{
		return Point(right, bottom);
	}
	const LONG width() const
	{
		return (right - left);
	}
	const LONG height() const
	{
		return (bottom - top);
	}
	Rect ToScreen(HWND hWnd)
	{
		Rect tmp(*this);

		Point lt = tmp.lefttop();
		Point rb = tmp.rightbottom();

		::ClientToScreen(hWnd, &lt);
		::ClientToScreen(hWnd, &rb);

		return Rect(lt, rb);
	}
	Rect ToClient(HWND hWnd)
	{
		Rect tmp(*this);

		Point lt = tmp.lefttop();
		Point rb = tmp.rightbottom();

		::ScreenToClient(hWnd, &lt);
		::ScreenToClient(hWnd, &rb);

		return Rect(lt, rb);
	}
	// OffsetRect 대용으로 쓰기 위한 연산자.
	Rect operator << (const Size& diff)
	{
		return Rect(left - diff.cx, top - diff.cy,
			right - diff.cx, bottom - diff.cy);
	}
	Rect operator >> (const Size& diff)
	{
		return Rect(left + diff.cx, top + diff.cy,
			right + diff.cx, bottom + diff.cy);
	}
	// InflateRect 대용으로 쓰기 위한 연산자.
	Rect operator + (const Size& diff)
	{
		return Rect(left - diff.cx, top - diff.cy,
			right + diff.cx, bottom + diff.cy);
	}
	Rect operator - (const Size& diff)
	{
		return Rect(left + diff.cx, top + diff.cy,
			right - diff.cx, bottom - diff.cy);
	}
};

template<typename T, int Row, int Col>
struct Matrix
{
	typedef Matrix<T,Row,Col> Me;

	Matrix()
	{
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				m[i][j] = T(0);
			}
		}
	}
	Me& LoadIdentity(void)
	{
		if (Row != Col) return *this;

		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				if (i == j)
					m[i][j] = T(1);
				else
					m[i][j] = T(0);
			}
		}
		return *this;
	}

	Me operator + (const Me& other)
	{
		Me tmp(*this);
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				m[i][j] += other.m[i][j];
			}
		}
		return tmp;
	}
	Me operator - (const Me& other)
	{
		Me tmp(*this);
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col; j++)
			{
				m[i][j] -= other.m[i][j];
			}
		}
		return tmp;
	}
	template<int Col2>
	Matrix<T,Row,Col2> operator * (const Matrix<T,Col,Col2>& obj)
	{
		Matrix<T,Row,Col2> tmp;
		for (int i = 0; i < Row; i++)
		{
			for (int j = 0; j < Col2; j++)
			{
				for (int k = 0; k < Col; k++)
				{
					tmp.m[i][j] += this->m[i][k] * obj.m[k][j];
				}
			}
		}
		
		return tmp;
	}
	T m[Row][Col];
};