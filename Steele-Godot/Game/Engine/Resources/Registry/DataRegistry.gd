class_name DataRegistry


static var m_textures_registry: TextureDataRegistry = TextureDataRegistry.new()


static func textures_registry() -> TextureDataRegistry:
	return m_textures_registry


static func get_ground_atlas_id(id: ResourceID) -> AtlasData:
	return textures_registry().get_ground_atlas_id(id)
