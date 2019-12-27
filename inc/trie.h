#pragma once

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

struct TrieNode: std::unordered_map<std::string, std::shared_ptr<TrieNode>> {
    TrieNode(std::string word, bool stopWord): name(word), canStop(stopWord) {}
    TrieNode(): name("root"), canStop(false) {}
    std::shared_ptr<TrieNode> Import(const std::string& word, bool stopWord);
    std::shared_ptr<TrieNode> MatchWord(const std::string& word);
    void setAsStopNode(bool isStop) { canStop = isStop; }
    bool CanStop();

private:
    std::string name;
    bool canStop;
};

struct TrieState {
    TrieState(std::shared_ptr<TrieNode> root): root(root) {
        Reset();
    }

    void Reset();
    void Update(const std::string& word, std::shared_ptr<TrieNode> node);
    bool Conclude(std::string& output) const;

    std::shared_ptr<TrieNode> root;
    std::shared_ptr<TrieNode> node;
    std::vector<std::string> buffer;
    bool completeWordBehind;
    std::string canBeReturned;
    int lastIndex;
};

struct TrieOfWords {
    typedef std::function<void(const std::string&&)> StringMatchedCallback;
    TrieOfWords() {
        root = std::shared_ptr<TrieNode>(new TrieNode());
        state = std::unique_ptr<TrieState>(new TrieState(root));
    }

    void Import(const std::string& str);
    void MatchString(const std::string& str, StringMatchedCallback callback) const;
    std::shared_ptr<TrieNode> root;
private:
    std::unique_ptr<TrieState> state;
    void __matchWord(const std::string& word, StringMatchedCallback callback) const;
    std::shared_ptr<TrieNode> __importWord(std::shared_ptr<TrieNode> node, const std::string& word, bool stopWord);
};
