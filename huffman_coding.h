#pragma once

#include "BitVector.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace huffman_coding {

struct HuffmanTreeNode {
    HuffmanTreeNode(char character, size_t frequency)
        : character(character)
        , frequency(frequency)
    {
    }
    size_t frequency;
    // 0 means it's additional node
    char character;
    std::shared_ptr<HuffmanTreeNode> left, right;
};

using String = std::wstring;
using CodeTable = std::unordered_map<String::value_type, size_t>;

std::unordered_map<String::value_type, size_t> getFrequenciesTable(const String& str);

std::tuple<std::shared_ptr<BitVector>, std::shared_ptr<CodeTable>, std::shared_ptr<HuffmanTreeNode>> encodeString(const String& str);

//std::pair<CodeTable, BitVector> encodeString(
//    const String& str,
//    const std::unique_ptr<HuffmanTreeNode>& huffmanTree);

//std::pair<CodeTable, BitVector> encodeString(
//    const String& str,
//    const CodeTable& codeTable);

void fillCodeTable(
    std::shared_ptr<HuffmanTreeNode> root,
    std::shared_ptr<CodeTable> codeTable,
    size_t previousBits = 0,
    bool isRight = false);
}
