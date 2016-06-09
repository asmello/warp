#ifndef Behaviour8_hpp
#define Behaviour8_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour8 : public warp::Behaviour
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