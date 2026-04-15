# ⚛️ React JS — The Complete Developer Guide
> **Topic 1 of many** · Crafted for clarity, depth, and real-world understanding

---

## Table of Contents

1. [What is React?](#what-is-react)
2. [Setting Up React with Vite](#setting-up-react-with-vite)
3. [Folder & File Structure](#folder--file-structure)
4. [Components — The Heart of React](#components--the-heart-of-react)
   - [What is a Component?](#what-is-a-component)
   - [Types of Components](#types-of-components)
   - [Creating a Component](#creating-a-component)
   - [Where to Place Components](#where-to-place-components)
   - [Naming Rules](#naming-rules)
   - [Using a Component](#using-a-component)
   - [Component File Structure (Inside a File)](#component-file-structure-inside-a-file)
   - [Default vs Named Exports](#default-vs-named-exports)
   - [Nested Components](#nested-components)
   - [Component Best Practices](#component-best-practices)

---

## What is React?

React is a **JavaScript library** built by Meta (Facebook) for building **user interfaces**. It lets you break your UI into small, reusable pieces called **components**, and efficiently updates only the parts of the page that change — thanks to its **Virtual DOM**.

```
Your App
  └── UI = Components + State + Props + Events
```

React doesn't handle routing, HTTP calls, or global state by itself — it focuses purely on the **View layer**. You pair it with other libraries (like React Router, Axios, Zustand, etc.) as needed.

---

## Setting Up React with Vite

> **Why Vite?** Vite is a blazing-fast modern build tool. It replaces the older `create-react-app` which is now deprecated and slow.

### Step 1 — Prerequisites

Make sure you have **Node.js** installed (v18+ recommended):

```bash
node -v    # Check Node version
npm -v     # Check npm version
```

Download Node from: https://nodejs.org

---

### Step 2 — Create the Project

```bash
npm create vite@latest my-react-app
```

You'll be prompted to choose:

```
✔ Project name: my-react-app
✔ Select a framework: › React
✔ Select a variant: › JavaScript     ← (or TypeScript if you prefer)
```

---

### Step 3 — Navigate & Install Dependencies

```bash
cd my-react-app
npm install
```

This installs all required packages listed in `package.json` into a `node_modules/` folder.

---

### Step 4 — Start the Dev Server

```bash
npm run dev
```

Output:
```
  VITE v5.x.x  ready in 300ms

  ➜  Local:   http://localhost:5173/
  ➜  Network: use --host to expose
```

Open `http://localhost:5173` in your browser — your React app is live! 🎉

---

### Other Useful Commands

| Command | What it Does |
|---|---|
| `npm run dev` | Start development server with hot reload |
| `npm run build` | Build the app for production (outputs to `/dist`) |
| `npm run preview` | Preview the production build locally |
| `npm install <pkg>` | Install a new package |

---

## Folder & File Structure

After setup, your project looks like this:

```
my-react-app/
├── node_modules/         ← All installed packages (never touch this)
├── public/               ← Static assets served as-is
│   └── vite.svg
├── src/                  ← YOUR CODE LIVES HERE
│   ├── assets/           ← Images, fonts, icons used in components
│   │   └── react.svg
│   ├── App.css           ← Styles specific to the App component
│   ├── App.jsx           ← Root component of your application
│   ├── index.css         ← Global CSS styles
│   └── main.jsx          ← App entry point — mounts React into the DOM
├── .gitignore            ← Files/folders Git should ignore
├── eslint.config.js      ← ESLint rules for code quality
├── index.html            ← The single HTML file (the shell of your SPA)
├── package.json          ← Project metadata, scripts, and dependencies
├── package-lock.json     ← Exact dependency tree (auto-generated)
└── vite.config.js        ← Vite configuration file
```

---

### Deep Dive — What Each File/Folder Does

#### 📁 `node_modules/`
Auto-generated when you run `npm install`. Contains all third-party packages. **Never manually edit anything here.** It's excluded from Git via `.gitignore`.

---

#### 📁 `public/`
Files placed here are **served directly** without processing by Vite. Good for things like:
- `favicon.ico`
- `robots.txt`
- Static images you want to reference by absolute URL (e.g., `/logo.png`)

> Files in `public/` are **NOT** imported via JavaScript — they're accessed via direct URL paths.

---

#### 📁 `src/`
This is where **all your React code** lives. Everything you write goes here.

---

#### 📄 `src/main.jsx`
The **entry point** of your app. It mounts your entire React app into the real DOM.

```jsx
import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import App from './App.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <App />
  </StrictMode>,
)
```

- `document.getElementById('root')` → finds the `<div id="root">` in `index.html`
- `createRoot(...).render(...)` → mounts your React component tree there
- `StrictMode` → a wrapper that highlights potential problems during development

> **You almost never need to edit `main.jsx`.**

---

#### 📄 `src/App.jsx`
The **root component** — the top of your component tree. Everything renders from here.

```jsx
function App() {
  return (
    <div>
      <h1>Hello React!</h1>
    </div>
  )
}

export default App
```

This is where you'll add your layout, routes, and top-level components.

---

#### 📄 `index.html`
The **single HTML page** that your entire app lives inside. Vite injects your JS bundle here automatically.

```html
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <link rel="icon" type="image/svg+xml" href="/vite.svg" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Vite + React</title>
  </head>
  <body>
    <div id="root"></div>               ← React mounts here
    <script type="module" src="/src/main.jsx"></script>
  </body>
</html>
```

---

#### 📄 `package.json`
The project's **manifest file**. Tracks:
- Project name and version
- `scripts` (like `dev`, `build`, `preview`)
- `dependencies` (used in production)
- `devDependencies` (used only during development)

---

#### 📄 `vite.config.js`
Configuration for Vite. You can set up:
- Aliases (e.g., `@` → `src/`)
- Plugins (e.g., `@vitejs/plugin-react`)
- Proxy settings for API calls

```js
import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

export default defineConfig({
  plugins: [react()],
})
```

---

## Components — The Heart of React

### What is a Component?

A **component** is an **independent, reusable piece of UI**. Think of it like a custom HTML element that you define yourself.

Instead of one giant HTML file, React lets you break your UI into logical pieces:

```
<App>
  ├── <Navbar>
  ├── <HeroSection>
  │     ├── <Title>
  │     └── <CTAButton>
  ├── <ProductList>
  │     ├── <ProductCard>
  │     ├── <ProductCard>
  │     └── <ProductCard>
  └── <Footer>
```

Each box above is a **component** — its own file, its own logic, its own styles.

---

### Types of Components

React has **one primary type** of component today:

#### ✅ Functional Components (Modern — Use This Always)

```jsx
function Greeting() {
  return <h1>Hello, World!</h1>
}
```

Simple JavaScript functions that return **JSX** (HTML-like syntax). They support all React features through **Hooks** (`useState`, `useEffect`, etc.).

---

#### ❌ Class Components (Legacy — Avoid for New Code)

```jsx
import { Component } from 'react'

class Greeting extends Component {
  render() {
    return <h1>Hello, World!</h1>
  }
}
```

Older syntax. Still works, but the React team recommends functional components for all new code.

---

### Creating a Component

#### Step 1 — Create a new file inside `src/`

**File:** `src/components/Greeting.jsx`

> 📌 **Rule:** One component per file. File name matches the component name.

```jsx
// src/components/Greeting.jsx

function Greeting() {
  return (
    <div>
      <h1>Hello, Developer! 👋</h1>
      <p>Welcome to React.</p>
    </div>
  )
}

export default Greeting
```

**Breaking it down:**

| Part | What it means |
|---|---|
| `function Greeting()` | Define a component called `Greeting` |
| `return ( ... )` | What the component renders on screen |
| `<div>...</div>` | JSX — looks like HTML, but it's JavaScript |
| `export default Greeting` | Makes this component importable in other files |

---

### Where to Place Components

Organize your components logically inside the `src/` folder:

```
src/
├── components/          ← Reusable, generic UI pieces
│   ├── Button.jsx
│   ├── Navbar.jsx
│   ├── Footer.jsx
│   └── Card.jsx
├── pages/               ← Full page components (used with routing)
│   ├── Home.jsx
│   ├── About.jsx
│   └── Contact.jsx
├── layouts/             ← Layout wrappers (e.g., with Navbar + Footer)
│   └── MainLayout.jsx
├── assets/              ← Images, SVGs, fonts
├── App.jsx
└── main.jsx
```

> 💡 **Tip:** Keep components that are reused across multiple pages in `components/`. Keep full-page views in `pages/`.

---

### Naming Rules

React has strict rules about component names:

| Rule | Example | Why |
|---|---|---|
| Must start with **Capital Letter** | `UserCard`, not `userCard` | React uses this to distinguish components from HTML tags |
| Use **PascalCase** | `ProductList`, `NavBar` | Community convention |
| File name should **match** component name | `UserCard.jsx` for `UserCard` | Makes imports predictable |
| Use `.jsx` extension | `Button.jsx` | Signals the file contains JSX |

```jsx
// ✅ Correct
function UserCard() { ... }

// ❌ Wrong — React will treat this as an HTML tag, not a component
function usercard() { ... }
```

---

### Using a Component

Once created, you **import and use** a component like a custom HTML tag.

**File:** `src/App.jsx`

```jsx
import Greeting from './components/Greeting'

function App() {
  return (
    <div>
      <Greeting />       {/* Self-closing tag — no children */}
    </div>
  )
}

export default App
```

> 📌 The `./` in the import means "relative to the current file."

You can use a component **multiple times**:

```jsx
function App() {
  return (
    <div>
      <Greeting />
      <Greeting />
      <Greeting />
    </div>
  )
}
```

All three render independently.

---

### Component File Structure (Inside a File)

A well-structured component file follows this order:

```jsx
// 1. Imports (external libraries first, then local)
import { useState } from 'react'
import './Button.css'
import Icon from '../assets/icon.svg'

// 2. The Component Function
function Button() {

  // 2a. State & variables (covered in State topic)
  const [clicked, setClicked] = useState(false)

  // 2b. Helper functions / handlers
  function handleClick() {
    setClicked(true)
  }

  // 2c. The returned JSX
  return (
    <button onClick={handleClick}>
      {clicked ? 'Clicked!' : 'Click Me'}
    </button>
  )
}

// 3. Export
export default Button
```

---

### Default vs Named Exports

#### Default Export (most common for components)

```jsx
// MyComponent.jsx
function MyComponent() {
  return <p>Hello</p>
}

export default MyComponent
```

```jsx
// Importing — you can name it anything
import MyComponent from './MyComponent'
import Whatever from './MyComponent'   // also valid
```

---

#### Named Export (for utility files or multiple exports)

```jsx
// helpers.jsx
export function add(a, b) { return a + b }
export function subtract(a, b) { return a - b }
```

```jsx
// Importing — must use the exact name, wrapped in { }
import { add, subtract } from './helpers'
```

---

#### When to use which?

| Scenario | Use |
|---|---|
| One main component per file | `export default` |
| Multiple functions/components from one file | Named exports |
| Component + some utility helpers | Default for component + named for helpers |

---

### Nested Components

Components can render other components inside them — this is how you build complex UIs.

```jsx
// src/components/Card.jsx
function Card() {
  return (
    <div className="card">
      <CardHeader />
      <CardBody />
      <CardFooter />
    </div>
  )
}

function CardHeader() {
  return <div className="card-header"><h2>Title</h2></div>
}

function CardBody() {
  return <div className="card-body"><p>Some content here.</p></div>
}

function CardFooter() {
  return <div className="card-footer"><button>Read More</button></div>
}

export default Card
```

> 📌 Sub-components like `CardHeader`, `CardBody`, `CardFooter` can live in the same file **if they're only used by that one component**. If they'll be reused, give them their own files.

---

### JSX — What's Actually Happening?

JSX looks like HTML, but it's **syntactic sugar for JavaScript**. Under the hood:

```jsx
// What you write:
return <h1 className="title">Hello</h1>

// What React actually sees (compiled by Babel/Vite):
return React.createElement('h1', { className: 'title' }, 'Hello')
```

**Key JSX rules:**

```jsx
// 1. Return a single root element (wrap in a div or Fragment)
return (
  <div>
    <h1>Hello</h1>
    <p>World</p>
  </div>
)

// Or use a Fragment (renders no extra DOM node):
return (
  <>
    <h1>Hello</h1>
    <p>World</p>
  </>
)

// 2. Use className instead of class (class is a reserved JS keyword)
<div className="container">

// 3. Self-close tags that have no children
<img src="photo.jpg" alt="photo" />
<input type="text" />
<MyComponent />

// 4. JavaScript expressions go inside { }
const name = "Riya"
return <h1>Hello, {name}!</h1>

// 5. Inline styles use an object with camelCase properties
<div style={{ backgroundColor: 'blue', fontSize: '16px' }}>
```

---

### Component Best Practices

```
✅ DO                                     ❌ DON'T
─────────────────────────────────────────────────────────
One component per file                    Dump 10 components in one file
Name files with PascalCase                Use lowercase or kebab-case for components
Keep components small & focused           Make one giant component that does everything
Place reusables in /components            Scatter components randomly in /src
Use descriptive names (UserCard)          Use vague names (Component1, Stuff)
Export at the bottom of the file          Mix exports throughout the file
Organize by feature as app grows          Keep everything flat forever
```

---

### Summary — Components Cheat Sheet

```jsx
// ─── Creating a Component ───────────────────────────────
function MyComponent() {          // PascalCase function name
  return (                        // Must return JSX
    <div>
      <h1>Hello!</h1>
    </div>
  )
}
export default MyComponent        // Export so others can import it

// ─── Using a Component ──────────────────────────────────
import MyComponent from './MyComponent'

function App() {
  return <MyComponent />          // Use like an HTML tag
}

// ─── Folder Structure ───────────────────────────────────
src/
  components/   ← Reusable bits of UI
  pages/        ← Full page views
  assets/       ← Images, icons
  App.jsx       ← Root component
  main.jsx      ← Entry point (don't touch)
```

---

> 📌 **Up Next:** Props — how to pass data into components to make them dynamic.

---
