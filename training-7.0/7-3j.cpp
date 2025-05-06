// https://contest.yandex.ru/contest/74967/problems/C/
def solve(nums):
    n = len(nums)
    max_bits = max(nums).bit_length()
    partity = [0] * max_bits
    masks = [1] * max_bits
    is_full = [False] * n
    total_cnt_1 = 0
    for i in range(1, max_bits):
        masks[i] = masks[i - 1] << 1
    for i, num in enumerate(nums):
        cnt_1 = bin(num).count('1')
        total_cnt_1 += cnt_1
        if cnt_1 == max_bits:
            tmp = nums[i]
            is_full[i] = True
        else:
            tmp = (1 << cnt_1) - 1
            nums[i] = tmp
        for j in range(tmp.bit_length()):
            partity[j] ^= tmp & 1
            tmp >>= 1
    if total_cnt_1 % 2:
        return [-1]
    for i in range(max_bits):
        if partity[i]:
            is_found = False
            for j in range(n):
                tmp = nums[j] >> i
                if is_full[j] or not tmp: 
                    continue
                for k in range(i, max_bits):
                    if not (tmp & 1):
                        partity[i] = 0
                        partity[k] ^= 1
                        nums[j] &= ~masks[i]
                        nums[j] |= masks[k]
                        is_found = True
                        break
                    tmp >>= 1
                if is_found:
                    break
                else:
                    is_full[j] = True
    if any(partity):
        return [-1]
    return nums


n = int(input())
a = list(map(int, input().split()))
b = solve(a)
if b == [-1]:
    print('impossible')
else:
    print(*b)
