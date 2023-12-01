from os import listdir
from subprocess import getoutput

#for test in ["vjs", '']:
#	out = getoutput(f"./test_terrain Terrains/{test}")
#	print(f"Debut du test fichier {test} :\n{out}\nFin du test fichier {test}\n\n\n")

for test in listdir("Terrains"):
	out = getoutput(f"./test_terrain Terrains/{test}")
	print(f"Debut du {test} :\n{out}\nFin du {test}\n\n\n")
