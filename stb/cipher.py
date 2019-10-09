import copy

from constants import H_TABLE
from utils import *


class BeLT:
    def __init__(self, encode_key):
        encode_key = string_to_bit_array(encode_key)
        self.sub_keys = nsplit(encode_key, 32)

    @staticmethod
    def H_get_data_from_table(val):
        if '0x' in val:
            val = val[2:]
            if len(val) > 2:
                raise ValueError('cannot transfer data from table')
            elif len(val) == 1:
                return H_TABLE[int('0x0', 16)][int(val[0], 16)]
        return H_TABLE[int(val[0], 16)][int(val[1], 16)]

    @staticmethod
    def mod_32(a, b, is_plus=True):
        int_a = bit_to_int(a)
        int_b = bit_to_int(b)
        if is_plus:
            int_result = (int_a + int_b) % (2 ** 32)
        else:
            int_result = (int_a - int_b) % (2 ** 32)
        result = int_to_bit(int_result)
        while len(result) < 32:
            result.insert(0, 0)
        return result

    def G_transition(self, data, num):
        int_data = nsplit(data, 8)
        new_data = []
        for val in int_data:
            int_val = bit_to_int(val)
            hex_val = str(hex(int_val))
            new_data.append(self.H_get_data_from_table(hex_val))

        for i in range(len(new_data)):
            temp = int_to_bit(new_data[i])
            while len(temp) < 8:
                temp.insert(0, 0)
            new_data[i] = temp

        new_data = [item for sublist in new_data for item in sublist]

        int_s = bit_to_int(new_data)
        int_s = ((int_s >> (32 - num)) | (int_s << num)) & 0xFFFFFFFF
        result = int_to_bit(int_s)
        while len(result) < 32:
            result.insert(0, 0)
        return result

    @staticmethod
    def bit_xor(arr1, arr2):
        bit_s = []
        for index, item in enumerate(arr1):
            bit_s.append(arr1[index] ^ arr2[index])
        return bit_s

    def calc(self, i, minus, part, g_index, all_keys):
        sub_key = copy.deepcopy(all_keys[7 * i - minus - 1])
        temp = self.mod_32(part, sub_key)
        temp = self.G_transition(temp, g_index)
        return temp

    def encode(self, raw_text):
        raw_text_bits = string_to_bit_array(raw_text)
        raw_splitted_text = nsplit(raw_text_bits, 32)
        a = raw_splitted_text[0]
        b = raw_splitted_text[1]
        c = raw_splitted_text[2]
        d = raw_splitted_text[3]

        all_keys = self.sub_keys * 7

        for i in range(1, 9):
            temp = self.calc(i, minus=6, part=a, g_index=5, all_keys=all_keys)
            b = self.bit_xor(b, temp)

            # step 2
            temp = self.calc(i, minus=5, part=d, g_index=21, all_keys=all_keys)
            c = self.bit_xor(c, temp)

            # step 3
            temp = self.calc(i, minus=4, part=b, g_index=13, all_keys=all_keys)
            a = self.mod_32(a, temp, is_plus=False)

            # step 4
            sub_key = copy.deepcopy(all_keys[7 * i - 3 - 1])
            temp = self.mod_32(b, c)
            temp = self.mod_32(temp, sub_key)
            temp = self.G_transition(temp, 21)
            val_i = i % (2 ** 32)
            val_i = int_to_bit(val_i)
            while len(val_i) < 32:
                val_i.insert(0, 0)
            e = self.bit_xor(temp, val_i)

            # step 5
            b = self.mod_32(b, e)

            # step 6
            c = self.mod_32(c, e, is_plus=False)

            # step 7
            temp = self.calc(i, minus=2, part=c, g_index=13, all_keys=all_keys)
            d = self.mod_32(d, temp)

            # step 8
            temp = self.calc(i, minus=1, part=a, g_index=21, all_keys=all_keys)
            b = self.bit_xor(b, temp)

            # step 9
            temp = self.calc(i, minus=0, part=d, g_index=5, all_keys=all_keys)
            c = self.bit_xor(c, temp)

            # step 10
            a, b = b, a

            # step 11
            c, d = d, c

            # step 12
            b, c = c, b

        encoded_text = b + d + a + c
        encoded_text = bit_array_to_string(encoded_text)
        return encoded_text

    def decode(self, encoded_text):
        raw_text_bits = string_to_bit_array(encoded_text)
        raw_splitted_text = nsplit(raw_text_bits, 32)
        a = raw_splitted_text[0]
        b = raw_splitted_text[1]
        c = raw_splitted_text[2]
        d = raw_splitted_text[3]

        all_keys = self.sub_keys * 7

        for i in range(8, 0, -1):
            # step 1
            temp = self.calc(i, minus=0, part=a, g_index=5, all_keys=all_keys)
            b = self.bit_xor(b, temp)

            # step 2
            temp = self.calc(i, minus=1, part=d, g_index=21, all_keys=all_keys)
            c = self.bit_xor(c, temp)

            # step 3
            temp = self.calc(i, minus=2, part=b, g_index=13, all_keys=all_keys)
            a = self.mod_32(a, temp, is_plus=False)

            # step 4
            sub_key = copy.deepcopy(all_keys[7 * i - 3 - 1])
            temp = self.mod_32(b, c)
            temp = self.mod_32(temp, sub_key)
            temp = self.G_transition(temp, 21)
            val_i = i % (2 ** 32)
            val_i = int_to_bit(val_i)
            while len(val_i) < 32:
                val_i.insert(0, 0)
            e = self.bit_xor(temp, val_i)

            # step 5
            b = self.mod_32(b, e)

            # step 6
            c = self.mod_32(c, e, is_plus=False)

            # step 7
            temp = self.calc(i, minus=4, part=c, g_index=13, all_keys=all_keys)
            d = self.mod_32(d, temp)

            # step 8
            temp = self.calc(i, minus=5, part=a, g_index=21, all_keys=all_keys)
            b = self.bit_xor(b, temp)

            # step 9
            temp = self.calc(i, minus=6, part=d, g_index=5, all_keys=all_keys)
            c = self.bit_xor(c, temp)

            # step 10
            a, b = b, a

            # step 11
            c, d = d, c

            # step 12
            a, d = d, a

        decoded_text = c + a + d + b
        decoded_text = bit_array_to_string(decoded_text)
        return decoded_text

    def simple_change(self, raw_text, is_encode=True):
        text = []
        raw_text_splitted = nsplit(raw_text, 16)
        for part in raw_text_splitted:
            if is_encode:
                text.append(self.encode(part))
            else:
                text.append(self.decode(part))

        text = ''.join(text)
        return text

    def block_chaining(self, raw_text, sync, is_encode=True):
        text = []
        raw_text_splitted = nsplit(raw_text, 16)
        temp = self.encode(sync)
        for part in raw_text_splitted:
            if is_encode:
                res = bit_array_to_string(self.bit_xor(string_to_bit_array(temp), string_to_bit_array(part)))
                encoded_part = self.encode(res)
                text.append(encoded_part)
                temp = encoded_part
            else:
                bit_temp = string_to_bit_array(temp)
                ans = bit_array_to_string(self.bit_xor(string_to_bit_array(self.decode(part)), bit_temp))
                text.append(ans)
                temp = part

        text = ''.join(text)
        return text

    def cipher_feedback(self, raw_text, sync, is_encode=True):
        splitted_raw_text = nsplit(raw_text, 16)
        text = []
        temp = sync
        for part in splitted_raw_text:
            enc_temp = self.encode(temp)
            enc_sliced = enc_temp[:len(part)]
            ans = bit_array_to_string(self.bit_xor(string_to_bit_array(part), string_to_bit_array(enc_sliced)))
            text.append(ans)
            if is_encode:
                temp = ans
            else:
                temp = part

        text = ''.join(text)
        return text

    def counter(self, raw_text, sync):
        splitted_raw_text = nsplit(raw_text, 16)
        text = []
        s = self.encode(sync)
        ones = [1 for _ in range(128)]
        for part in splitted_raw_text:
            s = self.mod_32(string_to_bit_array(s), ones)
            s = self.encode(s)
            sliced_s = s[:len(part)]
            ans = bit_array_to_string(self.bit_xor(string_to_bit_array(part), string_to_bit_array(sliced_s)))
            text.append(ans)

        text = ''.join(text)
        return text

