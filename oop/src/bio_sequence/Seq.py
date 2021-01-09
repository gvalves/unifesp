class Seq:
    def __init__(self, id: str, data: str, desc: str):
        self.id = id
        self.data = data
        self.desc = desc
        self.breakrow_in = 70

    def __str__(self):
        return self.composition()

    def composition(self) -> str:
        result = f'>gi|${self.id}| ${self.desc}\n'

        for i in range(0, len(self.data), self.breakrow_in):
            result += f'{self.data[i:i+self.breakrow_in]}\n'

        return result


class SeqAA(Seq):
    pass


class SeqDNA(Seq):
    def complementary_reverse(self) -> SeqDNA:
        pass

    def transcribe(self) -> SeqRNA:
        pass


class SeqRNA(Seq):
    def translate(self) -> SeqAA:
        pass
