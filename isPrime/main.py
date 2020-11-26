def isPrime(number: int) -> bool:
    if number < 2:
        return False

    if number in (2, 3, 5, 7):
        return True

    if number % 2 == 0 or number % 3 == 0 or number % 5 == 0 or number % 7 == 0:
        return False

    _isPrime = True

    divider = 11

    while True:
        if number / 2 < divider:
            break

        if number % divider == 0:
            _isPrime = False
            break

        divider += 2

    return _isPrime


while True:
    print('Digite um número para saber se ele é primo: ', end='')
    dataInput = input()

    if not dataInput.isnumeric():
        break

    number = int(dataInput)

    print(f"O número {number}{' não' if not isPrime(number) else ''} é primo!")
