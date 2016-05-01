template <class T>
class TSingleton
{
public:
	static inline T* getInstance()
	{
		if (!pInstance)
		{
			pInstance = new T;
			pInstance->Init();
		}
		return pInstance;
	}

	static inline void deleteInstance()
	{
		if (pInstance)
		{
			pInstance->UnInit();
			delete pInstance;
		}
	}
protected:
	TSingleton(void){};
	~TSingleton(void){};
	virtual void Init(){};
	virtual void UnInit(){};
private:
	TSingleton(const TSingleton<T>&){};
	TSingleton<T>& operator= (const TSingleton<T> &){};
	static T* pInstance;
};

template <class T>
T* TSingleton<T>::pInstance = NULL;