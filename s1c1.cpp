#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int NIBBLE_SIZE = 4;
const int BASE64_SIZE = 6;

typedef vector<unsigned char> bytes;
typedef vector<bool> binary_data;

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

binary_data bytes_to_binary(bytes data)
{
    binary_data raw;
    int j;
    for (int c : data) { //cast to int from unsigned char
        //cout << c << endl;
        for (int i = 0; i < 4; i++) {
            j = c & 0x8;
            j >>= 3;
            c <<= 1;
            //cout << " " << j;
            raw.push_back(j);
        }
        //cout << endl;
    }

    for (bool i : raw) {
        cout << i;
    }
    cout << endl;

    return raw;
}

string binary_to_base64(binary_data raw)
{
    stringstream out;
    queue<bool> buf;
    int j, k, ch;
    int limit = raw.size() / 6;

    for (bool b : raw) {
        buf.push(b);
    }

    for (int i = 0; i < limit; i++) {
        ch = 0;
        for (j = 5; j >= 0; j--) {
            k = buf.front();
            ch |= k;
            cout << k << " | 0 = " << ch << endl;
            ch <<= 1;
            buf.pop();
        }
        cout << ch << endl;
    }

    return "";
}

int main() {
    bytes data = parse_hex("AF0");
    binary_data raw = bytes_to_binary(data);
    // binary_to_base64(raw);
    return 0;
}