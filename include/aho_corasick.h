#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <queue>
#include <string>
#include <vector>

class AhoCorasick {
public:
  AhoCorasick() = default;

  void build(const std::vector<std::string> &patterns);

  std::vector<std::pair<int, int>> search(const std::string &text) const;

private:
  struct Node {
    std::vector<int> next;
    int fail = -1; // failure link
    std::vector<int> output;
    Node() : next(256, -1) {}
  };

  std::vector<Node> trie;
  std::vector<std::string> pattern_list;
  std::vector<int> pattern_lengths;
  int pattern_count = 0;
};

#endif // AHO_CORASICK_H
