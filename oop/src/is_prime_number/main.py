def is_prime_number(number: int) -> bool:
    if number < 2:
        return False

    if number in (2, 3, 5, 7):
        return True

    if number % 2 == 0 or number % 3 == 0 or number % 5 == 0 or number % 7 == 0:
        return False

    is_prime = True

    divider = 11

    while True:
        if number / 2 < divider:
            break

        if number % divider == 0:
            is_prime = False
            break

        divider += 2

    return is_prime


while True:
    print('Digite um número para saber se ele é primo: ', end='')
    data_in = input()

    if not data_in.isnumeric():
        break

    number = int(data_in)

    print(f"O número {number} {'' if is_prime_number(number) else 'não'}é primo!")
