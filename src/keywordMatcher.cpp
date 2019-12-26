#include "keywordMatcher.h"
#include <unistd.h>

KeywordMatcher::KeywordMatcher(std::string filename) {
	auto& dataLoader = DataLoader::GetInstance();
	dataLoader(filename);
	dataLoader.AcquireDataLineByLine([=] (const std::string& data) {
		this->trie.Import(data);
	});
}

void
KeywordMatcher::FindKeywords(const std::string& str) const {
	trie.MatchString(str, [](const std::string& str) {
		std::cout << "Found keyword: " << str << std::endl;
	});
}
