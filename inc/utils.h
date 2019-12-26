#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

struct StringSplitter {
	typedef std::function<void(const std::string&)> DataTransferCallback;
	static StringSplitter& GetInstance();
	int operator()(const std::string& str, std::vector<std::string>& results, char delimiter = ' ') const;
	void Generate(const std::string& str, DataTransferCallback callback, char delimiter = ' ');
private:
	static StringSplitter* instance;
};

struct StringJoiner {
	static StringJoiner& GetInstance();
	std::string operator()(const std::vector<std::string>& vstr, char delimiter = ' ') const;
private:
	static StringJoiner* instance;
};

struct DataLoader {
	typedef std::function<void(const std::string&)> DataTransferCallback;
	static DataLoader& GetInstance();
	bool operator()(std::string filename);
	void AcquireDataLineByLine(DataTransferCallback callback) const;
	void AcquireDataAll(DataTransferCallback callback) const;
private:
	static DataLoader* instance;
	std::vector<std::string> buffer;
};
