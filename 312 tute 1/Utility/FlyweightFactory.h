

#ifndef __FLYFACTORY_H__
#define __FLYFACTORY_H__

#include "../includes.h"
#include <map>


/**
 * @class	FlyweightFactory
 *
 * @brief	Flyweight factory. 
 *
 * @author	Noel Waghorn
 * @date	5/22/2011
 */

template <class T>
class FlyweightFactory
{
public:

	/**
	 * @fn	FlyweightFactory::FlyweightFactory()
	 *
	 * @brief	Default constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/22/2011
	 */

	FlyweightFactory(){Clear();}

	/**
	 * @fn	FlyweightFactory::~FlyweightFactory()
	 *
	 * @brief	Finaliser.
	 *
	 * @author	Noel Waghorn
	 * @date	5/22/2011
	 */

	~FlyweightFactory()
	{
		create_func = NULL;

		m_flyweights.clear();
	}

	/**
	 * @fn	T* FlyweightFactory::Get_data(std::string key);
	 *
	 * @brief	Gets a data.
	 *
	 * @author	Noel Waghorn
	 * @date	5/22/2011
	 *
	 * @param	key	The key.
	 *
	 * @return	null if it fails, else the data.
	 */

	T* Get_data(std::string key);

	/**
	 * @fn	void FlyweightFactory::Register_callbacks(bool(*create_fn)(std::string,T&));
	 *
	 * @brief	Registers the callbacks described by create_fn.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 *
	 * @param [in,out]	create_fn	If non-null, the create function.
	 */

	void Register_callbacks(bool(*create_fn)(std::string,T&));

private:

	/**
	 * @fn	void FlyweightFactory::Clear();
	 *
	 * @brief	Clears this object to its blank/initial state.
	 *
	 * @author	Noel Waghorn
	 * @date	18/09/2011
	 */

	void Clear();
	///< The flyweights
	std::map<std::string,T*> m_flyweights;

	/**
	 * @fn	FlyweightFactory::bool(*create_func)(std::string type,T&);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Noel Waghorn
	 * @date	5/22/2011
	 *
	 * @param	type		The type.
	 * @param [in,out]		@param [in,out]		The.
	 */

	bool(*create_func)(std::string type,T&) ;
	///< true to callback registered
	bool callback_registered;
};

/**
 * @fn	template <class T> void FlyweightFactory<T>::Clear()
 *
 * @brief	Clears this object to its blank/initial state.
 *
 * @author	Noel Waghorn
 * @date	5/22/2011
 *
 * @tparam	T	Generic type parameter.
 */

template <class T>
void FlyweightFactory<T>::Clear()
{
	m_flyweights.clear();
	callback_registered = false;
}

/**
 * @fn	template <class T> T* FlyweightFactory<T>::Get_data(std::string key)
 *
 * @brief	Gets a data.
 *
 * @author	Noel Waghorn
 * @date	5/22/2011
 *
 * @tparam	T	Generic type parameter.
 * @param	key	The key.
 *
 * @return	The data.
 */

template <class T>
T* FlyweightFactory<T>::Get_data(std::string key)
{
	if(m_flyweights.find(key)==m_flyweights.end())
	{
		m_flyweights[key] = new T;
		create_func(key,*m_flyweights[key]);
	}

	return m_flyweights[key];
}

/**
 * @fn	template <class T> void FlyweightFactory<T>::Register_callbacks(bool(*create_fn)(std::string,
 * 		T&))
 *
 * @brief	Registers the callbacks described by create_fn.
 *
 * @author	Noel Waghorn
 * @date	5/22/2011
 *
 * @tparam	T	Generic type parameter.
 * @param [in,out]	create_fn	If non-null, the create function.
 */

template <class T>
void FlyweightFactory<T>::Register_callbacks(bool(*create_fn)(std::string,T&))
{
	create_func = create_fn;
	callback_registered = true;
}

#endif



