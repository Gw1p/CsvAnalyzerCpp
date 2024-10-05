#include "csv_analyzer_cpp/analyzer.h"

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
// C:\\Users\\anton\\Trading\\rustlearn\\csv_analyzer_cpp\\tests\\test_data\\csv1.csv
namespace analyzer {
void Analyzer::run() {
    std::filesystem::path filePath(path);
    std::string fileName = filePath.filename().string();
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << fileName << std::endl;
        return;
    }

    std::cout << "CSV Analyzer" << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << "File: " << fileName << std::endl;

    std::vector<std::string> columns;
    Analyzer::getColumns(file, columns);
    int rowCount = Analyzer::getRowCount(file);

    std::cout << "Rows: " << rowCount << std::endl;
    std::cout << "Columns: " << columns.size() << std::endl;
    std::cout << "Analysis:" << std::endl;

    int colIdx = 0;
    for (std::string colName : columns) {
        Analyzer::columnAnalysis(file, colIdx, colName);
        colIdx += 1;
    }

    file.close();
}

void Analyzer::getColumns(std::ifstream &file,
                          std::vector<std::string> &columns) {
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Could not read first line" << std::endl;
    }

    std::stringstream ss(line);
    std::string cell;

    while (std::getline(ss, cell, ',')) {
        columns.push_back(cell);
    }
}

int Analyzer::getRowCount(std::ifstream &file) {
    int rowCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        rowCount += 1;
    }
    return rowCount;
}

void Analyzer::columnAnalysis(std::ifstream &file, int colIdx,
                              std::string colName) {
    // re-set file
    file.clear();
    file.seekg(0);

    std::string line;
    bool headerRow = true;
    bool firstRow = true;
    bool isNumeric = false;

    // Store information for text columns
    std::string mostFrequentValue{""};
    int mostFrequentCounter = 0;
    std::unordered_map<std::string, int> occurences;

    // Store information for numeric columns
    double colMin = std::numeric_limits<double>::max();
    double colMax = std::numeric_limits<double>::min();
    // Used to compute average
    double sum = 0;
    int count = 0;

    while (std::getline(file, line)) {
        // skip header
        if (headerRow) {
            headerRow = false;
            continue;
        }

        int cellIdx = 0;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            if (cellIdx != colIdx) {
                cellIdx += 1;
                continue;
            }

            if (firstRow) {
                auto num = Analyzer::toNumber(cell);
                if (num.has_value()) {
                    // it's a numeric column
                    isNumeric = true;
                }
                firstRow = false;
            }

            if (isNumeric) {
                auto num = Analyzer::toNumber(cell);
                if (num.has_value()) {
                    double numValue = num.value();
                    if (numValue < colMin) {
                        colMin = numValue;
                    }
                    if (numValue > colMax) {
                        colMax = numValue;
                    }
                    sum += numValue;
                    count += 1;
                }
            } else {
                // text column
                if (!occurences.count(cell)) {
                    occurences[cell] = 0;
                }
                occurences[cell] += 1;
                if (occurences[cell] > mostFrequentCounter) {
                    mostFrequentCounter = occurences[cell];
                    mostFrequentValue = cell;
                }
            }
            break;
        }
    }

    // Output
    // - Column 1 (Age):
    // the rest will be filled below
    std::cout << "- Column " << std::to_string(colIdx + 1) << " (" << colName
              << ") : ";

    if (isNumeric) {
        // Output format:
        // - Column 1 (Age): Min: 18, Max: 60, Average: 35.6
        std::cout << "Min: " << colMin << ", Max: " << colMax
                  << ", Average: " << sum / count << std::endl;
    } else {
        // Output format:
        // - Column 2 (Name): 20 unique values, most frequent: John (10 times)
        std::cout << occurences.size()
                  << " unique values, most frequent: " << mostFrequentValue
                  << " (" << mostFrequentCounter << " times)" << std::endl;
    }
}

std::optional<double> Analyzer::toNumber(std::string maybeNum) {
    try {
        std::size_t pos;
        double num = std::stod(maybeNum, &pos);
        if (pos == maybeNum.size()) {
            return num;
        }
    } catch (std::invalid_argument &) {
    } catch (std::out_of_range &) {
    }
    return std::nullopt;
}
} // namespace analyzer
