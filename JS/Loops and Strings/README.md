# JavaScript — Loops & Strings

---

## 📌 Table of Contents
1. [Loops](#loops)
   - [for](#1-for-loop)
   - [while](#2-while-loop)
   - [do...while](#3-dowhile-loop)
   - [forEach](#4-foreach)
   - [for...of](#5-forof)
   - [for...in](#6-forin)
2. [Strings](#strings)
   - [Creating Strings](#creating-strings)
   - [String Indices](#string-indices)
   - [.length](#length)
   - [Template Literals](#template-literals)
   - [String Methods](#string-methods)

---

## Loops

Loops let you run a block of code repeatedly. JavaScript gives you several ways to loop depending on the situation.

---

### 1. `for` Loop

The most common loop. Best when you know **how many times** you want to iterate.

**Syntax:**
```js
for (initialization; condition; update) {
  // code to run
}
```

**Example:**
```js
for (let i = 0; i < 5; i++) {
  console.log(i); // 0, 1, 2, 3, 4
}
```

- `let i = 0` → starts at 0
- `i < 5` → runs while this is true
- `i++` → increments after each loop

---

### 2. `while` Loop

Runs **as long as** a condition is true. Use when you don't know the exact number of iterations upfront.

**Syntax:**
```js
while (condition) {
  // code to run
}
```

**Example:**
```js
let count = 0;

while (count < 3) {
  console.log("count is:", count); // 0, 1, 2
  count++;
}
```

> ⚠️ Always make sure the condition eventually becomes `false`, or you'll get an infinite loop.

---

### 3. `do...while` Loop

Similar to `while`, but the code block runs **at least once** — the condition is checked *after* the first execution.

**Syntax:**
```js
do {
  // code to run
} while (condition);
```

**Example:**
```js
let x = 10;

do {
  console.log(x); // prints 10, even though condition is false
  x++;
} while (x < 5);
```

---

### 4. `forEach`

A method available on **arrays**. It calls a function once for each element. Clean and readable — ideal for simply iterating over array items.

**Syntax:**
```js
array.forEach(function(element, index) {
  // code to run
});
```

**Example:**
```js
const fruits = ["apple", "banana", "cherry"];

fruits.forEach((fruit, index) => {
  console.log(index, fruit);
  // 0 apple
  // 1 banana
  // 2 cherry
});
```

> ℹ️ `forEach` cannot be stopped early with `break`. Use a `for` loop if you need that.

---

### 5. `for...of`

Iterates over **iterable values** — arrays, strings, Sets, Maps, etc. Gives you the **value** directly.

**Syntax:**
```js
for (const item of iterable) {
  // code to run
}
```

**Example:**
```js
const colors = ["red", "green", "blue"];

for (const color of colors) {
  console.log(color); // red, green, blue
}
```

Works on strings too:
```js
for (const char of "hello") {
  console.log(char); // h, e, l, l, o
}
```

---

### 6. `for...in`

Iterates over the **keys (property names)** of an object. Best suited for plain objects.

**Syntax:**
```js
for (const key in object) {
  // code to run
}
```

**Example:**
```js
const user = { name: "Alice", age: 25, city: "Mumbai" };

for (const key in user) {
  console.log(key, "→", user[key]);
  // name → Alice
  // age → 25
  // city → Mumbai
}
```

> ⚠️ Avoid `for...in` on arrays — use `for...of` or `forEach` instead.

---

### Quick Comparison

| Loop         | Best For                          | Returns      |
|--------------|-----------------------------------|--------------|
| `for`        | Known number of iterations        | —            |
| `while`      | Unknown iterations, condition-based | —          |
| `do...while` | Run at least once                 | —            |
| `forEach`    | Array iteration (no break needed) | —            |
| `for...of`   | Iterables (arrays, strings, etc.) | **values**   |
| `for...in`   | Object properties                 | **keys**     |

---

## Strings

A **string** is a sequence of characters used to represent text. Strings are **immutable** — string methods always return a new string, they never change the original.

---

### Creating Strings

You can create strings using single quotes, double quotes, or backticks:

```js
const a = 'Hello';          // single quotes
const b = "World";          // double quotes
const c = `Hello, World!`;  // backticks (template literal)
```

All three are valid. Backticks unlock extra features — more on that below.

---

### String Indices

Each character in a string has an **index**, starting at `0`.

```
  H   e   l   l   o
  0   1   2   3   4
```

```js
const str = "Hello";
console.log(str[0]); // "H"
console.log(str[4]); // "o"
```

---

### `.length`

Returns the **total number of characters** in a string.

```js
const str = "JavaScript";
console.log(str.length); // 10
```

> ℹ️ `.length` is a property, not a method — no parentheses needed.

---

### Template Literals

Template literals use **backticks** and allow:
- **Embedded expressions** using `${}`
- **Multi-line strings** without `\n`

```js
const name = "Alice";
const age = 25;

const message = `My name is ${name} and I am ${age} years old.`;
console.log(message);
// My name is Alice and I am 25 years old.
```

Multi-line:
```js
const poem = `Roses are red,
Violets are blue,
JavaScript is awesome,
And so are you!`;
```

---

### String Methods

---

#### `str.toUpperCase()` / `str.toLowerCase()`

Converts all characters to uppercase or lowercase.

```js
const str = "Hello World";

console.log(str.toUpperCase()); // "HELLO WORLD"
console.log(str.toLowerCase()); // "hello world"
```

---

#### `str.trim()`

Removes **whitespace** from both ends of a string. Useful for cleaning up user input.

```js
const str = "   hello   ";
console.log(str.trim()); // "hello"
```

---

#### `str1.concat(str2)`

Joins two or more strings together.

```js
const first = "Hello";
const second = " World";

console.log(first.concat(second));        // "Hello World"
console.log(first.concat(", ", "JS!"));   // "Hello, JS!"
```

> ℹ️ The `+` operator does the same thing: `"Hello" + " World"`.

---

#### `str.slice(start, end)`

Extracts a **portion** of a string from `start` up to (but not including) `end`.

```js
const str = "JavaScript";

console.log(str.slice(0, 4));  // "Java"
console.log(str.slice(4));     // "Script"
console.log(str.slice(-6));    // "Script" (negative counts from the end)
```

---

#### `str.replace(searchVal, newVal)`

Replaces the **first occurrence** of `searchVal` with `newVal`.

```js
const str = "I love cats. Cats are great.";

console.log(str.replace("cats", "dogs")); // "I love dogs. Cats are great."
```

To replace **all occurrences**, use `replaceAll()` or a regex with the `g` flag:
```js
console.log(str.replaceAll("cats", "dogs"));
// or
console.log(str.replace(/cats/gi, "dogs")); // case-insensitive, global
```

---

#### `str.charAt(index)`

Returns the character at a given **index**. Similar to `str[index]`.

```js
const str = "Hello";

console.log(str.charAt(0)); // "H"
console.log(str.charAt(4)); // "o"
console.log(str.charAt(9)); // "" (out of range → empty string)
```

> `str.charAt(i)` returns `""` for invalid indices, while `str[i]` returns `undefined`.

---

### String Methods Summary

| Method                        | What it does                                |
|-------------------------------|---------------------------------------------|
| `.length`                     | Number of characters                        |
| `.toUpperCase()`              | Converts to UPPERCASE                       |
| `.toLowerCase()`              | Converts to lowercase                       |
| `.trim()`                     | Removes leading & trailing whitespace       |
| `.concat(str2)`               | Joins strings together                      |
| `.slice(start, end)`          | Extracts a substring                        |
| `.replace(searchVal, newVal)` | Replaces first match                        |
| `.charAt(index)`              | Character at a specific index               |

---

> 💡 **Remember:** Strings are immutable. Every method returns a **new** string — the original is never changed.