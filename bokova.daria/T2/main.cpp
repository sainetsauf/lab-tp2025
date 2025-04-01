#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cmath>

struct DataStruct {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

bool parseHexValue(const std::string& str, unsigned long long& value) {
    if (str.empty() || (str.substr(0, 2) != "0x" && str.substr(0, 2) != "0X")) {
        return false;
    }

    try {
        size_t pos = 0;
        value = std::stoull(str.substr(2), &pos, 16);
        return pos == str.substr(2).size();
    } catch (...) {
        return false;
    }
}

bool parseComplexNumber(const std::string& str, std::complex<double>& value) {
    if (str.size() < 5 || str.substr(0, 3) != "#c(" || str.back() != ')') {
        return false;
    }

    std::string content = str.substr(3, str.size() - 4);
    std::istringstream iss(content);
    double real, imag;
    
    if (iss >> real >> imag) {
        value = std::complex<double>(real, imag);
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }

    if (line.empty() || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    line = line.substr(1, line.size() - 2);
    size_t pos = 0;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    while (pos < line.size()) {
        while (pos < line.size() && std::isspace(line[pos])) {
            pos++;
        }
        if (pos >= line.size()) {
            break;
        }

        if (line[pos] != ':') {
            in.setstate(std::ios::failbit);
            return in;
        }
        pos++;

        size_t fieldEnd = line.find(' ', pos);
        if (fieldEnd == std::string::npos) {
            in.setstate(std::ios::failbit);
            return in;
        }

        std::string fieldName = line.substr(pos, fieldEnd - pos);
        pos = fieldEnd + 1;

        size_t valueEnd = line.find(':', pos);
        if (valueEnd == std::string::npos) {
            valueEnd = line.size();
        }

        std::string fieldValue = line.substr(pos, valueEnd - pos);
        pos = valueEnd;

        if (fieldName == "key1") {
            if (!parseHexValue(fieldValue, data.key1)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        } else if (fieldName == "key2") {
            if (!parseComplexNumber(fieldValue, data.key2)) {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        } else if (fieldName == "key3") {
            if (fieldValue.size() < 2 || fieldValue.front() != '"' || fieldValue.back() != '"') {
                in.setstate(std::ios::failbit);
                return in;
            }
            data.key3 = fieldValue.substr(1, fieldValue.size() - 2);
            hasKey3 = true;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 0x" << std::hex << std::uppercase << data.key1
        << ":key2 #c(" << data.key2.real() << " " << data.key2.imag()
        << "):key3 \"" << data.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
        return a.key1 < b.key1;
    }
    
    const double aModulus = std::abs(a.key2);
    const double bModulus = std::abs(b.key2);
    if (aModulus != bModulus) {
        return aModulus < bModulus;
    }
    
    return a.key3.length() < b.key3.length();
}

void runTests() {
    std::cout << "Running tests...\n";

    {
        std::istringstream testInput("(:key1 0xFF:key2 #c(1.0 -1.0):key3 \"test\":)");
        DataStruct data;
        testInput >> data;
        
        if (data.key1 == 0xFF && data.key2 == std::complex<double>(1.0, -1.0) && data.key3 == "test") {
            std::cout << "Test 1 passed\n";
        } else {
            std::cout << "Test 1 failed\n";
        }
    }

    {
        std::vector<DataStruct> testData = {
            {0x10, std::complex<double>(2.0, -3.0), "hello"},
            {0xFF, std::complex<double>(1.0, 1.0), "world"},
            {0x10, std::complex<double>(1.0, 1.0), "test"},
            {0x5, std::complex<double>(0.0, 0.0), "abc"}
        };
        
        std::sort(testData.begin(), testData.end(), compareDataStructs);
        
        bool sortedCorrectly = 
            testData[0].key1 == 0x5 &&
            testData[1].key1 == 0x10 &&
            testData[2].key1 == 0x10 &&
            testData[3].key1 == 0xFF;
            
        if (sortedCorrectly) {
            std::cout << "Test 2 passed\n";
        } else {
            std::cout << "Test 2 failed\n";
        }
    }
}

int main() {
    runTests();
    
    std::vector<DataStruct> data;
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));
    
    std::sort(data.begin(), data.end(), compareDataStructs);
    
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    
    return 0;
}