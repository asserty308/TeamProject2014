#pragma once

template <class T>
class Singleton
{
	protected:
		static T *singleton;

	public:
		virtual ~Singleton()
		{
		}

		inline static T* Get()
		{
			if (!singleton)
			{
				singleton = new T;
			}

			return (singleton);
		}

		static void Del()
		{
			if (singleton)	
			{
				delete (singleton);	
				singleton = NULL;
			}
		}
};

template <class T>
T* Singleton<T>::singleton = 0;