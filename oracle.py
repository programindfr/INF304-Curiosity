#!python3

from os import listdir
from subprocess import getoutput

RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"

def test_terrain(folder, filename):
	out = getoutput(f"./test_terrain {folder}/{filename}").split("\n")[1][0]
	print(f"Test {test}", GREEN+"[PASS]"+RESET if test[-1] == out else RED+"[FAIL]"+RESET)

print(YELLOW+"##### Terrains corrects #####"+RESET)
for test in listdir("Terrains_Corrects"):
	test_terrain("Terrains_Corrects", test)

print(YELLOW+"#### Terrains incorrects ####"+RESET)
for test in listdir("Terrains_Incorrects"):
	test_terrain("Terrains_Incorrects", test)
