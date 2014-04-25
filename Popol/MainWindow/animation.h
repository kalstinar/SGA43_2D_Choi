#pragma once

#include "image.h"
#include <vector>
#include "Manager.hpp"

class Animation
{
	typedef std::vector<Image*> depot;
	typedef depot::iterator depotiter;
public :
	Animation()
		: update_dt(0), delay(500)
		, bLoop(false), index(0)
		, bDoNotDraw(false)
	{
	}
	~Animation()
	{
		for (depotiter it = shotlist.begin();
			it != shotlist.end();
			it++)
		{
			delete (*it);
		}
	}

	void SetImage(depot& imagelist)
	{
		shotlist = imagelist;
	}
	void AddImage(Image* pImage)
	{
		shotlist.push_back(pImage);

		rcImage = pImage->getRect();
	}
	void SetLoop(bool _loop = true)
	{
		bLoop = _loop;
	}
	void SetDelay(DWORD _delay = 500)
	{
		delay = _delay;
	}
	void SetPosition(const Point& pt)
	{
		ptDraw = pt;
	}
	void Update(DWORD tick)
	{
		if (bDoNotDraw) return;

		if (update_dt >= delay)
		{
			index++;
			if (shotlist.size() == index)
			{
				if (bLoop)
				{
					index = 0;
				}
				else
				{
					bDoNotDraw = true;
				}
			}

			update_dt -= delay;
		}

		update_dt += tick;
	}
	void Draw(HDC hdc, const Rect& rc)
	{
		if (bDoNotDraw) return;

		shotlist[index]->Move(rc);
		shotlist[index]->Draw(hdc);
	}
	void Draw(HDC hdc)
	{
		if (bDoNotDraw) return;

		rcImage = Rect(ptDraw, Size(rcImage.width(), rcImage.height()));
		shotlist[index]->Move(rcImage);
		shotlist[index]->Draw(hdc);
	}
	void SetTransparent(COLORREF clr)
	{
		for (depotiter it = shotlist.begin();
			it != shotlist.end();
			it++)
		{
			(*it)->SetTransparent(clr);
		}
	}

private :
	depot shotlist;
	int index;
	DWORD delay;
	DWORD update_dt;
	bool bLoop;
	bool bDoNotDraw;
	Point ptDraw;
	Rect rcImage;

};


class AnimationManager : public Manager<Animation>, public singleton<AnimationManager>
{
};

#define AnimationDepot AnimationManager::getReference()