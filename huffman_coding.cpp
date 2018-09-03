#include "huffman_coding.h"

#include <algorithm>
#include <list>
#include <tuple>

namespace huffman_coding {

std::unordered_map<String::value_type, size_t> getFrequenciesTable(const String& str)
{
    std::unordered_map<String::value_type, size_t> result;

    for (const auto& ch : str)
        ++result[ch];

    return result;
}

std::shared_ptr<HuffmanTreeNode> createHuffmanTree(const String& str)
{
    std::list<std::shared_ptr<HuffmanTreeNode>> huffmanTree;

    auto frequenciesTable = getFrequenciesTable(str);
    std::vector<std::pair<char, size_t>> sortedFrequencies;

    for (const auto& pair : frequenciesTable)
        sortedFrequencies.push_back(pair);

    std::sort(sortedFrequencies.begin(), sortedFrequencies.end(), [](const auto& left, const auto& right) {
        return left.second > right.second;
    });

    for (const auto& pair : sortedFrequencies) {
        huffmanTree.push_back(std::make_shared<HuffmanTreeNode>(pair.first, pair.second));
    }

    while (huffmanTree.size() > 1) {
        auto lastElement = huffmanTree.end();
        --lastElement;
        auto penultimateElement = lastElement;
        --penultimateElement;

        while ((*penultimateElement)->frequency < (*lastElement)->frequency) {
            if (huffmanTree.size() == 2)
                break;

            --lastElement;
            --penultimateElement;
        }

        // push nodes to the bottom
        auto newElement = huffmanTree.insert(
            penultimateElement,
            std::make_shared<HuffmanTreeNode>(0, (*lastElement)->frequency + (*penultimateElement)->frequency));

        (*newElement)->left = *penultimateElement;
        (*newElement)->right = *lastElement;

        huffmanTree.erase(penultimateElement);
        huffmanTree.erase(lastElement);
    }

    return *huffmanTree.begin();
}

std::tuple<std::shared_ptr<BitVector>, std::shared_ptr<CodeTable>, std::shared_ptr<HuffmanTreeNode>> encodeString(
    const String& str)
{
    auto huffmanTree = createHuffmanTree(str);
    std::shared_ptr<CodeTable> codeTable = std::make_shared<CodeTable>();
    fillCodeTable(huffmanTree, codeTable);
    std::shared_ptr<BitVector> bitResult = std::make_shared<BitVector>();

    for (const auto& ch : str) {
        size_t byte = codeTable->at(ch);

        while (byte) {
            bitResult->push_back(byte & 1);
            byte >>= 1;
        }
    }

    return std::make_tuple(bitResult, codeTable, huffmanTree);
}

//std::pair<CodeTable, BitVector> encodeString(
//    const String& str,
//    const std::unique_ptr<HuffmanTreeNode>& huffmanTree)
//{
//    CodeTable codeTable;
//    fillCodeTable(huffmanTree, codeTable);

//    return encodeString(str, codeTable);
//}

//std::pair<CodeTable, BitVector> encodeString(
//    const String& str,
//    const CodeTable& codeTable)
//{
//    BitVector bitResult;

//    for (const auto& ch : str) {
//        size_t byte = codeTable.at(ch);

//        while (byte) {
//            bitResult.push_back(byte & 1);
//            byte >>= 1;
//        }
//    }

//    return std::make_pair(codeTable, bitResult);
//}

void fillCodeTable(
    std::shared_ptr<HuffmanTreeNode> root,
    std::shared_ptr<CodeTable> codeTable,
    size_t previousBits,
    bool isRight)
{
    if (!root)
        return;

    previousBits <<= 1;
    previousBits |= isRight;
    if (root->character) {
        (*codeTable)[root->character] = previousBits;
    }

    fillCodeTable(root->left, codeTable, previousBits, false);
    fillCodeTable(root->right, codeTable, previousBits, true);
}
}
