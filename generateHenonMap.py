from PIL import Image

def getImageMatrix(image):
    im = Image.open(image)  
    pix = im.load()
    image_size = im.size 
    print("Image Size : ",image_size)
    image_matrix = []
    for width in range(int(image_size[0])):
        row = []
        for height in range(int(image_size[1])):
           try:
                row.append((pix[width,height]))
           except:
                row=[pix[width, height]]
        try:
            image_matrix.append(row)
        except:
            image_matrix = [row]
    #file = open("ImageMatrix.csv","w")
    #file.write(str(image_matrix))
    #file.close()
    return image_matrix


def dec(bitSequence):
    decimal = 0
    for bit in bitSequence:
        decimal = decimal * 2 + int(bit)
    return decimal


def genTransformationMatrix(m):
    #initial Parameter and also the symmetric secret key
    x = 0.1
    y = 0.1
    sequenceSize = m * m * 8 #Total Number of bitSequence produced
    bitSequence = []    # 8 bits
    byteArray = []      # 512 bitS
    TImageMatrix = []   # 512 byteArray 
    for i in range(sequenceSize):
        #Henon Map formula
        xN = y + 1 - 1.4 * x**2
        yN = 0.3 * x

        # New x = xN and y = yN
        x = xN
        y = yN

        if xN <= 0.3992:
            bit = 0
        else:
            bit = 1
        try:
            bitSequence.append(bit)
        except:
            bitSequence = [bit]
 
        if i % 8 == 7:
            decimal = dec(bitSequence)
            try:
                byteArray.append(decimal)
            except:
                byteArray = [decimal]
            print(bitSequence,decimal)
            bitSequence = []
        byteArraySize = m*8
        if i % byteArraySize == byteArraySize-1:
            print(byteArray)
            try:
                TImageMatrix.append(byteArray)
            except:
                TImageMatrix = [byteArray]
            print(len(byteArray),byteArray)
            byteArray = []
            
    return TImageMatrix

