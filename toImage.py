from PIL import Image
from sys import argv

im = Image.new("RGB",size=(int(argv[1]),int(argv[2])))
with open(argv[3]+".dat","r") as f:
    p = f.read().split("\n")
p.pop();
im.putdata(tuple(map(eval,p)))
im.save(argv[3]+".png")
