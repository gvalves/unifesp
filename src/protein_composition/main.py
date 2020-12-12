def get_protein_composition_from(filename: str) -> dict:
    iostream = open(filename)
    data = dict()
    data['sequence'] = ''
    data['aa_or_na'] = dict()

    codes = ('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
             'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
             'U', 'V', 'W', 'X', 'Y', 'Z')

    for line in iostream.readlines():
        line = line[0:-2]

        if ('>' in line or ';' in line):
            continue

        data['sequence'] += line

    for code in codes:
        data['aa_or_na'][code] = data['sequence'].count(code)

    return data


print('Digite o nome de um arquivo em formato FASTA: ', end='')
filename = input()
print(get_protein_composition_from(filename)['aa_or_na'])
