# JavaScript — Asynchronous Programming

---

## 📌 Table of Contents
1. [What is Asynchronous Programming?](#what-is-asynchronous-programming)
2. [Synchronous vs Asynchronous](#synchronous-vs-asynchronous)
3. [The Event Loop](#the-event-loop)
4. [Callbacks](#callbacks)
5. [Callback Hell](#callback-hell)
6. [Promises](#promises)
   - [Creating a Promise](#creating-a-promise)
   - [.then() and .catch()](#then-and-catch)
   - [.finally()](#finally)
   - [Promise Chaining](#promise-chaining)
   - [Promise Methods](#promise-methods)
7. [Async / Await](#async--await)
   - [async function](#async-function)
   - [await keyword](#await-keyword)
   - [Error Handling with try/catch](#error-handling-with-trycatch)
   - [Parallel Execution](#parallel-execution)
8. [fetch API](#fetch-api)
   - [GET Request](#get-request)
   - [POST Request](#post-request)
9. [Real-World Patterns](#real-world-patterns)
10. [Callbacks vs Promises vs Async/Await](#callbacks-vs-promises-vs-asyncawait)
11. [Quick Reference](#quick-reference)

---

## What is Asynchronous Programming?

In JavaScript, **asynchronous** means: *start a task now, but don't wait for it to finish — move on, and handle the result when it's ready.*

Think of it like ordering food at a restaurant:
- **Synchronous** → You stand at the counter, wait while food is cooked, then leave. Everyone behind you waits. ❌
- **Asynchronous** → You order, sit down, do other things. Waiter brings food when ready. ✅

JavaScript is **single-threaded** — it can only do one thing at a time. Async programming is what lets it *appear* to handle multiple things simultaneously, like fetching data from a server while still responding to user clicks.

---

## Synchronous vs Asynchronous

### Synchronous — line by line, top to bottom, blocking

```js
console.log("1. Start");

// This blocks — nothing else runs until this finishes
for (let i = 0; i < 1000000000; i++) {} // fake heavy task

console.log("2. Heavy task done");
console.log("3. End");

// Output (in order, with a pause before line 2):
// 1. Start
// 2. Heavy task done  ← everything waits for this
// 3. End
```

### Asynchronous — non-blocking

```js
console.log("1. Start");

setTimeout(() => {
  console.log("2. This runs after 2 seconds");
}, 2000);

console.log("3. End");

// Output:
// 1. Start       ← immediate
// 3. End         ← immediate (JS doesn't wait for setTimeout)
// 2. This runs after 2 seconds  ← arrives later
```

> JS didn't freeze and wait. It scheduled the timer, moved on, and came back when the timer was done.

---

## The Event Loop

The **Event Loop** is what makes asynchronous JavaScript possible. Here's how it works:

```
  ┌─────────────────────────────────┐
  │          Call Stack             │  ← JS runs code here, one at a time
  │  (where your code executes)     │
  └────────────────┬────────────────┘
                   │ when stack is empty
                   ▼
  ┌─────────────────────────────────┐
  │         Callback Queue          │  ← finished async tasks wait here
  │  (setTimeout, fetch, events...) │
  └─────────────────────────────────┘
                   ▲
                   │ Event Loop moves callbacks here
  ┌─────────────────────────────────┐
  │       Web APIs / Node APIs      │  ← handles timers, network calls, etc.
  └─────────────────────────────────┘
```

```js
console.log("A"); // 1. Goes on call stack → runs → off stack

setTimeout(() => { // 2. Handed to Web API (timer starts)
  console.log("B"); // 4. Callback put in queue → Event Loop picks it up
}, 0);

console.log("C"); // 3. Goes on call stack → runs → off stack

// Output: A, C, B
// Even with 0ms delay, "B" is last — it still goes through the queue
```

---

## Callbacks

A **callback** is a function passed to another function, to be called when an async task completes.

**Simple example:**
```js
function fetchUserData(userId, callback) {
  console.log(`Fetching user ${userId}...`);

  // Simulating a network delay with setTimeout
  setTimeout(() => {
    const user = { id: userId, name: "Alice", age: 25 };
    callback(user); // call the function when data is ready
  }, 1500);
}

fetchUserData(1, function(user) {
  console.log("Got user:", user.name); // Got user: Alice
});

console.log("This runs while fetching..."); // runs immediately, doesn't wait
```

**Output:**
```
Fetching user 1...
This runs while fetching...
Got user: Alice          ← arrives after 1.5s
```

**Error-first callbacks** — a convention in Node.js where the first argument is always the error:

```js
function readFile(filename, callback) {
  setTimeout(() => {
    if (filename === "") {
      callback(new Error("Filename cannot be empty"), null);
    } else {
      callback(null, `Contents of ${filename}`); // null = no error
    }
  }, 1000);
}

readFile("data.txt", function(err, data) {
  if (err) {
    console.log("Error:", err.message);
    return;
  }
  console.log("Data:", data); // Data: Contents of data.txt
});

readFile("", function(err, data) {
  if (err) {
    console.log("Error:", err.message); // Error: Filename cannot be empty
    return;
  }
  console.log("Data:", data);
});
```

---

## Callback Hell

When async operations depend on each other, you start nesting callbacks inside callbacks inside callbacks. This is **callback hell** — also called the **pyramid of doom**.

**Real scenario: Login → Get Profile → Get Orders → Get Recommendations**

```js
loginUser("alice@email.com", "password123", function(err, user) {
  if (err) { console.log("Login failed:", err); return; }

  console.log("Logged in as:", user.name);

  getUserProfile(user.id, function(err, profile) {
    if (err) { console.log("Profile fetch failed:", err); return; }

    console.log("Profile loaded:", profile.bio);

    getUserOrders(profile.id, function(err, orders) {
      if (err) { console.log("Orders fetch failed:", err); return; }

      console.log("Orders loaded:", orders.length, "orders");

      getRecommendations(orders, function(err, recommendations) {
        if (err) { console.log("Recommendations failed:", err); return; }

        console.log("Recommendations ready:", recommendations);

        // And it keeps going deeper and deeper...  😱
      });
    });
  });
});
```

**Problems with callback hell:**
- Extremely hard to read (code drifts rightward)
- Error handling is repeated at every level
- Nearly impossible to maintain or debug
- Can't easily reuse individual steps

> 💡 **Promises** were created to solve exactly this problem.

---

## Promises

A **Promise** is an object representing the eventual completion or failure of an async operation. It's like a receipt — you don't have the food yet, but you're promised it will come (or you'll be told if it failed).

A Promise has three states:
```
  PENDING   →  the operation is ongoing
     ↓
  FULFILLED →  the operation succeeded (resolved)
     or
  REJECTED  →  the operation failed
```

Once a promise is fulfilled or rejected, it **never changes state**.

---

### Creating a Promise

```js
const myPromise = new Promise((resolve, reject) => {
  // Do async work here
  const success = true;

  if (success) {
    resolve("Operation succeeded! ✅"); // fulfilled
  } else {
    reject(new Error("Operation failed! ❌")); // rejected
  }
});
```

**Simulating async work:**
```js
function fetchUser(id) {
  return new Promise((resolve, reject) => {
    console.log(`Fetching user ${id}...`);

    setTimeout(() => {
      if (id <= 0) {
        reject(new Error("Invalid user ID"));
      } else {
        resolve({ id, name: "Alice", email: "alice@email.com" });
      }
    }, 1500);
  });
}
```

---

### `.then()` and `.catch()`

- `.then(callback)` — runs when the promise **resolves**
- `.catch(callback)` — runs when the promise **rejects**

```js
fetchUser(1)
  .then(function(user) {
    console.log("Success:", user.name); // Success: Alice
  })
  .catch(function(err) {
    console.log("Error:", err.message);
  });

fetchUser(-1)
  .then(function(user) {
    console.log("Success:", user.name); // skipped
  })
  .catch(function(err) {
    console.log("Error:", err.message); // Error: Invalid user ID
  });
```

**With arrow functions (cleaner):**
```js
fetchUser(1)
  .then(user => console.log("Got:", user.name))
  .catch(err => console.log("Failed:", err.message));
```

---

### `.finally()`

Runs **regardless** of whether the promise resolved or rejected. Perfect for cleanup.

```js
function loadData() {
  return new Promise((resolve, reject) => {
    setTimeout(() => resolve("Data loaded!"), 1000);
  });
}

console.log("Loading...");

loadData()
  .then(data  => console.log(data))       // Data loaded!
  .catch(err  => console.log(err.message))
  .finally(() => console.log("Done — hiding spinner.")); // always runs
```

---

### Promise Chaining

The real power of promises — each `.then()` returns a new promise, so you can **chain** them instead of nesting.

**The callback hell example, rewritten with promise chains:**

```js
function loginUser(email, password) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (password === "password123") {
        resolve({ id: 1, name: "Alice", email });
      } else {
        reject(new Error("Wrong password"));
      }
    }, 1000);
  });
}

function getUserProfile(userId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({ id: userId, bio: "Developer from Mumbai", followers: 200 });
    }, 800);
  });
}

function getUserOrders(profileId) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve([
        { id: 101, item: "Laptop",  price: 80000 },
        { id: 102, item: "Monitor", price: 20000 }
      ]);
    }, 600);
  });
}

function getRecommendations(orders) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(["Keyboard", "Mouse", "Webcam"]);
    }, 500);
  });
}

// Clean, readable, flat chain — no nesting! ✅
loginUser("alice@email.com", "password123")
  .then(user => {
    console.log("Logged in as:", user.name);
    return getUserProfile(user.id); // return next promise
  })
  .then(profile => {
    console.log("Bio:", profile.bio);
    return getUserOrders(profile.id);
  })
  .then(orders => {
    console.log("Orders:", orders.length);
    return getRecommendations(orders);
  })
  .then(recommendations => {
    console.log("Recommended:", recommendations.join(", "));
  })
  .catch(err => {
    // ONE catch handles errors from ANY step in the chain
    console.log("Something went wrong:", err.message);
  })
  .finally(() => {
    console.log("Process complete.");
  });
```

**Output:**
```
Logged in as: Alice
Bio: Developer from Mumbai
Orders: 2
Recommended: Keyboard, Mouse, Webcam
Process complete.
```

If the password is wrong, only the `.catch()` fires — all the `.then()` steps are skipped.

---

### Promise Methods

#### `Promise.all()` — Run multiple promises in **parallel**, wait for ALL

```js
const p1 = new Promise(resolve => setTimeout(() => resolve("Users loaded"),    1000));
const p2 = new Promise(resolve => setTimeout(() => resolve("Products loaded"), 1500));
const p3 = new Promise(resolve => setTimeout(() => resolve("Orders loaded"),    800));

Promise.all([p1, p2, p3])
  .then(results => {
    console.log(results);
    // ["Users loaded", "Products loaded", "Orders loaded"]
    // Takes ~1500ms (longest one), not 1000+1500+800=3300ms
  });
```

> ⚠️ If **any** promise rejects, `Promise.all` immediately rejects.

```js
const p1 = Promise.resolve("Success");
const p2 = Promise.reject(new Error("p2 failed"));
const p3 = Promise.resolve("Also success");

Promise.all([p1, p2, p3])
  .then(results => console.log(results))
  .catch(err => console.log("Failed:", err.message)); // Failed: p2 failed
```

---

#### `Promise.allSettled()` — Wait for ALL, regardless of pass or fail

```js
const p1 = Promise.resolve("Data A");
const p2 = Promise.reject(new Error("Server down"));
const p3 = Promise.resolve("Data C");

Promise.allSettled([p1, p2, p3]).then(results => {
  results.forEach(result => {
    if (result.status === "fulfilled") {
      console.log("✅ Value:", result.value);
    } else {
      console.log("❌ Reason:", result.reason.message);
    }
  });
});

// ✅ Value: Data A
// ❌ Reason: Server down
// ✅ Value: Data C
```

---

#### `Promise.race()` — Resolves/rejects with the **first** one to finish

```js
const fast = new Promise(resolve => setTimeout(() => resolve("Fast server"),   300));
const slow = new Promise(resolve => setTimeout(() => resolve("Slow server"),  2000));

Promise.race([fast, slow])
  .then(result => console.log("Winner:", result)); // Winner: Fast server
```

Useful for **timeouts**:
```js
function withTimeout(promise, ms) {
  const timeout = new Promise((_, reject) =>
    setTimeout(() => reject(new Error(`Timed out after ${ms}ms`)), ms)
  );
  return Promise.race([promise, timeout]);
}

const slowFetch = new Promise(resolve => setTimeout(() => resolve("Data"), 3000));

withTimeout(slowFetch, 1000)
  .then(data => console.log("Got:", data))
  .catch(err => console.log(err.message)); // Timed out after 1000ms
```

---

#### `Promise.any()` — Resolves with the **first successful** one (ignores rejections)

```js
const p1 = Promise.reject(new Error("Server 1 down"));
const p2 = Promise.resolve("Server 2 responded");
const p3 = Promise.resolve("Server 3 responded");

Promise.any([p1, p2, p3])
  .then(result => console.log("First success:", result)); // First success: Server 2 responded
```

---

## Async / Await

`async/await` is **syntactic sugar** over Promises — it makes async code look and feel like synchronous code. Much easier to read and write.

---

### `async` function

Adding `async` before a function means:
1. It **always returns a Promise**
2. You can use `await` inside it

```js
async function greet() {
  return "Hello!"; // automatically wrapped in a resolved Promise
}

greet().then(msg => console.log(msg)); // Hello!

// These are identical:
async function foo() { return 42; }
function foo() { return Promise.resolve(42); }
```

---

### `await` keyword

`await` **pauses** execution inside an `async` function until a Promise settles. The rest of the program keeps running normally.

```js
function delay(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function run() {
  console.log("Start");
  await delay(1000); // pauses HERE for 1 second
  console.log("After 1 second");
  await delay(500);
  console.log("After 500ms more");
}

run();
console.log("This runs immediately — async function doesn't block the outside");

// Output:
// Start
// This runs immediately — async function doesn't block the outside
// After 1 second          ← 1s later
// After 500ms more        ← 500ms later
```

**The callback hell example with async/await — cleanest version:**

```js
async function loadUserDashboard() {
  const user            = await loginUser("alice@email.com", "password123");
  console.log("Logged in as:", user.name);

  const profile         = await getUserProfile(user.id);
  console.log("Bio:", profile.bio);

  const orders          = await getUserOrders(profile.id);
  console.log("Orders:", orders.length);

  const recommendations = await getRecommendations(orders);
  console.log("Recommended:", recommendations.join(", "));
}

loadUserDashboard();
```

This is **identical in behaviour** to the promise chain but reads like straight-line code. Beautiful.

---

### Error Handling with `try/catch`

```js
async function loadUserDashboard() {
  try {
    const user    = await loginUser("alice@email.com", "wrongpassword");
    const profile = await getUserProfile(user.id);
    const orders  = await getUserOrders(profile.id);
    console.log("Orders:", orders.length);
  } catch (err) {
    console.log("Something went wrong:", err.message);
    // Something went wrong: Wrong password
  } finally {
    console.log("Done loading dashboard.");
  }
}

loadUserDashboard();
```

**Multiple specific catches:**
```js
async function processUser(id) {
  try {
    if (typeof id !== "number") throw new TypeError("ID must be a number");
    if (id <= 0)                throw new RangeError("ID must be positive");

    const user = await fetchUser(id);
    return user;

  } catch (err) {
    if (err instanceof TypeError)  console.log("Type error:",  err.message);
    if (err instanceof RangeError) console.log("Range error:", err.message);
    else                           console.log("Other error:", err.message);
  }
}

processUser("abc"); // Type error: ID must be a number
processUser(-5);    // Range error: ID must be positive
processUser(1);     // works fine
```

---

### Parallel Execution

`await` one-by-one is **sequential** (slow when tasks are independent). Use `Promise.all` with `await` for parallel execution.

**Sequential — slower (total: 3 seconds)**
```js
async function loadPageSlow() {
  console.time("sequential");

  const users    = await fakeAPI("Users",    1000); // wait 1s
  const products = await fakeAPI("Products", 1000); // wait 1s more
  const orders   = await fakeAPI("Orders",   1000); // wait 1s more

  console.timeEnd("sequential"); // ~3000ms
}
```

**Parallel — faster (total: 1 second)**
```js
function fakeAPI(name, ms) {
  return new Promise(resolve =>
    setTimeout(() => resolve(`${name} loaded`), ms)
  );
}

async function loadPageFast() {
  console.time("parallel");

  // All three start AT THE SAME TIME
  const [users, products, orders] = await Promise.all([
    fakeAPI("Users",    1000),
    fakeAPI("Products", 1000),
    fakeAPI("Orders",   1000)
  ]);

  console.log(users, products, orders);
  console.timeEnd("parallel"); // ~1000ms
}

loadPageFast();
// Users loaded  Products loaded  Orders loaded
// parallel: ~1000ms
```

---

## fetch API

`fetch` is the modern built-in way to make HTTP requests. It returns a **Promise**.

---

### GET Request

```js
async function getUsers() {
  try {
    const response = await fetch("https://jsonplaceholder.typicode.com/users");

    // fetch only rejects on network failure, not HTTP errors
    // so always check response.ok
    if (!response.ok) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }

    const users = await response.json(); // parse JSON body (also a Promise)

    users.forEach(user => {
      console.log(`${user.name} — ${user.email}`);
    });

  } catch (err) {
    console.log("Fetch error:", err.message);
  }
}

getUsers();
```

**Fetching a single resource:**
```js
async function getPost(id) {
  const response = await fetch(`https://jsonplaceholder.typicode.com/posts/${id}`);
  const post     = await response.json();

  console.log("Title:",  post.title);
  console.log("Body:", post.body);
}

getPost(1);
```

---

### POST Request

```js
async function createPost(title, body, userId) {
  try {
    const response = await fetch("https://jsonplaceholder.typicode.com/posts", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({ title, body, userId })
    });

    if (!response.ok) throw new Error(`Failed: ${response.status}`);

    const newPost = await response.json();
    console.log("Created post with ID:", newPost.id);
    console.log("Title:", newPost.title);

  } catch (err) {
    console.log("Error:", err.message);
  }
}

createPost("My First Post", "Hello from JS!", 1);
// Created post with ID: 101
// Title: My First Post
```

---

## Real-World Patterns

### Pattern 1 — Loading screen with async/await

```js
async function loadDashboard() {
  showSpinner(); // show loading UI

  try {
    const [user, stats, notifications] = await Promise.all([
      fetch("/api/user").then(r => r.json()),
      fetch("/api/stats").then(r => r.json()),
      fetch("/api/notifications").then(r => r.json())
    ]);

    renderUser(user);
    renderStats(stats);
    renderNotifications(notifications);

  } catch (err) {
    showError("Failed to load dashboard. Please refresh.");
  } finally {
    hideSpinner(); // always hide spinner
  }
}

loadDashboard();
```

---

### Pattern 2 — Retry logic

```js
async function fetchWithRetry(url, retries = 3) {
  for (let attempt = 1; attempt <= retries; attempt++) {
    try {
      console.log(`Attempt ${attempt}...`);
      const response = await fetch(url);
      if (!response.ok) throw new Error(`Status: ${response.status}`);
      return await response.json();

    } catch (err) {
      console.log(`Attempt ${attempt} failed: ${err.message}`);
      if (attempt === retries) throw new Error("All retries failed.");
      await new Promise(r => setTimeout(r, 1000 * attempt)); // wait longer each try
    }
  }
}

fetchWithRetry("https://jsonplaceholder.typicode.com/posts/1")
  .then(post  => console.log("Got:", post.title))
  .catch(err  => console.log(err.message));
```

---

### Pattern 3 — Sequential vs Parallel decision

```js
// Use sequential when tasks DEPEND on each other
async function sequential() {
  const user    = await fetchUser(1);           // need user first
  const profile = await fetchProfile(user.id);  // need user to get profile
  const orders  = await fetchOrders(profile.id);// need profile to get orders
  return { user, profile, orders };
}

// Use parallel when tasks are INDEPENDENT
async function parallel() {
  const [users, products, categories] = await Promise.all([
    fetchUsers(),     // these don't need each other
    fetchProducts(),
    fetchCategories()
  ]);
  return { users, products, categories };
}
```

---

## Callbacks vs Promises vs Async/Await

**Same task — get user then their posts — written three ways:**

### With Callbacks
```js
getUser(1, function(err, user) {
  if (err) { handleError(err); return; }
  getPosts(user.id, function(err, posts) {
    if (err) { handleError(err); return; }
    getComments(posts[0].id, function(err, comments) {
      if (err) { handleError(err); return; }
      console.log("Comments:", comments.length);
    });
  });
});
```

### With Promises
```js
getUser(1)
  .then(user    => getPosts(user.id))
  .then(posts   => getComments(posts[0].id))
  .then(comments=> console.log("Comments:", comments.length))
  .catch(err    => handleError(err));
```

### With Async/Await
```js
async function showComments() {
  try {
    const user     = await getUser(1);
    const posts    = await getPosts(user.id);
    const comments = await getComments(posts[0].id);
    console.log("Comments:", comments.length);
  } catch (err) {
    handleError(err);
  }
}
```

---

## Quick Reference

### Promise States

| State       | Meaning                         | Triggers   |
|-------------|---------------------------------|------------|
| `pending`   | Operation in progress           | —          |
| `fulfilled` | Operation succeeded             | `.then()`  |
| `rejected`  | Operation failed                | `.catch()` |
| settled     | Either fulfilled or rejected    | `.finally()`|

### Promise Methods

| Method                  | Behaviour                                              |
|-------------------------|--------------------------------------------------------|
| `Promise.all([])`       | Waits for all — fails if any fails                     |
| `Promise.allSettled([])` | Waits for all — never fails, reports each outcome    |
| `Promise.race([])`      | Resolves/rejects with the first to settle              |
| `Promise.any([])`       | Resolves with first success — fails only if ALL fail   |
| `Promise.resolve(val)`  | Creates an already-resolved Promise                    |
| `Promise.reject(err)`   | Creates an already-rejected Promise                    |

### Async/Await Rules

| Rule                                                       | Why                                        |
|------------------------------------------------------------|--------------------------------------------|
| `await` only works inside `async` functions               | It's a syntax requirement                  |
| Wrap in `try/catch` for error handling                    | Unhandled rejections crash the program     |
| Use `Promise.all` for parallel independent tasks          | Sequential `await` is unnecessarily slow   |
| `async` functions always return a Promise                 | Even if you return a plain value           |
| `await` on a non-Promise just returns the value           | It's safe to use even on regular values    |

### When to Use What

| Situation                                       | Use               |
|-------------------------------------------------|-------------------|
| Simple one-off async task                       | Callback          |
| Multiple chained async steps                    | Promises / Await  |
| Need to read async code like sync code          | Async/Await       |
| Multiple independent async tasks at once        | Promise.all       |
| Want result even if some fail                   | Promise.allSettled|
| Timeout or race condition                        | Promise.race      |
| First success from multiple sources             | Promise.any       |

---

> 💡 **Key Takeaway:** Callbacks came first but lead to unreadable nesting. Promises solved the structure with chains. Async/Await made it read like normal code. Internally, `async/await` is just Promises — just wearing nicer clothes. Master all three, because you'll see all three in the wild.