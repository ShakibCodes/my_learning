# JavaScript — Functions

---

## 📌 Table of Contents
1. [What is a Function?](#what-is-a-function)
2. [Function Declaration](#function-declaration)
3. [Function Call](#function-call)
4. [Parameters & Arguments](#parameters--arguments)
5. [Return Values](#return-values)
6. [Function Expression](#function-expression)
7. [Arrow Functions](#arrow-functions)
8. [Default Parameters](#default-parameters)
9. [Rest Parameters](#rest-parameters)
10. [Callback Functions](#callback-functions)
11. [forEach with Callbacks](#foreach-with-callbacks)
12. [Array Methods with Functions](#array-methods-with-functions)
    - [map()](#map)
    - [filter()](#filter)
    - [find()](#find)
    - [reduce()](#reduce)
    - [some() & every()](#some--every)
    - [sort()](#sort)
13. [Chaining Array Methods](#chaining-array-methods)
14. [Quick Reference](#quick-reference)

---

## What is a Function?

A **function** is a reusable block of code that performs a specific task. Instead of writing the same code multiple times, you define it once and **call** it whenever you need it.

```js
// Without a function — repeated code
console.log("Hello, Alice!");
console.log("Hello, Bob!");
console.log("Hello, Charlie!");

// With a function — write once, use many times
function greet(name) {
  console.log("Hello, " + name + "!");
}

greet("Alice");   // Hello, Alice!
greet("Bob");     // Hello, Bob!
greet("Charlie"); // Hello, Charlie!
```

---

## Function Declaration

A **function declaration** defines a named function using the `function` keyword.

**Syntax:**
```js
function functionName(parameters) {
  // code to run
}
```

**Example:**
```js
function sayHello() {
  console.log("Hello, World!");
}
```

> 💡 Function declarations are **hoisted** — you can call them even before they appear in the code.

```js
sayHello(); // Works fine! ✅

function sayHello() {
  console.log("Hello!");
}
```

---

## Function Call

Defining a function does nothing on its own — you have to **call** (invoke) it.

```js
function sayHello() {
  console.log("Hello, World!");
}

// Calling the function
sayHello(); // Hello, World!
sayHello(); // Hello, World! (call it as many times as you want)
```

---

## Parameters & Arguments

**Parameters** are the placeholders defined in the function. **Arguments** are the actual values passed when calling it.

```js
//              parameters ↓    ↓
function add(a, b) {
  console.log(a + b);
}

//        arguments ↓  ↓
add(3, 5); // 8
add(10, 20); // 30
```

You can pass as many parameters as needed:

```js
function introduce(name, age, city) {
  console.log(`I'm ${name}, ${age} years old, from ${city}.`);
}

introduce("Alice", 25, "Mumbai"); // I'm Alice, 25 years old, from Mumbai.
```

---

## Return Values

Functions can **return** a value back to wherever they were called from.

```js
function multiply(a, b) {
  return a * b;
}

const result = multiply(4, 5);
console.log(result); // 20
```

Without `return`, a function returns `undefined` by default.

```js
function add(a, b) {
  const sum = a + b;
  // no return — nothing comes back
}

console.log(add(2, 3)); // undefined
```

> ⚠️ Once `return` runs, the function stops immediately. Code after it is never reached.

```js
function check(num) {
  if (num > 0) return "positive";
  if (num < 0) return "negative";
  return "zero";
}

console.log(check(5));  // "positive"
console.log(check(-3)); // "negative"
console.log(check(0));  // "zero"
```

---

## Function Expression

A **function expression** assigns a function to a variable. The function can be named or anonymous.

```js
const greet = function(name) {
  return `Hello, ${name}!`;
};

console.log(greet("Bob")); // Hello, Bob!
```

> ⚠️ Unlike declarations, function expressions are **not hoisted** — you must define them before calling them.

```js
greet("Bob"); // ❌ ReferenceError — can't call before definition

const greet = function(name) {
  return `Hello, ${name}!`;
};
```

---

## Arrow Functions

**Arrow functions** are a shorter, modern way to write functions introduced in ES6. They use the `=>` syntax.

**Syntax:**
```js
const functionName = (parameters) => {
  // code
};
```

**Regular function vs Arrow function:**
```js
// Regular function
function add(a, b) {
  return a + b;
}

// Arrow function — exact same behaviour
const add = (a, b) => {
  return a + b;
};
```

---

### Shorthand Rules

**1. Single parameter — parentheses optional:**
```js
const double = num => {
  return num * 2;
};
```

**2. Single expression — curly braces and `return` optional (implicit return):**
```js
const double = num => num * 2;

console.log(double(5)); // 10
```

**3. No parameters — empty parentheses required:**
```js
const greet = () => "Hello, World!";

console.log(greet()); // Hello, World!
```

**All three forms side by side:**
```js
// Full form
const square = (num) => { return num * num; };

// Drop the braces + return (single expression)
const square = (num) => num * num;

// Drop the parentheses too (single parameter)
const square = num => num * num;

console.log(square(6)); // 36
```

---

## Default Parameters

You can set **default values** for parameters in case no argument is passed.

```js
function greet(name = "stranger") {
  return `Hello, ${name}!`;
}

console.log(greet("Alice")); // Hello, Alice!
console.log(greet());        // Hello, stranger!
```

Works with arrow functions too:
```js
const power = (base, exp = 2) => base ** exp;

console.log(power(3));    // 9  (3² — uses default exp=2)
console.log(power(3, 3)); // 27 (3³)
```

---

## Rest Parameters

**Rest parameters** (`...`) let a function accept any number of arguments as an array.

```js
function sum(...numbers) {
  return numbers.reduce((acc, curr) => acc + curr, 0);
}

console.log(sum(1, 2, 3));       // 6
console.log(sum(1, 2, 3, 4, 5)); // 15
```

You can mix regular and rest parameters — rest must always come last:
```js
function introduce(greeting, ...names) {
  names.forEach(name => console.log(`${greeting}, ${name}!`));
}

introduce("Hello", "Alice", "Bob", "Charlie");
// Hello, Alice!
// Hello, Bob!
// Hello, Charlie!
```

---

## Callback Functions

A **callback** is a function passed as an **argument** to another function, to be called later.

```js
function doSomething(callback) {
  console.log("Doing something...");
  callback(); // calling the function that was passed in
}

function sayDone() {
  console.log("Done!");
}

doSomething(sayDone);
// Doing something...
// Done!
```

You can also pass an **anonymous function** directly:
```js
doSomething(function() {
  console.log("Done!");
});
```

Or an **arrow function**:
```js
doSomething(() => console.log("Done!"));
```

> 💡 Callbacks are the foundation of how methods like `forEach`, `map`, and `filter` work.

---

## `forEach` with Callbacks

`forEach` takes a **callback function** and runs it once for every element in the array.

The callback receives three arguments automatically:

```js
array.forEach(function(value, index, array) {
  // value  → current element
  // index  → current index
  // array  → the whole array (rarely used)
});
```

**With a named callback:**
```js
function printItem(value, index) {
  console.log(`[${index}] → ${value}`);
}

const fruits = ["apple", "banana", "cherry"];
fruits.forEach(printItem);
// [0] → apple
// [1] → banana
// [2] → cherry
```

**With an anonymous function:**
```js
const nums = [10, 20, 30];

nums.forEach(function(value, index) {
  console.log(`Index ${index}: ${value}`);
});
```

**With an arrow function (most common):**
```js
const nums = [10, 20, 30];

nums.forEach((value, index) => {
  console.log(`Index ${index}: ${value}`);
});
// Index 0: 10
// Index 1: 20
// Index 2: 30
```

---

## Array Methods with Functions

These methods all accept a **callback function** and do powerful work with very little code.

---

### `map()`

Transforms **every** element and returns a **new array** of the same length. The original is unchanged.

**Callback receives:** `(value, index, array)`

```js
// arr.map(callbackFnx(value, index, array))

const nums = [1, 2, 3, 4, 5];

const squared = nums.map(function(value, index, array) {
  console.log(`index: ${index}, array: ${array}`); // full info available
  return value * value;
});

console.log(squared); // [1, 4, 9, 16, 25]
```

**Using arrow functions (the common way):**
```js
const nums = [1, 2, 3, 4, 5];

const doubled   = nums.map(val => val * 2);
const asStrings = nums.map(val => `Item ${val}`);
const isEven    = nums.map(val => val % 2 === 0);

console.log(doubled);   // [2, 4, 6, 8, 10]
console.log(asStrings); // ["Item 1", "Item 2", "Item 3", "Item 4", "Item 5"]
console.log(isEven);    // [false, true, false, true, false]
```

**With an array of objects:**
```js
const users = [
  { name: "Alice", age: 25 },
  { name: "Bob",   age: 30 },
  { name: "Carol", age: 22 }
];

const names = users.map(user => user.name);
console.log(names); // ["Alice", "Bob", "Carol"]

const nextYear = users.map(user => ({
  name: user.name,
  age: user.age + 1
}));
console.log(nextYear);
// [{ name: "Alice", age: 26 }, { name: "Bob", age: 31 }, { name: "Carol", age: 23 }]
```

---

### `filter()`

Returns a **new array** containing only elements for which the callback returns `true`.

**Callback receives:** `(value, index, array)`

```js
const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

// Keep only even numbers
const evens = nums.filter(val => val % 2 === 0);
console.log(evens); // [2, 4, 6, 8, 10]

// Keep only numbers greater than 5
const big = nums.filter(val => val > 5);
console.log(big); // [6, 7, 8, 9, 10]
```

**With strings:**
```js
const words = ["cat", "elephant", "dog", "rhinoceros", "ant"];

const longWords  = words.filter(word => word.length > 4);
const shortWords = words.filter(word => word.length <= 3);

console.log(longWords);  // ["elephant", "rhinoceros"]
console.log(shortWords); // ["cat", "dog", "ant"]
```

**With objects:**
```js
const products = [
  { name: "Laptop",  price: 80000, inStock: true  },
  { name: "Phone",   price: 50000, inStock: false },
  { name: "Tablet",  price: 30000, inStock: true  },
  { name: "Monitor", price: 20000, inStock: false }
];

// Only in-stock items
const available = products.filter(product => product.inStock);
console.log(available);
// [{ name: "Laptop", ... }, { name: "Tablet", ... }]

// Only affordable items
const affordable = products.filter(product => product.price < 40000);
console.log(affordable);
// [{ name: "Tablet", ... }, { name: "Monitor", ... }]
```

---

### `find()`

Returns the **first element** where the callback returns `true`. Returns `undefined` if nothing matches.

```js
const nums = [5, 12, 8, 130, 44];

const firstBig = nums.find(val => val > 10);
console.log(firstBig); // 12 (stops at first match)
```

```js
const users = [
  { id: 1, name: "Alice" },
  { id: 2, name: "Bob"   },
  { id: 3, name: "Carol" }
];

const user = users.find(u => u.id === 2);
console.log(user); // { id: 2, name: "Bob" }

const missing = users.find(u => u.id === 99);
console.log(missing); // undefined
```

> 💡 `find()` returns the **element**. `findIndex()` returns its **index**.

```js
const idx = users.findIndex(u => u.name === "Carol");
console.log(idx); // 2
```

---

### `reduce()`

Reduces the array to a **single value** by running a callback on each element and accumulating the result.

**Syntax:**
```js
array.reduce((accumulator, currentValue, index, array) => {
  return updatedAccumulator;
}, initialValue);
```

**Sum:**
```js
const nums = [10, 20, 30, 40];

const total = nums.reduce((acc, curr) => acc + curr, 0);
console.log(total); // 100
```

**Step-by-step breakdown:**
```
Start:  acc = 0
Step 1: acc = 0  + 10 = 10
Step 2: acc = 10 + 20 = 30
Step 3: acc = 30 + 30 = 60
Step 4: acc = 60 + 40 = 100
```

**Product of all numbers:**
```js
const nums = [1, 2, 3, 4, 5];

const product = nums.reduce((acc, curr) => acc * curr, 1);
console.log(product); // 120
```

**Flatten an array of arrays:**
```js
const nested = [[1, 2], [3, 4], [5, 6]];

const flat = nested.reduce((acc, curr) => acc.concat(curr), []);
console.log(flat); // [1, 2, 3, 4, 5, 6]
```

**Count occurrences:**
```js
const fruits = ["apple", "banana", "apple", "cherry", "banana", "apple"];

const count = fruits.reduce((acc, fruit) => {
  acc[fruit] = (acc[fruit] || 0) + 1;
  return acc;
}, {});

console.log(count);
// { apple: 3, banana: 2, cherry: 1 }
```

---

### `some()` & `every()`

These return a **boolean** — they test whether elements pass a condition.

**`some()`** — returns `true` if **at least one** element passes the test.

```js
const nums = [1, 3, 5, 8, 9];

console.log(nums.some(val => val % 2 === 0)); // true  (8 is even)
console.log(nums.some(val => val > 100));      // false (none > 100)
```

**`every()`** — returns `true` only if **all** elements pass the test.

```js
const nums = [2, 4, 6, 8];

console.log(nums.every(val => val % 2 === 0)); // true  (all even)
console.log(nums.every(val => val > 5));       // false (2, 4 are not > 5)
```

**Real-world example:**
```js
const users = [
  { name: "Alice", verified: true  },
  { name: "Bob",   verified: true  },
  { name: "Carol", verified: false }
];

const anyVerified = users.some(u => u.verified);
console.log(anyVerified); // true

const allVerified = users.every(u => u.verified);
console.log(allVerified); // false
```

---

### `sort()`

Sorts the array **in place**. Without a callback it sorts as **strings** (which breaks numbers). Always pass a compare function for numbers.

**Sorting strings (default — works fine):**
```js
const fruits = ["banana", "apple", "cherry", "date"];

fruits.sort();
console.log(fruits); // ["apple", "banana", "cherry", "date"]
```

**Sorting numbers — need a compare function:**
```js
const nums = [40, 1, 100, 5, 25];

// ❌ Wrong — sorts as strings
nums.sort();
console.log(nums); // [1, 100, 25, 40, 5]  ← incorrect!

// ✅ Correct — ascending
nums.sort((a, b) => a - b);
console.log(nums); // [1, 5, 25, 40, 100]

// ✅ Correct — descending
nums.sort((a, b) => b - a);
console.log(nums); // [100, 40, 25, 5, 1]
```

**How the compare function works:**
- Returns **negative** → `a` comes before `b`
- Returns **positive** → `b` comes before `a`
- Returns **0** → order unchanged

**Sort objects by a property:**
```js
const people = [
  { name: "Charlie", age: 30 },
  { name: "Alice",   age: 25 },
  { name: "Bob",     age: 28 }
];

// Sort by age ascending
people.sort((a, b) => a.age - b.age);
console.log(people);
// [{ Alice, 25 }, { Bob, 28 }, { Charlie, 30 }]

// Sort by name alphabetically
people.sort((a, b) => a.name.localeCompare(b.name));
console.log(people);
// [{ Alice, 25 }, { Bob, 28 }, { Charlie, 30 }]
```

---

## Chaining Array Methods

Since `map`, `filter`, and similar methods return new arrays, you can **chain** them together for powerful one-liners.

**Example — get doubled values of even numbers:**
```js
const nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

const result = nums
  .filter(val => val % 2 === 0)  // [2, 4, 6, 8, 10]
  .map(val => val * 2);          // [4, 8, 12, 16, 20]

console.log(result); // [4, 8, 12, 16, 20]
```

**Example — sum of prices of in-stock products:**
```js
const products = [
  { name: "Laptop",  price: 80000, inStock: true  },
  { name: "Phone",   price: 50000, inStock: false },
  { name: "Tablet",  price: 30000, inStock: true  },
  { name: "Monitor", price: 20000, inStock: false },
  { name: "Keyboard",price: 5000,  inStock: true  }
];

const totalInStock = products
  .filter(p => p.inStock)              // keep only in-stock
  .map(p => p.price)                   // extract prices → [80000, 30000, 5000]
  .reduce((acc, price) => acc + price, 0); // sum them up

console.log(totalInStock); // 115000
```

**Example — names of users over 25, sorted:**
```js
const users = [
  { name: "Charlie", age: 30 },
  { name: "Alice",   age: 22 },
  { name: "Bob",     age: 28 },
  { name: "Diana",   age: 35 }
];

const result = users
  .filter(u => u.age > 25)
  .map(u => u.name)
  .sort();

console.log(result); // ["Bob", "Charlie", "Diana"]
```

---

## Quick Reference

### Function Types

| Type                | Syntax                              | Hoisted? |
|---------------------|-------------------------------------|----------|
| Declaration         | `function name() {}`                | ✅ Yes   |
| Expression          | `const name = function() {}`        | ❌ No    |
| Arrow (full)        | `const name = (a, b) => { ... }`   | ❌ No    |
| Arrow (short)       | `const name = val => val * 2`      | ❌ No    |

### Array Methods with Callbacks

| Method      | Returns        | Callback Purpose                         |
|-------------|----------------|------------------------------------------|
| `forEach()` | `undefined`    | Run code for each element                |
| `map()`     | New array      | Transform each element                   |
| `filter()`  | New array      | Keep elements that pass a test           |
| `find()`    | Single element | Get first element that passes a test     |
| `reduce()`  | Single value   | Accumulate all elements into one result  |
| `some()`    | `true`/`false` | Does at least one element pass?          |
| `every()`   | `true`/`false` | Do all elements pass?                    |
| `sort()`    | Same array     | Reorder elements (mutates original)      |

---

> 💡 **Key Takeaway:** Callbacks are just functions passed as arguments. Arrow functions make callbacks short and readable. Methods like `map`, `filter`, and `reduce` are the backbone of clean, modern JavaScript — master these and you'll write far less code for far more power.