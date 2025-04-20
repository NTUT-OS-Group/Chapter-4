# Documentation

使用 `make` 工具來編譯並生成執行檔：

- `make sudoku` 生成 `sudoku` 執行檔（對應 4-1）
- `make mergesort` 生成 `mergesort` 執行檔（對應 4-2）

---

# Example

## 4-1: Sudoku Checker

### Input File (`sudoku.txt`):
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
./sudoku sudoku.txt
```

### Output:
```plaintext
The Sudoku board is valid.
```

---

## 4-2: Multithreaded Merge Sort

### 輸入範例：
```plaintext
Enter the size of the array: 6
Enter 6 elements of the array: 38 27 43 3 9 82
```

### 執行方式：
```bash
make mergesort
./mergesort
```

### Output:
```plaintext
Sorted array:
3 9 27 38 43 82
```

