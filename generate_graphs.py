#!/usr/bin/python
import os
import sys
from glob import glob

print("""Proste umistit vygenerovane txt do grafy/txt a pak spustit
        skript. Vysledne PDF je v grafy/pdf""")

def parse_file(txtfiles):

    for fname in txtfiles:
        print("Processing this file: ", fname)

        komplines = []
        with open(fname, "r") as ifile:
            komplines = ifile.readlines()

        newstr = 'digraph G {\nnode [fontname = "DejavuSans"];\n'
        for line in komplines:
            sli = line.split()
            newstr += "{0} -> {1};\n".format(sli[0],sli[1])

        newstr += "\n}"

        outname = fname.split(".")[0]

        with open("../dot/{0}.dot".format(outname), "w", encoding="utf8") as ofile:
            ofile.write(newstr)

        os.system("dot -Tpdf ../dot/{0}.dot -o ../pdf/{0}.pdf".format(outname))
        print("Output PDF: {0}.pdf. \nKeeping {0}.dot file".format(outname))

gdir = "/home/tereza/Documents/Programming/cowprog/treepripri/grafy/txt"
os.chdir(gdir)
alltxtf = glob("*.txt")
parse_file(alltxtf)
