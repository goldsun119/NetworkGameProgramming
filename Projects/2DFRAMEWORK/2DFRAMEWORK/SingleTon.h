#pragma once

/*
---------------------------------------------------------------------------------------
ΩÃ±€≈Ê ≈€«√∏¥ ≈¨∑πΩ∫
---------------------------------------------------------------------------------------
*/

template <typename T>
class CSingleTonBase
{

protected:

	static T* m_Instance;

protected:

	CSingleTonBase() {}
	~CSingleTonBase() {};


public:
	static T* GetInstance()
	{
		if (0 == m_Instance)
			return m_Instance = new T;

		return m_Instance;
	}

	void ReleseInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}
};

//ΩÃ±€≈œ ¿ŒΩ∫≈œΩ∫ √ ±‚»≠
template <typename T>
T*	CSingleTonBase<T>::m_Instance = 0;
#pragma once
