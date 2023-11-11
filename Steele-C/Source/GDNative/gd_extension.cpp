#include "gd_extension.h"


#include "Test/GodotTestPlugin.h"
#include "GDNative/RNG/XoroshiroRNG.h"
#include "GDNative/RNG/RandomState.h"
#include "GDNative/DataTypes/Dir.h"
#include "GDNative/DataTypes/Map/Ground.h"
#include "GDNative/DataTypes/Map/GroundTile.h"
#include "GDNative/DataTypes/Area.h"
#include "GDNative/DataTypes/IDMap.h"
#include "GDNative/DataTypes/Map/Cell.h"
#include "GDNative/DataTypes/Map/MapPatch.h"


using namespace godot;


void initialize_steele_module(ModuleInitializationLevel p_level) 
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) 
	{
		return;
	}
	
	// Test Stuff
	ClassDB::register_class<GodotTestPlugin>();
	
	
	// Data Types
	ClassDB::register_class<Dir>();
	ClassDB::register_class<Area>();
	ClassDB::register_abstract_class<IDMap>();

	// Data Types :: Map
	ClassDB::register_class<GroundTile>();
	ClassDB::register_class<Ground>();
	ClassDB::register_class<Cell>();
	ClassDB::register_class<MapPatch>();
	
	
	// RNG
	ClassDB::register_class<XoroshiroRNG>();
	ClassDB::register_class<RandomState>();
}

void uninitialize_steele_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}


extern "C"
{
	GDExtensionBool GDE_EXPORT steele_library_init(
			GDExtensionInterfaceGetProcAddress p_get_proc_address, 
			const GDExtensionClassLibraryPtr p_library, 
			GDExtensionInitialization *r_initialization) 
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	
		init_obj.register_initializer(initialize_steele_module);
		init_obj.register_terminator(uninitialize_steele_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
	
		return init_obj.init();
	}
}