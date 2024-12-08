#include "../include/aho_corasick.h"

void AhoCorasick::build(const std::vector<std::string> &patterns) {
    trie.clear();
    trie.push_back(Node());
    pattern_count = (int)patterns.size();
    pattern_list = patterns;
    pattern_lengths.clear();
    for (auto &p : patterns) {
        pattern_lengths.push_back((int)p.size());
    }

    // Build trie
    for (int pid = 0; pid < pattern_count; pid++) {
        const std::string &pattern = patterns[pid];
        int current = 0;
        for (char c : pattern) {
            unsigned char uc = (unsigned char)c;
            if (trie[current].next[uc] == -1) {
                trie[current].next[uc] = (int)trie.size();
                trie.push_back(Node());
            }
            current = trie[current].next[uc];
        }
        trie[current].output.push_back(pid);
    }

    // Build failure links
    std::queue<int> q;
    for (int c = 0; c < 256; c++) {
        int nxt = trie[0].next[c];
        if (nxt != -1 && nxt != 0) {
            trie[nxt].fail = 0;
            q.push(nxt);
        } else {
            trie[0].next[c] = (trie[0].next[c] == -1) ? 0 : trie[0].next[c];
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        int f = trie[u].fail;
        // Merge output from the fail link
        for (int out_pattern : trie[f].output) {
            trie[u].output.push_back(out_pattern);
        }

        for (int c = 0; c < 256; c++) {
            int v = trie[u].next[c];
            if (v != -1) {
                trie[v].fail = trie[f].next[c];
                q.push(v);
            } else {
                trie[u].next[c] = trie[f].next[c];
            }
        }
    }
}

std::vector<std::pair<int,int>> AhoCorasick::search(const std::string &text) const {
    std::vector<std::pair<int,int>> results;
    int state = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        unsigned char c = (unsigned char)text[i];
        state = trie[state].next[c];
        if (!trie[state].output.empty()) {
            for (int pid : trie[state].output) {
                int start_pos = i - pattern_lengths[pid] + 1;
                results.emplace_back(pid, start_pos);
            }
        }
    }
    return results;
}

