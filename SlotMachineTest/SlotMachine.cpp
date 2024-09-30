#include "SlotMachine.h"

SlotMachine::SlotMachine(const int& cost, const std::string& fileName, const std::shared_ptr<int>& bank) :cost{ cost },
																										  fileName{ fileName },
																										  bank{ bank }, 
																										  generator{std::make_shared<std::mt19937>()}
{
	std::random_device device;
	*generator = std::mt19937(device());
	if (fileName.size() != 0) 
	{
		file.open(fileName);
	}
}

SlotMachine::SlotMachine( const SlotMachine& slotMachine) :cost{ slotMachine.cost }, 
														   fileName{ slotMachine.fileName },
														   bank{ slotMachine.bank },
														   symbols{ slotMachine.symbols }, 
														   reels{ slotMachine.reels},
														   paylines{ slotMachine.paylines },
														   generator{ std::make_shared<std::mt19937>() }
{
	std::random_device device;
	*generator = std::mt19937(device());
	if (fileName.size() != 0)
	{
		file.open(fileName);
	}
}

SlotMachine::~SlotMachine()
{
	if (fileName.size() != 0)
	{
		file.close();
	}
}

int SlotMachine::Draw()
{
	int prize = 0;
	int i = 0;
	for (auto it = reels.begin(); it != reels.end(); ++it,++i) 
	{
		it->Draw(symbols,i%2);

#ifdef _DEBUG
		sums.at((it->at(0)->CurrentSymbol))++;
		sums.at((it->at(1)->CurrentSymbol))++;
		sums.at((it->at(2)->CurrentSymbol))++;
#endif
	}
	for (auto i = paylines.begin(); i != paylines.end(); ++i)
	{
		prize+=i->Prize();
	}
	*bank = (*bank) - 100 + prize;

	if (fileName.size() != 0)
	{
		file << *bank << std::endl;
	}
	return prize;
}

int SlotMachine::Draw(const std::vector<int>& customSymbols)
{
	if (customSymbols.size() != 15) 
	{
		throw std::exception();
	}
	int prize = 0;
	int i = 0;
	for (int i = 0; i < 15; ++i) 
	{
		slots[i % 5][i / 5]->CurrentSymbol = symbols[customSymbols[i]];
	}
	for (auto i = paylines.begin(); i != paylines.end(); ++i)
	{
		prize += i->Prize();
	}
	return prize;
}
