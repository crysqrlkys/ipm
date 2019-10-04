//
// Created by whyko on 04.10.2019.
//

#include <iostream>
#include <string>
#include <vector>
#include "DES.h"
#include "constants.h"
#include "utils.h"

using namespace std;

DES::DES(string key) {
    keygen(key);
}

string DES::encrypt(string block) {
    return des(block, false);
}

string DES::decrypt(string block) {
    return des(block, true);
}

string DES::process_string(string substring, int p) {
    string row, col;
    for (int i = 0; i < 6; i++) {
        if (i == 0 || i == 5)row = row + substring[i];
        else {
            col = col + substring[i];
        }
    }
    int r = bin_to_dec(row);
    int c = bin_to_dec(col);
    int s_box_pos = sbox[p][r][c];
    string fbit_bin_str = "0000";
    int len = dec_to_bin(s_box_pos).length();
    string bin = dec_to_bin(s_box_pos);

    for (int i = 0; i < len; i++) {
        fbit_bin_str[i + (4 - len)] = bin[i];
    }
    return fbit_bin_str;
}

string DES::expanded_msg(string R) {
    int ep_msg_index = 0, R_index = 0, i, j;
    string ep_msg;
    for (i = 0; i < 48; i++)ep_msg = ep_msg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 6; j++) {
            R_index = ep[i][j] - 1;
            ep_msg[ep_msg_index] = R[R_index];
            ep_msg_index++;
        }
    }
    return ep_msg;
}

string DES::xored_msg(string ep_msg, string fe_key) {
    int xor_val, i, len = ep_msg.length();
    char holder[len];
    string xored_msg;

    for (i = 0; i < len; i++) {
        xor_val = ((fe_key[i] - '0') ^ (ep_msg[i] - '0'));
        itoa(xor_val, holder, 10);
        xored_msg = xored_msg + holder;
    }
    return xored_msg;
}

string DES::substitution_function(string xored_message) {
    string thirty_two_bit_msg;
    int index = 0, len = 6;
    for (int i = 0; i < 48; i += 6) {
        thirty_two_bit_msg = thirty_two_bit_msg + process_string(xored_message.substr(i, len), index);
        index++;
    }
    return thirty_two_bit_msg;
}

string permuted_message(string thirty_two_bit_msg) {
    int index = 0, thirty_two_bit_msg_index = 0, i, j;
    string permuted_msg;
    for (i = 0; i < thirty_two_bit_msg.length(); i++)permuted_msg = permuted_msg + '0';
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            thirty_two_bit_msg_index = pf[i][j] - 1;
            permuted_msg[index] = thirty_two_bit_msg[thirty_two_bit_msg_index];
            index++;
        }
    }
    return permuted_msg;
}

string DES::getKeys48(string C, string D) {
    int fe_bin_key_index = 0, concat_key_index = 0, i, j, k;
    string fe_bin_key, concat_keys = C + D;
    for (i = 0; i < 48; i++)fe_bin_key = fe_bin_key + '0';
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 8; j++) {
            concat_key_index = pc2[i][j] - 1;
            fe_bin_key[fe_bin_key_index] = concat_keys[concat_key_index];
            fe_bin_key_index++;
        }
    }
    return fe_bin_key;
}

string DES::rol_keys(string key, int i) {
    int count = rotating_schedule[i], l, j, k;
    string rol_key;
    for (k = 0; k < 28; k++)rol_key = rol_key + '0';
    while (count > 0) {
        for (l = 0; l < 28; l++) {
            if (l == 0)j = 27;
            else {
                j = l - 1;
            }
            rol_key[j] = key[l];
        }
        key = rol_key;
        count--;
    }
    return rol_key;
}

void DES::keygen(string key) {
    string fs_key = getKey56(key);
    cout << "Fifty Six Bit Key:\n" << fs_key << endl;

    string Co = fs_key.substr(0, 28);
    string Do = fs_key.substr(28, 56);

    string fe_key;
    for (int i = 0; i < 16; i++) {
        int iteration = i;
        string C1 = rol_keys(Co, iteration % 16);
        string D1 = rol_keys(Do, iteration % 16);

        fe_key = getKeys48(C1, D1);
        sub_key[i] = fe_key;

        Co = C1;
        Do = D1;
    }
}


string DES::getKey56(string key) {
    int i, j, k, bin_key_index = 0, index = 0;
    string fs_bin_key;

    for (k = 0; k < 56; k++)fs_bin_key = fs_bin_key + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 7; j++) {
            index = pc1[i][j] - 1;
            fs_bin_key[bin_key_index] = key[index];
            bin_key_index++;
        }
    }
    return fs_bin_key;
}


string DES::des(string message, bool encrypt) {
    string input;
    input = std::move(message);

    string ip_msg = ip(input);
    cout << "IP message:\n" << ip_msg << endl;

    string Lo = ip_msg.substr(0, 32);
    cout << "\nL[" << 0 << "]:" << Lo << endl;

    string Ro = ip_msg.substr(32, 64);
    cout << "R[" << 0 << "]:" << Ro << endl;

    string fe_key;

    for (int r = 0; r < 16; r++) {
        cout << "\nRound:" << r + 1;
        string ep_msg = expanded_msg(Ro);

        if (!encrypt) {
            fe_key = "";
            for (int j = 0; j < 48; j++)fe_key = fe_key + sub_key[16 - r - 1][j];
            cout << "\nkey[" << 16-r << "]:\n" << fe_key << endl;
        } else {
            fe_key = "";
            for (int j = 0; j < 48; j++)fe_key = fe_key + sub_key[r][j];
            cout << "\nkey[" << r + 1 << "]:\n" << fe_key << endl;
        }

        string xored_message = xored_msg(ep_msg, fe_key);
        string substituted_msg = substitution_function(xored_message);
        cout << "Substituted Message(S-Box outputs):\n" << substituted_msg << endl <<
             endl;

        string permuted_msg = permuted_message(substituted_msg);
        cout << "Permuted message(f(R[" << r << "],K[" << r + 1 << "])):\n" << permuted_msg << endl <<
             endl;

        string L1 = Ro;
        string R1 = xored_msg(Lo, permuted_msg);
        Lo = L1;
        Ro = R1;
    }


    string reversed_msg = Ro + Lo;
    cout << "\nR+L:\n" << reversed_msg << endl;

    string des_encrypted_msg = fp(reversed_msg);
    cout << "DES Encrypted/Decrypted Binary Message:\n" << des_encrypted_msg << endl;

    return des_encrypted_msg;

}

string DES::ip(string msg) {
    int ip_msg_index = 0, msg_index = 0, i, j;
    string ip_msg;
    for (i = 0; i < 64; i++)ip_msg = ip_msg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            msg_index = IP[i][j] - 1;
            ip_msg[ip_msg_index] = msg[msg_index];
            ip_msg_index++;
        }
    }
    return ip_msg;
}

string DES::fp(string reversed_msg) {
    int inv_msg_index = 0, index = 0, i, j;
    string inv_msg = "";
    for (i = 0; i < 64; i++)inv_msg = inv_msg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            index = FP[i][j] - 1;
            inv_msg[inv_msg_index] = reversed_msg[index];
            inv_msg_index++;
        }
    }
    return inv_msg;
}