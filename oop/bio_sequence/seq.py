from __future__ import annotations
from functools import reduce
from typing import List


class Seq:
    @staticmethod
    def is_generic_fasta(filename: str) -> bool:
        return filename.split('.')[-1] in ('fasta', 'fas', 'seq', 'fa', 'fsa')

    def __init__(self, id='', seq='', desc='', chars=(), origin=None):
        self.__chars = chars

        self.id = str(id)
        self.seq = str(seq)
        self.desc = str(desc).replace('\n', '')
        self.origin = origin

        self.breakrow_in = 70

    def __str__(self):
        return self.seq

    def __add__(self, seq):
        return str(self) + str(seq)

    def __len__(self):
        return len(self.seq)

    def frequency(self) -> dict:
        frequency = {}

        for char in self.chars:
            frequency[char] = self.seq.count(char)

        return frequency

    def relative_frequency(self) -> dict:
        frequency = {}

        for char in self.chars:
            frequency[char] = self.seq.count(char) / len(self)

        return frequency

    def to_fasta(self) -> str:
        result = f'>gi|{self.id}| {self.desc}\n'

        for i in range(0, len(self), self.breakrow_in):
            result += f'{self.seq[i:i+self.breakrow_in]}\n'

        return result

    def save_as(self, filename: str, append: bool = False) -> None:
        if not Seq.is_generic_fasta(filename):
            raise ValueError('Filename must be a generic fasta.')

        fastafile = open(f'{filename}', 'a' if append else 'w')
        fastafile.write(self.to_fasta())

    def load_from(self, filename: str, load=0):
        if not Seq.is_generic_fasta(filename):
            raise ValueError('Filename must be a generic fasta.')

        fastafile = open(f'{filename}', 'r')
        seqs: List[self.__class__] = []
        curseq = None

        for line in fastafile.readlines():
            if '>' in line:
                if curseq:
                    seqs.append(curseq)

                if 'gi|' in line:
                    header = line.split('|')
                    curseq = self.__class__(
                        header[1], '', header[-1] if len(header) > 2 else ''
                    )
                else:
                    curseq = self.__class__()

                continue

            curseq.seq += line

        if curseq:
            seqs.append(curseq)

        if load < 0 and -load > len(seqs):
            load = 0
        elif load >= len(seqs):
            load = len(seqs) - 1

        if len(seqs) > 0:
            self.id = seqs[load].id
            self.seq = seqs[load].seq
            self.desc = seqs[load].desc
            self.origin = seqs[load].origin

        return seqs

    @property
    def seq(self) -> str:
        return self.__seq

    @seq.setter
    def seq(self, value: str):
        value = str(value)

        if not self.chars:
            self.__seq = value
            return

        try:
            self.__seq = str(reduce(
                lambda a, b: a + b,
                filter(lambda char: self.chars.count(char), value)
            ))
        except:
            self.__seq = ''

    @property
    def chars(self) -> tuple:
        return self.__chars

    @chars.setter
    def chars(self, value):
        return


class SeqDNA(Seq):
    def __init__(self, id='', seq='', desc='', chars=(), origin=None):
        super().__init__(id, seq, desc, ('A', 'T', 'G', 'C'))
        self.origin: SeqDNA = self

    @staticmethod
    def __complementary_nitro_base(nitro_base: str) -> str:
        if nitro_base == 'A':
            return 'T'
        elif nitro_base == 'T':
            return 'A'
        elif nitro_base == 'G':
            return 'C'
        elif nitro_base == 'C':
            return 'G'
        return ''

    def complementary_reverse(self) -> SeqDNA:
        seq = ''
        for nitro_base in self.seq:
            seq += SeqDNA.__complementary_nitro_base(nitro_base)

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

    def __init__(self, id='', seq='', desc='', chars=(), origin=None):
        super().__init__(id, seq, desc, ('A', 'U', 'G', 'C'))
        self.origin: SeqDNA = origin

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


class SeqAA(Seq):
    def __init__(self, id='', seq='', desc='', chars=(), origin=None):
        super().__init__(
            id, seq, desc, ('C', 'F', 'L', 'I', 'M', 'V', 'S',
                            'P', 'A', 'Y', '*', 'H', 'Q', 'N',
                            'K', 'D', 'E', 'W', 'R', 'S', 'G')
        )
        self.origin: SeqRNA = origin


class SeqAAFrames:
    def __init__(self):
        self.frames = [SeqAA(), SeqAA(), SeqAA(), SeqAA(), SeqAA(), SeqAA()]

    def save_as(self, filename: str) -> None:
        if not Seq.is_generic_fasta(filename):
            raise ValueError('Filename must be a generic fasta.')

        open(filename, 'w').close()
        for frame in self.frames:
            frame.save_as(filename, append=True)
