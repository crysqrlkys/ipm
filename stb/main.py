from cipher import BeLT

if __name__ == '__main__':
    key = 'sanfksalkfn1esdkmfsdfd23j32fmsdl'
    sync_send = '1a2b3c4d5d6e7f8g'
    stb = BeLT(key)

    print('ECB')
    with open('ecb.txt', 'r+') as f:
        text = f.read()

    enc_data = stb.simple_change(text, is_encode=True)
    print(enc_data)
    dec_data = stb.simple_change(enc_data, is_encode=False)
    print(dec_data)

    print('\nCBC')
    with open('cbc.txt', 'r+') as f:
        text = f.read()

    enc_data = stb.block_chaining(text, sync_send, is_encode=True)
    print(enc_data)
    dec_data = stb.block_chaining(enc_data, sync_send, is_encode=False)
    print(dec_data)

    print('\nCFB')
    with open('cfb.txt', 'r+') as f:
        text = f.read()

    enc_data = stb.cipher_feedback(text, sync_send, is_encode=True)
    print(enc_data)
    dec_data = stb.cipher_feedback(enc_data, sync_send, is_encode=False)
    print(dec_data)

    print('\nCTR')
    with open('ctr.txt', 'r+') as f:
        text = f.read()

    enc_data = stb.counter(text, sync_send)
    print(enc_data)
    dec_data = stb.counter(enc_data, sync_send)
    print(dec_data)