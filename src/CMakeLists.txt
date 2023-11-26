cmake_minimum_required(VERSION 3.23)
project(DataStructure C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(DataStructure src/LinkedList/Node.c src/LinkedList/Node.h src/LinkedList/LinkedList.c src/LinkedList/LinkedList.h src/Stack.c src/Stack.h src/Queue.c src/Queue.h src/ArrayList.c src/ArrayList.h src/Heap/HeapNode.c src/Heap/HeapNode.h src/Heap/Heap.c src/Heap/Heap.h src/HashMap/HashMap.c src/HashMap/HashMap.h src/HashMap/HashNode.c src/HashMap/HashNode.h src/HashMap/HashSet.c src/HashMap/HashSet.h src/Cache/LRUCache.c src/Cache/LRUCache.h src/Tree/TreeNode.c src/Tree/TreeNode.h src/Tree/Tree.c src/Tree/Tree.h src/Tree/AvlTreeNode.c src/Tree/AvlTreeNode.h src/Tree/AvlTree.c src/Tree/AvlTree.h src/Tree/BTreeNode.c src/Tree/BTreeNode.h src/Tree/BTree.c src/Tree/BTree.h src/CounterHashMap.c src/CounterHashMap.h src/HashMap/LinkedHashMap.c src/HashMap/LinkedHashMap.h  src/Memory/Memory.c src/Memory/Memory.h)
