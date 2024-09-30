#pragma once

#include <memory>
#include <utility>
#include "Symbol.h"

class Slot
{
public:
	Slot() {}
	Slot(const Slot& slot):Slot(slot.CurrentSymbol){}
	Slot(Slot&& slot)noexcept : CurrentSymbol(std::exchange(slot.CurrentSymbol, nullptr)) {}
	Slot(const std::shared_ptr<Symbol>& currentSymbol) :CurrentSymbol{ currentSymbol } {}
	Slot(std::shared_ptr<Symbol>&&currentSymbol)
	{
		CurrentSymbol=std::move(currentSymbol);
	}

	virtual ~Slot() {}

	Slot& operator=(const Slot& slot)
	{
		if (this == &slot)
			return *this;

		Slot temp(slot);
		std::swap(CurrentSymbol, temp.CurrentSymbol);

		return *this;
	}

	Slot& operator=(Slot&& slot) noexcept
	{
		Slot temp(std::move(slot));
		std::swap(CurrentSymbol, temp.CurrentSymbol);
	}

	std::shared_ptr<Symbol> CurrentSymbol;
};

