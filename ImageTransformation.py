import generateHenonMap as ghm
from PIL import Image
import os

def pixelManipulation(size,imageName):
    imageMatrix = ghm.getImageMatrix(imageName)
    print("ImageMatrix Rows : %d Cols : %d " % (len(imageMatrix), len(imageMatrix[0])))
    transformationMatrix = ghm.genTransformationMatrix(size)
    print("Transformation Matrix Rows : %d Cols : %d" %(len(transformationMatrix),len(transformationMatrix[0])))


    resultantMatrix = []
    for i in range(size):
        row = []
        for j in range(size):
            try:
                row.append(transformationMatrix[i][j] ^ imageMatrix[i][j])
            except:
                row = [transformationMatrix[i][j] ^ imageMatrix[i][j]]
        try:
            resultantMatrix.append(row)
        except:
            resultantMatrix = [row]

    print("Pixel Manipulated Values : ")
    for rows in resultantMatrix:
         print(rows)


    im = Image.new("L", (size, size))
    pix = im.load()
    for x in range(size):
        for y in range(size):
            pix[x, y] = resultantMatrix[x][y]
    im.save("HenonTransformedImage.bmp", "BMP")
    absPath = os.path.abspath("HenonTransformedImage.bmp")
    return absPath