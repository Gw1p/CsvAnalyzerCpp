#include "csv_analyzer_cpp/analyzer.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

// defined in CMakeLists
const auto TEST_DIR_PATH = std::string(TEST_DATA_PATH);
const auto TEST_SMALL_CSV_PATH = std::string("/csv_small.csv");
const auto TEST_LARGE_CSV_PATH = std::string("/csv_large.csv");

class AnalyzerTest : public ::testing::Test {
  protected:
    std::ostringstream outputBuffer;
    std::ostringstream errorBuffer;
    std::streambuf *originalCout;
    std::streambuf *originalCerr;

    void SetUp() override {
        originalCout = std::cout.rdbuf();
        std::cout.rdbuf(outputBuffer.rdbuf());

        originalCerr = std::cerr.rdbuf();
        std::cerr.rdbuf(errorBuffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(originalCout);
        std::cerr.rdbuf(originalCerr);
    }
};

TEST_F(AnalyzerTest, ErrorsNonExistentFile) {
    std::string filePath = TEST_DIR_PATH + "/random_non_existent_file.csv";
    analyzer::Analyzer analyzerInstance(filePath);
    analyzerInstance.run();

    std::string expectedOutput =
        "Could not open the file: random_non_existent_file.csv\n";
    EXPECT_EQ(errorBuffer.str(), expectedOutput);
}

TEST_F(AnalyzerTest, AnalyzesSmallCsvCorrectly) {
    analyzer::Analyzer analyzerInstance(TEST_DIR_PATH + TEST_SMALL_CSV_PATH);
    analyzerInstance.run();

    std::string expectedOutput = "CSV Analyzer";
    expectedOutput += "\n------------";
    expectedOutput += "\nFile: csv_small.csv";
    expectedOutput += "\nRows: 10";
    expectedOutput += "\nColumns: 5";
    expectedOutput += "\nAnalysis:";
    expectedOutput += "\n- Column 1 (Name) : 10 unique values, most frequent: "
                      "Alice (1 times)";
    expectedOutput += "\n- Column 2 (Age) : Min: 22, Max: 50, Average: 33.8";
    expectedOutput += "\n- Column 3 (Occupation) : 5 unique values, most "
                      "frequent: Engineer (3 times)";
    expectedOutput +=
        "\n- Column 4 (Salary) : Min: 45000, Max: 150000, Average: 83300";
    expectedOutput += "\n- Column 5 (City) : 5 unique values, most frequent: "
                      "New York (2 times)\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);
}

TEST_F(AnalyzerTest, AnalyzesLargeCsvCorrectly) {
    analyzer::Analyzer analyzerInstance(TEST_DIR_PATH + TEST_LARGE_CSV_PATH);
    analyzerInstance.run();

    std::string expectedOutput = "CSV Analyzer";
    expectedOutput += "\n------------";
    expectedOutput += "\nFile: csv_large.csv";
    expectedOutput += "\nRows: 1488";
    expectedOutput += "\nColumns: 5";
    expectedOutput += "\nAnalysis:";
    expectedOutput += "\n- Column 1 (First Name) : 48 unique values, most "
                      "frequent: Alice (31 times)";
    expectedOutput += "\n- Column 2 (Age) : Min: 22, Max: 55, Average: 36.25";
    expectedOutput += "\n- Column 3 (Job) : 11 unique values, most frequent: "
                      "Engineer (217 times)";
    expectedOutput += "\n- Column 4 (Remuneration) : Min: 45000, Max: 150000, "
                      "Average: 83458.3";
    expectedOutput += "\n- Column 5 (Location) : 15 unique values, most "
                      "frequent: New York (186 times)\n";
    EXPECT_EQ(outputBuffer.str(), expectedOutput);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
