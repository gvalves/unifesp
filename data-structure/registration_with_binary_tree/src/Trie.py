from __future__ import annotations
from typing import List
from functools import reduce


class Trie:
    class Node:
        def __init__(self, letter: str):
            self._letter: str = letter
            self._values: List[int] = []
            self._children: List[Node] = [None] * 27
            self._is_leaf: bool = False
            self._parent: Node = None

        def __repr__(self):
            word = []

            def append_letter_in_word(node: Node) -> None:
                if not node or not node._letter:
                    return

                word.append(node._letter)

                append_letter_in_word(node._parent)

            append_letter_in_word(self)

            return reduce(lambda a, b: a + b, word[::-1])

        def bind_values(self, node: Node):
            self._values = node._values

        @property
        def has_child(self) -> bool:
            for child in self._children:
                if child:
                    return True

            return False

        @property
        def children(self) -> List[Node]:
            return [child for child in self._children if child]

        @property
        def letter(self) -> str:
            return self._letter

        @property
        def values(self) -> List[int]:
            return self._values.copy()

    def __init__(self):
        self._root: self.Node = self.Node(None)

    def _char_to_index(self, char: str) -> int:
        if char == ' ':
            return 26

        index = ord(char) - ord('A')

        if not 0 <= index < 26:
            raise ValueError(f'Unsupported character: {char}')

        return index

    def insert(self, key: str, value: int) -> self.Node:
        node = self.get(key)

        if node:
            node._values.append(value)
            return node

        if len(key) == 1:
            index = self._char_to_index(key)
            node = self.Node(key)
            node._values.append(value)
            node._parent = self._root
            self._root._children[index] = node
        else:
            node = self._root
            for i, char in enumerate(key):
                index = self._char_to_index(char)
                if node._children[index]:
                    node = node._children[index]
                else:
                    new_node = self.Node(char)
                    node._children[index] = new_node
                    new_node._parent = node
                    node = new_node
                    if len(key) == i + 1:
                        node._values.append(value)
                        node._is_leaf = True

        return node

    def delete(self, key: str) -> None:
        def _delete(node: self.Node, recursive_call: bool) -> None:
            if not node:
                return

            if node.has_child:
                if not recursive_call:
                    node._is_leaf = False

                return

            index = self._char_to_index(node._letter)
            node._parent._children[index] = None
            _delete(node._parent, True)
            del node

        _delete(self.get(key), False)

    def get(self, key: str) -> self.Node:
        node: self.Node = self._root

        for char in key:
            index = self._char_to_index(char)
            if node._children[index]:
                node = node._children[index]
                continue
            return

        if not node._is_leaf:
            return

        return node

    def search(self, key: str) -> List[self.Node]:
        node: self.Node = self._root

        for char in key:
            index = self._char_to_index(char)
            if node._children[index]:
                node = node._children[index]

        def get_leaf_from(_node: self.Node, leaves: List[self.Node] = []):
            if _node._is_leaf:
                leaves.append(_node)

            children = _node.children

            if children:
                for child in children:
                    get_leaf_from(child, leaves)

            return leaves

        return get_leaf_from(node)

    def has(self, key: str) -> bool:
        return bool(self.get(key))
