#ifndef Behaviour2_hpp
#define Behaviour2_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour2 : public warp::Behaviour
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