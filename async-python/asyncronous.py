import asyncio

async def task(id):
    print(f"Starting download {id}")
    await asyncio.sleep(2)
    print(f"Finished download {id}")

async def main():
    task1 = asyncio.create_task(task(1))
    task2 = asyncio.create_task(task(2))
    task3 = asyncio.create_task(task(3))

    await task1
    await task2
    await task3

asyncio.run(main())