#ifndef STEELE_ABORTMAP_H
#define STEELE_ABORTMAP_H


#include "SimpleMap.h"
#include "MapDecorator.h"
#include "IStackableMap.h"

#include "Exceptions/PaintException.h"


namespace Steele
{
	template <typename CELL>
	class AbortMap : 
		public MapDecorator<CELL>
	{
	private:
		inline IMap<CELL>& get_map() { return this->next(); }
		inline const IMap<CELL>& get_map() const { return this->next(); }
		
		
	private:
		bool m_abort = false;
		
		
	public:
		explicit AbortMap(IMap<CELL>& map) : MapDecorator<CELL>(map) {}
		
		AbortMap() = default;
		~AbortMap() = default;
		
		
	public:
		void clear() override
		{
			get_map().clear();
		}
		
	
	protected:
		void _set(const CELL &c, v3i at) override
		{
			validate_abort();
			get_map().set(c, at);
		}
		
		void _set(CELL&& c, v3i at) override
		{
			validate_abort();
			get_map().set(c, at);
		}
		
		CELL* _try_get(v3i at) override				{ return get_map().try_get(at); }
		const CELL* _try_get(v3i at) const override	{ return get_map().try_get(at); }
		CELL* _get(v3i at) override					{ return get_map().get(at); }
		bool _is_empty(v3i at) const override		{ return get_map().is_empty(at); }
		bool _remove(v3i at) override				{ return get_map().remove(at); }
	
		
	public:
		size_t size() const override				{ return get_map().size(); };
		
		
	public:
		void abort()
		{
			m_abort = true;
		}
		
		void reset_abort()
		{
			m_abort = false;
		}
		
		void validate_abort()
		{
			if (m_abort)
			{
				throw AbortException();
			}
		}
	};
}


#endif