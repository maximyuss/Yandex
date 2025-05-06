// https://contest.yandex.ru/contest/74967/problems/J/
import sys

def write_14bit_code(output, code, bit_pos, buffer):
    buffer[0] |= code << bit_pos[0]
    bit_pos[0] += 14
    while bit_pos[0] >= 8:
        output.append(buffer[0] & 0xFF)
        buffer[0] >>= 8
        bit_pos[0] -= 8

def flush_buffer(output, bit_pos, buffer):
    while bit_pos[0] > 0:
        output.append(buffer[0] & 0xFF)
        buffer[0] >>= 8
        bit_pos[0] -= 8

def lzw_compress_14bit(text):
    dict_size = 26
    dictionary = {chr(ord('a') + i): i for i in range(26)}
    
    w = ''
    output = bytearray()
    bit_pos = [0]
    buffer = [0]

    for c in text:
        wc = w + c
        if wc in dictionary:
            w = wc
        else:
            write_14bit_code(output, dictionary[w], bit_pos, buffer)
            if dict_size < (1 << 14):
                dictionary[wc] = dict_size
                dict_size += 1
            w = c
    if w:
        write_14bit_code(output, dictionary[w], bit_pos, buffer)
    
    flush_buffer(output, bit_pos, buffer)
    return output

def lzw_decompress_14bit(data):
    dict_size = 26
    dictionary = [chr(ord('a') + i) for i in range(26)]

    buffer = 0
    bit_pos = 0
    codes = []
    total_bits = len(data) * 8
    bits_read = 0

    for byte in data:
        buffer |= byte << bit_pos
        bit_pos += 8

        while bit_pos >= 14 and bits_read + 14 <= total_bits:
            code = buffer & 0x3FFF
            codes.append(code)
            buffer >>= 14
            bit_pos -= 14
            bits_read += 14

    result = []
    w = dictionary[codes[0]]
    result.append(w)

    for code in codes[1:]:
        if code < dict_size:
            entry = dictionary[code]
        elif code == dict_size:
            entry = w + w[0]
        else:
            entry = ''  # в нормальной ситуации сюда не попадём
        result.append(entry)

        if dict_size < (1 << 14):
            dictionary.append(w + entry[0])
            dict_size += 1
        w = entry

    return ''.join(result)

def parse_byte_string(s):
    return bytearray(map(int, s.strip().split()))

def format_byte_string(data):
    return ' '.join(str(x) for x in data)

def main():
    command = sys.stdin.readline().strip()
    if command == 'pack':
        line = sys.stdin.readline().strip()
        compressed = lzw_compress_14bit(line)
        print(len(compressed))
        print(format_byte_string(compressed))
        sys.stdout.flush()
    else:
        line = sys.stdin.readline()
        line = sys.stdin.readline()
        compressed = parse_byte_string(line)
        decompressed = lzw_decompress_14bit(compressed)
        print(decompressed)
        sys.stdout.flush()

if __name__ == "__main__":
    main()
