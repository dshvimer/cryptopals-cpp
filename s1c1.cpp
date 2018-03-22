#include <iostream>
#include <sstream>
#include <string>

#include <boost/archive/iterators/base64_from_binary.hpp>

int main() {
    std::string in = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    unsigned int raw;   
    std::stringstream input;
    input << std::hex << in;
    input >> raw;
    return 0;
}