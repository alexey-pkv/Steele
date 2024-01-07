#include "RoadMap.h"
#include "json.h"
#include "Exceptions/SteeleException.h"


using namespace Steele;


void RoadMap::connect(Steele::RoadEdge* a, Steele::RoadEdge* b, t_id via, v2i segment, RoadType type)
{
	m_nodes.push_back(std::make_unique<RoadNode>());
	
	RoadNode* node = m_nodes.back().get();
	
	node->Type		= type;
	node->A			= a;
	node->B			= b;
	node->Segment	= segment;
	node->Via		= via;
	
	a->Nodes.push_back(node);
	b->Nodes.push_back(node);
}

void RoadMap::connect_road(Steele::RoadEdge* a, Steele::RoadEdge* b, t_id via, v2i segment)
{
	connect(a, b, via, segment, RoadType::Road);
}

void RoadMap::connect_subway(Steele::RoadEdge* a, Steele::RoadEdge* b)
{
	connect(a, b, STEELE_NULL_ID, v2i_zero, RoadType::Subway);
}


void RoadMap::index_subways()
{
	for (int outer = 0; outer < (int)(m_subways.size()) - 1; outer++)
	{
		for (int inner = outer + 1; inner < m_subways.size(); inner++)
		{
			auto* a = m_subways[outer];
			auto* b = m_subways[inner];
			
			connect_subway(a, b);
		}
	}
}

void RoadMap::index_by_location()
{
	for (auto& e : m_edges)
	{
		if (e->has_location_attached())
		{
			m_edgesByLocationID[e->LocationID] = e.get();
		}
	}
}

void RoadMap::index_by_road_id()
{
	for (auto& ptr : m_edges)
	{
		auto e = ptr.get();
		std::set<t_id> roads;
		
		for (auto c : e->Nodes)
		{
			roads.insert(c->Via);
		}
		
		for (auto id : roads)
		{
			auto existing = m_edgesByRoadID.find(id);
			
			if (existing == m_edgesByRoadID.end())
			{
				m_edgesByRoadID[id] = { e };
			}
			else
			{
				existing->second.push_back(e);
			}
		}
	}
}

void RoadMap::index_subway_path()
{
	vec<RoadEdge*> curr = m_subways;
	vec<RoadEdge*> next;
	
	while (!curr.empty())
	{
		for (auto* e : curr)
		{
			for (auto node : e->Nodes)
			{
				auto* other = node->get_other(e);
				auto dist = node->length() + e->DistanceToSubway;
				
				if (other == e)
					continue;
					
				if (other->Type == RoadType::Subway)
				{
					continue;
				}
				else if (other->ToSubway && other->DistanceToSubway <= dist)
				{
					continue;
				}
				
				other->ToSubway = node;
				other->DistanceToSubway = dist;
				
				next.push_back(other);
			}
		}
		
		std::swap(curr, next);
		next.clear();
	}
}


RoadEdge* RoadMap::create(t_id locationID, v2i at, RoadType type)
{
	m_edges.push_back(std::make_unique<RoadEdge>());
	
	auto edge = m_edges.back().get();
	
	edge->Type		= type;
	edge->LocationID = locationID;
	edge->At			= at;
	
	return edge;
}

RoadEdge* RoadMap::create_road(t_id locationID, v2i at)
{
	return create(locationID, at, RoadType::Road);
}

RoadEdge* RoadMap::create_subway(t_id locationID, v2i at)
{
	auto edge = create(locationID, at, RoadType::Subway);
	
	m_subways.push_back(edge);
	
	return edge;
}


void RoadMap::index()
{
	index_subways();
	index_by_location();
	index_by_road_id();
	index_subway_path();
}

svec<RoadEdge> RoadMap::find_path(t_id from, v2i from_segment, t_id to, v2i to_segment) const
{
	return svec<RoadEdge>();
}


void RoadEdge::json_write(nlohmann::json& into) const
{
	into = {
		{ "id",		LocationID },
		{ "at",		Steele::json_write(At) },
		{ "type",	(int)Type }
	};
}

void RoadEdge::json_read(const nlohmann::json& from)
{
	if (!from.is_object())
		return;
	
	LocationID	= from["id"].get<int>();
	At			= from["at"].get<v2i>();
	Type		= (RoadType)from["type"].get<int>();
}

void RoadNode::json_write(nlohmann::json& into) const
{
	into = {
		{ "edges",		nlohmann::json::array({ A->LocationID, B->LocationID }) },
		{ "via",		Via },
		{ "type",		(int)Type },
		{ "segment",	Steele::json_write(Segment) }
	};
}

void RoadNode::json_read(const nlohmann::json& from, const std::map<t_id, RoadEdge*>& map)
{
	if (!from.is_object())
		return;
	
	Segment		= from["segment"].get<v2i>();
	Via			= from["via"].get<int>();
	Type		= (RoadType)from["type"].get<int>();
	
	auto& edges = from["edges"];
	
	if (!edges.is_array() || edges.size() != 2)
		throw SteeleException("Missing edges value or it's not correctly formatted");
	
	auto a_id = edges[0].get<int>();
	auto b_id = edges[0].get<int>();
	
	auto a = map.find(a_id);
	auto b = map.find(b_id);
	
	if (a == map.end())
		throw SteeleException("Edge with ID ", a_id, " not found");
	if (b == map.end())
		throw SteeleException("Edge with ID ", b_id, " not found");
	
	A = a->second;
	B = b->second;
}

void RoadMap::json_write(nlohmann::json& into) const
{
	into = nlohmann::json::object();
	
	auto nodes = nlohmann::json::array();
	auto edges = nlohmann::json::array();
	
	for (auto& e : m_edges)
	{
		nlohmann::json j;
		e->json_write(j);
		nodes.push_back(j);
	}
	
	for (auto& n : m_nodes)
	{
		nlohmann::json j;
		n->json_write(j);
		nodes.push_back(j);
	}
	
	into["nodes"] = nodes;
	into["edges"] = edges;
}

void RoadMap::json_read(const nlohmann::json& from)
{
	
}
