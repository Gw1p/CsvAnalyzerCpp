#include "csv_analyzer_cpp/analyzer.h"
#include <iostream>

/*
Output format:

CSV Analyzer
------------
File: data.csv
Rows: 100
Columns: 5
Analysis:
- Column 1 (Age): Min: 18, Max: 60, Average: 35.6
- Column 2 (Name): 20 unique values, most frequent: John (10 times)
*/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    analyzer::Analyzer analyzer(path);
    analyzer.run();
    return 0;
}
