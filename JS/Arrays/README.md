# JavaScript — Arrays

---

## 📌 Table of Contents
1. [What is an Array?](#what-is-an-array)
2. [Creating Arrays](#creating-arrays)
3. [Array Indices](#array-indices)
4. [Accessing & Modifying Elements](#accessing--modifying-elements)
5. [Looping Over an Array](#looping-over-an-array)
6. [Array Methods](#array-methods)
   - [push()](#push)
   - [pop()](#pop)
   - [unshift()](#unshift)
   - [shift()](#shift)
   - [toString()](#tostring)
   - [concat()](#concat)
   - [slice()](#slice)
   - [splice()](#splice)
   - [indexOf()](#indexof)
   - [includes()](#includes)
   - [reverse()](#reverse)
   - [join()](#join)
   - [find()](#find)
   - [filter()](#filter)
   - [map()](#map)
   - [reduce()](#reduce)
7. [Spread Operator with Arrays](#spread-operator-with-arrays)
8. [Array Destructuring](#array-destructuring)
9. [Methods Cheat Sheet](#methods-cheat-sheet)

---

## What is an Array?

An **array** is a special variable that can hold **multiple values** in a single place, in an **ordered list**.

Instead of doing this:
```js
const fruit1 = "apple";
const fruit2 = "banana";
const fruit3 = "cherry";
```

You can do this:
```js
const fruits = ["apple", "banana", "cherry"];
```

Arrays can store **any data type** — numbers, strings, booleans, objects, even other arrays:

```js
const mixed = [42, "hello", true, null, { name: "Alice" }, [1, 2, 3]];
```

---

## Creating Arrays

**Using array literal `[]` — most common:**
```js
const numbers = [10, 20, 30, 40];
const names   = ["Alice", "Bob", "Charlie"];
const empty   = [];
```

**Using the `Array` constructor:**
```js
const arr = new Array(3);        // creates [empty × 3]
const arr2 = new Array(1, 2, 3); // creates [1, 2, 3]
```

> 💡 Stick with `[]` literals — they're simpler and less error-prone.

---

## Array Indices

Arrays are **zero-indexed** — the first element is at index `0`.

```
  "apple"   "banana"   "cherry"   "date"
     0          1          2         3
```

```js
const fruits = ["apple", "banana", "cherry", "date"];

console.log(fruits[0]); // "apple"
console.log(fruits[2]); // "cherry"
console.log(fruits[3]); // "date"

// Last element using .length
console.log(fruits[fruits.length - 1]); // "date"
```

Accessing an index that doesn't exist returns `undefined`:
```js
console.log(fruits[10]); // undefined
```

---

## Accessing & Modifying Elements

You can **read** or **change** any element using its index:

```js
const colors = ["red", "green", "blue"];

// Read
console.log(colors[1]); // "green"

// Modify
colors[1] = "yellow";
console.log(colors); // ["red", "yellow", "blue"]
```

Check how many items with `.length`:
```js
console.log(colors.length); // 3
```

---

## Looping Over an Array

There are multiple ways to loop through an array in JavaScript. Each has its place.

---

### Using `for` loop
The classic approach — gives you full control over the index.

```js
const fruits = ["apple", "banana", "cherry"];

for (let i = 0; i < fruits.length; i++) {
  console.log(i, fruits[i]);
  // 0 apple
  // 1 banana
  // 2 cherry
}
```

---

### Using `while` loop
Useful when the stopping condition isn't just the length.

```js
const nums = [10, 20, 30, 40];
let i = 0;

while (i < nums.length) {
  console.log(nums[i]); // 10, 20, 30, 40
  i++;
}
```

---

### Using `forEach`
Clean and readable. Runs a function for each element. No index management needed.

```js
const fruits = ["apple", "banana", "cherry"];

fruits.forEach((fruit, index) => {
  console.log(index, fruit);
  // 0 apple
  // 1 banana
  // 2 cherry
});
```

---

### Using `for...of`
The simplest way to loop — gives you the **value** directly.

```js
const fruits = ["apple", "banana", "cherry"];

for (const fruit of fruits) {
  console.log(fruit); // apple, banana, cherry
}
```

---

### Using `for...in`
Gives you the **index** as a string key. Works but not recommended for arrays.

```js
const fruits = ["apple", "banana", "cherry"];

for (const index in fruits) {
  console.log(index, fruits[index]);
  // "0" apple, "1" banana, "2" cherry
}
```

> ⚠️ `for...in` is designed for objects. Use `for...of` or `forEach` for arrays.

---

### Quick Comparison

| Method      | Gives You       | Can `break`? | Best For                   |
|-------------|-----------------|--------------|----------------------------|
| `for`       | index           | ✅ Yes       | When index matters          |
| `while`     | index           | ✅ Yes       | Condition-based stopping    |
| `forEach`   | value + index   | ❌ No        | Simple iteration            |
| `for...of`  | value           | ✅ Yes       | Clean, simple loops         |
| `for...in`  | key (as string) | ✅ Yes       | ⚠️ Avoid for arrays         |

---

## Array Methods

---

### `push()`

Adds one or more elements to the **end** of an array. Returns the new length.

```js
const fruits = ["apple", "banana"];

fruits.push("cherry");
console.log(fruits); // ["apple", "banana", "cherry"]

// Push multiple at once
fruits.push("date", "elderberry");
console.log(fruits); // ["apple", "banana", "cherry", "date", "elderberry"]
```

---

### `pop()`

Removes the **last** element and **returns** it.

```js
const fruits = ["apple", "banana", "cherry"];

const removed = fruits.pop();
console.log(removed); // "cherry"
console.log(fruits);  // ["apple", "banana"]
```

---

### `unshift()`

Adds one or more elements to the **beginning** of an array. Returns the new length.

```js
const fruits = ["banana", "cherry"];

fruits.unshift("apple");
console.log(fruits); // ["apple", "banana", "cherry"]

// Unshift multiple
fruits.unshift("kiwi", "mango");
console.log(fruits); // ["kiwi", "mango", "apple", "banana", "cherry"]
```

---

### `shift()`

Removes the **first** element and **returns** it.

```js
const fruits = ["apple", "banana", "cherry"];

const removed = fruits.shift();
console.log(removed); // "apple"
console.log(fruits);  // ["banana", "cherry"]
```

---

### push / pop / unshift / shift — Visual Summary

```
         unshift() →  [ 🍎  🍌  🍒 ]  ← push()
          shift()  ←  [ 🍎  🍌  🍒 ]  → pop()
```

| Method      | Where      | Action  |
|-------------|------------|---------|
| `push()`    | End        | Add     |
| `pop()`     | End        | Remove  |
| `unshift()` | Beginning  | Add     |
| `shift()`   | Beginning  | Remove  |

---

### `toString()`

Converts the entire array to a **comma-separated string**.

```js
const nums = [1, 2, 3, 4, 5];
console.log(nums.toString()); // "1,2,3,4,5"

const fruits = ["apple", "banana", "cherry"];
console.log(fruits.toString()); // "apple,banana,cherry"
```

---

### `concat()`

Merges two or more arrays into a **new** array. Does not modify the originals.

```js
const a = [1, 2, 3];
const b = [4, 5, 6];
const c = [7, 8, 9];

const merged = a.concat(b);
console.log(merged); // [1, 2, 3, 4, 5, 6]

// Merge multiple arrays at once
const all = a.concat(b, c);
console.log(all); // [1, 2, 3, 4, 5, 6, 7, 8, 9]

// Original arrays are unchanged
console.log(a); // [1, 2, 3]
```

---

### `slice()`

Returns a **shallow copy** of a portion of the array from `start` to `end` (end not included). Does **not** modify the original.

```js
const fruits = ["apple", "banana", "cherry", "date", "elderberry"];

console.log(fruits.slice(1, 3)); // ["banana", "cherry"]
console.log(fruits.slice(2));    // ["cherry", "date", "elderberry"]
console.log(fruits.slice(-2));   // ["date", "elderberry"] (counts from the end)

// Original is unchanged
console.log(fruits); // ["apple", "banana", "cherry", "date", "elderberry"]
```

---

### `splice()`

The Swiss Army knife of array methods. It can **add**, **remove**, or **replace** elements — and it **modifies the original** array.

**Syntax:**
```js
array.splice(startIndex, deleteCount, item1, item2, ...)
```

**Remove elements:**
```js
const fruits = ["apple", "banana", "cherry", "date"];

const removed = fruits.splice(1, 2); // start at index 1, remove 2 items
console.log(removed); // ["banana", "cherry"]
console.log(fruits);  // ["apple", "date"]
```

**Insert elements (without removing):**
```js
const fruits = ["apple", "date"];

fruits.splice(1, 0, "banana", "cherry"); // at index 1, remove 0, add these
console.log(fruits); // ["apple", "banana", "cherry", "date"]
```

**Replace elements:**
```js
const fruits = ["apple", "banana", "cherry"];

fruits.splice(1, 1, "blueberry"); // remove 1 at index 1, insert "blueberry"
console.log(fruits); // ["apple", "blueberry", "cherry"]
```

> 🔑 `slice` = copy a portion (non-destructive). `splice` = cut/insert/replace in place (destructive).

---

### `indexOf()`

Returns the **index** of the first occurrence of a value. Returns `-1` if not found.

```js
const fruits = ["apple", "banana", "cherry", "banana"];

console.log(fruits.indexOf("banana")); // 1 (first occurrence)
console.log(fruits.indexOf("grape"));  // -1 (not found)
```

---

### `includes()`

Returns `true` or `false` — checks if a value **exists** in the array.

```js
const fruits = ["apple", "banana", "cherry"];

console.log(fruits.includes("banana")); // true
console.log(fruits.includes("grape"));  // false
```

---

### `reverse()`

Reverses the array **in place** — modifies the original.

```js
const nums = [1, 2, 3, 4, 5];

nums.reverse();
console.log(nums); // [5, 4, 3, 2, 1]
```

To reverse without modifying the original:
```js
const original = [1, 2, 3, 4, 5];
const reversed = [...original].reverse();
console.log(original); // [1, 2, 3, 4, 5] — unchanged
console.log(reversed); // [5, 4, 3, 2, 1]
```

---

### `join()`

Joins all elements into a **string**, with a custom separator.

```js
const fruits = ["apple", "banana", "cherry"];

console.log(fruits.join());       // "apple,banana,cherry" (default: comma)
console.log(fruits.join(" - ")); // "apple - banana - cherry"
console.log(fruits.join(" "));   // "apple banana cherry"
console.log(fruits.join(""));    // "applebananacherry"
```

> 💡 `join()` is like `toString()` but lets you choose the separator.

---

### `find()`

Returns the **first element** that passes a test function. Returns `undefined` if none match.

```js
const nums = [5, 12, 8, 130, 44];

const found = nums.find(num => num > 10);
console.log(found); // 12 (first value greater than 10)
```

```js
const users = [
  { id: 1, name: "Alice" },
  { id: 2, name: "Bob" },
  { id: 3, name: "Charlie" }
];

const user = users.find(u => u.id === 2);
console.log(user); // { id: 2, name: "Bob" }
```

---

### `filter()`

Returns a **new array** of all elements that pass a test. Does not modify the original.

```js
const nums = [1, 2, 3, 4, 5, 6];

const evens = nums.filter(num => num % 2 === 0);
console.log(evens); // [2, 4, 6]

const odds = nums.filter(num => num % 2 !== 0);
console.log(odds);  // [1, 3, 5]
```

```js
const words = ["spray", "limit", "elite", "exuberant", "destruction"];

const longWords = words.filter(word => word.length > 5);
console.log(longWords); // ["exuberant", "destruction"]
```

---

### `map()`

Creates a **new array** by transforming every element using a function. Does not modify the original.

```js
const nums = [1, 2, 3, 4, 5];

const doubled = nums.map(num => num * 2);
console.log(doubled); // [2, 4, 6, 8, 10]
```

```js
const names = ["alice", "bob", "charlie"];

const capitalized = names.map(name => name.toUpperCase());
console.log(capitalized); // ["ALICE", "BOB", "CHARLIE"]
```

---

### `reduce()`

Reduces the entire array down to a **single value** by accumulating results.

**Syntax:**
```js
array.reduce((accumulator, currentValue) => {
  // return updated accumulator
}, initialValue);
```

**Sum of all numbers:**
```js
const nums = [1, 2, 3, 4, 5];

const sum = nums.reduce((acc, curr) => acc + curr, 0);
console.log(sum); // 15
```

**How it works step by step:**
```
acc=0,  curr=1  →  0  + 1 = 1
acc=1,  curr=2  →  1  + 2 = 3
acc=3,  curr=3  →  3  + 3 = 6
acc=6,  curr=4  →  6  + 4 = 10
acc=10, curr=5  →  10 + 5 = 15
```

**Find the max value:**
```js
const nums = [3, 17, 5, 9, 2];

const max = nums.reduce((acc, curr) => (curr > acc ? curr : acc), 0);
console.log(max); // 17
```

---

## Spread Operator with Arrays

The **spread operator** `...` expands an array into individual elements.

**Copy an array:**
```js
const original = [1, 2, 3];
const copy = [...original];
copy.push(4);

console.log(original); // [1, 2, 3] — unchanged
console.log(copy);     // [1, 2, 3, 4]
```

**Merge arrays:**
```js
const a = [1, 2, 3];
const b = [4, 5, 6];

const merged = [...a, ...b];
console.log(merged); // [1, 2, 3, 4, 5, 6]
```

**Insert in the middle:**
```js
const start = [1, 2];
const end   = [5, 6];

const full = [...start, 3, 4, ...end];
console.log(full); // [1, 2, 3, 4, 5, 6]
```

---

## Array Destructuring

Destructuring lets you **unpack** values from an array into individual variables cleanly.

**Basic:**
```js
const fruits = ["apple", "banana", "cherry"];

const [first, second, third] = fruits;
console.log(first);  // "apple"
console.log(second); // "banana"
console.log(third);  // "cherry"
```

**Skip elements:**
```js
const [,, third] = ["apple", "banana", "cherry"];
console.log(third); // "cherry"
```

**With rest operator:**
```js
const [head, ...tail] = [1, 2, 3, 4, 5];
console.log(head); // 1
console.log(tail); // [2, 3, 4, 5]
```

**Swap two variables:**
```js
let a = 1, b = 2;
[a, b] = [b, a];
console.log(a, b); // 2 1
```

---

## Methods Cheat Sheet

| Method        | Modifies Original? | Returns                | What it does                         |
|---------------|--------------------|------------------------|--------------------------------------|
| `push()`      | ✅ Yes             | New length             | Adds to end                          |
| `pop()`       | ✅ Yes             | Removed element        | Removes from end                     |
| `unshift()`   | ✅ Yes             | New length             | Adds to beginning                    |
| `shift()`     | ✅ Yes             | Removed element        | Removes from beginning               |
| `splice()`    | ✅ Yes             | Array of removed items | Add / remove / replace at any index  |
| `reverse()`   | ✅ Yes             | The reversed array     | Reverses in place                    |
| `toString()`  | ❌ No              | String                 | Converts to comma-separated string   |
| `concat()`    | ❌ No              | New array              | Merges arrays                        |
| `slice()`     | ❌ No              | New array (portion)    | Copies a section                     |
| `indexOf()`   | ❌ No              | Index or `-1`          | Finds first index of a value         |
| `includes()`  | ❌ No              | `true` / `false`       | Checks if value exists               |
| `join()`      | ❌ No              | String                 | Joins elements into a string         |
| `find()`      | ❌ No              | First matching element | Finds first element passing a test   |
| `filter()`    | ❌ No              | New array              | Filters elements passing a test      |
| `map()`       | ❌ No              | New array              | Transforms every element             |
| `reduce()`    | ❌ No              | Single value           | Accumulates array into one result    |

---

> 💡 **Key Takeaway:** Methods like `push`, `pop`, `splice`, `reverse` **mutate** the original array. Methods like `map`, `filter`, `slice`, `concat` return a **new array** and leave the original untouched. Knowing this difference will save you from tricky bugs.