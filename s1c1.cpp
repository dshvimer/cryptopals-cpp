#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int NIBBLE_SIZE = 4;
const int BASE64_SIZE = 6;

typedef vector<unsigned char> bytes;
typedef vector<bool> raw_data;

bytes parse_hex(const string hex_input)
{
    string padded_input;
    stringstream hex_reader;
    bytes data;
    unsigned char value;

    //Padded to be easily
    int bit_count = hex_input.length() * NIBBLE_SIZE;
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
    
    for (char& c : padded_input) {
        cout << c << endl;
        unsigned char byte;
        hex_reader << hex << c;
        hex_reader >> byte;
        data.push_back(byte);
    }

    for (int i : data) {
        cout << i << endl;
    }

    return data;
}

string bytes_to_base64(bytes data)
{
    string out;
    
}

int main() {
    bytes data = parse_hex("03F");
    return 0;
}