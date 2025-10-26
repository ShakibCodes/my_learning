# AsyncIO in Python

In normal Synchronous Programminng every tasks happens simultaneously but in case of Asynchronous it's opposite
<br>
every task happens start with a same time, i mean it helps to handle multiple task without extra loads, use it where tasks wait for the first one to complete first 

## 1. The Event Loop

Now this is one for the concept of async
<Br>
here all the task keeps on going and one is selected to be executed but if it's dependent or waits for something then it will be paused fot that moment but in that moment another task comes in and executes until the other one is in await, and this is how the program never stops and tasks are always being executed 


# Syntax

To work with async python we have to import the `asyncio` module