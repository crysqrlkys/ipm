#include<iostream>
#include<string>
#include<cmath>
#include<cstdio>
#include<bitset>
#include<sstream>
#include <utility>
#include<vector>
#include"constants.h"

using namespace std;


//char *itoa(int value, char *result, int base) {
//    // check that the base if valid
//    if (base < 2 || base > 36) {
//        *result = '\0';
//        return result;
//    }
//
//    char *ptr = result, *ptr1 = result, tmp_char;
//    int tmp_value;
//
//    do {
//        tmp_value = value;
//        value /= base;
//        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
//                                                                                           (tmp_value - value * base)];
//    } while (value);
//
//    // Apply negative sign
//    if (tmp_value < 0) *ptr++ = '-';
//    *ptr-- = '\0';
//    while (ptr1 < ptr) {
//        tmp_char = *ptr;
//        *ptr-- = *ptr1;
//        *ptr1++ = tmp_char;
//    }
//    return result;
//}
//
//string BinaryToString(const string &binaryString) {
//    stringstream sstream(binaryString);
//    string text;
//    while (sstream.good()) {
//        bitset<8> bits;
//        sstream >> bits;
//        char c = char(bits.to_ulong());
//        if (c != 0) {
//            text += c;
//        }
//    }
//    return text;
//}
//
//string TextToBinaryString(const string &text) {
//    string binaryString;
//    for (size_t i = 0; i < text.size(); i++) {
//        binaryString += bitset<8>(text.c_str()[i]).to_string();
//    }
//    return binaryString;
//}
//
//int bin_to_dec(string bin) {
//    int dec = 0, incr = 0, sum = 0;
//    for (int i = (bin.length() - 1); i >= 0; i--) {
//        dec = bin[i] - '0';
//        sum = sum + (int) (dec * (pow(2, incr)));
//        incr++;
//    }
//    return sum;
//}
//
//string dec_to_bin(int dec) {
//    int i = dec;
//    string str = "";
//    char binary[4];
//    while (1) {
//        int quotient = i / 2;
//        int remainder = i % 2;
//        i = quotient;
//        itoa(remainder, binary, 10);
//        str = str + binary;
//        if (quotient == 0)break;
//    }
//    string fin_str = "";
//    for (int i = (str.length() - 1); i >= 0; i--) {
//        fin_str = fin_str + str[i];
//    }
//    return fin_str;
//}
//
//string process_string(string substring, int s[][4][16], int p) {
//    string row, col;
//    for (int i = 0; i < 6; i++) {
//        if (i == 0 || i == 5)row = row + substring[i];
//        else {
//            col = col + substring[i];
//        }
//    }
//    int r = bin_to_dec(row);
//    int c = bin_to_dec(col);
//    int s_box_pos = s[p][r][c];
//    string fbit_bin_str = "0000";
//    int len = dec_to_bin(s_box_pos).length();
//    string bin = dec_to_bin(s_box_pos);
//
//    for (int i = 0; i < len; i++) {
//        fbit_bin_str[i + (4 - len)] = bin[i];
//    }
//    return fbit_bin_str;
//}
//
//string fifty_six_bit_key(string key, int pc1[8][7]) {
//    int i, j, k, bin_key_index = 0, index = 0;
//    string fs_bin_key;
//
//    for (k = 0; k < 56; k++)fs_bin_key = fs_bin_key + '0';
//    for (i = 0; i < 8; i++) {
//        for (j = 0; j < 7; j++) {
//            index = pc1[i][j] - 1;
//            fs_bin_key[bin_key_index] = key[index];
//            bin_key_index++;
//        }
//    }
//    return fs_bin_key;
//}
//
//string rol_keys(string key, int rotating_schedule[16], int i) {
//    int count = rotating_schedule[i], l, j, k;
//    string rol_key;
//    for (k = 0; k < 28; k++)rol_key = rol_key + '0';
//    while (count > 0) {
//        for (l = 0; l < 28; l++) {
//            if (l == 0)j = 27;
//            else {
//                j = l - 1;
//            }
//            rol_key[j] = key[l];
//        }
//        key = rol_key;
//        count--;
//    }
//    return rol_key;
//}
//
//string fourty_eight_bit_key(string C, string D, int pc2[6][8]) {
//    int fe_bin_key_index = 0, concat_key_index = 0, i, j, k;
//    string fe_bin_key, concat_keys = C + D;
//    for (i = 0; i < 48; i++)fe_bin_key = fe_bin_key + '0';
//    for (i = 0; i < 6; i++) {
//        for (j = 0; j < 8; j++) {
//            concat_key_index = pc2[i][j] - 1;
//            fe_bin_key[fe_bin_key_index] = concat_keys[concat_key_index];
//            fe_bin_key_index++;
//        }
//    }
//    return fe_bin_key;
//}
//
//string initial_permuted_msg(string msg, int ip[8][8]) {
//    int ip_msg_index = 0, msg_index = 0, i, j;
//    string ip_msg;
//    for (i = 0; i < 64; i++)ip_msg = ip_msg + '0';
//    for (i = 0; i < 8; i++) {
//        for (j = 0; j < 8; j++) {
//            msg_index = ip[i][j] - 1;
//            ip_msg[ip_msg_index] = msg[msg_index];
//            ip_msg_index++;
//        }
//    }
//    return ip_msg;
//}
//
//string expanded_msg(string R, int ep[8][6]) {
//    int ep_msg_index = 0, R_index = 0, i, j;
//    string ep_msg;
//    for (i = 0; i < 48; i++)ep_msg = ep_msg + '0';
//    for (i = 0; i < 8; i++) {
//        for (j = 0; j < 6; j++) {
//            R_index = ep[i][j] - 1;
//            ep_msg[ep_msg_index] = R[R_index];
//            ep_msg_index++;
//        }
//    }
//    return ep_msg;
//}
//
//string xored_msg(string ep_msg, string fe_key) {
//    int xor_val, i, len = ep_msg.length();
//    char holder[len];
//    string xored_msg;
//
//    for (i = 0; i < len; i++) {
//        xor_val = ((fe_key[i] - '0') ^ (ep_msg[i] - '0'));
//        itoa(xor_val, holder, 10);
//        xored_msg = xored_msg + holder;
//    }
//    return xored_msg;
//}
//
//string substitution_function(string xored_message, int sbox[][4][16]) {
//    string thirty_two_bit_msg;
//    int index = 0, len = 6;
//    for (int i = 0; i < 48; i += 6) {
//        thirty_two_bit_msg = thirty_two_bit_msg + process_string(xored_message.substr(i, len), sbox, index);
//        index++;
//    }
//    return thirty_two_bit_msg;
//}
//
//string permuted_message(string thirty_two_bit_msg, int pf[4][8]) {
//    int index = 0, thirty_two_bit_msg_index = 0, i, j;
//    string permuted_msg;
//    for (i = 0; i < thirty_two_bit_msg.length(); i++)permuted_msg = permuted_msg + '0';
//    for (i = 0; i < 4; i++) {
//        for (j = 0; j < 8; j++) {
//            thirty_two_bit_msg_index = pf[i][j] - 1;
//            permuted_msg[index] = thirty_two_bit_msg[thirty_two_bit_msg_index];
//            index++;
//        }
//    }
//    return permuted_msg;
//}
//
//string inverse_ip_msg(string reversed_msg, int inv_ip[8][8]) {
//    int inv_msg_index = 0, index = 0, i, j;
//    string inv_msg = "";
//    for (i = 0; i < 64; i++)inv_msg = inv_msg + '0';
//    for (i = 0; i < 8; i++) {
//        for (j = 0; j < 8; j++) {
//            index = inv_ip[i][j] - 1;
//            inv_msg[inv_msg_index] = reversed_msg[index];
//            inv_msg_index++;
//        }
//    }
//    return inv_msg;
//}
//
//string des_process(string message, string key, bool encrypt) {
//    string bin_key, input;
//    input = std::move(message);
//    bin_key = std::move(key);
//
//    string fs_key = fifty_six_bit_key(bin_key, pc1);
//    cout << "Fifty Six Bit Key:\n" << fs_key << endl;
//
//    string ip_msg = initial_permuted_msg(input, ip);
//    cout << "IP message:\n" << ip_msg << endl;
//
//    string Lo = ip_msg.substr(0, 32);
//    cout << "\nL[" << 0 << "]:" << Lo << endl;
//
//    string Ro = ip_msg.substr(32, 64);
//    cout << "R[" << 0 << "]:" << Ro << endl;
//
//    string Co = fs_key.substr(0, 28);
//
//    string Do = fs_key.substr(28, 56);
//
//    int round = 16;
//    string key_holder[round], fe_key;
//    for (int i = 0; i < round; i++) {
//        int iteration = i;
//        string C1 = rol_keys(Co, rotating_schedule, iteration % round);
//        string D1 = rol_keys(Do, rotating_schedule, iteration % round);
//
//        fe_key = fourty_eight_bit_key(C1, D1, pc2);
//        key_holder[i] = fe_key;
//
//        Co = C1;
//        Do = D1;
//    }
//
//    int i = 0;
//    while (round > 0) {
//        cout << "\nRound:" << i + 1;
//
//        string ep_msg = expanded_msg(Ro, ep);
//
//        if (!encrypt) {
//            fe_key = "";
//            for (int j = 0; j < 48; j++)fe_key = fe_key + key_holder[round - 1][j];
//            cout << "\nkey[" << round << "]:\n" << fe_key << endl;
//        } else {
//            fe_key = "";
//            for (int j = 0; j < 48; j++)fe_key = fe_key + key_holder[i][j];
//            cout << "\nkey[" << i + 1 << "]:\n" << fe_key << endl;
//        }
//
//        string xored_message = xored_msg(ep_msg, fe_key);
//        string substituted_msg = substitution_function(xored_message, sbox);
//        cout << "Substituted Message(S-Box outputs):\n" << substituted_msg << endl << endl;
//
//        string permuted_msg = permuted_message(substituted_msg, pf);
//        cout << "Permuted message(f(R[" << i << "],K[" << i + 1 << "])):\n" << permuted_msg << endl << endl;
//
//        string L1 = Ro;
//        cout << "L[" << i + 1 << "]:" << L1 << endl;
//
//        string R1 = xored_msg(Lo, permuted_msg);
//        cout << "R[" << i + 1 << "]:" << R1 << endl;
//
//        Lo = L1;
//        Ro = R1;
//
//        round--;
//        i++;
//    }
//
//    string reversed_msg = Ro + Lo;
//    cout << "\nR+L:\n" << reversed_msg << endl;
//
//    string des_encrypted_msg = inverse_ip_msg(reversed_msg, inv_ip);
//    cout << "DES Encrypted/Decrypted Binary Message:\n" << des_encrypted_msg << endl;
//
//    return des_encrypted_msg;
//
//}
//
//bool input_verifier(const string &message) {
//    return message.length() == 8;
//}
//
//vector<string> getBlocks(string &binaryString) {
//    vector<string> blocks;
//    string word;
//    for (char _char : binaryString) {
//        word += _char;
//        if (word.length() == 64) {
//            blocks.push_back(word);
//            word = "";
//        }
//    }
//    return blocks;
//}

int main() {
    string plainText, key;
    cout << "Enter plain text" << endl;
    cin >> plainText;
    string binaryString = TextToBinaryString(plainText);
    uint missingBitsCount = (64 - binaryString.length() % 64);

    string correctBinaryString;

    if (missingBitsCount != 64) {
        string missingBits(missingBitsCount, '0');
        correctBinaryString = missingBits + binaryString;
    } else {
        correctBinaryString = binaryString;
    }
    vector<string> encodeBlocks;
    encodeBlocks = getBlocks(correctBinaryString);

    char question;
    cout << "Y/N" << endl;
    cin >> question;
    if (question == 'y') {
        while (true) {
            cout << "Enter the key " << endl;
            cin >> key;
            bool check = input_verifier(key);
            if (check) break;
            else {
                cout << "Wrong Input" << endl;
            }
        }
    } else {
        key = "12345678";
    }

    cout << "Plain text:" << endl;
    cout << plainText << endl;

    string binaryEncodedText;

    for (vector<string>::const_iterator i = encodeBlocks.begin(); i != encodeBlocks.end(); ++i) {
        cout << *i << endl;
        string desString = *i;

        string binString = TextToBinaryString(desString);
        string binKey = TextToBinaryString(key);
        string enc_msg = des_process(binString, binKey, true);
        cout << "DES Encrypted Message:" << BinaryToString(enc_msg) << endl;
        binaryEncodedText += enc_msg;
    }

    cout << "Encrypted text:" << endl;
    string encodedText;
    encodedText = BinaryToString(binaryEncodedText);
    cout << encodedText << endl;

    vector<string> decodeBlocks;
    decodeBlocks = getBlocks(binaryEncodedText);
    string decodedText;
    for (vector<string>::const_iterator i = decodeBlocks.begin(); i != decodeBlocks.end(); ++i) {
        string desString = *i;
        string binString = TextToBinaryString(desString);
        string binKey = TextToBinaryString(key);
        string de_msg = des_process(desString, binKey, false);
        cout << "DES Decrypted Message:" << BinaryToString(de_msg) << endl;
        decodedText += de_msg;
    }
    cout << "Decrypted text:" << endl;
    cout<< decodedText;
    return 0;
}



