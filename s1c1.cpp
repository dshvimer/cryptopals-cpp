#include <iostream>
#include <stdio.h>
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
    //stringstream hex_reader; //Does not work when declared here.
    bytes data;
    unsigned char value;

    //Padded to be easily transformed into base64
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
        stringstream hex_reader; //Needs to be declared here.
        int i; //Must be an integer. unsinged char does not work.
        hex_reader << hex << c;
        hex_reader >> i;
        data.push_back(i);
    }

    return data;
}

raw_data bytes_to_raw(bytes data)
{
    raw_data raw;
    int j;
    for (int c : data) { //cast to int from unsigned char
        cout << c << endl;
        for (int i = 0; i < 4; i++) {
            j = c & 0x8;
            j >>= 3;
            c <<= 1;
            cout << " " << j;

            raw.push_back(j);
        }
        cout << endl;
    }

    for (bool i : raw) {
        cout << i << endl;
    }

    return raw;
}

int main() {
    bytes data = parse_hex("3F");
    raw_data raw = bytes_to_raw(data);
    return 0;
}