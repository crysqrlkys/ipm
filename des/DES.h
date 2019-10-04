//
// Created by whyko on 04.10.2019.
//

#ifndef DES_DES_H
#define DES_DES_H


using namespace std;

class DES {
public:
    DES(string key);

    string des(string message, bool encrypt);

    string encrypt(string block);

    string decrypt(string block);

protected:
    static string rol_keys(string key, int i);
    static string getKey56(string key);
    static string getKeys48(string C, string D);
    string process_string(string substring, int p);
    string expanded_msg(string R);
    string xored_msg(string ep_msg, string fe_key);
    string substitution_function(string xored_message);

    void keygen(string fs_key);
    static string ip(string block);
    static string fp(string block);
private:
    string sub_key[16];
};

#endif //DES_DES_H
