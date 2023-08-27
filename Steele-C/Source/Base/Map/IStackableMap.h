#ifndef STEELE_ISTACKABLEMAP_H
#define STEELE_ISTACKABLEMAP_H


namespace Steele
{
	class IStackableMap
	{
	public:
		virtual void checkpoint() = 0;
		virtual void rollback() = 0;
		virtual void commit() = 0;
		virtual int stack_depth() const = 0;
		virtual bool is_in_checkpoint() const = 0;
	};
}


#endif