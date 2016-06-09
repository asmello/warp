#ifndef Behaviour6_hpp
#define Behaviour6_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour6 : public warp::Behaviour
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