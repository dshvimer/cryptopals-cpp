#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int NIBBLE_SIZE = 4;
const int BASE64_SIZE = 6;
const char base64_encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

typedef vector<int> data_stream;
typedef vector<bool> binary_stream;

string encode_hex(data_stream in)
{
    stringstream out;
    for (int i : in) {
        out << hex << i;
    }
    return out.str();
}

string encode_base64(data_stream in)
{
    stringstream out;
    for (int i : in) {
        out << base64_encoding_table[i];
    }
    return out.str();
  
}

string base64_padding(string in)
{
    string padded_input;

    int bit_count = in.length() * NIBBLE_SIZE;
    int rmdr = bit_count % BASE64_SIZE;
    switch(rmdr)
    {
        case 2:
            padded_input = "0" + in;
            break;
        case 4:
            padded_input = "00" + in;
            break;
        default:
            padded_input = in;
    }
    return padded_input;
}

data_stream parse_ascii(string input)
{
    data_stream data;

    for (char& c : input) {
        data.push_back((int)c);
    }

    return data;
}

data_stream parse_hex(string hex_input)
{
    stringstream hex_reader;
    data_stream data;

    for (char& c : hex_input) {
        int i;
        hex_reader << hex << c;
        hex_reader >> i;
        data.push_back(i);
        hex_reader.str(string()); //clear the stream
        hex_reader.clear();
    }

    return data;
}

binary_stream data_stream_to_binary(data_stream data)
{
    binary_stream raw;
    int j;
    for (int c : data) {
        for (int i = 0; i < 4; i++) {
            j = c & 0x8;
            j >>= 3;
            c <<= 1;            //cout << " " << j;
            raw.push_back(j);
        }
    }

    return raw;
}

data_stream as_width(binary_stream raw, int width)
{
    // data needs to be aligned.
    data_stream out;
    queue<bool> buf;
    int j, k, ch;
    int limit = raw.size() / width;

    for (bool b : raw) {
        buf.push(b);
    }

    for (int i = 0; i < limit; i++) {
        ch = 0;
        for (j = 0; j < BASE64_SIZE; j++) {
            k = buf.front();
            ch |= k;
            ch <<= 1;
            buf.pop();
        }
        ch >>= 1;
        out.push_back(ch);
    }

    return out;

}

data_stream myxor(data_stream input, data_stream key)
{
    data_stream output;
    int key_len = key.size();
    for (int i = 0; i < input.size(); i++) {
        output.push_back(input[i] ^ key[i % key_len]);
    }
    return output;
}

data_stream myxor(data_stream input, int key)
{
    data_stream output;
    for (int i : input) {
        output.push_back(i ^ key);
    }
    return output;

}

int main() {
    data_stream in = parse_ascii("Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal");
    data_stream key = parse_ascii("ICE");
    data_stream out = myxor(in, key);
    cout << encode_hex(out) << endl;
    return 0;
}