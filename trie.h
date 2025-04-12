#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class trie {
private:
    class Node {
    public:
        bool is_terminal;
        Node* children[26];

        Node() : is_terminal(false) {
            for (int i = 0; i < 26; ++i)
                children[i] = nullptr;
        }

        ~Node() {
            for (int i = 0; i < 26; ++i)
                delete children[i];
        }
    };

    Node* root;

    // Helper to recursively delete nodes
    void clear(Node* node) {
        if (node) {
            for (int i = 0; i < 26; ++i)
                clear(node->children[i]);
            delete node;
        }
    }

    // Helper for extend()
    void extend_helper(Node* node, std::string current, std::vector<std::string>& result) {
        if (!node) return;
        if (node->is_terminal)
            result.push_back(current);
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                extend_helper(node->children[i], current + static_cast<char>('a' + i), result);
            }
        }
    }

public:
    trie() {
        root = new Node();
    }

    ~trie() {
        clear(root);
    }

    void insert(const std::string& s) {
        Node* curr = root;
        for (char c : s) {
            if (c < 'a' || c > 'z') continue;
            int idx = c - 'a';
            if (!curr->children[idx])
                curr->children[idx] = new Node();
            curr = curr->children[idx];
        }
        curr->is_terminal = true;
    }

    bool contains(const std::string& s) {
        Node* curr = root;
        for (char c : s) {
            if (c < 'a' || c > 'z') return false;
            int idx = c - 'a';
            if (!curr->children[idx]) return false;
            curr = curr->children[idx];
        }
        return curr->is_terminal;
    }

    bool is_prefix(const std::string& s) {
        Node* curr = root;
        for (char c : s) {
            if (c < 'a' || c > 'z') return false;
            int idx = c - 'a';
            if (!curr->children[idx]) return false;
            curr = curr->children[idx];
        }
        return true;
    }

    void extend(const std::string& prefix, std::vector<std::string>& result) {
        Node* curr = root;
        for (char c : prefix) {
            if (c < 'a' || c > 'z') return;
            int idx = c - 'a';
            if (!curr->children[idx]) return;
            curr = curr->children[idx];
        }
        extend_helper(curr, prefix, result);
    }
};

#endif // TRIE_H
