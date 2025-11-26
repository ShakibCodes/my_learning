# Vectors in C++ 
A vector is a dynamic array — meaning it can grow or shrink automatically.
#### Features
- Dynamic Size
- Fast indexing (O(1))
- Tons of built-in functions
- Easy to pass around in functions
- Works great with STL algorithms (sort, lower_bound, etc.)

### Declaretion of Vector

```cpp
vector<int> v;            // empty vector
vector<int> v(5);         // size = 5, initialized to 0
vector<int> v(5, 10);     // size = 5, every element = 10
vector<int> v = {1,2,3};  // initialization list
```
<br>

# Vector Function

### 1. `push_back()`
>Adds element at the end.

```cpp
v.push_back(10);
```
**TC: amortized O(1)**

<br>

### 2. `pop_back()`
>Removes last element.
```cpp
v.pop_back();
```
**TC: O(1)**

<br>

### 3. `size()`
>Returns number of elements.
```cpp
int n = v.size();
```
**TC: O(1)**

<br>

### 4. `empty()`
>Checks if vector is empty.
```cpp
if(v.empty()) { ... }
```
**TC: O(1)**

<br>

### 5. `resize(n)`
>Changes the size of the vector.
```cpp
v.resize(10);     // now size = 10
v.resize(3);      // shrink to 3
```

<br>

### 6. `clear()`
>Removes all elements (size becomes 0).
```cpp
v.clear();
```
**TC: O(n)**

<br>

### 7. `insert()`
>Inserts element at any position.
```cpp
v.insert(v.begin() + 2, 50);     // insert 50 at index 2
```
**TC: O(n)**<br>
(because shifting is required)

<br>

### 8. `erase()`
>Erase a single element OR a range.
```cpp
v.erase(v.begin() + 3);                    // erase index 3
v.erase(v.begin() + 2, v.begin() + 5);     // erase range [2,5)
```
**TC: O(n)**

<br>

### 9. `front()` and `back()`
>Access first and last elements.
```cpp
int x = v.front();
int y = v.back();
```
**TC: O(1)**

<br>

### 10. `at()`
>Bounds-checked access (throws error if invalid index).
```cpp
cout << v.at(2);
```
**TC: O(1)**

<br>

### 11. `begin()` and `end()`
>Return iterators (pointers-like).
```cpp
auto it = v.begin();
```
<Br>

> [!NOTE]
> Useful information that users should know, even when skimming content.