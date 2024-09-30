#pragma once

#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include "Slot.h"

class Payline: public std::array<std::shared_ptr<Slot>,5>
{
public:
	Payline(std::array<std::shared_ptr<Slot>, 5> a) : std::array<std::shared_ptr<Slot>, 5>(a) {};

	int Prize();
};

