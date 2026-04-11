# JavaScript — Classes & Objects

---

## 📌 Table of Contents
1. [What is an Object?](#what-is-an-object)
2. [Ways to Create an Object](#ways-to-create-an-object)
   - [Object Literal](#1-object-literal)
   - [Constructor Function](#2-constructor-function)
   - [Object.create()](#3-objectcreate)
   - [Class (ES6)](#4-class-es6)
3. [Accessing & Modifying Properties](#accessing--modifying-properties)
4. [Object Methods](#object-methods)
5. [Looping Over an Object](#looping-over-an-object)
6. [Prototypes in JavaScript](#prototypes-in-javascript)
7. [Classes](#classes)
   - [Class Declaration](#class-declaration)
   - [Constructor](#constructor)
   - [Class Methods](#class-methods)
   - [Static Methods](#static-methods)
   - [Getters & Setters](#getters--setters)
8. [Inheritance](#inheritance)
9. [The `super` Keyword](#the-super-keyword)
10. [Method Overriding](#method-overriding)
11. [Private Fields](#private-fields)
12. [Error Handling](#error-handling)
    - [try / catch / finally](#try--catch--finally)
    - [Custom Errors](#custom-errors)
    - [Error Types](#error-types)
13. [Quick Reference](#quick-reference)

---

## What is an Object?

An **object** is a collection of related data and behaviour stored as **key-value pairs**. It represents a real-world thing — a user, a product, a car.

```js
// A real-world "person" represented as a JS object
const person = {
  name: "Alice",
  age: 25,
  city: "Mumbai",
  isStudent: false
};
```

- The **keys** (`name`, `age`, `city`) are called **properties**
- The **values** can be anything — strings, numbers, booleans, arrays, functions, or even other objects

---

## Ways to Create an Object

---

### 1. Object Literal

The simplest and most common way. Just use `{}`.

```js
const car = {
  brand: "Toyota",
  model: "Camry",
  year: 2023,
  color: "white"
};
```

Best for: **one-off objects** where you only need one instance.

---

### 2. Constructor Function

A regular function that acts as a blueprint for creating multiple objects. Use `new` to call it.

```js
function Person(name, age, city) {
  this.name = name;
  this.age  = age;
  this.city = city;
}

const alice = new Person("Alice", 25, "Mumbai");
const bob   = new Person("Bob",   30, "Delhi");

console.log(alice.name); // "Alice"
console.log(bob.city);   // "Delhi"
```

> `this` refers to the new object being created.

---

### 3. `Object.create()`

Creates a new object with a specified **prototype**. Gives you fine control over inheritance.

```js
const animalProto = {
  speak() {
    console.log(`${this.name} makes a sound.`);
  }
};

const dog = Object.create(animalProto);
dog.name = "Rex";
dog.speak(); // Rex makes a sound.
```

---

### 4. Class (ES6)

The modern, clean way to create objects — covered in depth below.

```js
class Person {
  constructor(name, age) {
    this.name = name;
    this.age  = age;
  }
}

const alice = new Person("Alice", 25);
```

---

## Accessing & Modifying Properties

**Dot notation** — most common:
```js
const user = { name: "Alice", age: 25 };

console.log(user.name); // "Alice"
user.age = 26;          // modify
user.city = "Mumbai";   // add new property
delete user.age;        // remove property
```

**Bracket notation** — useful when the key is dynamic or has spaces:
```js
const key = "name";
console.log(user[key]);        // "Alice"
console.log(user["city"]);     // "Mumbai"
```

**Check if a property exists:**
```js
console.log("name" in user); // true
console.log("phone" in user); // false
```

---

## Object Methods

When a function is stored as a property of an object, it's called a **method**.

```js
const person = {
  name: "Alice",
  age: 25,
  greet() {
    console.log(`Hi, I'm ${this.name} and I'm ${this.age} years old.`);
  },
  birthday() {
    this.age++;
    console.log(`Happy Birthday! Now ${this.age}.`);
  }
};

person.greet();    // Hi, I'm Alice and I'm 25 years old.
person.birthday(); // Happy Birthday! Now 26.
```

> `this` inside a method refers to the object the method belongs to.

---

## Looping Over an Object

```js
const scores = { Alice: 95, Bob: 82, Carol: 78 };

// Keys
for (const key in scores) {
  console.log(key, "→", scores[key]);
}
// Alice → 95 / Bob → 82 / Carol → 78

// Get arrays of keys, values, or pairs
console.log(Object.keys(scores));   // ["Alice", "Bob", "Carol"]
console.log(Object.values(scores)); // [95, 82, 78]
console.log(Object.entries(scores));
// [["Alice", 95], ["Bob", 82], ["Carol", 78]]
```

---

## Prototypes in JavaScript

Every object in JavaScript has a hidden link to another object called its **prototype**. When you access a property that doesn't exist on an object, JS automatically looks up the prototype chain until it finds it (or reaches `null`).

```js
const animal = {
  breathe() {
    console.log("Breathing...");
  }
};

const dog = Object.create(animal); // dog's prototype = animal
dog.name = "Rex";

dog.breathe(); // "Breathing..." — found on the prototype, not on dog itself
console.log(dog.hasOwnProperty("name"));    // true  (own property)
console.log(dog.hasOwnProperty("breathe")); // false (inherited from prototype)
```

**The Prototype Chain:**
```
dog  →  animal  →  Object.prototype  →  null
```

When you call `dog.breathe()`, JS checks:
1. Does `dog` have `breathe`? → No
2. Does `dog`'s prototype (`animal`) have `breathe`? → ✅ Yes — use it

**Constructor functions & prototypes:**
```js
function Car(brand) {
  this.brand = brand;
}

// Methods added to the prototype are shared by all instances (memory efficient)
Car.prototype.drive = function() {
  console.log(`${this.brand} is driving.`);
};

const tesla = new Car("Tesla");
const bmw   = new Car("BMW");

tesla.drive(); // Tesla is driving.
bmw.drive();   // BMW is driving.

// Both share the same drive function — not duplicated in memory
console.log(tesla.drive === bmw.drive); // true
```

> 💡 **ES6 Classes are just cleaner syntax over prototypes** — under the hood, it's the same prototype chain.

---

## Classes

A **class** is a blueprint for creating objects. It bundles data (properties) and behaviour (methods) into one clean structure.

---

### Class Declaration

```js
class Person {
  // class body
}

const alice = new Person();
```

> ⚠️ Unlike function declarations, classes are **not hoisted**. Define the class before using it.

---

### Constructor

The `constructor` is a special method that runs **automatically** when you create a new instance with `new`. It sets up the initial state of the object.

```js
class Person {
  constructor(name, age, city) {
    this.name = name; // instance property
    this.age  = age;
    this.city = city;
  }
}

const alice = new Person("Alice", 25, "Mumbai");
const bob   = new Person("Bob",   30, "Delhi");

console.log(alice.name); // "Alice"
console.log(bob.age);    // 30
```

A class can only have **one** constructor.

---

### Class Methods

Methods are defined directly inside the class body — no `function` keyword needed.

```js
class Person {
  constructor(name, age) {
    this.name = name;
    this.age  = age;
  }

  greet() {
    console.log(`Hi, I'm ${this.name}!`);
  }

  isAdult() {
    return this.age >= 18;
  }

  birthday() {
    this.age++;
    console.log(`${this.name} is now ${this.age}.`);
  }
}

const alice = new Person("Alice", 25);

alice.greet();            // Hi, I'm Alice!
console.log(alice.isAdult()); // true
alice.birthday();         // Alice is now 26.
```

---

### Static Methods

**Static methods** belong to the **class itself**, not to any instance. You call them on the class, not on an object.

```js
class MathHelper {
  static add(a, b) {
    return a + b;
  }

  static multiply(a, b) {
    return a * b;
  }
}

console.log(MathHelper.add(3, 4));      // 7
console.log(MathHelper.multiply(3, 4)); // 12

// ❌ Can't call on an instance
const m = new MathHelper();
m.add(1, 2); // TypeError
```

A practical example — a factory static method:
```js
class User {
  constructor(name, role) {
    this.name = name;
    this.role = role;
  }

  static createAdmin(name) {
    return new User(name, "admin");
  }
}

const admin = User.createAdmin("Alice");
console.log(admin); // User { name: "Alice", role: "admin" }
```

---

### Getters & Setters

**Getters** let you access a computed value as if it's a property.
**Setters** let you run logic when a property is assigned.

```js
class Circle {
  constructor(radius) {
    this.radius = radius;
  }

  get area() {
    return (Math.PI * this.radius ** 2).toFixed(2);
  }

  get diameter() {
    return this.radius * 2;
  }

  set diameter(d) {
    this.radius = d / 2;
  }
}

const c = new Circle(5);

console.log(c.area);     // "78.54"  — called like a property, not a method
console.log(c.diameter); // 10

c.diameter = 20; // triggers the setter
console.log(c.radius);   // 10
```

---

## Inheritance

**Inheritance** lets one class **extend** another, gaining all its properties and methods — and adding its own on top.

```js
// Parent class (Superclass)
class Animal {
  constructor(name, sound) {
    this.name  = name;
    this.sound = sound;
  }

  speak() {
    console.log(`${this.name} says ${this.sound}!`);
  }

  eat() {
    console.log(`${this.name} is eating.`);
  }
}

// Child class (Subclass) — inherits from Animal
class Dog extends Animal {
  constructor(name) {
    super(name, "Woof"); // calls Animal's constructor
    this.tricks = [];
  }

  learn(trick) {
    this.tricks.push(trick);
    console.log(`${this.name} learned: ${trick}`);
  }

  showTricks() {
    console.log(`${this.name}'s tricks: ${this.tricks.join(", ")}`);
  }
}

const rex = new Dog("Rex");

rex.speak();          // Rex says Woof!   ← inherited from Animal
rex.eat();            // Rex is eating.   ← inherited from Animal
rex.learn("sit");     // Rex learned: sit
rex.learn("roll over");
rex.showTricks();     // Rex's tricks: sit, roll over
```

**Multi-level inheritance:**
```js
class GuideDog extends Dog {
  constructor(name, owner) {
    super(name); // calls Dog's constructor
    this.owner = owner;
  }

  guide() {
    console.log(`${this.name} is guiding ${this.owner}.`);
  }
}

const buddy = new GuideDog("Buddy", "Alice");
buddy.speak();  // Buddy says Woof!  ← from Animal
buddy.guide();  // Buddy is guiding Alice. ← own method
```

---

## The `super` Keyword

`super` has two uses:

**1. In the constructor** — calls the parent's constructor (must be called before using `this` in a subclass):

```js
class Vehicle {
  constructor(brand, speed) {
    this.brand = brand;
    this.speed = speed;
  }
}

class Car extends Vehicle {
  constructor(brand, speed, doors) {
    super(brand, speed); // ← must come first
    this.doors = doors;
  }
}

const myCar = new Car("Toyota", 180, 4);
console.log(myCar); // Car { brand: "Toyota", speed: 180, doors: 4 }
```

**2. In a method** — calls the parent's version of the same method:

```js
class Animal {
  describe() {
    return `I am an animal named ${this.name}`;
  }
}

class Cat extends Animal {
  constructor(name, color) {
    super();
    this.name  = name;
    this.color = color;
  }

  describe() {
    const base = super.describe(); // get parent's description
    return `${base}, I'm a ${this.color} cat.`;
  }
}

const kitty = new Cat("Kitty", "orange");
console.log(kitty.describe());
// I am an animal named Kitty, I'm an orange cat.
```

---

## Method Overriding

A child class can **override** a parent method by redefining it with the same name. The child's version takes priority.

```js
class Shape {
  area() {
    return 0;
  }

  describe() {
    console.log(`This shape has an area of ${this.area()}`);
  }
}

class Rectangle extends Shape {
  constructor(width, height) {
    super();
    this.width  = width;
    this.height = height;
  }

  // Overrides Shape's area()
  area() {
    return this.width * this.height;
  }
}

class Triangle extends Shape {
  constructor(base, height) {
    super();
    this.base   = base;
    this.height = height;
  }

  // Overrides Shape's area()
  area() {
    return 0.5 * this.base * this.height;
  }
}

const rect = new Rectangle(5, 10);
const tri  = new Triangle(6, 8);

rect.describe(); // This shape has an area of 50
tri.describe();  // This shape has an area of 24
```

Each shape has its **own formula**, but they both work through the same `describe()` from the parent.

---

## Private Fields

Private fields (prefixed with `#`) are only accessible **inside** the class. They can't be read or changed from outside.

```js
class BankAccount {
  #balance; // private field declaration

  constructor(owner, initialBalance) {
    this.owner  = owner;
    this.#balance = initialBalance;
  }

  deposit(amount) {
    if (amount <= 0) throw new Error("Deposit must be positive.");
    this.#balance += amount;
    console.log(`Deposited ₹${amount}. New balance: ₹${this.#balance}`);
  }

  withdraw(amount) {
    if (amount > this.#balance) throw new Error("Insufficient funds.");
    this.#balance -= amount;
    console.log(`Withdrew ₹${amount}. New balance: ₹${this.#balance}`);
  }

  get balance() {
    return this.#balance; // expose read-only via getter
  }
}

const acc = new BankAccount("Alice", 1000);
acc.deposit(500);   // Deposited ₹500. New balance: ₹1500
acc.withdraw(200);  // Withdrew ₹200. New balance: ₹1300

console.log(acc.balance);   // 1300  ✅ via getter
console.log(acc.#balance);  // ❌ SyntaxError — private field!
```

---

## Error Handling

JavaScript uses `try...catch` to **handle errors gracefully** instead of crashing the program.

---

### `try` / `catch` / `finally`

```js
try {
  // code that might throw an error
} catch (error) {
  // runs if an error occurs
} finally {
  // ALWAYS runs — error or not
}
```

**Basic example:**
```js
try {
  const result = 10 / 0;
  console.log(result); // Infinity — no error here

  JSON.parse("invalid json"); // ← this throws!
} catch (error) {
  console.log("Error caught:", error.message);
} finally {
  console.log("This always runs.");
}

// Error caught: Unexpected token i in JSON at position 0
// This always runs.
```

**Manually throwing an error with `throw`:**
```js
function divide(a, b) {
  if (b === 0) {
    throw new Error("Cannot divide by zero!");
  }
  return a / b;
}

try {
  console.log(divide(10, 2)); // 5
  console.log(divide(10, 0)); // throws!
} catch (err) {
  console.log("Caught:", err.message); // Caught: Cannot divide by zero!
}
```

**The `error` object has:**
```js
try {
  null.property; // throws TypeError
} catch (err) {
  console.log(err.name);    // "TypeError"
  console.log(err.message); // "Cannot read properties of null"
  console.log(err.stack);   // full stack trace
}
```

---

### Custom Errors

Extend the built-in `Error` class to create your own descriptive error types.

```js
class ValidationError extends Error {
  constructor(message, field) {
    super(message);
    this.name  = "ValidationError";
    this.field = field;
  }
}

class NetworkError extends Error {
  constructor(message, statusCode) {
    super(message);
    this.name       = "NetworkError";
    this.statusCode = statusCode;
  }
}

function validateAge(age) {
  if (typeof age !== "number") {
    throw new ValidationError("Age must be a number.", "age");
  }
  if (age < 0 || age > 120) {
    throw new ValidationError("Age must be between 0 and 120.", "age");
  }
  return true;
}

try {
  validateAge("twenty"); // throws ValidationError
} catch (err) {
  if (err instanceof ValidationError) {
    console.log(`Validation failed on "${err.field}": ${err.message}`);
  } else {
    console.log("Unknown error:", err.message);
  }
}
// Validation failed on "age": Age must be a number.
```

---

### Error Types

JavaScript has several built-in error types:

| Error Type       | When it occurs                                          | Example                        |
|------------------|---------------------------------------------------------|--------------------------------|
| `Error`          | Generic error base class                                | `throw new Error("oops")`      |
| `TypeError`      | Wrong data type used                                    | `null.property`                |
| `ReferenceError` | Variable doesn't exist                                  | `console.log(undeclaredVar)`   |
| `SyntaxError`    | Invalid JS syntax                                       | `JSON.parse("bad")`            |
| `RangeError`     | Value is out of allowed range                           | `new Array(-1)`                |
| `URIError`       | Malformed URI                                           | `decodeURIComponent("%")`      |

**Catching specific error types:**
```js
function riskyOperation(input) {
  try {
    if (input === null) throw new TypeError("Input cannot be null.");
    if (input < 0)      throw new RangeError("Input must be positive.");
    return Math.sqrt(input);
  } catch (err) {
    if (err instanceof TypeError)  console.log("Type issue:", err.message);
    if (err instanceof RangeError) console.log("Range issue:", err.message);
  }
}

riskyOperation(null); // Type issue: Input cannot be null.
riskyOperation(-5);   // Range issue: Input must be positive.
riskyOperation(25);   // 5
```

---

## Quick Reference

### Object Creation Methods

| Method              | Best For                                   |
|---------------------|--------------------------------------------|
| Object literal `{}` | Single one-off objects                     |
| Constructor function| Multiple instances (pre-ES6 style)         |
| `Object.create()`   | Fine-grained prototype control             |
| `class` (ES6)       | Modern, clean, multiple instances          |

### Class Keywords

| Keyword      | Purpose                                              |
|--------------|------------------------------------------------------|
| `class`      | Declares a class blueprint                           |
| `constructor`| Initializes instance properties (runs on `new`)      |
| `extends`    | Creates a subclass (inheritance)                     |
| `super()`    | Calls parent constructor or parent method            |
| `static`     | Method belongs to class, not instance                |
| `get` / `set`| Define computed properties with logic                |
| `#field`     | Declares a private field (inaccessible outside class)|

### Error Handling

| Keyword   | Role                                              |
|-----------|---------------------------------------------------|
| `try`     | Wraps code that might throw                       |
| `catch`   | Runs if an error is thrown — receives error object|
| `finally` | Always runs regardless of outcome                 |
| `throw`   | Manually triggers an error                        |

---

> 💡 **Key Takeaway:** Objects hold data and behaviour together. Classes are reusable blueprints for objects. Inheritance lets child classes build on parents without rewriting code. `super` connects the two. And error handling ensures your program fails gracefully instead of crashing completely.