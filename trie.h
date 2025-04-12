#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class trie {
private:
    class Node {
    public:
        bool is_terminal = false;
        Node* children[26] = {nullptr};

        ~Node() {
            for (Node* child : children) {
                delete child;  // This safely deletes entire subtree
            }
        }
    };

    Node* root;

    void extend_helper(Node* node, std::string& current, std::vector<std::string>& result) const {
        if (node->is_terminal)
            result.push_back(current);

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                current.push_back('a' + i);
                extend_helper(node->children[i], current, result);
                current.pop_back();
            }
        }
    }

public:
    trie() : root(new Node()) {}

    ~trie() {
        delete root;  // Let Node's destructor recursively clean up
    }

    void insert(const std::string& s) {
        Node* curr = root;
        for (char c : s) {
            int i = c - 'a';
            if (!curr->children[i])
                curr->children[i] = new Node();
            curr = curr->children[i];
        }
        curr->is_terminal = true;
    }

    bool contains(const std::string& s) const {
        Node* curr = root;
        for (char c : s) {
            int i = c - 'a';
            if (!curr->children[i]) return false;
            curr = curr->children[i];
        }
        return curr->is_terminal;
    }

    bool is_prefix(const std::string& s) const {
        Node* curr = root;
        for (char c : s) {
            int i = c - 'a';
            if (!curr->children[i]) return false;
            curr = curr->children[i];
        }
        return true;
    }

    void extend(const std::string& prefix, std::vector<std::string>& result) const {
        Node* curr = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!curr->children[i]) return;
            curr = curr->children[i];
        }
        std::string current = prefix;
        extend_helper(curr, current, result);
    }
};

#endif // TRIE_H
