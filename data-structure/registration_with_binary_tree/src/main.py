from functools import reduce
from AVLTree3 import AVLTree
from Registration import Registration


def main():
    def create_tree(data_source_path: str):
        index_tree = AVLTree()

        data_stream = open(data_source_path, 'r', encoding='ISO-8859-1')
        data_stream.readline()
        pos = data_stream.tell()

        for line in data_stream.readlines():
            name: str = line.split('|')[Registration.NOME.value]
            index_tree.insert(pos, name)
            pos += len(line)

        return index_tree

    data_source_path = './data/cadastro2019.csv'
    index_tree = create_tree(data_source_path)

    name_to_search = input('Entre com nome para busca: ')
    data_stream = open(data_source_path, 'r', encoding='ISO-8859-1')
    indexes = index_tree.find_all_by_substr(name_to_search)

    print(f'\n{len(indexes)} registro encontrado!\n')

    for index in indexes:
        data_stream.seek(index[0])
        data = data_stream.readline().split('|')
        print(f'Nome: {data[Registration.NOME.value]}')
        print(f'ORG_LOTAÇÃO: {data[Registration.ORG_LOTACAO.value]}')
        print('-' * 50)


if __name__ == '__main__':
    main()
