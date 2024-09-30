#include "Payline.h"

int Payline::Prize()
{
	int prize = 0;
	for (int i = 1; i < this->size(); ++i)
	{
		if ((this->at(i))->CurrentSymbol->scatter || ((this->at(i))->CurrentSymbol != (this->at(i - 1))->CurrentSymbol))
		{
			break;
		}
		prize = this->at(i-1)->CurrentSymbol->wins[i - 1];
	}
	auto scatterSymbolSlotIt = std::find_if(this->begin(),
											this->end(),
											[]
											(const std::shared_ptr<Slot>& slot)
											{
												return slot->CurrentSymbol->scatter;
											});
	if (scatterSymbolSlotIt != end())
	{
		auto scatterNumber = std::count_if( this->begin(),
											this->end(),
											[scatterSymbolSlotIt]
											(const std::shared_ptr<Slot>& slot)
											{
												return *(slot->CurrentSymbol) == *((*scatterSymbolSlotIt)->CurrentSymbol);
											});
		if (scatterNumber > 1)
		{
			prize += (*scatterSymbolSlotIt)->CurrentSymbol->wins[scatterNumber-2];
		}
	}
	return prize;
}