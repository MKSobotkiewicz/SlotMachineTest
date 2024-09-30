#pragma once

#include <map>
#include <vector>
#include <memory>
#include <fstream>
#include <exception>
#include <random>
#include "Symbol.h"
#include "Slot.h"
#include "Reel.h"
#include "Payline.h"

class SlotMachine
{
public:
	std::array<std::array<std::shared_ptr<Slot>, 3>, 5> slots ={ std::array<std::shared_ptr<Slot>, 3>({std::make_shared <Slot>(),std::make_shared <Slot>(),std::make_shared <Slot>()}),
																 std::array<std::shared_ptr<Slot>, 3>({std::make_shared <Slot>(),std::make_shared <Slot>(),std::make_shared <Slot>()}),
																 std::array<std::shared_ptr<Slot>, 3>({std::make_shared <Slot>(),std::make_shared <Slot>(),std::make_shared <Slot>()}),
																 std::array<std::shared_ptr<Slot>, 3>({std::make_shared <Slot>(),std::make_shared <Slot>(),std::make_shared <Slot>()}) ,
																 std::array<std::shared_ptr<Slot>, 3>({std::make_shared <Slot>(),std::make_shared <Slot>(),std::make_shared <Slot>()}) };

	SlotMachine(const int& cost, const std::string& fileName, const std::shared_ptr<int>& bank);

	SlotMachine(const SlotMachine& slotMachine);

	~SlotMachine();

	int Draw();
	int Draw(const std::vector<int>& customSymbols);

private:

	const int cost;
	const std::string fileName;
	std::ofstream file;
	const std::shared_ptr<int> bank;
	const std::shared_ptr<std::mt19937> generator;

	const std::vector<std::shared_ptr<Symbol>> symbols = { std::make_shared<Symbol>("crown",		std::array<int, 4>{ 0,200,1000,5000 },	true,	std::array<int, 2>{16,16}),
														   std::make_shared<Symbol>("cherry" ,		std::array<int, 4>{25, 100, 250, 1000}, false,	std::array<int, 2>{64,64}),
														   std::make_shared<Symbol>("lemon",		std::array<int, 4>{ 0,100,250,1000 },	false,	std::array<int, 2>{48,64}),
														   std::make_shared<Symbol>("orange",		std::array<int, 4>{ 0,100,250,1000 },	false,	std::array<int, 2>{64,48}),
														   std::make_shared<Symbol>("plum",			std::array<int, 4>{ 0,100,250,1000 },	false,	std::array<int, 2>{48,64}),
														   std::make_shared<Symbol>("grapes",		std::array<int, 4>{ 0,250,1000,2500 },	false,	std::array<int, 2>{24,64}),
														   std::make_shared<Symbol>("watermelon",	std::array<int, 4>{ 0,250,1000,2500 },	false,	std::array<int, 2>{64,24}),
														   std::make_shared<Symbol>("seven",		std::array<int, 4>{ 0,500,5000,25000 }, false,	std::array<int, 2>{8,8}) };
	
	std::array<Reel, 5> reels ={Reel({ SlotMachine::slots[0][0], SlotMachine::slots[0][1], SlotMachine::slots[0][2] },generator),
								Reel({ SlotMachine::slots[1][0], SlotMachine::slots[1][1], SlotMachine::slots[1][2] },generator),
								Reel({ SlotMachine::slots[2][0], SlotMachine::slots[2][1], SlotMachine::slots[2][2] },generator),
								Reel({ SlotMachine::slots[3][0], SlotMachine::slots[3][1], SlotMachine::slots[3][2] },generator),
								Reel({ SlotMachine::slots[4][0], SlotMachine::slots[4][1], SlotMachine::slots[4][2] },generator)};

	std::array<Payline, 20> paylines = {Payline({ slots[0][1],slots[1][1],slots[2][1],slots[3][1],slots[4][1] }),
										Payline({ slots[0][2],slots[1][2],slots[2][2],slots[3][2],slots[4][2] }),
										Payline({ slots[0][0],slots[1][0],slots[2][0],slots[3][0],slots[4][0] }),
										Payline({ slots[0][1],slots[1][1],slots[2][2],slots[3][1],slots[4][1] }),
										Payline({ slots[0][2],slots[1][1],slots[2][0],slots[3][1],slots[4][2] }),
										Payline({ slots[0][0],slots[1][1],slots[2][2],slots[3][1],slots[4][0] }),
										Payline({ slots[0][1],slots[1][2],slots[2][1],slots[3][2],slots[4][1] }),
										Payline({ slots[0][1],slots[1][0],slots[2][1],slots[3][0],slots[4][1] }),
										Payline({ slots[0][2],slots[1][2],slots[2][1],slots[3][0],slots[4][0] }),
										Payline({ slots[0][0],slots[1][0],slots[2][1],slots[3][2],slots[4][2] }),
										Payline({ slots[0][0],slots[1][1],slots[2][2],slots[3][1],slots[4][1] }),
										Payline({ slots[0][0],slots[1][1],slots[2][2],slots[3][2],slots[4][2] }),
										Payline({ slots[0][2],slots[1][1],slots[2][0],slots[3][1],slots[4][1] }),
										Payline({ slots[0][2],slots[1][1],slots[2][0],slots[3][0],slots[4][0] }),
										Payline({ slots[0][2],slots[1][1],slots[2][2],slots[3][1],slots[4][2] }),
										Payline({ slots[0][0],slots[1][1],slots[2][0],slots[3][1],slots[4][0] }),
										Payline({ slots[0][2],slots[1][2],slots[2][1],slots[3][1],slots[4][1] }),
										Payline({ slots[0][0],slots[1][0],slots[2][1],slots[3][1],slots[4][1] }),
										Payline({ slots[0][0],slots[1][0],slots[2][0],slots[3][1],slots[4][2] }),
										Payline({ slots[0][2],slots[1][2],slots[2][2],slots[3][1],slots[4][0] })};

#ifdef _DEBUG
public:

	std::map<std::shared_ptr<Symbol>, int> sums = std::map<std::shared_ptr<Symbol>, int>({ {(symbols[0]),0 },
	{(symbols[1]),0 },
	{(symbols[2]),0 },
	{(symbols[3]),0 },
	{(symbols[4]),0 },
	{(symbols[5]),0 },
	{(symbols[6]),0 },
	{(symbols[7]),0 } });
#endif
};

