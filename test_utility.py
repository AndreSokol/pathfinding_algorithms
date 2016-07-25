from PIL import Image
import os, sys


def drawSquare(xOffset, yOffset, color):
    global im, BLOCK_SIZE
    for i in range(xOffset * BLOCK_SIZE, (xOffset + 1) * BLOCK_SIZE):
        for j in range(yOffset * BLOCK_SIZE, (yOffset + 1) * BLOCK_SIZE):
            im.putpixel((i, j), color)


if len(sys.argv) not in (3, 4):
    print("Usage: " + sys.argv[0] + " <path_to_xml_log_file> <cell_size_in_pixels> [-map_only]")
    exit()

MAP_ONLY = False
if len(sys.argv) == 4:
    MAP_ONLY = True

BLOCK_SIZE = int(sys.argv[2])
BLACK_COLOR = (0, 0, 0)
WHITE_COLOR = (255, 255, 255)
RED_COLOR = (255, 0, 0)
YELLOW_COLOR = (255, 191, 0)

pathToTestedFile = os.path.abspath(sys.argv[1])
print("Generating from file: '" + pathToTestedFile + "'...")
testedFile = open(pathToTestedFile)

if MAP_ONLY:
    newline = testedFile.readline().strip()
    while newline != "<grid>":
        if newline == "":
            print("Error!")
            exit()
        newline = testedFile.readline().strip()

    newline = testedFile.readline().strip()
    mapContainer = []
    while newline != "</grid>":
        newline = newline[newline.find(">") + 1:newline.rfind("<")]
        mapContainer.append(newline.split())
        newline = testedFile.readline().strip()

else:
    newline = testedFile.readline().strip()
    while newline != "<path>":
        if newline == "":
            print("No path found!")
            exit()
        newline = testedFile.readline().strip()

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
            drawSquare(j, i, BLACK_COLOR)  # SWAP HERE !!!
        elif mapContainer[i][j] == '*':
            drawSquare(j, i, YELLOW_COLOR)  # SWAP HERE !!!
    print((i + 1) / len(mapContainer) * 100, "% generated", sep="")

if MAP_ONLY:
    im.save("test_image.bmp")
    print("Image generated")
    exit()

while newline != "<hplevel>":
    newline = testedFile.readline().strip()

hops = []
newline = testedFile.readline().strip()

# draw start point
input_list = newline.split('"')
drawSquare(int(input_list[3]), int(input_list[5]), RED_COLOR)

while newline != "</hplevel>":
    input_list = newline.split('"')
    drawSquare(int(input_list[7]), int(input_list[9]), RED_COLOR)
    newline = testedFile.readline().strip()

im.save("test_image.bmp")

print("Image saved!")
