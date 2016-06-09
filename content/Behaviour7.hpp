#ifndef Behaviour7_hpp
#define Behaviour7_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour7 : public warp::Behaviour
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