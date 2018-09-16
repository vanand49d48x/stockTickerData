
#include "tickDataRecord.h"
using namespace tickRecord;

int main() {

        tickDataRecord rec;
        rec.readInputFile();
        rec.writeToFile();

        return 0;

}
