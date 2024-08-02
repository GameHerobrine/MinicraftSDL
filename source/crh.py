with open("icons.rimg", "rb") as f:
	pxls = f.read()

with open("icons.c", "w") as f:
	f.write("#define t (char)")
	f.write("const SpriteSheet icons_spritesheet = {256, 256,")
	for px in pxls:
		f.write("t "+str(px))
		f.write(",")
	f.write("};")

