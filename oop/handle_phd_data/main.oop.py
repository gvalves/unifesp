class PhdFile:
    def __init__(self, filepath: str):
        self.name = filepath.split('/')[-1].split('.')[0]
        self.path = filepath
        self.io = open(filepath)
        self.sequence = PhdSequence(self)

    def create_fasta_file(self, directory: str) -> None:
        fasta_file = open(f'{directory}/{self.sequence.name}.fasta', 'w')
        fasta_file.write(f'> {self.sequence.name}\n\n')
        fasta_file.writelines([i for i in self.sequence.data.fasta_data])

    def create_qual_file(self, directory: str) -> None:
        qual_file = open(f'{directory}/{self.sequence.name}.qual', 'w')
        qual_file.write(f'> {self.sequence.name}\n\n')
        qual_file.writelines([i for i in self.sequence.data.quality_data])


class PhdSequence:
    def __init__(self, file: PhdFile):
        self.file = file
        self.name = file.name
        self.data = PhdSequenceData()
        self.comments = {}

        is_in_comment = False
        is_in_dna = False
        dna_counter = 0

        for line in self.file.io.readlines():
            if 'BEGIN_SEQUENCE' in line and not line[14:].isspace():
                self.name = line[14:].strip()
                continue

            if 'BEGIN_COMMENT' in line:
                is_in_comment = True
                continue

            if is_in_comment:
                try:
                    separator = line.index(':')
                    key = line[:separator]
                    value = line[separator + 1:].strip()
                    self.comments[key] = value
                except:
                    continue

            if 'BEGIN_DNA' in line:
                is_in_comment = False
                is_in_dna = True
                continue

            if 'END_DNA' in line:
                is_in_dna = False
                break

            if not is_in_dna:
                continue

            line_data = line.split(' ')
            dna_counter += 1

            try:
                self.data.fasta_data.append(line_data[0])
                self.data.quality_data.append(f'{line_data[1]} ')

                if dna_counter % 60 == 0:
                    self.data.fasta_data.append('\n')
                    self.data.quality_data.append('\n')
            except:
                continue

    def __str__(self):
        sequence = ''

        for line in self.file.io.readlines():
            sequence += line

        return sequence


class PhdSequenceData:
    def __init__(self):
        self.fasta_data = []
        self.quality_data = []


def handle_phd_data_from(filepath: str) -> None:
    phd_file = PhdFile(filepath)
    phd_file.create_fasta_file('fasta')
    phd_file.create_qual_file('qual')


handle_phd_data_from('examples/example1.phd')
handle_phd_data_from('examples/example2.phd')
