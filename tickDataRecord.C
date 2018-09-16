#include "tickDataRecord.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

namespace tickRecord {

        unsigned long maxTime (unsigned long receviedTS, unsigned long previousTS, unsigned long maxTS)
        {
                unsigned long diffTS = receviedTS - previousTS;

                if (diffTS > maxTS)
                        return diffTS;

                return maxTS;

        }

        void tickDataRecord:: writeToFile()
        {
                std::ofstream outFile;
                outFile.open("output.csv");

                if (outFile.is_open()) {

                        for ( const auto& [ key, value ] : tickDataMap ) {
                                outFile << key << "," << std::get<0>(value) << "," << std::get<2>(value) << "," << std::get<5>(value) <<
                                        "," << std::get<3>(value) << std::endl;
                        }

                }
        }

        bool tickDataRecord::checkFileConsistency(const unsigned long long & timeStamp,
                        const std::string& symbolName,
                        const int & tradeSize,
                        const int & tradePrice)
        {
                if ((timeStamp > MICROSEC_PER_DAY) || (symbolName.length() != 3) || (tradeSize <= 0) || (tradePrice <= 0))
                                        return false;

                return true;
        }
        void tickDataRecord:: readInputFile()
        {

                std::ifstream inputFile("input.csv");

                if (!inputFile.is_open()) {
                        std::cout << "Cannot open input.txt file" << std::endl;
                        exit(1);
                }

                std::string readLine;

                unsigned long long timeStamp;
                std::string symbolName;
                int tradeSize;
                int tradePrice;

                int result;
                int line = 0;

                while (!getline(inputFile, readLine).eof()) {
                        char  buff[100];
                        result = sscanf(readLine.c_str(), "%llu,%[^,],%d,%d", &timeStamp, buff, &tradeSize, &tradePrice);

                        line++;

                        if (result == EOF || result != 4) {
                                std::cout << "Error in file input.txt on line  " <<  line << ". This record will not be taken into consideration for calculation" << 
                                        std::endl;
dl;
                                continue;
                        }

                        symbolName = buff;
                                                if (!checkFileConsistency(timeStamp, symbolName, tradePrice, tradeSize)) {
                                std::cout << "Error in file input.txt on line  " <<  line << ". This record will not be taken into consideration for calculation" <<
                                        std::endl;
dl;
                                continue;
                        }


                        line++;
                        parseData(timeStamp, symbolName, tradeSize, tradePrice);
                }
        }

        void  tickDataRecord:: parseData (unsigned long long timeStamp, std::string& symbolName, int tradeSize, int tradePrice)
        {

                auto it = tickDataMap.find(symbolName);

                if ( it  == tickDataMap.end())
                {
                        it = tickDataMap.insert(it, std::pair<std::string, std::tuple<unsigned long  long, unsigned  long long, int, int, int, int>>(symbolName, 
                                                                                                                 std::make_tuple(0,0,0,0,0,0)));
                }


                //Calculate Max Time but not for the 1st entry because that might be the only trade
                //Could have used a flag instead but this is ok since the problem guarantees that prices will be greater than 0.
                if (std::get<3>(it->second) != 0)
                        std::get<0>(it->second) = maxTime(timeStamp, std::get<1>(it->second), std::get<0>(it->second));

                if (std::get<3>(it->second) < tradePrice)
                        std::get<3>(it->second) = tradePrice ;

                //Save current timestamp for trade to be used in calculation for the next max gap time.
                std::get<1>(it->second) = timeStamp;

                //Add tradeSize to volume
                std::get<2>(it->second) += tradeSize;

                //Calculate the WAP
                                std::get<5>(it->second) = (std::get<4>(it->second) + (tradePrice * tradeSize))/std::get<2>(it->second);

                //Save the previous state for tradePrice x tradeSize
                std::get<4>(it->second) = std::get<4>(it->second) + (tradePrice * tradeSize);

        }
}

                        
