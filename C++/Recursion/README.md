# What is Recursion

Recursion simply means:
> A function calling itself.

Example:

```cpp
void hello() {
    cout << "Hello";
    hello();
}
```
Here,

```bash
hello()
   ↓
hello()
   ↓
hello()
   ↓
hello()
```

It keeps calling itself forever.<br>
Eventually your program crashes with something called `Stack Overflow`<br>

So recursion **always needs a stopping condition**.

## What is Stack Overflow in Recursion?

Whenever recursion calls are executed, they’re simultaneously stored in a recursion stack where they wait for the completion of the recursive function. A recursive function can only be completed if a base condition is fulfilled and the control returns to the parent function. 

But, when there is no base condition given for a particular recursive function, it gets called indefinitely which results in a Stack Overflow i.e, exceeding the memory limit of the recursion stack and hence the program terminates giving a Segmentation Fault error (or maybe just stop without giving an error in some cases). 

# Why do we need recursion?
Imagine I tell you:

> Count backwards from 5 to 1.

Normally you'd write:

```cpp
for(int i=5;i>=1;i--)
    cout<<i<<" ";
```
Output:
```
5 4 3 2 1
```

Now imagine you don't have loops.

How could you do it?

**Answer**:
```
Print 5

Then tell yourself:

"Now count backwards from 4."

Then tell yourself:

"Now count backwards from 3."

Then...

Until reaching 1.
```

That's **recursion**.

###  Recursive Function to Count backwards from 5 to 1.

```cpp
#include <iostream>
using namespace std;

void countdown(int n)
{
    if(n==0)
        return;

    cout<<n<<" ";

    countdown(n-1);
}

int main()
{
    countdown(5);
}
```
Output:
```
5 4 3 2 1
```

#### what actually happens?

We call
```cpp
countdown(5)
```
Inside:
```cpp
n = 5
Print 5
Call countdown(4)
```
Now
```cpp
countdown(4)
```
prints
> 4

Then calls
```cpp
countdown(3)
```
which calls `countdown(2)` which calls `countdown(1)`  
Now:
```cpp
if(n==0)
    return;
```
The **function stops**.