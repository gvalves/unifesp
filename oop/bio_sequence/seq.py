class Seq:
    def __init__(self, id: str, data: str, desc: str = '', chars: tuple = ()):
        from functools import reduce

        self.id = id
        self.data = str(reduce(lambda x, y: x + y,
                               filter(lambda char: chars.count(char), data)))
        self.desc = desc
        self.breakrow_in = 70
        self.chars = chars

    def __str__(self):
        return self.composition()

    def composition(self) -> str:
        result = f'>gi|${self.id}| ${self.desc}\n'

        for i in range(0, len(self.data), self.breakrow_in):
            result += f'{self.data[i:i+self.breakrow_in]}\n'

        return result


class SeqAA(Seq):
    def __init__(self, id: str, data: str, desc: str = '', chars: tuple = ()):
        super().__init__(id, data, desc, ('C', 'F', 'L', 'I', 'M', 'V', 'S',
                                          'P', 'A', 'Y', '*', 'H', 'Q', 'N',
                                          'K', 'D', 'E', 'W', 'R', 'S', 'G'))


class SeqDNA(Seq):
    def __init__(self, id: str, data: str, desc: str = '', chars: tuple = ()):
        super().__init__(id, data, desc, ('A', 'T', 'G', 'C'))

    def complementary_reverse(self) -> SeqDNA:
        data = ''

        def reverse_nitro_base(nitro_base: str) -> str:
            if nitro_base == 'A':
                return 'T'
            elif nitro_base == 'T':
                return 'A'
            elif nitro_base == 'G':
                return 'C'
            elif nitro_base == 'C':
                return 'G'
            return ''

        for nitro_base in self.data:
            data += reverse_nitro_base(nitro_base)

        return SeqDNA(self.id, data, self.desc)

    def transcribe(self) -> SeqRNA:
        return SeqRNA(self.id, self.data.replace('T', 'U'), self.desc)


class SeqRNA(Seq):
    translator = {'UGU': 'C', 'UGC': 'C', 'UUU': 'F', 'UUC': 'F', 'UUA': 'L',
                  'UUG': 'L', 'CUU': 'L', 'CUC': 'L', 'CUA': 'L', 'CUG': 'L',
                  'AUU': 'I', 'AUC': 'I', 'AUA': 'I', 'AUG': 'M', 'GUU': 'V',
                  'GUC': 'V', 'GUA': 'V', 'GUG': 'V', 'UCU': 'S', 'UCA': 'S',
                  'UCG': 'S', 'UCC': 'S', 'CCU': 'P', 'CCC': 'P', 'CCG': 'P',
                  'CCA': 'P', 'ACU': 'T', 'ACG': 'T', 'ACA': 'T', 'ACC': 'T',
                  'GCU': 'A', 'GCC': 'A', 'GCG': 'A', 'GCA': 'A', 'UAU': 'Y',
                  'UAC': 'Y', 'UAA': '*', 'UAG': '*', 'CAU': 'H', 'CAC': 'H',
                  'CAA': 'Q', 'CAG': 'Q', 'AAU': 'N', 'AAC': 'N', 'AAA': 'K',
                  'AAG': 'K', 'GAU': 'D', 'GAC': 'D', 'GAA': 'E', 'GAG': 'E',
                  'UGA': '*', 'UGG': 'W', 'CGU': 'R', 'CGC': 'R', 'CGA': 'R',
                  'CGG': 'R', 'AGU': 'S', 'AGC': 'S', 'AGA': 'R', 'AGG': 'R',
                  'GGU': 'G', 'GGC': 'G', 'GGA': 'G', 'GGG': 'G'}

    def __init__(self, id: str, data: str, desc: str = '', chars: tuple = ()):
        super().__init__(id, data, desc, ('A', 'U', 'G', 'C'))

    def translate(self) -> SeqAA:
        init = self.data.find('AUG')
        stop = (self.data.find('UAA'),
                self.data.find('UAG'),
                self.data.find('UGA'))
        stop = min(filter(lambda x: x > 0, stop))
        data = ''

        for i in range(init, stop, 3):
            data += SeqRNA.translator.get(self.data[i:i+3]) or ''

        return SeqAA(self.id, data, self.desc)
