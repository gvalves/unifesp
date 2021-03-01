from Trie import Trie
from functools import reduce


def main():
    def create_tree():
        index_tree = Trie()

        data_stream = open('cadastro2019.csv', 'r', encoding='ISO-8859-1')
        data_stream.readline()
        pos = data_stream.tell()

        for line in data_stream.readlines():
            name: str = line.split('|')[2]
            name_fragments = name.split(' ')

            for name_fragment in name_fragments:
                index_tree.insert(
                    reduce(lambda a, b: f'{a} {b}', name_fragments),
                    pos
                )
                del name_fragments[0]

            pos += len(line)

        return index_tree


if __name__ == '__main__':
    main()
