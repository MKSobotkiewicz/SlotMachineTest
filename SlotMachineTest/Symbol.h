#pragma once

#include <Utility>
#include <Tuple>
#include <Array>
#include <String>

class Symbol
{
public:
	std::string name = "";
	std::array<int,4> wins = {};
	bool scatter = false;
	std::array<int, 2> probabilities = {};

public:
	Symbol() = default;
	Symbol(const std::string& name, const std::array<int, 4>& wins, const bool& scatter, const std::array<int, 2>& probabilities)
		: name{ name }, wins{ wins }, scatter{ scatter }, probabilities{ probabilities } {}
	Symbol(const Symbol& other)
		: name{ other.name }, wins{ other.wins }, scatter{ other.scatter }, probabilities{ other.probabilities } {}
	Symbol(Symbol&& other) noexcept
		: name{ std::move(other.name) }, wins{ std::move(other.wins) }, scatter{ std::exchange(other.scatter, false) }, probabilities{ std::exchange(other.probabilities, {0,0}) } {}
	
	virtual ~Symbol() = default;

	Symbol& operator=(const Symbol&other)
	 {
		if (this == &other)
			return *this;

		Symbol temp(other);
		std::swap(name, temp.name);
		std::swap(wins, temp.wins);
		std::swap(scatter, temp.scatter);
		std::swap(probabilities, temp.probabilities);

		return *this;
	}

	Symbol& operator=(Symbol&& other) noexcept
	 {
		Symbol temp(std::move(other));
		std::swap(name, temp.name);
		std::swap(wins, temp.wins);
		std::swap(scatter, temp.scatter);
		std::swap(probabilities, temp.probabilities);
	}
	

	bool operator==(const Symbol& other) const
	{
		return name == other.name;
	}

	bool operator!=(const Symbol& other) const
	{
		return name != other.name;
	}

};

