cmake_minimum_required(VERSION 3.23)
project(DataStructure C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

add_library(DataStructure LinkedList/Node.c LinkedList/Node.h LinkedList/LinkedList.c LinkedList/LinkedList.h Stack.c Stack.h Queue.c Queue.h ArrayList.c ArrayList.h Heap/HeapNode.c Heap/HeapNode.h Heap/Heap.c Heap/Heap.h HashMap/HashMap.c HashMap/HashMap.h HashMap/HashNode.c HashMap/HashNode.h HashMap/HashSet.c HashMap/HashSet.h Cache/LRUCache.c Cache/LRUCache.h Tree/TreeNode.c Tree/TreeNode.h Tree/Tree.c Tree/Tree.h Tree/AvlTreeNode.c Tree/AvlTreeNode.h Tree/AvlTree.c Tree/AvlTree.h Tree/BTreeNode.c Tree/BTreeNode.h Tree/BTree.c Tree/BTree.h CounterHashMap.c CounterHashMap.h HashMap/LinkedHashMap.c HashMap/LinkedHashMap.h  Memory/Memory.c Memory/Memory.h)
