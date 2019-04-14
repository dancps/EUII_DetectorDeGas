def bcdDigits(chars):
    for char in chars:
        char = ord(char)
        for val in (char >> 4, char & 0xF):
            if val == 0xF:
                return
            yield val

print("Digite o valor inteiro")
while(end):
	inputT=input(">>")