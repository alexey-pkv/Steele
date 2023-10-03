#ifndef STEELE_GROUND_H
#define STEELE_GROUND_H


#include "Utils.h"
#include "DataTypes/Types.h"
#include "DataTypes/Direction.h"
#include "DataTypes/IDMap.h"


namespace Steele
{
	struct GroundTile
	{
	public:
		t_id		ID;
		Direction	Dir; 
		uint8_t 	Index;
		
		
	public: // JSON
		void json_write(const IDMap& map, nlohmann::json& into) const;
		void json_read(const IDMap& map, const nlohmann::json& from);
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
		void add(const GroundTile &gt);
		inline void add(t_id id, Direction d, uint8_t index) { add({id, d, index}); }
		
		inline void set(const GroundTile &gt) { clear(); add(gt); }
		inline void set(t_id id, Direction d, uint8_t index) { set({id, d, index}); }
		
		bool has(t_id id) const;
		inline bool has(const GroundTile& gt) const { return has(gt.ID); }
		
		bool remove(t_id id);
		inline bool remove(const GroundTile& gt) { return remove(gt.ID); }
		
		inline void clear() { ::clear(m_ground); }
		inline size_t size() const { return m_ground.size(); }
		inline bool is_empty() const { return m_ground.empty(); }
		
		
	public:
		inline std::vector<GroundTile>::const_iterator begin() const { return m_ground.cbegin(); }
		inline std::vector<GroundTile>::const_iterator end() const { return m_ground.cend(); }
		inline std::vector<GroundTile>::iterator begin() { return m_ground.begin(); }
		inline std::vector<GroundTile>::iterator end() { return m_ground.end(); }
		
		inline std::vector<GroundTile>::const_reverse_iterator rbegin() const { return m_ground.crbegin(); }
		inline std::vector<GroundTile>::const_reverse_iterator rend() const { return m_ground.crend(); }
		inline std::vector<GroundTile>::reverse_iterator rbegin() { return m_ground.rbegin(); }
		inline std::vector<GroundTile>::reverse_iterator rend() { return m_ground.rend(); }
		
		
	public:
		inline GroundTile* operator[](int index) { return index < 0 || index >= m_ground.size() ? nullptr : &m_ground[index]; }
	};
}


#endif
