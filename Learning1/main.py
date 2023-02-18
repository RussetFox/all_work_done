def convertRom(roman):
    if roman == "I":
        return 1
    if roman == "V":
        return 5
    if roman == "X":
        return 10
    if roman == "L":
        return 50
    if roman == "C":
        return 100
    if roman == "D":
        return 500
    if roman == "M":
        return 1000
def checkForCorrect(roman):
    repeat = 0
    repeatsymbols = 0
    previous = "I"
    for i in range (0, len(roman)):
        if repeat > 1 and convertRom(roman[i]) > convertRom(previous):
            print ("Nie mozna wprowwadzic 2 mniejszych liczb przed wieksza liczba")
            return False
        if (convertRom(roman[i])/convertRom(previous)) % 10 == 2:
            print ("Blad wprowadzania, nie mozna umiescic jednego z symboli przed innym")
            return False
        if roman[i] != previous:
            repeat = 1
        else:
            repeat += 1
        if (convertRom(roman[i]) == 5 or convertRom(roman[i]) == 50 or convertRom(roman[i]) == 500) and roman[i] == previous:
            repeatsymbols = 2
        if repeat == 4 or repeatsymbols == 2:
            print ("Cztery liczby nie mogą występować po sobie lub 2 okreslone")
            return False
        previous = roman[i]
    return True
def romanToInt(str):
    help = 0
    if checkForCorrect(str):
        for i in range(0, len(str)-1):
            if convertRom(str[i]) < convertRom(str[i+1]):
                help -= convertRom(str[i])
            else:
                help += convertRom(str[i])
        help+= convertRom(str[len(str)-1])
        return help
    else:
        print ("Blad wprowadzania liczby")
        return 0
romannumber = input("Type roman number: ")
print(romanToInt(romannumber))

