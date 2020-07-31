#pragma once

#include <hello.h>
#include <iostream>

#include <hi.h>

void hello()
{
	std::cout << "lib output: hello func" << std::endl;

	hi();
}

