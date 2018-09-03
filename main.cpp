#include "huffman_coding.h"

#include <algorithm>
#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

//void printBT(const std::string& prefix, const HuffmanTreeNode* node, bool isLeft)
//{
//    if (node != nullptr) {
//        std::cout << prefix;

//        std::cout << (isLeft ? "├──" : "└──");

//        // print the value of the node
//        std::cout << node->character << ": " << node->frequency << std::endl;

//        // enter the next tree level - left and right branch
//        printBT(prefix + (isLeft ? "│   " : "    "), node->left.get(), true);
//        printBT(prefix + (isLeft ? "│   " : "    "), node->right.get(), false);
//    }
//}

//template <typename T>
//std::string intToBitString(T value)
//{
//    std::string result;
//    while (value) {
//        result.push_back(value & 1 ? '1' : '0');
//        value >>= 1;
//    }

//    std::reverse(result.begin(), result.end());
//    return result;
//}

int main(int argc, char* argv[])
{
    std::wstring str(L"Hello, fucking World!");

    //    if (argc > 1) {
    //        std::ifstream file(argv[1]);
    //        std::istreambuf_iterator<char> inputBegin(std::cin), inputEnd;
    //        str = std::string(inputBegin, inputEnd);
    //    } else {
    //        std::istreambuf_iterator<char> inputBegin(std::cin), inputEnd;
    //        str = std::string(inputBegin, inputEnd);
    //    }

    //    std::ifstream t("/home/user/downloads/Telegram Desktop/data.cp.txt");
    //    std::stringstream buffer;
    //    buffer << t.rdbuf();
    //    str = buffer.str();

    auto result = huffman_coding::encodeString(str);

    std::cout << "original size:   " << str.size() << std::endl;
    std::cout << "compressed size: " << std::get<1>(result)->size() / 8 << std::endl;

    return 0;
}
