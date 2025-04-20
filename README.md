# Documentation


## **小組分工**
- **組員及負責內容：**
  - **[111590002 鄭重雨]：** [Ch.4]
  - **[111590010 林益賢]：** [Ch.5]
  - **[111590027 陳睿泰]：** [documentation]
  - **[111590028 林柏儒]：** [測試]

---


使用 `make` 工具來編譯並生成執行檔：

- `make sudoku ` 生成 `sudoku` 執行檔（對應 4-1）
- `make sort` 生成 `sort` 執行檔（對應 4-2）

---

# Example

## 4-1: Sudoku Checker

### Input File (`valid.txt`):
```plaintext
5 3 4 6 7 8 9 1 2
6 7 2 1 9 5 3 4 8
1 9 8 3 4 2 5 6 7
8 5 9 7 6 1 4 2 3
4 2 6 8 5 3 7 9 1
7 1 3 9 2 4 8 5 6
9 6 1 5 3 7 2 8 4
2 8 7 4 1 9 6 3 5
3 4 5 2 8 6 1 7 9
```

### 執行方式：
```bash
make sudoku
./sudoku valid.txt
```

### Output:
```plaintext
The Sudoku board is valid.
```

---

### Input File (`invalid.txt`):
```plaintext
5 3 4 6 7 8 9 1 3
6 7 2 1 9 5 3 4 8
1 9 8 3 4 2 5 6 7
8 5 9 7 6 1 4 2 3
4 2 6 8 5 3 7 9 1
7 1 3 9 2 4 8 5 6
9 6 1 5 3 7 2 8 4
2 8 7 4 1 9 6 3 5
3 4 5 2 8 6 1 7 9
```

### 執行方式：
```bash
make sudoku
./sudoku invalid.txt
```

### Output:
```plaintext
The Sudoku board is invalid.
```

---

## 4-2: Multithreaded Merge Sort

### 輸入範例：
```plaintext
Enter the size of the array: 7
Enter 7 elements of the array: 9 0 8 4 6 7 1
```

### 執行方式：
```bash
make sort
./sort
```

### Output:
```plaintext
Sorted array:
0 1 4 6 7 8 9
```

