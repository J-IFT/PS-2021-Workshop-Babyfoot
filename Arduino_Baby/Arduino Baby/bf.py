import serial

ser = serial.Serial('COM6', 9800, timeout=1)
b = 0
r = 0


while (True):
    textSortie = str(b) + '   ' + str(r)
    a = str(ser.readline())
    sortie = a.split("'")[1].split('\\r')[0]
    print(sortie)
    if sortie != '':
        if 'B' in sortie:
            b += 1
            textSortie = str(b) + '-' + str(r)
        elif 'R' in sortie:
            r += 1
            textSortie = str(b) + '-' + str(r)
        with open('bf.txt', 'w') as txt:
            txt.write(textSortie)
    

    
