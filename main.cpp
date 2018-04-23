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
    cout << key_len << endl;
    for (int i = 0; i < input.size(); i++) {
        output.push_back(input[i] ^ key[i % key_len]);
        cout << i % key_len << endl;
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
    string str = base64_padding("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    data_stream in = parse_hex(str);
    binary_stream bin = data_stream_to_binary(in);
    data_stream out = as_width(bin, 6);
    cout << encode_base64(out) << endl;
    return 0;
}