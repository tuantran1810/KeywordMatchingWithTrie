#include "utils.h"

StringSplitter* StringSplitter::instance = nullptr;

StringSplitter&
StringSplitter::GetInstance() {
    if (instance == nullptr) instance = new StringSplitter();
    return *instance;
}

int
StringSplitter::operator()(const std::string& str, std::vector<std::string>& results, char delimiter) const {
    int len = 0;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        len++;
        if (token != "") results.push_back(token);
    }
    return len;
}

void
StringSplitter::Generate(const std::string& str, DataTransferCallback callback, char delimiter) {
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        callback(token);
    }
}

StringJoiner* StringJoiner::instance = nullptr;

StringJoiner&
StringJoiner::GetInstance() {
    if (instance == nullptr) instance = new StringJoiner();
    return *instance;
}

std::string
StringJoiner::operator()(const std::vector<std::string>& vstr, char delimiter) const {
    std::stringstream ss;
    int len = vstr.size();
    if (len > 0) {
        ss << vstr[0];
        for (int i = 1; i < len; i++) {
            ss << delimiter << vstr[i];
        }
    }
    return ss.str();
}

DataLoader* DataLoader::instance = nullptr;

DataLoader&
DataLoader::GetInstance() {
    if (instance == nullptr) instance = new DataLoader();
    return *instance;
}

bool
DataLoader::operator()(std::string filename) {
    buffer.clear();
    std::ifstream in(filename.c_str());
    if (!in) {
        std::cout << "Error while opening file!" << std::endl;
        return false;
    }

    std::string str;
    while (std::getline(in, str)) {
        if (str.size() > 0) buffer.push_back(str);
    }
    in.close();
    return true;
}

void
DataLoader::AcquireDataLineByLine(DataTransferCallback callback) const {
    for (auto& data : buffer) {
        callback(data);
    }
}

void
DataLoader::AcquireDataAll(DataTransferCallback callback) const {
    callback(StringJoiner::GetInstance()(buffer));
}
