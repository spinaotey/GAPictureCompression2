import sys
from PIL import Image
import csv

im = Image.open(sys.argv[1])
L = list(im.getdata())
for i,l in enumerate(L):
    L[i] = list(l)
with open('target.csv','w') as f:
    f.write(str(im.width)+","+str(im.height)+"\n")
    writer = csv.writer(f)
    writer.writerows(L)
