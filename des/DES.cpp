//
// Created by whyko on 04.10.2019.
//

#include <string>
#include <vector>
#include "DES.h"
#include "constants.h"
#include "utils.h"

using namespace std;

bool isEnabled = false;

DES::DES(string key) {
    keygen(key);
}

string DES::encrypt(string block) {
    return des(block, false);
}

string DES::decrypt(string block) {
    return des(block, true);
}

string DES::processString(string substring, int p) {
    string row, col;
    for (int i = 0; i < 6; i++) {
        if (i == 0 || i == 5)row = row + substring[i];
        else {
            col = col + substring[i];
        }
    }
    int r = binaryToDecimal(row);
    int c = binaryToDecimal(col);
    int s_box_pos = sbox[p][r][c];
    string fbitBinStr = "0000";
    int len = decimalToBinary(s_box_pos).length();
    string bin = decimalToBinary(s_box_pos);

    for (int i = 0; i < len; i++) {
        fbitBinStr[i + (4 - len)] = bin[i];
    }
    return fbitBinStr;
}

string DES::expandedMessage(string R) {
    int epMsgIndex = 0, R_index = 0, i, j;
    string epMsg;
    for (i = 0; i < 48; i++)epMsg = epMsg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 6; j++) {
            R_index = ep[i][j] - 1;
            epMsg[epMsgIndex] = R[R_index];
            epMsgIndex++;
        }
    }
    return epMsg;
}

string DES::xoredMessage(string epMsg, string feKey) {
    int xorVal, i, len = epMsg.length();
    char holder[len];
    string xoredMsg;

    for (i = 0; i < len; i++) {
        xorVal = ((feKey[i] - '0') ^ (epMsg[i] - '0'));
        itoa(xorVal, holder, 10);
        xoredMsg = xoredMsg + holder;
    }
    return xoredMsg;
}

string DES::substitutionFunction(string xoredMessage) {
    string thirtyTwoBitMsg;
    int index = 0, len = 6;
    for (int i = 0; i < 48; i += 6) {
        thirtyTwoBitMsg = thirtyTwoBitMsg + processString(xoredMessage.substr(i, len), index);
        index++;
    }
    return thirtyTwoBitMsg;
}

string permuted_message(string thirtyTwoBitMsg) {
    int index = 0, thirtyTwoBitMsgIndex = 0, i, j;
    string permutedMsg;
    for (i = 0; i < thirtyTwoBitMsg.length(); i++)permutedMsg = permutedMsg + '0';
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 8; j++) {
            thirtyTwoBitMsgIndex = pf[i][j] - 1;
            permutedMsg[index] = thirtyTwoBitMsg[thirtyTwoBitMsgIndex];
            index++;
        }
    }
    return permutedMsg;
}

string DES::getKeys48(string C, string D) {
    int feBinKeyIndex = 0, concatKeyIndex = 0, i, j, k;
    string feBinKey, concatKeys = C + D;
    for (i = 0; i < 48; i++)feBinKey = feBinKey + '0';
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 8; j++) {
            concatKeyIndex = pc2[i][j] - 1;
            feBinKey[feBinKeyIndex] = concatKeys[concatKeyIndex];
            feBinKeyIndex++;
        }
    }
    return feBinKey;
}

string DES::rolKeys(string key, int i) {
    int count = rotatingSchedule[i], l, j, k;
    string rolKey;
    for (k = 0; k < 28; k++)rolKey = rolKey + '0';
    while (count > 0) {
        for (l = 0; l < 28; l++) {
            if (l == 0)j = 27;
            else {
                j = l - 1;
            }
            rolKey[j] = key[l];
        }
        key = rolKey;
        count--;
    }
    return rolKey;
}

void DES::keygen(string key) {
    string fsKey = getKey56(key);
    logToConsole(isEnabled, "Fifty Six Bit Key: \n", fsKey);

    string Co = fsKey.substr(0, 28);
    string Do = fsKey.substr(28, 56);

    string feKey;
    for (int i = 0; i < 16; i++) {
        int iteration = i;
        string C1 = rolKeys(Co, iteration % 16);
        string D1 = rolKeys(Do, iteration % 16);

        feKey = getKeys48(C1, D1);
        sub_key[i] = feKey;

        Co = C1;
        Do = D1;
    }
}


string DES::getKey56(string key) {
    int i, j, k, binKeyIndex = 0, index = 0;
    string fsBinKey;

    for (k = 0; k < 56; k++)fsBinKey = fsBinKey + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 7; j++) {
            index = pc1[i][j] - 1;
            fsBinKey[binKeyIndex] = key[index];
            binKeyIndex++;
        }
    }
    return fsBinKey;
}


string DES::des(string message, bool encrypt) {
    string input;
    input = std::move(message);

    string ip_msg = ip(input);
    logToConsole(isEnabled, "IP message:\n", ip_msg);

    string Lo = ip_msg.substr(0, 32);
    logToConsole(isEnabled, "\nL[0]: ", Lo);

    string Ro = ip_msg.substr(32, 64);
    logToConsole(isEnabled, "\nR[0]: ", Ro);

    string feKey;

    for (int r = 0; r < 16; r++) {
        logToConsole(isEnabled, "\nRound: ", to_string(r+1));
        string epMsg = expandedMessage(Ro);

        if (!encrypt) {
            feKey = "";
            for (int j = 0; j < 48; j++)feKey = feKey + sub_key[16 - r - 1][j];
            logToConsole(isEnabled, "\nKey: ", feKey);
        } else {
            feKey = "";
            for (int j = 0; j < 48; j++)feKey = feKey + sub_key[r][j];
            logToConsole(isEnabled, "\nKey: ", feKey);
        }

        string xoredMsg = xoredMessage(epMsg, feKey);
        string substitutedMsg = substitutionFunction(xoredMsg);
        logToConsole(isEnabled, "Substituted Message(S-Box outputs):\n", substitutedMsg);

        string permutedMsg = permuted_message(substitutedMsg);
        logToConsole(isEnabled, "Permuted message:\n", permutedMsg);
        string L1 = Ro;
        string R1 = xoredMessage(Lo, permutedMsg);
        Lo = L1;
        Ro = R1;
    }


    string reversedMsg = Ro + Lo;

    logToConsole(isEnabled, "R+L\n", reversedMsg);

    string desEncryptedMsg = fp(reversedMsg);
    logToConsole(isEnabled, "DES Encrypted/Decrypted Binary Message:\n", reversedMsg);

    return desEncryptedMsg;

}

string DES::ip(string msg) {
    int ipMsgIndex = 0, msgIndex = 0, i, j;
    string ipMsg;
    for (i = 0; i < 64; i++) ipMsg = ipMsg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            msgIndex = IP[i][j] - 1;
            ipMsg[ipMsgIndex] = msg[msgIndex];
            ipMsgIndex++;
        }
    }
    return ipMsg;
}

string DES::fp(string reversedMsg) {
    int invMsgIndex = 0, index = 0, i, j;
    string invMsg = "";
    for (i = 0; i < 64; i++) invMsg = invMsg + '0';
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            index = FP[i][j] - 1;
            invMsg[invMsgIndex] = reversedMsg[index];
            invMsgIndex++;
        }
    }
    return invMsg;
}