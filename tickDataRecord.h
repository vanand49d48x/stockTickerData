#pragma once

#include <tuple>
#include <map>

namespace tickRecord {

#define MICROSEC_PER_DAY  86400000000

        class tickDataRecord {
                private :
                        //Tuple for max time gap, previous trade time, total Vol traded, max Trade Price, WAP
                        //  std::tuple<unsigned long, unsigned long, int, int, int> tickData;
                        std::map<std::string, std::tuple<unsigned long long, unsigned long long, int, int, int, int>> tickDataMap;
                public:
                        tickDataRecord(){}

                        ~tickDataRecord() { tickDataMap.clear(); }
                        /** FunctionName:readInputFile()
                         *  This function reads the input.csv file from current directory, checks the consistency for the line and passes the data to parseData function.
                         *  Input  : None
                         *  Output : None
                         */

                        void readInputFile();

                        /** FunctionName:parseData()
                         *  This function parses the individual line read from input.csv into there respective variable and formats..
                         *  Input  : timeStamp - timeStamp read from file (1st column)
                         *           symbolName - name for the symbol from file (2nd column - max 3 chars)
                         *           tradeSize  - size of the trade from file (3rd column)
                         *           tradePrice - price for the trade from file (4th column)
                         *  Output : None
                         */
                        void parseData (unsigned long long timeStamp, std::string& symbolName, int tradeSize, int tradePrice);

                        /** FunctionName:writeToFile()
                         *  This function writes output.csv file in current directory, that contains the info related to a symbol in sorted format.
                         *  Input  : None
                         *  Output : None
                         */
                         void writeToFile();
                         
                        /** FunctionName: checkFileConsistency()
                         *  This function checks for consistency for individual fields read from file
                         *  Input  : timeStamp - timeStamp read from file (1st column)
                         *           symbolName - name for the symbol from file (2nd column - max 3 chars)
                         *           tradeSize  - size of the trade from file (3rd column)
                         *           tradePrice - price for the trade from file (4th column)
                         *  Output : returns false if any field is inconsistent else return true.
                         */
                        bool checkFileConsistency(const unsigned long long&  timestamp,
                                        const std::string& symbolName,
                                        const int& tradeSize,
                                        const int & tradePrice);
        };

}
