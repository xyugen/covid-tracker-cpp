# COVID-19 Tracker

This is a command-line application that retrieves and displays COVID-19 data using the [disease.sh](https://disease.sh/) API. The program is written in C++ and uses several third-party libraries, including [libcurl](https://curl.se/libcurl/) and [nlohmann's json](https://github.com/nlohmann/json), to fetch and parse JSON data.

## Features

The application allows users to retrieve COVID-19 data at a global, continent, or country level. Data displayed includes:

- Total cases
- Total deaths
- Total recovered
- Active cases
- Critical cases
- Cases, deaths, and recoveries in the past 24 hours

## Usage

To use the application, simply compile and run the program in a C++ environment. Once running, the user will be prompted to select the level of data they wish to retrieve.

## Third-party Libraries

- [libcurl](https://curl.se/libcurl/)
- [nlohmann's json](https://github.com/nlohmann/json)
- [colormod](https://github.com/JoelSjogren/libquick/blob/master/colormod.h)

## Installation
### Prerequisites

Before you can use this C++ code, you will need to make sure that the following software is installed on your computer:

- C++ compiler: This code was written in C++11, so make sure that your compiler supports this version of C++. We recommend using GCC, which can be installed on Linux or macOS using the following command:
`sudo apt install g++` or `sudo pacman -S g++`
- CMake: This is a tool that helps automate the build process for C++ code. You can download the latest version of CMake from the official website: [https://cmake.org/download/](https://cmake.org/download/)

### Building the code

Once you have installed the prerequisites, you can build the C++ code using the following steps:
1. Close the repository
```bash
git clone https://github.com/xyugen/covid-tracker-cpp.git
```
2. Changed into the closed repository:
```bash
cd covid-tracker-cpp
```
3. Compile the code:
```bash
make
```

### Running the code

To run the compiled code, you can use the following command:
```bash
./CovidTracker
```

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/xyugen/covid-tracker-cpp/blob/master/LICENSE) file for more details.
