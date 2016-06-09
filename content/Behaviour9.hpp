#ifndef Behaviour9_hpp
#define Behaviour9_hpp

#include "Behaviour.hpp"
#include <iostream>


class Behaviour9 : public warp::Behaviour
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