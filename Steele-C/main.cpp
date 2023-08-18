#include <iostream>
#include "godot_cpp/variant/rect2i.hpp"
#include "DataTypes/Area.h"
#include "DataTypes/Area/Alignment.h"
#include "Utils.h"
#include "DataTypes/Area/outline_scalar_iterator.h"
#include "DataTypes/Area/AlignSettings.h"

#include <chrono>
#include <set>


using namespace godot;
using namespace std;
using namespace Steele;



void print(const Area& data)
{
	set<v2i> set;
	
	for (auto n : data)
	{
		set.insert(n);
	}
	
	cout << "---------" << endl;
	
	for (int y = data.Top(); y >= 0; y--)
	{
		for (int x = 0; x <= data.Right(); x++)
		{
			if (set.find(v2i(x, y)) != set.end())
			{
				cout << '*';
			}
			else
			{
				cout << " ";
			}
		}
		
		cout << endl;
	}
	
	cout << "---------" << endl;
}


int main()
{
	cout << sizeof(Steele::Align::AlignSettings) << endl;
	return 0;
}

