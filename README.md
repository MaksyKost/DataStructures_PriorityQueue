# DataStructures_PriorityQueue
Implementation and benchmarking of a priority queue in C++.

# Data Structures: Priority queue

This repository was created for the **Data Structures** course at **Wrocław University of Science and Technology**.

## 📌 Project Description
The goal of the project is to implement a **MAX priority queue** in C++ using two different data structures:

- **Binary Heap**
- **Doubly Linked List**

The project includes the implementation of key priority queue operations as well as performance testing and comparison between the two approaches.

---

⚙️ Implemented Operations

The following operations have been implemented for both structures:
- insert(e, p) – inserts element e with priority p
- extract-max() – removes and returns the element with the highest priority
- find-max()/peek() – returns the highest-priority element without removing it
- modify-key(e, p) – updates the priority of element e to p (increase-key or decrease-key)
- return-size() – returns the size of the queue

---
🧪 Benchmarking
Performance analysis of both implementations includes:
- Measuring operation time for different structure sizes (e.g., 1,000 to 10,000 elements)
- Storing benchmarking results in results/ as .txt files
- Visualizing and analyzing performance in the final report

---
🛠️ Technologies
- Language: C++
- No STL containers used – all structures are implemented from scratch


---

