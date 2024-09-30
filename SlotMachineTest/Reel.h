#pragma once

#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <random>
#include "Slot.h"

class Reel : public std::array<std::shared_ptr<Slot>, 3>
{
public:
	Reel(const std::array<std::shared_ptr<Slot>, 3>& a, const std::shared_ptr<std::mt19937>& generator) : std::array<std::shared_ptr<Slot>, 3>{a}, generator{ generator }{};

	void Draw(std::vector<std::shared_ptr<Symbol>> symbols,const int& randomSet);

private:
	int CalculatePropabilities(std::vector<int>& startPos, const std::vector<std::shared_ptr<Symbol>>& symbols, const int& randomSet);

	const std::shared_ptr<std::mt19937> generator;
};

