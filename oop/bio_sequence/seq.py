from __future__ import annotations


class Seq:
    def __init__(self, id: str, seq: str, desc: str = '', chars: tuple = ()):
        from functools import reduce

        self.id = id

        try:
            self.seq = str(reduce(lambda x, y: x + y,
                                  filter(lambda char: chars.count(char), seq)))
        except:
            self.seq = ''

        self.desc = desc
        self.breakrow_in = 70
        self.chars = chars

    def __str__(self):
        return self.seq

    def __add__(self, seq):
        return str(self) + str(seq)

    def __len__(self):
        return len(self.seq)

    def composition(self) -> str:
        result = f'>gi|{self.id}| {self.desc}\n'

        for i in range(0, len(self.seq), self.breakrow_in):
            result += f'{self.seq[i:i+self.breakrow_in]}\n'

        return result


class SeqAA(Seq):
    def __init__(self,
                 id: str,
                 seq: str,
                 desc: str = '',
                 chars: tuple = (),
                 origin: SeqRNA = None):
        super().__init__(id, seq, desc, ('C', 'F', 'L', 'I', 'M', 'V', 'S',
                                         'P', 'A', 'Y', '*', 'H', 'Q', 'N',
                                         'K', 'D', 'E', 'W', 'R', 'S', 'G'))
        self.origin = origin


class SeqAAFrames:
    def __init__(self):
        self.frames = [SeqAA('', ''), SeqAA('', ''), SeqAA('', ''),
                       SeqAA('', ''), SeqAA('', ''), SeqAA('', '')]
        self.frames[2]


class SeqDNA(Seq):
    def __init__(self, id: str, seq: str, desc: str = '', chars: tuple = ()):
        super().__init__(id, seq, desc, ('A', 'T', 'G', 'C'))

    def complementary_reverse(self) -> SeqDNA:
        seq = ''

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

        for nitro_base in self.seq:
            seq += reverse_nitro_base(nitro_base)

        return SeqDNA(self.id, seq[::-1], self.desc)

    def transcribe(self) -> SeqRNA:
        return SeqRNA(
            self.id, self.seq.replace('T', 'U'), self.desc, origin=self
        )


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

    def __init__(self,
                 id: str,
                 seq: str,
                 desc: str = '',
                 chars: tuple = (),
                 origin: SeqDNA = None):
        super().__init__(id, seq, desc, ('A', 'U', 'G', 'C'))
        self.origin = origin

    def translate(self) -> SeqAAFrames:
        seq = self.seq
        revseq = self.origin.complementary_reverse().transcribe().seq
        seqaaframes = SeqAAFrames()

        for frame in seqaaframes.frames:
            frame.id = self.id
            frame.desc = self.desc
            frame.origin = self

        for i in range(0, len(self), 3):
            for j in range(0, 3):
                seqaaframes.frames[j].seq += SeqRNA.translator \
                    .get(seq[i + j:i + j + 3]) or ''
                seqaaframes.frames[j + 3].seq += SeqRNA.translator \
                    .get(revseq[i + j:i + j + 3]) or ''

        return seqaaframes
