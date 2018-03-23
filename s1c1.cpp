#include <iostream>
#include <sstream>
#include <string>
#include <bitset>

using namespace std;

const int NIBBLE_SIZE = 4;
const int BASE64_SIZE = 6;

void hex_to_base64(const string hex_input)
{
    string padded_input;
    stringstream data, output;
    int iterations;
    int bit_count = hex_input.length() * NIBBLE_SIZE;
    int base64_len = bit_count / BASE64_SIZE;
    int rmdr = bit_count % BASE64_SIZE;

    switch(rmdr)
    {
        case 2:
            padded_input = "0" + hex_input;
            break;
        case 4:
            padded_input = "00" + hex_input;
            break;
        default:
            padded_input = hex_input;
    }
    
    data << hex << padded_input;

    iterations = padded_input.length() / 3;
    for (int i = 0; i < iterations; i++) {
        unsigned char buf[3];
        unsigned char digit;
        
        data.read((char*)buf, 3);
        digit = buf[0];
        cout << bitset<8>(digit) << endl;
        digit <<= 2;
        cout << bitset<8>(digit) << endl;
    }
}

int main() {
    hex_to_base64("FFF");
    return 0;
}