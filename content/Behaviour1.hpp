#ifndef Behaviour1_hpp
#define Behaviour1_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour1 : public warp::Behaviour
{

public:

	virtual void Start()
	{
//		std::cout << "Start() call \n";
	}

	virtual void Update()
	{
//		std::cout << "Update() call \n";
	}
};
#endif