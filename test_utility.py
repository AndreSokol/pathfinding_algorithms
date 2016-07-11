from PIL import Image
import os, sys


def drawSquare(xOffset, yOffset, color):
    global im, BLOCK_SIZE
    for i in range(xOffset * BLOCK_SIZE, (xOffset + 1) * BLOCK_SIZE):
        for j in range(yOffset * BLOCK_SIZE, (yOffset + 1) * BLOCK_SIZE):
            im.putpixel((i, j), color)


if len(sys.argv) != 3:
    print("Usage: " + sys.argv[0] + " <path_to_xml_log_file> <cell_size_in_pixels>")
    exit()

BLOCK_SIZE = int(sys.argv[2])
BLACK_COLOR = (0, 0, 0)
WHITE_COLOR = (255, 255, 255)
RED_COLOR = (255, 0, 0)

pathToTestedFile = os.path.abspath(sys.argv[1])
print("Generating from file: '" + pathToTestedFile + "'...")
testedFile = open(pathToTestedFile)

while testedFile.readline().strip() != "<path>":
    continue

newline = testedFile.readline().strip()
mapContainer = []
while newline != "</path>":
    newline = newline[newline.find(">") + 1:newline.rfind("<")]
    mapContainer.append(newline.split())
    newline = testedFile.readline().strip()


im = Image.new("RGB", (len(mapContainer) * BLOCK_SIZE, len(mapContainer[0]) * BLOCK_SIZE), "white")

for i in range(len(mapContainer)):
    for j in range(len(mapContainer[0])):
        if mapContainer[i][j] == '1':
            drawSquare(j, i, BLACK_COLOR) # SWAP HERE !!!
        elif mapContainer[i][j] == '*':
            drawSquare(j, i, RED_COLOR) # SWAP HERE !!!

im.save("test_image.bmp")

print("Image generated")