from threading import Thread, Semaphore  # Import threading tools
import time
import random

# Shared variables
buffer = []                # This is the shared list where produced items go.
buffer_size = 5            # Maximum number of items that can be held in the buffer.
MAX_ITEMS = 10             # Total items that producer and consumer will handle.
produced = 0               # Count of how many items the producer has made.
consumed = 0               # Count of how many items the consumer has taken.

# Semaphores to manage access
mutex = Semaphore(1)       # Semaphore with count 1; used like a "lock" to manage safe access to buffer.
empty = Semaphore(buffer_size)  # Starts with buffer_size count, meaning all slots are empty.
full = Semaphore(0)        # Starts with 0 count, meaning no slots are full initially.

# Producer function
def producer():
    global produced
    while produced < MAX_ITEMS:          # Loop until MAX_ITEMS are produced
        item = random.randint(1, 100)    # Create a random item

        empty.acquire()                  # Wait if there are no empty slots; if there’s an empty slot, it moves forward and reduces the empty count.
        mutex.acquire()                  # Lock the buffer so only the producer or consumer can access it at a time.
        buffer.append(item)              # Add the item to the buffer.
        print(f"Produced: {item}, Buffer: {buffer}")
        produced += 1                    # Increase the produced count.

        mutex.release()                  # Unlock the buffer, allowing others to access it.
        full.release()                   # Signal that a new item is in the buffer, increasing the count of full slots.
        time.sleep(random.uniform(0.2, 1))  # Pause briefly to simulate time taken to produce an item.

# Consumer function
def consumer():
    global consumed
    while consumed < MAX_ITEMS:           # Loop until MAX_ITEMS are consumed
        full.acquire()                    # Wait if there are no filled slots; if there’s an item, it moves forward and reduces the full count.
        mutex.acquire()                   # Lock the buffer so only the consumer or producer can access it at a time.
        item = buffer.pop(0)              # Remove the first item from the buffer.
        print(f"Consumed: {item}, Buffer: {buffer}")
        consumed += 1                     # Increase the consumed count.

        mutex.release()                   # Unlock the buffer.
        empty.release()                   # Signal that a slot in the buffer is now empty, increasing the count of empty slots.
        time.sleep(random.uniform(0.5, 1.5))  # Pause briefly to simulate time taken to consume an item.

# Start producer and consumer threads
Thread(target=producer).start()  # Start a thread to run the producer function.
Thread(target=consumer).start()  # Start a thread to run the consumer function.
