def handle_phd_data_from(filename: str) -> None:
    fetched_file = open(filename)

    is_in_comment = False
    dna_index = 0

    fasta_file = {
        'name': filename.split('/')[-1].split('.')[0],
        'data': []
    }
    qual_file = {
        'name': filename.split('/')[-1].split('.')[0],
        'data': []
    }

    for line in fetched_file.readlines():
        if 'BEGIN_DNA' in line:
            is_in_comment = False
            continue

        if is_in_comment:
            continue

        if 'END_DNA' in line:
            break

        if 'BEGIN_SEQUENCE' in line:
            newname = line.replace('BEGIN_SEQUENCE', '')[1:-1]
            fasta_file['name'] = newname
            qual_file['name'] = newname
            continue

        if 'BEGIN_COMMENT' in line:
            is_in_comment = True
            continue

        line_data = line.split(' ')
        dna_index += 1

        # Using try/except to avoid IndexError when line is \n
        try:
            fasta_file['data'].append(line_data[0])
            qual_file['data'].append(line_data[1] + ' ')

            if dna_index % 60 == 0:
                fasta_file['data'].append('\n')
                qual_file['data'].append('\n')
        except:
            dna_index -= 1

    iofasta = open(f"fasta/{fasta_file['name']}.fasta", mode='w')
    iofasta.writelines([f"> {qual_file['name']}\n"] +
                       [i for i in fasta_file['data']])

    ioqual = open(f"qual/{fasta_file['name']}.qual", mode='w')
    ioqual.writelines([f"> {qual_file['name']}\n"] +
                      [i for i in qual_file['data']])


# handle_phd_data_from('examples/example1.phd')
# handle_phd_data_from('examples/example2.phd')
