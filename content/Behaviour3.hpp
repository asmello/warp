#ifndef Behaviour3_hpp
#define Behaviour3_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour3 : public warp::Behaviour
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