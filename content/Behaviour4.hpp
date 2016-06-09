#ifndef Behaviour4_hpp
#define Behaviour4_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour4 : public warp::Behaviour
{

public:

	virtual void Start()
	{
		std::cout << "Start() call \n";
	}

	virtual void Update()
	{
		std::cout << "Update() call \n";
	}
};
#endif