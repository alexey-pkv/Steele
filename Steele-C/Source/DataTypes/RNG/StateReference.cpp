#include "StateReference.h"


Steele::StateReference::StateReference(const v3i& ref)	{ set_reference(ref); }
Steele::StateReference::StateReference(const v2i& ref)	{ set_reference(ref); }
Steele::StateReference::StateReference(int32_t ref)		{ set_reference(ref); }
Steele::StateReference::StateReference(float ref)		{ set_reference(ref); }

std::vector<int32_t> Steele::StateReference::to_vector() const
{
	switch (Type)
	{
		case RefType::V2I:
			return { Reference.Vector2i.x, Reference.Vector2i.y };
		case RefType::V3I:
			return { Reference.Vector3i.x, Reference.Vector3i.y, Reference.Vector3i.y };
		case RefType::INT32:
		case RefType::FLOAT:
			return { Reference.Int32 };
		case RefType::NONE:
		default:
			return {};
	}
}
