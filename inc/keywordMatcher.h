#pragma once

#include <iostream>
#include "trie.h"
#include "utils.h"

struct KeywordMatcher {
    KeywordMatcher(std::string filename);
    void FindKeywords(const std::string& str) const;
private:
    TrieOfWords trie;
};
