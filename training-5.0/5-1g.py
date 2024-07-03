# https://contest.yandex.ru/contest/59539/problems/G/
# Solution using simulation and brute force
def model(limit, my_units, enemy_hp, enemy_inc):
    steps = 0
    enemy_units = 0
    while enemy_hp >= limit:
        if enemy_units >= my_units:
            return MyInf
        enemy_hp -= my_units - enemy_units
        enemy_units = 0
        if enemy_hp > 0:
            enemy_units += enemy_inc
        steps += 1
    while enemy_hp > 0:
        if my_units <= 0:
            return MyInf
        if enemy_hp > my_units:
            enemy_hp -= my_units
        else:
            enemy_units = max(enemy_units - (my_units - enemy_hp), 0)
            enemy_hp = 0
        my_units -= enemy_units
        if enemy_hp > 0:
            enemy_units += enemy_inc
        steps += 1
    while enemy_units > 0:
        if my_units <= 0:
            return MyInf
        enemy_units -= my_units
        if enemy_units > 0:
            my_units -= enemy_units
        steps += 1
    return steps

MyInf = 10 ** 9
x = int(input())  # the number of your soldiers at the start of the game
y = int(input())  # the number of barracks health points
p = int(input())  # the number of soldiers produced per round by the barracks
res = MyInf
for i in range(y + 10):
    res = min(res, model(i, x, y, p))
if res == MyInf:
    res = -1
print(res)
