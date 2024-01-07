#ifndef STEELE_STEELEENGINE_H
#define STEELE_STEELEENGINE_H


namespace Steele
{
	class SteeleEngine
	{
	public:
		enum class State
		{
			Idle,
			Running,
			Stopping,
			Stopped
		};
		
		
	private:
		State	m_state = State::Idle;
		
		
	public:
		State get_state() const { return m_state; }
	
	
	public:
		bool run_once();
		void run();
		
		
	public:
		void stop();
	};
}


#endif