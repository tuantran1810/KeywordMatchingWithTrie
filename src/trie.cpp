#include "trie.h"
#include "utils.h"

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
//		std::cout << "MatchWord: " << word  << " at node " << this->name << " not found" << std::endl;
		return nullptr;
	}
//	std::cout << "MatchWord: " << word << " at node " << this->name <<  " found!!!!!!!!" << std::endl;
	return iter->second;
}

bool
TrieNode::CanStop() {
	return canStop;
}

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
	auto node = root;
	std::vector<std::string> buffer;
	StringSplitter::GetInstance().Generate(str, [&](const std::string& word) {
		__matchWord(word, node, buffer, callback);
	});
	if (node != root && node != nullptr && node->CanStop() && buffer.size() > 0) {
		callback(StringJoiner::GetInstance()(buffer));
	}
}

void
TrieOfWords::__matchWord(const std::string& word, std::shared_ptr<TrieNode>& node, std::vector<std::string>& buffer, StringMatchedCallback callback) const {
	if (node == nullptr) {
		std::cout << "node nullptr!!!" << std::endl;
		return;
	}
	auto tmp = node->MatchWord(word);
	if (tmp != nullptr) {
		node = tmp;
		buffer.push_back(word);
	} else {
		if (buffer.size() > 0) {
			if (node->CanStop()) {
				callback(StringJoiner::GetInstance()(buffer));
				__resetState(node, buffer);
				__matchWord(word, node, buffer, callback);
			} else {
				buffer.push_back(word);
				std::vector<std::string> tmpvec;
				tmpvec.swap(buffer);
				node = root;
				for (int i = 1; i < tmpvec.size(); i++) __matchWord(tmpvec[i], node, buffer, callback);
			}
		} else __resetState(node, buffer);
	}

}

void
TrieOfWords::__resetState(std::shared_ptr<TrieNode>& node, std::vector<std::string>& buffer) const {
	node = root;
	buffer.clear();
}

std::shared_ptr<TrieNode>
TrieOfWords::__importWord(std::shared_ptr<TrieNode> node, const std::string& word, bool stopWord) {
	if (node == nullptr) return nullptr;
	return node->Import(word, stopWord);
}
