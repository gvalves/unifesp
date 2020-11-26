def isPrime(number: int) -> bool:
    if number < 2:
        return False

    if number in (2, 3, 5, 7):
        return True

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


print('Digite um número para saber se ele é primo: ', end='')
number = int(input())
print(f"O número {number}{' não' if not isPrime(number) else ''} é primo!")
