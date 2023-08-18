#ifndef STEELE_ALIGNMENT_H
#define STEELE_ALIGNMENT_H


namespace Steele
{
	struct Alignment 
	{
	public:
		bool IsSuccessful;
		
		
	public:
		~Alignment() = default;
		Alignment(const Alignment&) = default;
		Alignment(Alignment&&) = default;
	};
}


#endif