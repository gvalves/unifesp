from __future__ import annotations
from typing import List


class PriorityQueue:
    def __init__(self):
        self.__items: List[PriorityQueueItem] = []

    def enqueue(self, value: any, priority=0) -> None:
        try:
            priority = int(priority if priority >= 0 else 0)
        except:
            priority = 0

        item = PriorityQueueItem(value, priority)
        self.__items.append(item)

    def dequeue(self) -> PriorityQueueItem:
        if not self.size():
            return

        index = 0
        del_index = 0
        g_priority = 0

        for item in self.__items:
            if item.priority > g_priority:
                del_index = index
                g_priority = item.priority
            index += 1

        del_item = self.__items[del_index]

        del self.__items[del_index]
        return del_item

    def isEmpty(self) -> bool:
        return not self.__items

    def size(self) -> int:
        return len(self.__items)


class PriorityQueueItem:
    def __init__(self, value, priority):
        self.value = value
        self.priority = priority


# queue = PriorityQueue()

# queue.enqueue('Hello', -1)
# queue.enqueue('World', 1)
# queue.enqueue('How', 1)
# queue.enqueue('Are')
# queue.enqueue('You')

# print(queue.dequeue().value)
# print(queue.dequeue().value)
# print(queue.dequeue().value)
# print(queue.isEmpty())
# print(queue.size())
