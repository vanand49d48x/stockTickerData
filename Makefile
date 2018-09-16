data: tickDataRecord.o main.o
        g++ -std=c++1z -Wall -W -pedantic  tickDataRecord.C main.C -o stockTickerData
