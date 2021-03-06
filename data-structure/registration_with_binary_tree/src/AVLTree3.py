from __future__ import annotations
from functools import reduce
from typing import List


class AVLTree:
    class Node:
        def __init__(self, key: int, value: str):
            self._key: int = key
            self._value: str = value
            self._height: int = 0
            self._balance_factor: int = 0
            self._parent: self.__class__ = None
            self._left_child: self.__class__ = None
            self._right_child: self.__class__ = None

        def _update_balance_factor(self) -> None:
            l_height = self._left_child.height if self._left_child else -1
            r_height = self._right_child.height if self._right_child else -1

            self._balance_factor = l_height - r_height

        def _insert(self, node: Node) -> None:
            if node._key < self._key:
                self._left_child = node
                node._parent = self
            else:
                self._right_child = node
                node._parent = self

        def _append(self, node: Node) -> None:
            if node._key < self._key:
                if self._left_child:
                    self._height += 1
                    self._left_child._append(node)
                else:
                    self._insert(node)
            else:
                if self._right_child:
                    self._height += 1
                    try:
                        self._right_child._append(node)
                    except:
                        pass
                else:
                    self._insert(node)

        def _delete(self) -> Node:
            if not self._parent:
                raise Exception('Cannot delete node without parent')

            if self.number_of_children == 0:
                self._decrease_all_parents_height(self)

                if self._parent._left_child == self:
                    self._parent._left_child = None
                else:
                    self._parent._right_child = None

                return self._parent
            elif self.number_of_children == 1:
                self._decrease_all_parents_height(self)

                if self._left_child:
                    self._parent._insert(self._left_child)
                    return self._left_child
                else:
                    self._parent._insert(self._right_child)
                    return self._right_child
            else:
                successor: Node = self._right_child.left_most_child

                self._key = successor._key
                self._value = successor._value

                return successor._delete()

        def _find(self, key: str) -> Node:
            def find_in(node: Node) -> Node:
                while True:
                    if not node:
                        raise KeyError('Dont exists node with the passed key')

                    if key == node._key:
                        return node
                    elif key < node._key:
                        node = node._left_child
                    else:
                        node = node._right_child

            return find_in(self)

        def _find_all_by_substr(self, substr: str) -> List[tuple]:
            return [el for el in self._to_list() if el[1].lower().count(substr.lower())]

        def _to_list(self) -> List[tuple]:
            _list: List[tuple] = []

            def add_in_list(node: Node) -> None:
                _list.append((node._key, node._value))

                if node._left_child:
                    add_in_list(node._left_child)
                if node._right_child:
                    add_in_list(node._right_child)

            add_in_list(self)

            return _list

        def _decrease_all_parents_height(self, node: Node) -> None:
            while node._parent:
                node._parent._height -= 1
                node = node._parent

        def _balance(self):
            if self.is_balanced:
                return

            if self.is_left_heavy:
                if self._left_child.is_right_heavy:
                    self._left_child._left_rotation()
                    self._right_rotation()
                    self._decrease_all_parents_height(self)
                else:
                    self._right_rotation()
                    self._decrease_all_parents_height(self)
            elif self.is_right_heavy:
                if self._right_child.is_right_heavy:
                    self._left_rotation()
                    self._decrease_all_parents_height(self)
                else:
                    self._right_child._right_rotation()
                    self._left_rotation()
                    self._decrease_all_parents_height(self)

        def _left_rotation(self) -> None:
            child = self._right_child
            self._right_child = None

            child._parent = self._parent

            if child._left_child:
                self._append(child._left_child)

            self._parent = child
            child._left_child = self

            if child._parent:
                if child._key < child._parent._key:
                    child._parent._left_child = child
                else:
                    child._parent._right_child = child

            self._height -= 2
            child._height += 1

        def _right_rotation(self) -> None:
            child = self._left_child
            self._left_child = None

            child._parent = self._parent

            if child._right_child:
                self._append(child._right_child)

            self._parent = child
            child._right_child = self

            if child._parent:
                if child._key < child._parent._key:
                    child._parent._left_child = child
                else:
                    child._parent._right_child = child

            self._height -= 2
            child._height += 1

        @property
        def is_balanced(self) -> bool:
            self._update_balance_factor()
            return abs(self._balance_factor) <= 1

        @property
        def is_left_heavy(self) -> bool:
            self._update_balance_factor()
            return self._balance_factor > 0

        @property
        def is_right_heavy(self) -> bool:
            self._update_balance_factor()
            return self._balance_factor < 0

        @property
        def key(self) -> int:
            return self._key

        @property
        def value(self) -> str:
            return self._value

        @property
        def balance_factor(self) -> int:
            return self._balance_factor

        @property
        def height(self) -> int:
            return self._height

        @property
        def parent(self) -> Node:
            return self._parent

        @property
        def left_child(self) -> Node:
            return self._left_child

        @property
        def right_child(self) -> Node:
            return self._right_child

        @property
        def number_of_children(self) -> int:
            n = 0
            if self._left_child:
                n += 1
            if self._right_child:
                n += 1
            return n

        @property
        def left_most_child(self) -> Node:
            def _left_most_child(node: Node) -> Node:
                if node._left_child:
                    return _left_most_child(node._left_child)

                return node

            return _left_most_child(self)

        @property
        def right_most_child(self) -> Node:
            def _right_most_child(node: Node) -> Node:
                if node._right_child:
                    return _right_most_child(node._right_child)

                return node

            return _right_most_child(self)

    def __init__(self):
        self._root: self.Node = None

    def _get_unbalanced_node(self, node: self.Node) -> self.Node:
        while node.is_balanced:
            node = node._parent

        return node

    def _delete_balance(self, node: self.Node) -> None:
        while not self.is_balanced:
            unbalanced_node = self._get_unbalanced_node(node)
            unbalanced_node._balance()

            if unbalanced_node == self._root:
                self._root = self._root._parent

            node = node._parent

    def _insert_balance(self, node: self.Node) -> None:
        if self.is_balanced:
            return

        unbalanced_node = self._get_unbalanced_node(node)
        unbalanced_node._balance()

        if unbalanced_node == self._root:
            self._root = self._root._parent

    def insert(self, key: str, value: int) -> self.Node:
        if self.is_empty:
            self._root = self.Node(key, value)
            return self._root

        new_node = self.Node(key, value)
        self._root._append(new_node)
        self._insert_balance(new_node)

        return new_node

    def delete(self, key: str) -> self.Node:
        if self.is_empty:
            raise Exception('Cannot delete node with empty tree')

        node = self.find(key)

        if self._root.number_of_children == 0:
            self._root = None
        else:
            self._delete_balance(node._delete())

        return node

    def find(self, key: str) -> self.Node:
        if self.is_empty:
            raise Exception('Cannot find node with empty tree')

        return self._root._find(key)

    def depth(self) -> int:
        return self._root.height

    def print_tree(self) -> None:
        def _print_tree(node: self.Node, depth: int = 0, path: list = ['R']) -> None:
            print(
                f'key: {node._key}; value: {node._value}; ' +
                f'depth: {depth}; path: {reduce(lambda a, b: a + b, path)}'
            )
            depth += 1

            if node._left_child:
                _path = path.copy()
                _path.append('0')
                _print_tree(node._left_child, depth, _path)
            if node._right_child:
                _path = path.copy()
                _path.append('1')
                _print_tree(node._right_child, depth, _path)

        _print_tree(self._root)

    def find_all_by_substr(self, substr: str) -> List[tuple]:
        return self._root._find_all_by_substr(substr)

    @property
    def is_empty(self) -> bool:
        return self._root == None

    @property
    def is_balanced(self) -> bool:
        return self._root.is_balanced

    @property
    def root(self) -> AVLTree:
        return self._root
