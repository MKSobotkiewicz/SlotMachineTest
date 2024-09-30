#include "SlotMachineTest.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include "Slot.h"
#include "Symbol.h"
#include "Payline.h"
#include "SlotMachine.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> input;
    int gamesCount = 100000;
    int totalWins = 0;
    int startingBank = 5000000;
    std::string fileName = "result.txt";
    for (int i = 0; i < argc; i++)
    {
        input.push_back(argv[i]);
#ifdef _DEBUG
        std::cout << input[i] << std::endl;
#endif
    }
    for (size_t i = 1; i < input.size() - 1; i += 2)
    {
        if (input[i] == "-gamesCount")
        {
            gamesCount = std::stoi(input[i + 1]);
            std::cout << "custom games count: " << gamesCount << std::endl;
        }
        else if (input[i] == "-startCredit")
        {
            startingBank = std::stoi(input[i + 1]);
        }
        else if (input[i] == "-creditOutFile")
        {
            fileName = input[i + 1];
        }
        else if (input[i] == "-symbols")
        {
            if (input[i + 1].length() < 29)
            {
                return 0;
            }
            auto customSymbols = std::vector<int>();

            for (int j = 0; j < 15; j++)
            {
                customSymbols.push_back((input[i + 1][j * 2] - '0'));
            }
            int startingBank = 0;
            auto bank = std::make_shared<int>(startingBank);
            auto slotmachine = SlotMachine(100, "", bank);
            auto prize = slotmachine.Draw(customSymbols);
            std::cout << prize << std::endl;
            return 0;
        }
    }
#ifdef _DEBUG
    time_t start = time(0);
#endif
    auto bank = std::make_shared<int>(startingBank);
    auto slotmachine = SlotMachine(100, fileName, bank);
    int i = 0;
    int winNumber = 0;
    std::array<std::tuple<int, int, int>, 6> prizeSizes = { std::tuple<int, int, int>{100,0,0},
                                                            std::tuple<int, int, int>{250,0,0},
                                                            std::tuple<int, int, int>{500,0,0},
                                                            std::tuple<int, int, int>{1000,0,0},
                                                            std::tuple<int, int, int>{5000,0,0},
                                                            std::tuple<int, int, int>{std::numeric_limits<int>::max(),0,0} };
    for (; i < gamesCount; ++i)
    {
        if (*bank < 100)
        {
            break;
        }
        auto prize = slotmachine.Draw();
        if (prize > 0)
        {
            ++winNumber;
            totalWins += prize;
            for (auto it = prizeSizes.begin(); it < prizeSizes.end(); ++it)
            {
                if (prize < std::get<0>(*it))
                {
                    *it = std::tuple<int, int, int>{ std::get<0>(*it),std::get<1>(*it) + 1,std::get<2>(*it) + prize };
                    break;
                }
            }
        }
    }
    std::cout << std::endl << "Number of games: " << i << std::endl;
    std::cout << "Number of wins: " << winNumber << std::endl;
    std::cout << "HF: " << (winNumber * 100) / i << "%" << std::endl;
    std::cout << "RTP: " << ((*bank) * 100) / startingBank << "%" << std::endl << std::endl;
    std::cout << "range\tcount\tcount%\tvalue\tvalue%" << std::endl;
    for (auto it = prizeSizes.begin(); it < prizeSizes.end(); ++it)
    {
        if (std::get<0>(*it) > 5000)
        {
            std::cout << ">" << std::get<0>(*(--it)) << "\t"
                << std::get<1>(*it) << "\t"
                << (std::get<1>(*it) * 100) / i << "%\t"
                << std::get<2>(*it) << "\t"
                << (std::get<2>(*it) * 100) / totalWins << "%" << std::endl;
            break;
        }
        std::cout << "<" << std::get<0>(*it) << "\t"
            << std::get<1>(*it) << "\t"
            << (std::get<1>(*it) * 100) / i << "%\t"
            << std::get<2>(*it) << "\t"
            << (std::get<2>(*it) * 100) / totalWins << "%" << std::endl;
    }
#ifdef _DEBUG
    std::cout << std::endl;
    for (auto it = slotmachine.sums.begin(); it != slotmachine.sums.end(); ++it)
    {
        std::cout << it->first->name << ": " << it->second << std::endl;
    }
    double seconds_since_start = difftime(time(0), start);
    std::cout << "time passed: " << seconds_since_start << std::endl;
#endif
}