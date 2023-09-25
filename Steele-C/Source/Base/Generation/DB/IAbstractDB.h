#ifndef STEELE_IABSTRACTDB_H
#define STEELE_IABSTRACTDB_H


#include <map>

#include "Utils.h"
#include "DataTypes/Types.h"


namespace Steele
{
	template<typename T>
	class IAbstractDB
	{
	public:
		virtual bool has(t_id id) = 0;
		virtual T* get(t_id id) = 0;
		virtual const T* get(t_id id) const = 0;
		virtual T* require(t_id id) = 0;
		virtual const T* require(t_id id) const = 0;
		virtual bool remove(t_id id) = 0;
	};
	
	
	template<typename T>
	class AbstractDB : public IAbstractDB<T>
	{
	private:
		std::map<t_id, uptr<T>>	m_db;
		
		
	protected:
		inline std::map<t_id, uptr<T>>&	db() { return m_db; };
		
		T* _create_(t_id id)
		{
			remove(id);
			db()[id] = std::move(std::make_unique<T>());
			return get(id);
		}
		
		template<class N>
		N* _create_(t_id id)
		{
			remove(id);
			db()[id] = std::move(std::make_unique<N>());
			return (N*)get(id);
		}
		
		
	public:
		bool has(t_id id) override
		{
			return contains(m_db, id);
		}
		
		T* get(t_id id) override
		{
			auto kvp = m_db.find(id);
			return kvp == m_db.end() ? nullptr : kvp->second.get();
		}
		
		const T* get(t_id id) const override
		{
			auto kvp = m_db.find(id);
			return kvp == m_db.end() ? nullptr : kvp->second.get();
		}
		
		T* require(t_id id) override
		{
			auto res = get(id);
			
			if (!res)
				throw SteeleException("Object with id ", id, " not found");
			
			return res;
		}
		
		const T* require(t_id id) const override
		{
			auto res = get(id);
			
			if (!res)
				throw SteeleException("Object with id ", id, " not found");
			
			return res;
		}
		
		bool remove(t_id id) override
		{
			return ::remove(m_db, id);
		}
	};
	
	
	template<typename T>
	class IAbstractSingleTypeDB : public IAbstractDB<T>
	{
	public:
		virtual T* create(t_id id) = 0;
	};
	
	template<typename T>
	class AbstractSingleTypeDB : public IAbstractSingleTypeDB<T>, public AbstractDB<T>
	{
	public:
		bool has(t_id id) override { return AbstractDB<T>::has(id); }
		T* get(t_id id) override { return AbstractDB<T>::get(id); }
		const T* get(t_id id) const override { return AbstractDB<T>::get(id); }
		bool remove(t_id id) override { return AbstractDB<T>::remove(id); }
		T* require(t_id id) override { return AbstractDB<T>::require(id); }
		const T* require(t_id id) const override { return AbstractDB<T>::require(id); }
	
	
	public:
		T* create(t_id id) override
		{
			remove(id);
			this->_create_(id);
			return get(id);
		}
	};
}


#endif