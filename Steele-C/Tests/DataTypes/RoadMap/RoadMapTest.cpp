#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "test_utils.h"


#include "DataTypes/RoadMap/RoadMap.h"


using namespace Steele;


RoadNode* assert_connected(RoadEdge* e1, RoadEdge* e2)
{
	RoadNode* node = nullptr;
	
	for (auto* n1 : e1->Nodes)
	{
		if (n1->has(e2))
		{
			ASSERT_NULL(node);
			node = n1;
		}
	}
	
	for (auto* n2 : e2->Nodes)
	{
		if (n2->has(e1))
		{
			ASSERT_IS(node, n2);
		}
	}
	
	// Node must be found at this point
	ASSERT_NOT_NULL(node);
	
	ASSERT_TRUE(node->has(e1));
	ASSERT_TRUE(node->has(e2));
	
	if (e1->Type == Steele::RoadType::Subway && e2->Type == Steele::RoadType::Subway)
	{
		ASSERT_IS(RoadType::Subway, node->Type);
		ASSERT_IS(v2i_zero, node->Segment);
	}
	else
	{
		ASSERT_IS(RoadType::Road, node->Type);
	}
	
	return node;
}


TEST(RoadMap__EmptyMap__NoErrors)
{
	RoadMap rm;
	
	rm.index();
	
	ASSERT_TRUE(rm.is_empty());
	ASSERT_FALSE(rm.has_subways());
	ASSERT_IS(0, rm.edges_count());
	ASSERT_IS(0, rm.intersections_count());
	ASSERT_IS(0, rm.subways_count());
	ASSERT_IS(0, rm.nodes_count());
}


TEST(RoadMap__SingleRoad)
{
	RoadMap rm;
	
	rm.create_road(1, { 1, 1 });
	rm.index();
	
	ASSERT_FALSE(rm.is_empty());
	ASSERT_FALSE(rm.has_subways());
	ASSERT_IS(1, rm.edges_count());
	ASSERT_IS(1, rm.intersections_count());
	ASSERT_IS(0, rm.subways_count());
	ASSERT_IS(0, rm.nodes_count());
}

TEST(RoadMap__SingleSubway)
{
	RoadMap rm;
	
	rm.create_subway(1, { 1, 1 });
	rm.index();
	
	ASSERT_FALSE(rm.is_empty());
	ASSERT_TRUE(rm.has_subways());
	ASSERT_IS(1, rm.edges_count());
	ASSERT_IS(0, rm.intersections_count());
	ASSERT_IS(1, rm.subways_count());
	ASSERT_IS(0, rm.nodes_count());
}

TEST(RoadMap__Multiple_Items_Exists__Counts_Are_Correct)
{
	RoadMap rm;
	
	rm.create_subway(1, { 1, 1 });
	rm.create_subway(2, { 2, 2 });
	rm.create_road(3, { 1, 4 });
	rm.create_road(4, { 2, 5 });
	rm.create_road(5, { 1, 6 });
	rm.create_road(6, { 2, 7 });
	
	rm.index();
	
	ASSERT_FALSE(rm.is_empty());
	ASSERT_TRUE(rm.has_subways());
	ASSERT_IS(6, rm.edges_count());
	ASSERT_IS(4, rm.intersections_count());
	ASSERT_IS(2, rm.subways_count());
	ASSERT_IS(1, rm.nodes_count());
}

TEST(RoadMap__More_Than_One_Subway__Subways_Connected_Ater_Index)
{
	RoadMap rm;
	
	auto e1 = rm.create_subway(1, { 1, 1 });
	auto e2 = rm.create_subway(2, { 2, 2 });
	
	rm.index();
	
	ASSERT_IS(1, rm.nodes_count());
	
	assert_connected(e1, e2);
}

TEST(RoadMap__Nearest_Subway_Set_Correctly)
{
	RoadMap rm;
	
	auto e1 = rm.create_subway(1, { 1, 1 });
	auto e2 = rm.create_subway(2, { 2, 2 });
	
	auto r1 = rm.create_road(2, {0, 0});
	auto r2 = rm.create_road(2, {2, 2});
	
	rm.connect_road(r1, e1, 13, { 1, 2 });
	rm.connect_road(r2, e2, 14, { 8, 10 });
	rm.connect_road(r1, r2, 12, { 2, 8 });
	
	
	rm.index();
	
	
	ASSERT_IS(4, rm.nodes_count());
	
	ASSERT_IS(1, r1->DistanceToSubway);
	ASSERT_IS(2, r2->DistanceToSubway);
	ASSERT_NOT_NULL(r1->ToSubway);
	ASSERT_NOT_NULL(r2->ToSubway);
	
	ASSERT_IS(e1, r1->ToSubway->get_other(r1));
	ASSERT_IS(e2, r2->ToSubway->get_other(r2));
}

TEST(RoadMap__Sanity_Test)
{
	RoadMap rm;
	const int SIZE	= 200;
	std::map<v2i, RoadEdge*> map;
	
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			map[{x, y}] = rm.create_road(x * SIZE + y, {x, y});
		}
	}
	
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			v2i curr = { x, y };
			auto* e = map[curr];
			
			for (int n = 0; n <= 1; n++)
			{
				for (int m = 0; m <= 1; m++)
				{
					v2i off = v2i { n, m };
					v2i p = curr + v2i { n, m };
					
					if (off == v2i_zero || off == v2i_one || p.x >= SIZE || p.y >= SIZE)
						continue;
					
					auto* with = map[p];
					
					rm.connect_road(e, with, p.x * SIZE + p.y + SIZE * SIZE, { 2, 4 });
				}
			}
		}
	}
	
	ASSERT_IS(SIZE * SIZE, rm.edges_count());
	ASSERT_IS((SIZE - 1) * SIZE * 2, rm.nodes_count());
}


#pragma clang diagnostic pop
