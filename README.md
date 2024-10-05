# CsvAnalyzerCpp

## Description

`CsvAnalyzerCpp` is a *super* fast, memory-efficient analyzer of CSV files.

Written in C++, it focuses on "efficiently" gathering simple statistics about CSV files.

It never loads the full CSV into memory. At most, it holds a single line in memory.

The analyzer gathers and outputs simple statistics about your CSV and each column. See more in the Usage example below.

## Usage

There is a pre-built binary of the project in the GitHub releases.

Which you can then use like so:
```
csv_analyzer_cpp.exe your_csv.csv
```

The output looks like:
```
CSV Analyzer
------------
File: csv_small.csv
Rows: 10
Columns: 5
Analysis:
- Column 1 (Name) : 10 unique values, most frequent: Alice (1 times)
- Column 2 (Age) : Min: 22, Max: 50, Average: 33.8
- Column 3 (Occupation) : 5 unique values, most frequent: Engineer (3 times)
- Column 4 (Salary) : Min: 45000, Max: 150000, Average: 83300
- Column 5 (City) : 5 unique values, most frequent: New York (2 times)
```

## Why?

Why not? I'm a believer in "learning by doing". As I was learning various C++ concepts, I wanted to "give it a go" and make a proper project.

Often, developers focus on the core features of the language and miss a lot of the necessary tools and processes around it (how do you properly test an app, how does the build system work, how do you manage dependencies...).

As much as analyzing CSVs may sound boring, I actually found working on this project a lot of fun.

## Development

I'm currently working on a Windows machine so I've mainly provided scripts for building and testing the project on Windows. Sorry!

There's a `Makefile` you'll find at the root of the project which has targets for building and testing the project. That's pretty much all there is to it.

Dependencies are managed with vcpkg and there's a `dev/setup_vcpkg.bat` script that should work for Windows users.

The only dependencies you'll need are `GTest` for testing and `Clang` for formatting.

# Limitations and Future Work

The idea for this project was to have a fast but memory efficient CSV Analyzer.

Here are further improvements for the project:
- don't read entire lines from the file but instead only read single cells (in case there's a CSV with an ungodly amount of columns)
- currently, there's an assumption that every line in the CSV is "valid" (has the correct number of columns). This shouldn't be an assumption.
- better error message when something goes wrong
- different output modes (json, text, etc)
- logging with something like easylogging for debugging
