#!python3

from os import listdir
from subprocess import getoutput

for test in listdir("Terrains"):
	print(f"Test {test}")
	out = getoutput(f"./test_terrain Terrains/{test}").split("\n")[1][0]
	print("[PASS]" if test[-1] == out else "[FAIL]")
