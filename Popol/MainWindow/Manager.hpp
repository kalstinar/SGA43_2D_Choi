#pragma once

#include <string>
#include <map>

template<typename T>
class Manager
{
protected :
	typedef T element;
	typedef element* pointer;
	typedef element& reference;
	typedef std::map<std::string,pointer> Container;
	typedef typename Container::iterator Iter;
public :
	Manager()
	{
	}
	virtual ~Manager()
	{
		_release();
	}

public :
	void push(const std::string& name, pointer pEntity)
	{
		if (!pEntity) return;

		depot.insert(std::make_pair(name, pEntity));
	}
   pointer get(const std::string& name)
   {
      Iter it = depot.find(name);
      if (it == depot.end())
         return NULL;

      return it->second;
   }
   pointer operator [] (const std::string& name)
   {
      Iter it = depot.find(name);
      if (it == depot.end())
         return NULL;

      return it->second;
   }

private :
	void _release()
	{
		for (Iter it = depot.begin();
			  it != depot.end();)
		{
			delete it->second;
			it = depot.erase(it);
		}
	}
protected :
	Container depot;
};
