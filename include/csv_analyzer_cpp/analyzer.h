#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <optional>
#include <limits>
#include <filesystem>


namespace analyzer {
    class Analyzer {
        private:
            std::string path;
            void getColumns(std::ifstream &file, std::vector<std::string> &columns);
            int getRowCount(std::ifstream &file);
            void columnAnalysis(std::ifstream &file, int colIdx, std::string colName);
            std::optional<double> toNumber(std::string maybeNum);
        public:
            Analyzer(std::string file_path) {
                path = file_path;
            };
            void run();
    };
}