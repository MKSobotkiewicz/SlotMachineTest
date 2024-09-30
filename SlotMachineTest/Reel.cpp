#include "Reel.h"

void Reel::Draw(std::vector<std::shared_ptr<Symbol>> symbols, const int& randomSet)
{
	std::vector<int> startPos;

	int allProb = CalculatePropabilities(startPos, symbols, randomSet);
	std::uniform_int_distribution < std::mt19937::result_type > distribution(0, allProb);
	
	for (auto i = begin(); i != end(); ++i)
	{
		auto symbolPos = distribution(*generator);
		int symbolId = 0;
		do
		{
			if (symbolPos >= startPos.at(symbolId) && symbolPos < startPos.at(symbolId + 1))
			{
				break;
			}
			++symbolId;
		} while ((symbolId < symbols.size()-1));

		(*i)->CurrentSymbol = symbols.at(symbolId);
		if ((*i)->CurrentSymbol->scatter)
		{
			symbols.erase(symbols.begin() + symbolId);
			int allProb = CalculatePropabilities(startPos, symbols, randomSet);
			distribution= std::uniform_int_distribution < std::mt19937::result_type >(0, allProb);
		}
	}
}

int Reel::CalculatePropabilities(std::vector<int>& startPos, const std::vector<std::shared_ptr<Symbol>>& symbols, const int& randomSet)
{
	startPos = std::vector<int>(symbols.size());
	auto startPosIt = startPos.begin();

	auto bopa= std::accumulate( symbols.begin(),
								symbols.end(),
								0,
								[&startPosIt,&randomSet]
								(int sum, const std::shared_ptr<Symbol>& symbol)
								{
									(*startPosIt) = sum;
									++startPosIt;
									return sum + symbol->probabilities[randomSet];
								});
	return bopa;
}
