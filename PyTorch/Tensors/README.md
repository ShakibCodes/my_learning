# 🔥 PyTorch Tensors — Complete Reference Guide

> A comprehensive, tutorial-style reference covering everything you need to know about tensors in PyTorch — from creation to GPU management.

---

## Table of Contents

1. [Tensor Creation](#1-tensor-creation)
2. [Tensor Properties](#2-tensor-properties)
3. [Indexing](#3-indexing)
4. [Slicing](#4-slicing)
5. [Modifying Tensor Values](#5-modifying-tensor-values)
6. [Tensor Arithmetic Operations](#6-tensor-arithmetic-operations)
7. [Mathematical Functions](#7-mathematical-functions)
8. [Reduction Operations](#8-reduction-operations)
9. [Dimension-wise Operations](#9-dimension-wise-operations)
10. [Tensor Reshaping](#10-tensor-reshaping)
11. [Viewing Tensors](#11-viewing-tensors)
12. [Flattening Tensors](#12-flattening-tensors)
13. [Adding Dimensions](#13-adding-dimensions-unsqueeze)
14. [Removing Dimensions](#14-removing-dimensions-squeeze)
15. [Transposing Tensors](#15-transposing-tensors)
16. [Permuting Dimensions](#16-permuting-dimensions)
17. [Matrix Multiplication](#17-matrix-multiplication)
18. [Tensor Concatenation](#18-tensor-concatenation)
19. [Tensor Stacking](#19-tensor-stacking)
20. [Splitting Tensors](#20-splitting-tensors)
21. [Tensor Type Conversion](#21-tensor-type-conversion)
22. [Tensor Cloning](#22-tensor-cloning)
23. [Copying Tensors](#23-copying-tensors)
24. [Tensor Comparison Operations](#24-tensor-comparison-operations)
25. [Boolean Masking](#25-boolean-masking)
26. [Conditional Operations](#26-conditional-operations-where)
27. [Tensor Broadcasting](#27-tensor-broadcasting)
28. [Random Tensor Generation](#28-random-tensor-generation)
29. [Tensor Initialization Methods](#29-tensor-initialization-methods)
30. [NumPy ↔ PyTorch Conversion](#30-numpy--pytorch-conversion)
31. [Tensor Memory Layout & Contiguity](#31-tensor-memory-layout--contiguity)
32. [Tensor Device Management](#32-tensor-device-management-cpugpu)
33. [Random Seeds & Reproducibility](#33-random-seeds--reproducibility)

---

## Setup

```python
import torch
import numpy as np
```

---

## 1. Tensor Creation

A **tensor** is the core data structure in PyTorch — a multi-dimensional array that supports automatic differentiation and GPU acceleration.

### From Python lists

```python
# 1D tensor (vector)
t1 = torch.tensor([1, 2, 3])
print(t1)  # tensor([1, 2, 3])

# 2D tensor (matrix)
t2 = torch.tensor([[1, 2, 3],
                   [4, 5, 6]])
print(t2)
# tensor([[1, 2, 3],
#         [4, 5, 6]])

# 3D tensor
t3 = torch.tensor([[[1, 2], [3, 4]],
                   [[5, 6], [7, 8]]])
print(t3.shape)  # torch.Size([2, 2, 2])
```

### With explicit dtype

```python
t_float = torch.tensor([1.0, 2.0, 3.0], dtype=torch.float32)
t_int   = torch.tensor([1, 2, 3],       dtype=torch.int64)
t_bool  = torch.tensor([True, False, True], dtype=torch.bool)
```

### Factory functions

```python
torch.zeros(3, 4)         # All zeros, shape (3, 4)
torch.ones(2, 3)          # All ones,  shape (2, 3)
torch.full((2, 3), 7.0)   # Filled with 7.0, shape (2, 3)
torch.eye(4)              # 4×4 identity matrix
torch.empty(2, 3)         # Uninitialized (values are garbage)
torch.arange(0, 10, 2)    # [0, 2, 4, 6, 8]  (start, stop, step)
torch.linspace(0, 1, 5)   # [0.0, 0.25, 0.5, 0.75, 1.0]
```

### Like-shaped tensors

```python
x = torch.tensor([[1, 2], [3, 4]], dtype=torch.float32)

torch.zeros_like(x)   # zeros with same shape & dtype as x
torch.ones_like(x)    # ones  with same shape & dtype as x
torch.empty_like(x)   # uninitialized, same shape & dtype
torch.rand_like(x)    # uniform random [0, 1), same shape & dtype
```

---

## 2. Tensor Properties

```python
t = torch.tensor([[1.0, 2.0, 3.0],
                  [4.0, 5.0, 6.0]])

print(t.shape)    # torch.Size([2, 3])  — dimensions
print(t.size())   # torch.Size([2, 3])  — same as .shape
print(t.dtype)    # torch.float32       — element data type
print(t.device)   # cpu                 — where the tensor lives
print(t.ndim)     # 2                   — number of dimensions
print(t.numel())  # 6                   — total number of elements
print(t.is_cuda)  # False               — True if on GPU
print(t.requires_grad)  # False         — True if tracking gradients
```

### Accessing individual dimension sizes

```python
t = torch.zeros(3, 4, 5)
print(t.shape[0])  # 3
print(t.shape[1])  # 4
print(t.shape[2])  # 5
```

---

## 3. Indexing

PyTorch uses 0-based indexing. Negative indices count from the end.

```python
t = torch.tensor([[10, 20, 30],
                  [40, 50, 60],
                  [70, 80, 90]])

# Single element
print(t[0, 0])   # tensor(10)
print(t[1, 2])   # tensor(60)
print(t[-1, -1]) # tensor(90)  — last row, last column

# Entire row / column
print(t[0])      # tensor([10, 20, 30])  — row 0
print(t[:, 1])   # tensor([20, 50, 80])  — column 1

# Extract scalar value from a 0-d tensor
val = t[0, 0].item()
print(val, type(val))  # 10  <class 'int'>
```

---

## 4. Slicing

Slicing syntax: `start:stop:step` (same as NumPy).

```python
t = torch.arange(16).reshape(4, 4)
# tensor([[ 0,  1,  2,  3],
#         [ 4,  5,  6,  7],
#         [ 8,  9, 10, 11],
#         [12, 13, 14, 15]])

t[1:3]       # rows 1 and 2
# tensor([[ 4,  5,  6,  7],
#         [ 8,  9, 10, 11]])

t[:, 1:3]    # all rows, columns 1 and 2
# tensor([[ 1,  2],
#         [ 5,  6],
#         [ 9, 10],
#         [13, 14]])

t[0:4:2]     # every other row (rows 0 and 2)
# tensor([[ 0,  1,  2,  3],
#         [ 8,  9, 10, 11]])

t[1:3, 1:3]  # sub-matrix
# tensor([[ 5,  6],
#         [ 9, 10]])

t[::-1]      # reverse rows (use torch.flip for clarity)
```

> **Note:** Slices return **views**, not copies. Modifying a slice modifies the original tensor.

---

## 5. Modifying Tensor Values

```python
t = torch.zeros(3, 3)

# Set a single element
t[0, 0] = 9.0

# Set an entire row
t[1] = torch.tensor([1.0, 2.0, 3.0])

# Set an entire column
t[:, 2] = 7.0

# Set a sub-region
t[0:2, 0:2] = torch.tensor([[10.0, 20.0],
                              [30.0, 40.0]])

print(t)
# tensor([[10., 20.,  7.],
#         [30., 40.,  7.],
#         [ 0.,  0.,  7.]])
```

### In-place operations (trailing `_`)

In-place operations modify the tensor **directly** (no new allocation).

```python
t = torch.ones(3)
t.fill_(5.0)    # t is now tensor([5., 5., 5.])
t.add_(2.0)     # t is now tensor([7., 7., 7.])
t.zero_()       # t is now tensor([0., 0., 0.])
```

> ⚠️ In-place operations can break autograd — avoid them on tensors that require gradients.

---

## 6. Tensor Arithmetic Operations

All standard arithmetic operators work element-wise when tensor shapes match (or are broadcastable).

```python
a = torch.tensor([1.0, 2.0, 3.0])
b = torch.tensor([4.0, 5.0, 6.0])

# Addition
a + b                  # tensor([5., 7., 9.])
torch.add(a, b)        # same

# Subtraction
a - b                  # tensor([-3., -3., -3.])
torch.sub(a, b)        # same

# Element-wise multiplication
a * b                  # tensor([ 4., 10., 18.])
torch.mul(a, b)        # same

# Element-wise division
a / b                  # tensor([0.2500, 0.4000, 0.5000])
torch.div(a, b)        # same

# Element-wise power
a ** 2                 # tensor([1., 4., 9.])
torch.pow(a, 2)        # same

# Floor division
a // b                 # tensor([0., 0., 0.])

# Modulo
b % a                  # tensor([0., 1., 0.])

# Scalar arithmetic (broadcasts automatically)
a + 10                 # tensor([11., 12., 13.])
a * 3                  # tensor([3., 6., 9.])
```

---

## 7. Mathematical Functions

```python
t = torch.tensor([0.0, 1.0, 2.0, 3.0])

torch.sqrt(t)           # tensor([0.0000, 1.0000, 1.4142, 1.7321])
torch.exp(t)            # tensor([ 1.0000,  2.7183,  7.3891, 20.0855])
torch.log(t + 1)        # tensor([0.0000, 0.6931, 1.0986, 1.3863])
torch.log2(t + 1)       # base-2 logarithm
torch.log10(t + 1)      # base-10 logarithm
torch.abs(t - 1.5)      # tensor([1.5000, 0.5000, 0.5000, 1.5000])
torch.ceil(torch.tensor([1.2, 2.7, -0.3]))   # tensor([ 2.,  3., -0.])
torch.floor(torch.tensor([1.2, 2.7, -0.3]))  # tensor([ 1.,  2., -1.])
torch.round(torch.tensor([1.4, 1.5, 1.6]))   # tensor([1., 2., 2.])
torch.clamp(t, min=1.0, max=2.5)             # tensor([1.0000, 1.0000, 2.0000, 2.5000])

# Trigonometry
torch.sin(t)
torch.cos(t)
torch.tan(t)

# Hyperbolic
torch.tanh(t)   # commonly used as an activation function
torch.sigmoid(t) # 1 / (1 + exp(-t))
```

---

## 8. Reduction Operations

Reduction operations collapse one or more dimensions into a single scalar (or smaller tensor).

```python
t = torch.tensor([[1.0, 2.0, 3.0],
                  [4.0, 5.0, 6.0]])

torch.sum(t)          # tensor(21.)        — sum of all elements
torch.mean(t)         # tensor(3.5000)     — mean of all elements
torch.max(t)          # tensor(6.)         — global maximum
torch.min(t)          # tensor(1.)         — global minimum
torch.prod(t)         # tensor(720.)       — product of all elements
torch.std(t)          # tensor(1.8708)     — standard deviation
torch.var(t)          # tensor(3.5000)     — variance
torch.median(t)       # tensor(3.5000)     — median
torch.norm(t)         # tensor(9.5394)     — L2 norm (Frobenius)

# argmax / argmin — index of the max/min element
torch.argmax(t)   # tensor(5) — flat index
torch.argmin(t)   # tensor(0) — flat index
```

---

## 9. Dimension-wise Operations

Specify `dim` to reduce along a particular axis.

```python
t = torch.tensor([[1.0, 2.0, 3.0],
                  [4.0, 5.0, 6.0]])
#                   dim=1 →
# dim=0 ↓

torch.sum(t, dim=0)          # sum along rows    → tensor([5., 7., 9.])
torch.sum(t, dim=1)          # sum along columns → tensor([ 6., 15.])

torch.mean(t, dim=0)         # tensor([2.5000, 3.5000, 4.5000])
torch.mean(t, dim=1)         # tensor([2., 5.])

torch.max(t, dim=0)          # values: tensor([4., 5., 6.]), indices: tensor([1, 1, 1])
torch.max(t, dim=1)          # values: tensor([3., 6.]),    indices: tensor([2, 2])

torch.argmax(t, dim=0)       # tensor([1, 1, 1])
torch.argmax(t, dim=1)       # tensor([2, 2])

# keepdim=True preserves the reduced dimension
torch.sum(t, dim=1, keepdim=True)
# tensor([[ 6.],
#         [15.]])  — shape (2, 1) instead of (2,)
```

---

## 10. Tensor Reshaping

`reshape` returns a tensor with a new shape. The total number of elements must remain the same.

```python
t = torch.arange(12)
print(t)         # tensor([ 0,  1,  2, ..., 11])
print(t.shape)   # torch.Size([12])

a = t.reshape(3, 4)    # shape (3, 4)
b = t.reshape(4, 3)    # shape (4, 3)
c = t.reshape(2, 2, 3) # shape (2, 2, 3)
d = t.reshape(2, -1)   # -1 means "infer this dimension" → shape (2, 6)
e = t.reshape(-1, 4)   # infer first dim → shape (3, 4)

print(c)
# tensor([[[ 0,  1,  2],
#          [ 3,  4,  5]],
#         [[ 6,  7,  8],
#          [ 9, 10, 11]]])
```

> `reshape` returns a **view** when possible, otherwise a **copy**.

---

## 11. Viewing Tensors

`view` is like `reshape` but **always returns a view** (zero copy). The tensor must be **contiguous** in memory.

```python
t = torch.arange(6)

v = t.view(2, 3)
print(v)
# tensor([[0, 1, 2],
#         [3, 4, 5]])

# Modifying the view modifies the original
v[0, 0] = 99
print(t[0])  # tensor(99)

# If tensor is not contiguous, call .contiguous() first
t_t = t.view(2, 3).t()           # transpose makes it non-contiguous
t_c = t_t.contiguous().view(-1)  # safe
```

### `reshape` vs `view`

| | `view` | `reshape` |
|---|---|---|
| Always a view? | ✅ Yes (or raises error) | ❌ No (may copy) |
| Requires contiguous? | ✅ Yes | ❌ No |
| Recommended? | When you need guaranteed view | General use |

---

## 12. Flattening Tensors

Collapse all (or some) dimensions into one.

```python
t = torch.tensor([[[1, 2], [3, 4]],
                  [[5, 6], [7, 8]]])   # shape (2, 2, 2)

# Flatten all dimensions
f = t.flatten()
print(f)       # tensor([1, 2, 3, 4, 5, 6, 7, 8])
print(f.shape) # torch.Size([8])

# Flatten only specific dimensions (start_dim, end_dim)
f2 = t.flatten(start_dim=1)   # flatten dims 1 and 2 only
print(f2.shape)                # torch.Size([2, 4])
print(f2)
# tensor([[1, 2, 3, 4],
#         [5, 6, 7, 8]])

# torch.flatten is equivalent
torch.flatten(t)
```

---

## 13. Adding Dimensions (`unsqueeze`)

Insert a new dimension of size 1 at the specified position.

```python
t = torch.tensor([1.0, 2.0, 3.0])  # shape (3,)

t.unsqueeze(0)   # shape (1, 3) — add batch dimension
# tensor([[1., 2., 3.]])

t.unsqueeze(1)   # shape (3, 1) — add channel dimension
# tensor([[1.],
#         [2.],
#         [3.]])

# Negative indexing
t.unsqueeze(-1)  # same as unsqueeze(1) for 1D tensors

# Common use: add batch dimension to a single image (C, H, W) → (1, C, H, W)
img = torch.randn(3, 64, 64)       # (C, H, W)
batch = img.unsqueeze(0)            # (1, C, H, W)
print(batch.shape)                  # torch.Size([1, 3, 64, 64])
```

---

## 14. Removing Dimensions (`squeeze`)

Remove dimensions of size 1.

```python
t = torch.zeros(1, 3, 1, 4)
print(t.shape)          # torch.Size([1, 3, 1, 4])

t.squeeze()             # removes ALL size-1 dims → shape (3, 4)
t.squeeze(0)            # removes only dim 0     → shape (3, 1, 4)
t.squeeze(2)            # removes only dim 2     → shape (1, 3, 4)
t.squeeze(-1)           # removes last dim       → shape (1, 3, 1) — only if size is 1

# squeeze does NOT remove a dim of size > 1
x = torch.zeros(2, 3)
x.squeeze(0)            # no change — dim 0 has size 2
print(x.shape)          # torch.Size([2, 3])
```

---

## 15. Transposing Tensors

### 2D transpose

```python
t = torch.tensor([[1, 2, 3],
                  [4, 5, 6]])   # shape (2, 3)

t.T                 # shape (3, 2)  — shorthand for 2D
t.t()               # same
torch.transpose(t, 0, 1)  # same, explicit

print(t.T)
# tensor([[1, 4],
#         [2, 5],
#         [3, 6]])
```

### Multi-dimensional transpose

For tensors with more than 2 dimensions, `torch.transpose` swaps exactly two specified dimensions.

```python
t = torch.randn(2, 3, 4)          # shape (2, 3, 4)
t_tr = torch.transpose(t, 1, 2)   # swap dim 1 and 2 → shape (2, 4, 3)
print(t_tr.shape)                  # torch.Size([2, 4, 3])
```

> `.T` only works cleanly for 2D tensors. For higher-dimensional tensors, use `permute` (see next section).

---

## 16. Permuting Dimensions

`permute` rearranges all dimensions at once (more flexible than `transpose`).

```python
t = torch.randn(2, 3, 4)       # shape (2, 3, 4)

# Reorder dimensions by index
t.permute(2, 0, 1)             # shape (4, 2, 3)
t.permute(0, 2, 1)             # shape (2, 4, 3)

# Common use: convert between (Batch, Height, Width, Channels)
#             and (Batch, Channels, Height, Width) for neural networks
image = torch.randn(8, 64, 64, 3)      # (B, H, W, C)
image_pytorch = image.permute(0, 3, 1, 2)  # (B, C, H, W)
print(image_pytorch.shape)             # torch.Size([8, 3, 64, 64])
```

---

## 17. Matrix Multiplication

```python
a = torch.tensor([[1.0, 2.0],
                  [3.0, 4.0]])   # shape (2, 2)

b = torch.tensor([[5.0, 6.0],
                  [7.0, 8.0]])   # shape (2, 2)

# All three are equivalent:
torch.matmul(a, b)
torch.mm(a, b)         # 2D only
a @ b                  # @ operator (recommended for readability)

# Result:
# tensor([[19., 22.],
#         [43., 50.]])
```

### Matrix-vector multiplication

```python
A = torch.randn(3, 4)
v = torch.randn(4)

result = A @ v           # shape (3,)
result = torch.mv(A, v)  # same, explicit matrix-vector
```

### Batched matrix multiplication

```python
# When input has 3+ dimensions, matmul does batched matmul
batch_a = torch.randn(10, 3, 4)   # 10 matrices of shape (3, 4)
batch_b = torch.randn(10, 4, 5)   # 10 matrices of shape (4, 5)

result = batch_a @ batch_b
print(result.shape)   # torch.Size([10, 3, 5])
```

### Dot product (1D vectors)

```python
a = torch.tensor([1.0, 2.0, 3.0])
b = torch.tensor([4.0, 5.0, 6.0])

torch.dot(a, b)    # tensor(32.)  — 1*4 + 2*5 + 3*6
a @ b              # same
```

---

## 18. Tensor Concatenation

`torch.cat` joins tensors along an **existing** dimension.

```python
a = torch.tensor([[1, 2], [3, 4]])   # shape (2, 2)
b = torch.tensor([[5, 6], [7, 8]])   # shape (2, 2)

# Along dim 0 (stacks rows)
torch.cat([a, b], dim=0)
# tensor([[1, 2],
#         [3, 4],
#         [5, 6],
#         [7, 8]])  — shape (4, 2)

# Along dim 1 (stacks columns)
torch.cat([a, b], dim=1)
# tensor([[1, 2, 5, 6],
#         [3, 4, 7, 8]])  — shape (2, 4)

# Concatenate more than two tensors
c = torch.tensor([[9, 10], [11, 12]])
torch.cat([a, b, c], dim=0)   # shape (6, 2)
```

---

## 19. Tensor Stacking

`torch.stack` creates a **new dimension** and stacks tensors along it. All input tensors must have the **same shape**.

```python
a = torch.tensor([1, 2, 3])
b = torch.tensor([4, 5, 6])
c = torch.tensor([7, 8, 9])

torch.stack([a, b, c], dim=0)
# tensor([[1, 2, 3],
#         [4, 5, 6],
#         [7, 8, 9]])  — shape (3, 3) — new dim at position 0

torch.stack([a, b, c], dim=1)
# tensor([[1, 4, 7],
#         [2, 5, 8],
#         [3, 6, 9]])  — shape (3, 3) — new dim at position 1
```

### `cat` vs `stack`

| | `cat` | `stack` |
|---|---|---|
| Creates new dim? | ❌ No | ✅ Yes |
| Shape requirement | Matching except on `dim` | All identical |
| Output ndim | Same as input | Input ndim + 1 |

---

## 20. Splitting Tensors

### `torch.split` — split into chunks of specified size

```python
t = torch.arange(12).reshape(4, 3)

# Split into chunks of size 2 along dim 0
parts = torch.split(t, 2, dim=0)
# (tensor([[0, 1, 2], [3, 4, 5]]),
#  tensor([[6, 7, 8], [9, 10, 11]]))

# Split into unequal chunks (list of sizes)
parts = torch.split(t, [1, 3], dim=0)
# sizes 1 and 3 along dim 0
```

### `torch.chunk` — split into N equal-ish parts

```python
t = torch.arange(10)

parts = torch.chunk(t, 3)   # split into 3 parts
# (tensor([0, 1, 2, 3]),
#  tensor([4, 5, 6, 7]),
#  tensor([8, 9]))           # last chunk may be smaller
```

---

## 21. Tensor Type Conversion

### Check the dtype

```python
t = torch.tensor([1, 2, 3])
print(t.dtype)   # torch.int64
```

### Convert with `.to(dtype)` (recommended)

```python
t = torch.tensor([1, 2, 3])

t.to(torch.float32)   # integer → float32
t.to(torch.float64)   # integer → float64
t.to(torch.int32)     # int64   → int32
t.to(torch.bool)      # nonzero → True
```

### Shorthand casting methods

```python
t.float()     # → float32
t.double()    # → float64
t.int()       # → int32
t.long()      # → int64
t.short()     # → int16
t.byte()      # → uint8
t.bool()      # → bool
t.half()      # → float16
```

### Example

```python
t = torch.tensor([1.7, 2.3, 3.9])
print(t.long())    # tensor([1, 2, 3])  — truncates decimal
print(t.bool())    # tensor([True, True, True])  — nonzero = True
print(torch.tensor([0, 1, 0]).bool())  # tensor([False, True, False])
```

---

## 22. Tensor Cloning

`clone()` creates a **deep copy** — a completely independent tensor with its own memory. Changes to the clone do **not** affect the original.

```python
a = torch.tensor([1.0, 2.0, 3.0])
b = a.clone()

b[0] = 99.0
print(a)   # tensor([1., 2., 3.])   — unchanged
print(b)   # tensor([99.,  2.,  3.])

# clone preserves gradient history by default
# use clone().detach() to break gradient tracking
c = a.clone().detach()
```

### View vs Clone

```python
a = torch.tensor([1.0, 2.0, 3.0])

b = a.view(3)    # b is a VIEW — shares memory
c = a.clone()    # c is a COPY — independent memory

b[0] = 99.0
print(a[0])  # tensor(99.)  — a was modified!

c[0] = 0.0
print(a[0])  # tensor(99.)  — a unchanged
```

---

## 23. Copying Tensors

`copy_()` is an **in-place** copy — it overwrites the destination tensor with the values from the source.

```python
src = torch.tensor([1.0, 2.0, 3.0])
dst = torch.zeros(3)

dst.copy_(src)
print(dst)   # tensor([1., 2., 3.])

# copy_ also works across dtypes (automatic casting)
dst_int = torch.zeros(3, dtype=torch.int32)
dst_int.copy_(src)
print(dst_int)   # tensor([1, 2, 3], dtype=torch.int32)

# copy_ also works across devices
# dst_gpu = dst_cpu.to('cuda')  — preferred
# dst_gpu.copy_(src_cpu)        — also valid
```

---

## 24. Tensor Comparison Operations

Element-wise comparisons return **boolean tensors**.

```python
a = torch.tensor([1, 2, 3, 4, 5])
b = torch.tensor([5, 4, 3, 2, 1])

a == b    # tensor([False, False,  True, False, False])
a != b    # tensor([ True,  True, False,  True,  True])
a <  b    # tensor([ True,  True, False, False, False])
a <= b    # tensor([ True,  True,  True, False, False])
a >  b    # tensor([False, False, False,  True,  True])
a >= b    # tensor([False, False,  True,  True,  True])

# Functional equivalents
torch.eq(a, b)
torch.lt(a, b)   # less than
torch.le(a, b)   # less than or equal
torch.gt(a, b)   # greater than
torch.ge(a, b)   # greater than or equal

# Compare all elements of two tensors
torch.equal(a, b)          # False — are ALL elements equal?
torch.allclose(a.float(), b.float(), atol=1e-5)  # False — for float comparisons
```

---

## 25. Boolean Masking

Use a boolean tensor to **select** or **filter** elements.

```python
t = torch.tensor([10, -3, 7, -1, 5, -8])

# Create a mask
mask = t > 0
print(mask)   # tensor([ True, False,  True, False,  True, False])

# Select elements where mask is True
t[mask]
# tensor([10,  7,  5])

# Equivalent: torch.masked_select
torch.masked_select(t, mask)
# tensor([10,  7,  5])

# Mask assignment — set negative values to 0
t[~mask] = 0
print(t)   # tensor([10,  0,  7,  0,  5,  0])

# Count how many True values
mask.sum()    # tensor(3)
mask.any()    # tensor(True)  — at least one True?
mask.all()    # tensor(False) — all True?
```

---

## 26. Conditional Operations (`where`)

`torch.where` is a vectorized if-else.

```python
# Syntax: torch.where(condition, x, y)
#         returns x where condition is True, y elsewhere

t = torch.tensor([-2.0, -1.0, 0.0, 1.0, 2.0])

# ReLU manually
relu = torch.where(t > 0, t, torch.zeros_like(t))
print(relu)   # tensor([0., 0., 0., 1., 2.])

# Replace negatives with -1, positives with 1 (sign function)
sign = torch.where(t > 0, torch.ones_like(t), torch.full_like(t, -1.0))
print(sign)   # tensor([-1., -1., -1.,  1.,  1.])

# Scalar alternatives
result = torch.where(t >= 0, t, t * -1)   # abs value
```

---

## 27. Tensor Broadcasting

Broadcasting allows operations between tensors of **different shapes** by automatically expanding dimensions to match.

### Rules

1. If tensors have different numbers of dimensions, the smaller one is padded with 1s **on the left**.
2. Dimensions of size 1 are expanded to match the other tensor.
3. If sizes are incompatible and neither is 1, an error is raised.

```python
# Scalar broadcast
a = torch.tensor([[1, 2, 3], [4, 5, 6]])
a + 10
# tensor([[11, 12, 13],
#         [14, 15, 16]])

# 1D + 2D
row = torch.tensor([10, 20, 30])          # shape (3,)
matrix = torch.ones(2, 3)                 # shape (2, 3)
matrix + row
# tensor([[11., 21., 31.],
#         [11., 21., 31.]])

# Column vector + row vector
col = torch.tensor([[1], [2], [3]])       # shape (3, 1)
row = torch.tensor([10, 20, 30])          # shape (3,)
col + row
# tensor([[11, 21, 31],
#         [12, 22, 32],
#         [13, 23, 33]])   — shape (3, 3)

# Check if shapes are broadcastable before operating
torch.broadcast_shapes((3, 1), (1, 4))   # → torch.Size([3, 4])
```

---

## 28. Random Tensor Generation

```python
# Uniform distribution [0, 1)
torch.rand(3, 4)

# Standard normal (mean=0, std=1)
torch.randn(3, 4)

# Normal with custom mean and std
torch.normal(mean=5.0, std=2.0, size=(3, 4))

# Random integers [low, high)
torch.randint(low=0, high=10, size=(3, 4))

# Random permutation of integers 0..n-1
torch.randperm(10)
# tensor([4, 2, 7, 0, ...])

# Random boolean
torch.randint(0, 2, size=(3,)).bool()

# Sample from a multinomial distribution
weights = torch.tensor([0.1, 0.5, 0.4])
torch.multinomial(weights, num_samples=5, replacement=True)
```

---

## 29. Tensor Initialization Methods

Common patterns for weight initialization in neural networks.

```python
# Uniform distribution in [a, b)
t = torch.empty(3, 4)
torch.nn.init.uniform_(t, a=0.0, b=1.0)

# Normal distribution
torch.nn.init.normal_(t, mean=0.0, std=1.0)

# Constant
torch.nn.init.constant_(t, val=0.5)

# Zeros / Ones
torch.nn.init.zeros_(t)
torch.nn.init.ones_(t)

# Xavier uniform (Glorot) — good for tanh/sigmoid
torch.nn.init.xavier_uniform_(t)

# Xavier normal
torch.nn.init.xavier_normal_(t)

# Kaiming uniform (He) — good for ReLU
torch.nn.init.kaiming_uniform_(t, nonlinearity='relu')

# Kaiming normal
torch.nn.init.kaiming_normal_(t, nonlinearity='relu')

# Orthogonal
torch.nn.init.orthogonal_(t)

# Eye (identity matrix, for 2D only)
t2d = torch.empty(4, 4)
torch.nn.init.eye_(t2d)
```

---

## 30. NumPy ↔ PyTorch Conversion

PyTorch and NumPy share memory when the tensor is on CPU — changes to one are reflected in the other.

### NumPy → PyTorch

```python
import numpy as np

arr = np.array([[1.0, 2.0], [3.0, 4.0]])

# Shared memory (zero-copy)
t = torch.from_numpy(arr)
arr[0, 0] = 99.0
print(t[0, 0])  # tensor(99.)  — t reflects the change!

# Independent copy
t_copy = torch.tensor(arr)   # breaks the link
```

### PyTorch → NumPy

```python
t = torch.tensor([[1.0, 2.0], [3.0, 4.0]])

# Shared memory (zero-copy) — tensor must be on CPU
arr = t.numpy()
t[0, 0] = 99.0
print(arr[0, 0])  # 99.0 — arr reflects the change!

# Detach first if gradients are tracked
t_grad = torch.tensor([1.0, 2.0], requires_grad=True)
arr = t_grad.detach().numpy()
```

> ⚠️ `.numpy()` only works on **CPU tensors**. For GPU tensors: `t.cpu().numpy()` or `t.cpu().detach().numpy()`.

---

## 31. Tensor Memory Layout & Contiguity

A tensor is **contiguous** when its elements are laid out in memory in the same order as the logical index order (row-major / C-style).

```python
t = torch.arange(12).reshape(3, 4)
print(t.is_contiguous())   # True

# Operations like transpose return non-contiguous views
t_t = t.T
print(t_t.is_contiguous())  # False

# Make contiguous
t_c = t_t.contiguous()
print(t_c.is_contiguous())  # True

# Memory strides — number of elements to step per dimension
print(t.stride())     # (4, 1)   — move 4 elements to go to next row
print(t_t.stride())   # (1, 4)   — transposed: strides are swapped
```

### Why does this matter?

- `view()` requires contiguous tensors.
- Some C++/CUDA kernels require contiguous memory for performance.
- After transpose/permute, call `.contiguous()` before `view()` if needed.

```python
# Common pattern
out = t.permute(1, 0).contiguous().view(-1)
```

---

## 32. Tensor Device Management (CPU/GPU)

### Check available devices

```python
print(torch.cuda.is_available())           # True if CUDA GPU is present
print(torch.cuda.device_count())           # number of GPUs
print(torch.cuda.get_device_name(0))       # GPU name
```

### Move tensors between devices

```python
t = torch.tensor([1.0, 2.0, 3.0])   # lives on CPU

# Move to GPU (if available)
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

t_gpu = t.to(device)
t_gpu = t.to('cuda')       # equivalent shorthand
t_gpu = t.cuda()           # equivalent, older style

# Move back to CPU
t_cpu = t_gpu.to('cpu')
t_cpu = t_gpu.cpu()        # equivalent

# Specify GPU index
t_gpu1 = t.to('cuda:1')    # second GPU
```

### Create tensors directly on a device

```python
device = torch.device('cuda')

t = torch.zeros(3, 4, device=device)
t = torch.randn(3, 4, device=device)
t = torch.tensor([1.0, 2.0], device=device)
```

### Device-aware code (best practice)

```python
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# Tensors and models on the same device
x = torch.randn(10, 3).to(device)
model = MyModel().to(device)
output = model(x)
```

> ⚠️ Operations between tensors on different devices will raise a `RuntimeError`. Always ensure both tensors are on the same device before computing.

---

## 33. Random Seeds & Reproducibility

Setting seeds ensures experiments are **reproducible** — the same random numbers are generated each run.

```python
# CPU seed
torch.manual_seed(42)

# GPU seed (for all GPUs)
torch.cuda.manual_seed_all(42)

# NumPy seed (if using NumPy alongside PyTorch)
import numpy as np
np.random.seed(42)

# Python built-in random
import random
random.seed(42)
```

### Full reproducibility setup

```python
import torch
import numpy as np
import random

def set_seed(seed: int = 42):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.deterministic = True
    torch.backends.cudnn.benchmark = False

set_seed(42)
```

> `cudnn.deterministic = True` forces cuDNN to use deterministic algorithms.
> `cudnn.benchmark = False` disables auto-tuning (which is non-deterministic).
> Both may slightly reduce performance but are necessary for full reproducibility on GPU.

### Check and save RNG state

```python
# Save the current state
state = torch.get_rng_state()

# ... do something random ...

# Restore the state (replay the same random numbers)
torch.set_rng_state(state)
```

---

## Quick Reference Cheat Sheet

| Operation | Syntax |
|---|---|
| Create from list | `torch.tensor([1, 2, 3])` |
| Zeros / Ones | `torch.zeros(3, 4)` / `torch.ones(3, 4)` |
| Range | `torch.arange(0, 10, 2)` |
| Shape | `t.shape` or `t.size()` |
| Dtype | `t.dtype` |
| Device | `t.device` |
| Reshape | `t.reshape(2, -1)` |
| View | `t.view(2, -1)` |
| Flatten | `t.flatten()` |
| Add dim | `t.unsqueeze(0)` |
| Remove dim | `t.squeeze(0)` |
| Transpose (2D) | `t.T` or `t.t()` |
| Permute | `t.permute(2, 0, 1)` |
| Matrix multiply | `a @ b` |
| Concatenate | `torch.cat([a, b], dim=0)` |
| Stack | `torch.stack([a, b], dim=0)` |
| Split | `torch.split(t, 2, dim=0)` |
| Cast | `t.float()` / `t.to(torch.float32)` |
| Clone | `t.clone()` |
| Copy into | `dst.copy_(src)` |
| Boolean mask | `t[t > 0]` |
| Where | `torch.where(cond, x, y)` |
| To GPU | `t.to('cuda')` |
| To NumPy | `t.numpy()` |
| From NumPy | `torch.from_numpy(arr)` |
| Set seed | `torch.manual_seed(42)` |
| Sum / Mean / Max | `t.sum()` / `t.mean()` / `t.max()` |
| Argmax | `torch.argmax(t, dim=1)` |
| Contiguous | `t.contiguous()` |

---

*PyTorch documentation: https://pytorch.org/docs/stable/torch.html*