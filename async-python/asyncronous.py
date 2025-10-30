import asyncio

async def start_task():
    await asyncio.sleep(2)
    print("Start")

async def end_task():
    await asyncio.sleep(2)
    print("End")

async def main():
    # Run both tasks *concurrently*
    await asyncio.gather(
        start_task(),
        end_task()
    )

asyncio.run(main())
