#ifndef Area_h
#define Area_h

enum status
{
	thinking,
	hungry,
	eating
};

class Area
{
	status state[5] = {thinking, thinking, thinking, thinking, thinking};

public:
	Area(){};
	status getStatus(int philosopher) { return state[philosopher]; }
	void setStatus(int philosopher, status newState) { state[philosopher] = newState; }
};

#endif