def input_digit():
    while True:
        x = raw_input("input number:")
        if x.isdigit():
            break
        else:
            print ("Please input number!")
    return int(x)

def hat():
    num = input_digit()
    a = range(num)
    for i in range(num):
        a[i] = input_digit()
    a.sort()

    lea = a[0]
    j = 0
    thir = -1
    for i in range(num):
        if lea < a[i]:
            lea = a[i]
            j = j + 1
        if j == 2:
            thir = lea
            break

    print thir


if __name__ == "__main__":
    print ('This is hat.py')
    hat()
