#ifndef Behaviour5_hpp
#define Behaviour5_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour5 : public warp::Behaviour
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