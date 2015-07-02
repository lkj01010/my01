/*
* Copyright (C) 2010
* All rights reserved.
*/
/*
* Filename:        Singleton.h
* Creator Date:
* Author:         Andy
*/
#ifndef _SINGLETON_H
#define _SINGLETON_H
#include <stddef.h>

namespace my
{
	template<typename T>
	class singleton
	{
	public:
		static T &instance()
		{
			if (NULL == inst)
			{
				inst = new T();
			}
			return *inst;
		}

		static T* instance_ptr()
		{
			if (NULL == inst)
			{
				inst = new T();
			}
			return inst;
		}

		static void destroy()
		{
			if (NULL != inst)
			{
				delete inst;
				inst = NULL;
			}
		}

	protected:
		singleton()
		{
		}
		~singleton()
		{
		}

	private:
		/*singleton (const singleton &)
		{
		}    */
		static T *inst;
		/*singleton &operator = (const singleton &)
		{
		}*/
	};

	template<typename T>
	T *singleton<T>::inst = NULL;
}

#endif
