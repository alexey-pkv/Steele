#ifndef STEELE_REFERENCEVALUE_H
#define STEELE_REFERENCEVALUE_H


#include "DataTypes/Types.h"


namespace Steele
{
	class ReferenceValue
	{
	public:
		enum class RefType : char
		{
			NONE		= 0,
			V2I			= 1,
			V3I			= 2,
			INT32		= 3,
			FLOAT		= 4
		}
		Type = RefType::NONE;
		
	public:
		union // NOLINT(*-pro-type-member-init)
		{
			v3i		Vector3i;
			v2i		Vector2i;
			int32_t Int32;
			float 	Float;
		}
		Reference = { .Vector3i = v3i_zero };
		
		
	public:
		~ReferenceValue() = default;
		ReferenceValue() = default;
		explicit ReferenceValue(const v3i& ref);
		explicit ReferenceValue(const v2i& ref);
		explicit ReferenceValue(int32_t ref);
		explicit ReferenceValue(float ref);
		
		
	public:
		std::vector<int32_t> to_vector() const;
		
	public:
		inline bool has_reference() const { return Type == RefType::NONE; }
		
		inline void remove_reference() { Type = RefType::NONE; Reference.Vector3i = v3i_zero; }
		
		inline void set_reference(const v3i& ref)	{ Type = RefType::V3I;		Reference.Vector3i = ref; }
		inline void set_reference(const v2i& ref)	{ Type = RefType::V2I;		Reference.Vector2i = ref; }
		inline void set_reference(int32_t ref)		{ Type = RefType::INT32;	Reference.Int32 = ref; }
		inline void set_reference(float ref)		{ Type = RefType::FLOAT;	Reference.Float = ref; }
	};
}


#endif