#ifndef __PROGTEST__

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
using Symbol = char;
using Word = std::vector<Symbol>;

struct Grammar {
    std::set<Symbol> m_Nonterminals;
    std::set<Symbol> m_Terminals;
    std::vector<std::pair<Symbol, std::vector<Symbol>>> m_Rules;
    Symbol m_InitialSymbol;
};
#endif


using Cell = map<int, vector<int>>;
using Table = vector<vector<Cell>>;
using Rules = vector<pair<Symbol, vector<Symbol>>>;

vector<int> find_rule_indexes(const Rules &rules, const vector<Symbol> &s) {
    vector<int> indexes;
    for (int rule_index = 0; rule_index < rules.size(); rule_index++) {
        if (s == rules[rule_index].second) {
            indexes.push_back(rule_index);
        }
    }
    return indexes;
}

Symbol index_to_symbol(int index, const Rules &rules) {
    return rules[index].first;
}

void print_table(const Table &t, const Grammar &g) {
    for (int row = 0; row < t.size(); row++) {
        for (int column = 0; column < t.size(); column++) {
            if (column == 0)
                cout << "|";
            cout << "{";
            for (const auto &element: t[row][column]) {
                cout << " " << index_to_symbol(element.first, g.m_Rules) << " ";
            }
            cout << "}|";
        }
        cout << endl;
    }
}

pair<int, int> get_diagonal_position(int i, int j, int l) {
    return {i + l + 1, j - l - 1};
}

vector<pair<pair<int, int>, vector<Symbol>>>
get_permutations(const Cell &direct, const Cell &diag, const Rules &rules) {
    vector<pair<pair<int, int>, vector<Symbol>>> rule_images;
    for (const auto &[index_direct, predecessor_direct]: direct) {
        for (const auto &[index_diag, predecessor_diag]: diag) {
            rule_images.push_back({{index_direct,                         index_diag},
                                   {index_to_symbol(index_direct, rules), index_to_symbol(index_diag, rules)}});
        }
    }
    return rule_images;
}

std::vector<size_t> trace(const Grammar &g, const Word &w) {
//    initialize table
    size_t n = w.size();
    Table T = Table(n, vector<Cell>(n));

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            if (j == 0) { // first column
                const auto indexes = find_rule_indexes(g.m_Rules, {w[i]});
                for (const auto index: indexes) {
                    T[i][j].insert({index, {}});
                }
            }
            set<Symbol> inserted_symbols;

            for (int l = 0; l < j; l++) {
                auto [diag_i, diag_l] = get_diagonal_position(i, j, l);
                auto rule_images = get_permutations(T[i][l], T[diag_i][diag_l], g.m_Rules);

                for (const auto &[rule_image_indexes, rule_image_symbols]: rule_images) {
                    auto indexes = find_rule_indexes(g.m_Rules, rule_image_symbols);
                    for (const auto index: indexes) {
                        const auto &[it, inserted] = inserted_symbols.insert(index_to_symbol(index, g.m_Rules));
                        if (inserted) {
                            T[i][j].insert({index, {i, l, rule_image_indexes.first, rule_image_indexes.second}});
                        }
                    }
                }
            }

        }
    }
    vector<size_t> predecessors;
    queue<pair<vector<int>, pair<int, int>>> q;
    for (const auto &[index, predecessor]: T[0][n - 1]) {
        if (index_to_symbol(index, g.m_Rules) == g.m_InitialSymbol) {
            predecessors.push_back(index);
            q.push({predecessor, {0, n - 1}});
            break;
        }
    }

    if (predecessors.empty()) {
        return {};
    }

    while (!q.empty()) {
        auto [predecessor, current_pos] = q.front();
        q.pop();
        int i_direct = predecessor[0];
        int j_direct = predecessor[1];
        int index_direct = predecessor[2];
        int index_diag = predecessor[3];
        auto [i_diag, j_diag] = get_diagonal_position(current_pos.first, current_pos.second, j_direct);

        // direct
        predecessors.push_back(index_direct);
        auto it_direct = T[i_direct][j_direct].find(index_direct);
        if (!it_direct->second.empty()) {
            q.push({it_direct->second, {i_direct, j_direct}});
        }


        // diag
        predecessors.push_back(index_diag);
        auto it_diag = T[i_diag][j_diag].find(index_diag);
        if (!it_diag->second.empty()) {
            q.push({it_diag->second, {i_diag, j_diag}});
        }
    }
#ifndef __PROGTEST__
//    print_table(T, g);
    for (auto i: predecessors) {
        cout << i << ", ";
    }
    cout << endl;
#endif
    return predecessors;
}

#ifndef __PROGTEST__

int main() {

    assert(vector<int>({1, 2, 3}) == vector<int>({1, 2, 3}));
    assert(vector<int>({1, 2, 3}) != vector<int>({2, 1, 3}));
    assert(vector<int>({1, 2, 3}) != vector<int>({1, 2}));

    Grammar g0{
            {'A', 'B', 'C', 'S'},
            {'a', 'b'},
            {
                    {'S', {'A', 'B'}},
                    {'S', {'B', 'C'}},
                    {'A', {'B', 'A'}},
                    {'A', {'a'}},
                    {'B', {'C', 'C'}},
                    {'B', {'b'}},
                    {'C', {'A', 'B'}},
                    {'C', {'a'}},
            },
            'S'};

    assert(trace(g0, {'b', 'a', 'a', 'b', 'a'}) == std::vector<size_t>({0, 2, 5, 3, 4, 6, 3, 5, 7}));
    assert(trace(g0, {'b'}) == std::vector<size_t>({}));
    assert(trace(g0, {'a'}) == std::vector<size_t>({}));
    assert(trace(g0, {}) == std::vector<size_t>({}));
    assert(trace(g0, {'a', 'a', 'a', 'a', 'a'}) == std::vector<size_t>({1, 4, 6, 3, 4, 7, 7, 7, 7}));
    assert(trace(g0, {'a', 'b'}) == std::vector<size_t>({0, 3, 5}));
    assert(trace(g0, {'b', 'a'}) == std::vector<size_t>({1, 5, 7}));
    assert(trace(g0, {'c', 'a'}) == std::vector<size_t>({}));

    Grammar g1{
            {'A', 'B'},
            {'x', 'y'},
            {
                    {'A', {}},
                    {'A', {'x'}},
                    {'B', {'x'}},
                    {'A', {'B', 'B'}},
                    {'B', {'B', 'B'}},
            },
            'A'};

    assert(trace(g1, {}) == std::vector<size_t>({0}));
    assert(trace(g1, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g1, {'x', 'x'}) == std::vector<size_t>({3, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x'}) ==
           std::vector<size_t>({3, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) ==
           std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) ==
           std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2}));

    Grammar g2{
            {'A', 'B'},
            {'x', 'y'},
            {
                    {'A', {'x'}},
                    {'B', {'x'}},
                    {'A', {'B', 'B'}},
                    {'B', {'B', 'B'}},
            },
            'B'};

    assert(trace(g2, {}) == std::vector<size_t>({}));
    assert(trace(g2, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g2, {'x', 'x'}) == std::vector<size_t>({3, 1, 1}));
    assert(trace(g2, {'x', 'x', 'x'}) == std::vector<size_t>({3, 3, 1, 1, 1}));

    Grammar g3{
            {'A', 'B', 'C', 'D', 'E', 'S'},
            {'a', 'b'},
            {
                    {'S', {'A', 'B'}},
                    {'S', {'S', 'S'}},
                    {'S', {'a'}},
                    {'A', {'B', 'S'}},
                    {'A', {'C', 'D'}},
                    {'A', {'b'}},
                    {'B', {'D', 'D'}},
                    {'B', {'b'}},
                    {'C', {'D', 'E'}},
                    {'C', {'b'}},
                    {'C', {'a'}},
                    {'D', {'a'}},
                    {'E', {'S', 'S'}},
            },
            'S'};

    assert(trace(g3, {}) == std::vector<size_t>({}));
    assert(trace(g3, {'b'}) == std::vector<size_t>({}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b'}) == std::vector<size_t>({1, 2, 0, 3, 7, 1, 2, 2, 7}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a'}) ==
           std::vector<size_t>({1, 1, 0, 4, 8, 11, 12, 0, 5, 6, 11, 11, 0, 4, 9, 11, 7, 11, 7, 2, 2}));
}

#endif

