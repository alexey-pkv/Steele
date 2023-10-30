extends GenericTab
class_name AtlasViewTab


var c_ground_atlas_view: GroundAtlasView:
	get: return $DrawingBoard/GroundAtlasView


func load_resource() -> void:
	c_ground_atlas_view.atlas_id = resource_id

