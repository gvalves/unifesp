def get_protein_composition_from(filename: str) -> dict:
    iostream = open(filename)
    data = {
        'sequence': '',
        'aminoacid': {
            'quantity': {},
            'frequence': {}
        }
    }

    aminoacid_codes = ('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                       'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                       'U', 'V', 'W', 'X', 'Y', 'Z')

    for line in iostream.readlines():
        line = line[0:-2]

        if ('>' in line or ';' in line):
            continue

        data['sequence'] += line

    for code in aminoacid_codes:
        aminoacid_qt = data['sequence'].count(code)

        data['aminoacid']['quantity'][code] = aminoacid_qt
        data['aminoacid']['frequence'][code] = '{:.2%}'.format(
            aminoacid_qt / len(data['sequence']))

    return data


filename = input('Digite o nome de um arquivo em formato FASTA: ')
print(get_protein_composition_from(filename)['aminoacid'])
