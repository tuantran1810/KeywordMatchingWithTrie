#include "trie.h"
#include "utils.h"

/******************************************
*                 Trie Node               *
******************************************/
std::shared_ptr<TrieNode>
TrieNode::Import(const std::string& word, bool stopWord) {
    auto iter = this->find(word);
    std::shared_ptr<TrieNode> nextNode = nullptr;
    if (iter == this->end()) {
        nextNode = std::shared_ptr<TrieNode>(new TrieNode(word, stopWord));
        this->insert({ word, nextNode });
    } else if (iter != this->end() && iter->second != nullptr && stopWord) {
        nextNode = iter->second;
        nextNode->setAsStopNode(true);
    } else nextNode = iter->second;

    return nextNode;
}

std::shared_ptr<TrieNode>
TrieNode::MatchWord(const std::string& word) {
    auto iter = this->find(word);
    if (iter == this->end()) {
     // std::cout << "MatchWord: " << word  << " at node " << this->name << " not found" << std::endl;
        return nullptr;
    }
 // std::cout << "MatchWord: " << word << " at node " << this->name <<  " found!!!!!!!!" << std::endl;
    return iter->second;
}

bool
TrieNode::CanStop() {
    return canStop;
}

/******************************************
*                Trie State               *
******************************************/

void
TrieState::Reset() {
    node = root;
    buffer.clear();
    completeWordBehind = false;
    canBeReturned = "";
    lastIndex = 0;
}

void
TrieState::Update(const std::string& word, std::shared_ptr<TrieNode> node) {
    if (node == nullptr) {
        std::cout << "input node == nullptr" << std::endl;
        return;
    }
    this->node = node;
    buffer.push_back(word);
    if (node->CanStop()) {
        completeWordBehind = true;
        canBeReturned = StringJoiner::GetInstance()(buffer);
        lastIndex = buffer.size();
    }
}

bool
TrieState::Conclude(std::string& output) const {
    output = canBeReturned;
    return completeWordBehind;
}

/******************************************
*                  Trie                   *
******************************************/

void
TrieOfWords::Import(const std::string& str) {
    std::vector<std::string> results;
    auto len = StringSplitter::GetInstance()(str, results);
    auto node = root;
    bool stopFlag = false;
    for (auto i = 0; i < len - 1; i++) {
        node = __importWord(node, results[i], false);
        if (node == nullptr) {
            std::cout << "cannot insert more word, error in implementation!" << std::endl;
            stopFlag = true;
            break;
        }
    }
    if (!stopFlag) {
        __importWord(node, results[len - 1], true);
    }
}

void
TrieOfWords::MatchString(const std::string& str, StringMatchedCallback callback) const {
    state->Reset();
    StringSplitter::GetInstance().Generate(str, [&](const std::string& word) {
        __matchWord(word, callback);
    });
    if (state->node != root && state->node != nullptr && state->node->CanStop() && state->buffer.size() > 0) {
        callback(StringJoiner::GetInstance()(state->buffer));
    }
}

void
TrieOfWords::__matchWord(const std::string& word, StringMatchedCallback callback) const {
    if (state->node == nullptr) {
        std::cout << "node nullptr!!!" << std::endl;
        return;
    }
    auto tmp = state->node->MatchWord(word);
    if (tmp != nullptr) {
        state->Update(word, tmp);
    } else {
        if (state->buffer.size() > 0) {
            if (state->node->CanStop()) {
                callback(StringJoiner::GetInstance()(state->buffer));
                state->Reset();
                __matchWord(word, callback);
            } else {
                std::vector<std::string> tmpvec;
                tmpvec.swap(state->buffer);
                tmpvec.push_back(word);
                std::string tmp;
                int lastIndex = 1;
                if (state->Conclude(tmp)) {
                    lastIndex = state->lastIndex;
                    callback(std::move(tmp));
                }
                state->Reset();
                for (int i = lastIndex; i < tmpvec.size(); i++) __matchWord(tmpvec[i], callback);
            }
        } else state->Reset();
    }
}

std::shared_ptr<TrieNode>
TrieOfWords::__importWord(std::shared_ptr<TrieNode> node, const std::string& word, bool stopWord) {
    if (node == nullptr) return nullptr;
    return node->Import(word, stopWord);
}
