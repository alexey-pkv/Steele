#ifndef STEELE_GROUND_H
#define STEELE_GROUND_H


#include "Utils.h"
#include "DataTypes/Types.h"
#include "DataTypes/Direction.h"


namespace Steele
{
	struct GroundTile
	{
	public:
		t_id		ID;
		Direction	Dir; 
		uint8_t 	Index;
	};
	
	
	class Ground
	{
	private:
		std::vector<GroundTile>	m_ground;
		
		
	public:
		~Ground() = default;
		
		Ground() = default;
		Ground(const Ground&) = default;
		Ground(Ground&&) = default;
		
		Ground& operator=(Ground&&) = default;
		Ground& operator=(const Ground&) = default;
		
		
	public:
		void Add(const GroundTile &gt);
		inline void Add(t_id id, Direction d, uint8_t index) { Add({id, d, index}); }
		
		bool Has(t_id id) const;
		inline bool Has(const GroundTile& gt) const { return Has(gt.ID); }
		
		bool Remove(t_id id);
		inline bool Remove(const GroundTile& gt) { return Remove(gt.ID); }
		
		inline void Clear() { clear(m_ground); }
		inline size_t Count() { return m_ground.size(); }
		inline bool IsEmpty() { return m_ground.empty(); }
		
		
	public:
		inline std::vector<GroundTile>::const_iterator begin() const { return m_ground.cbegin(); }
		inline std::vector<GroundTile>::const_iterator end() const { return m_ground.cend(); }
		inline std::vector<GroundTile>::iterator begin() { return m_ground.begin(); }
		inline std::vector<GroundTile>::iterator end() { return m_ground.end(); }
	};
}


#endif
