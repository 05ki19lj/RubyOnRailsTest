# Test

class Node:
    """节点类，双向环形链表：包含数据字段及左右链接。"""
    def __init__(self, data=None):
        self.data = data
        self.llink = None  # 左向指针（前驱）
        self.rlink = None  # 右向指针（后继）

class CircularDoublyLinkedList:
    def __init__(self):
        # 设置一个“头”节点，不存储数据，仅作为哨兵使用
        self.head = Node()
        # 初始时 head 的左右都指向自己，构成空的环
        self.head.llink = self.head
        self.head.rlink = self.head

    def is_empty(self):
        return self.head.rlink == self.head

    def traverse(self, left=False):
        """遍历链表，从 head 向右（默认）或向左，打印 data（跳过 head）"""
        direction = 'llink' if left else 'rlink'
        ptr = getattr(self.head, direction)
        while ptr != self.head:
            print(ptr.data, end=' <-> ')
            ptr = getattr(ptr, direction)
        print('HEAD')

    def add_right(self, data):
        """在 head 之后插入节点（右新增）"""
        new_node = Node(data)
        right = self.head.rlink
        self.head.rlink = new_node
        new_node.llink = self.head
        new_node.rlink = right
        right.llink = new_node

    def add_left(self, data):
        """在 head 之前插入节点（左新增）"""
        new_node = Node(data)
        left = self.head.llink
        left.rlink = new_node
        new_node.llink = left
        new_node.rlink = self.head
        self.head.llink = new_node

    def insert_at(self, position, data, left=False):
        """
        在第 position 个节点前插入新节点。
        position 从 1 开始；left 表示以左遍历方式定位。
        """
        ptr = self.head
        count = 0
        # 选择方向遍历
        while True:
            ptr = ptr.llink if left else ptr.rlink
            if ptr == self.head:
                break
            count += 1
            if count == position:
                break

        # 插入 new_node 到 ptr 前（以当前位置为后驱）
        new_node = Node(data)
        prev_node = ptr.llink
        prev_node.rlink = new_node
        new_node.llink = prev_node
        new_node.rlink = ptr
        ptr.llink = new_node

    def remove_at(self, position, left=False):
        """删除第 position 个节点（position 从 1 开始）"""
        ptr = self.head
        count = 0
        while True:
            ptr = ptr.llink if left else ptr.rlink
            if ptr == self.head:
                return False  # 不存在
            count += 1
            if count == position:
                break
        # unlink ptr
        prev_node = ptr.llink
        next_node = ptr.rlink
        prev_node.rlink = next_node
        next_node.llink = prev_node
        return True

# 测试示例
if __name__ == "__main__":
    cl = CircularDoublyLinkedList()
    cl.add_right("A")
    cl.add_right("B")
    cl.add_left("Z")
    print("Traverse right:")
    cl.traverse()           # Z <-> A <-> B <-> HEAD
    print("Traverse left:")
    cl.traverse(left=True)  # B <-> A <-> Z <-> HEAD
    cl.insert_at(2, "X")    # 在第 2 位前插入 X
    print("After insert:")
    cl.traverse()
    cl.remove_at(3)
    print("After remove at 3:")
    cl.traverse()
