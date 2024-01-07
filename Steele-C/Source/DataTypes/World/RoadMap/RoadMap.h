#ifndef STEELE_ROADMAP_H
#define STEELE_ROADMAP_H


#include "Utils.h"
#include "DataTypes/Types.h"
#include "DataTypes/World/Road.h"


namespace Steele
{
	struct RoadEdge;
	struct RoadNode;
	
	
	enum class RoadType : char
	{
		Road	= 0,
		Subway	= 10
	};
	
	
	struct RoadEdge
	{
	public:
		t_id			LocationID;
		v2i 			At;
		RoadType		Type				= RoadType::Subway;
		vec<RoadNode*>	Nodes;
		RoadNode*		ToSubway			= nullptr;
		int 			DistanceToSubway	= 0;
		
		
	public:
		inline bool has_location_attached() const { return LocationID != STEELE_NULL_ID; }
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const;
		void json_read(const nlohmann::json& from);
	};
	
	
	struct RoadNode
	{
	private:
	public:
		RoadEdge*	A		= nullptr;
		RoadEdge*	B		= nullptr;
		t_id		Via		= STEELE_NULL_ID;
		RoadType	Type	= RoadType::Road;
		v2i 		Segment;
		
	
	public:
		inline RoadEdge* get_other(RoadEdge* e) { return e == A ? B : A; }
		inline int length() const { return abs(Segment.y - Segment.x); }
		inline bool has(RoadEdge* e) const { return e == A || e == B; }
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const;
		void json_read(const nlohmann::json& from, const std::map<t_id, RoadEdge*>&);
	};
	
	
	class INavigator
	{
	public:
		virtual ~INavigator() = default;
		
		
	public:
		virtual bool can_use(const RoadNode* node) const = 0;
		virtual bool can_use(const RoadEdge* edge) const = 0;
		
		virtual int segment_cost(const RoadEdge* edge, v2i segment) const = 0;
		virtual int node_cost(const RoadNode* node) const = 0;
	};
	
	
	class RoadMap
	{
	private:
		vec_unique<RoadEdge>			m_edges;
		vec_unique<RoadNode>			m_nodes;
		vec<RoadEdge*>					m_subways;
		std::map<t_id, RoadEdge*>		m_edgesByLocationID;
		std::map<t_id, vec<RoadEdge*>>	m_edgesByRoadID;
		
		
	private:
		void index_subways();
		void index_by_location();
		void index_by_road_id();
		void index_subway_path();
		
		
	public:
		inline size_t subways_count() const { return m_subways.size(); }
		inline size_t intersections_count() const { return edges_count() - subways_count(); }
		inline size_t edges_count() const { return m_edges.size(); }
		inline size_t nodes_count() const { return m_nodes.size(); }
		
		inline bool has_subways() const { return !m_subways.empty(); }
		inline bool is_empty() const { return m_edges.empty(); }
		
		
	public:
		RoadEdge* create(t_id locationID, v2i at, RoadType type);
		RoadEdge* create_road(t_id locationID, v2i at);
		RoadEdge* create_subway(t_id locationID, v2i at);
		
		void index();
		
		
	public:
		void connect(RoadEdge* a, RoadEdge* b, t_id via, v2i segment, RoadType type);
		void connect_road(RoadEdge* a, RoadEdge* b, t_id via, v2i segment);
		void connect_subway(RoadEdge* a, RoadEdge* b);
		
		
	public:
		svec<RoadEdge> find_path(t_id from, v2i from_segment, t_id to, v2i to_segment) const;
		
		inline svec<RoadEdge> find_path(const Road* from, v2i from_segment, const Road* to, v2i to_segment) const
		{
			return find_path(from->ID, from_segment, to->ID, to_segment);
		}
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const;
		void json_read(const nlohmann::json& from);
	};
}


#endif