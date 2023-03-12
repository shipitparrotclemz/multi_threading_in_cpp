# Multithreading Practice in C++

Hello! This repository contains a repository containing our chain of thought behind understanding multi-threading in C++

## Contents

1. Introduction to the standard thread library.

**Understanding the low-level`thread` object**

- Creating a second thread the low level way with the `thread` object

```c++
#include <thread>

void DoWork() {
    // do something
}

int main() {
    // creates a second thread, which runs off DoWork()
    std::thread worker(DoWork);
}
```

- Making the current thread wait for the second thread to finish with `worker.join()`

```c++
#include <thread>

void DoWork() {
    // do something
}

int main() {
    // creates a second thread, which runs off DoWork()
    std::thread worker(DoWork);
    
    // makes the first thread wait for the second thread to finish
    worker.join();
}
```

## Building and Running the Project

```
// Generate a build system for the current directory with CMake
cmake .

// Use the generated build system above to build the project
// Compiles the project into an executable binary file VanillaThreads
cmake --build .

// Run the executable binary file VanillaThreads

➜  multi_threading_in_c++ git:(master) ✗ ./VanillaThreads
C++ version: 201402
Main thread starts. Main thread id is: 0x202d362c0
Starting a second thread to start the database call
database call started on second thread. Second thread id: 0x309932000
database call completed on second thread
Main thread finishes
```

Now, our smart parrots might ask:

**Q: What is a thread?**

A: A thread is a sequence of instructions that can be executed independently of other parts of a program.

We can use threads to break up our program into smaller pieces, and execute them concurrently.

**Q: That is still quite hard to graspe! Gimme an analogy!**

A: Think of a program as a book. 

Each page of the book contains a set of instructions that tell the story. 

A thread is like a bookmark that you can place on a particular page of the book. 

You can have multiple bookmarks in the same book, and each bookmark represents a different thread of the story. 

You can flip back and forth between the pages represented by each bookmark, and the story will continue to unfold in parallel.

**Q: I see! What are some common use cases of threads?**

A: Here are two common use cases:

1. Speed up computations by performing multiple tasks concurrently 

We can break up our program into threads; smaller sequences of instructions, each capable of being executed independently of each other.

Our operating system then manages the execution of these threads, switching between them as necessary to ensure that they all make progress.

Now you smart parrots might ask:

**Q: What is a common, specific example of this use case?**

If we have a long-running operation which we have to make, such as making and waiting for a slow-running database query

We can choose to run that on a separate thread, and context switch to our main thread to execute other instructions while we wait.

**Q: Woah! Looks like multi-threading / concurrency with threading is really helpful! What are some of its drawbacks though?**

A: Very smart of you parrots!

Here are some drawbacks

1. Concurrency - Switching between threads requires additional instructions (CPU) and memory (RAM) 

We need more instructions (CPU) to switch between threads

and memory to keep track of where each thread's progress is.

We should ideally avoid context switching unless the benefits of shorter execution time is worth it.

2. Multi-threading can cause race conditions and deadlocks.

**Race conditions** 

Specifically happens when two or more running threads are allowed to access the same variable, database, or state of any sort.

**Q: Gimme a specific example!**

Imagine two interns, Bob and Boban, keeping track of people coming into a Starbucks cafe on a whiteboard.

Bob notices Sarah coming in, while Boban notices Shawn coming in at the same time.

Both attempt to read off the whiteboard (now showing 0), add 1 to it (new number: 1), and replace the whiteboard with the new score!

This results in the whiteboard having 1, though the result should really be two.

In this specific example, the race condition happens when both Bob and Boban access and update the whiteboard at the same time.

In this case, the whiteboard represents a variable, and Bob updating the whiteboard, and Boban updating the whiteboard as two separate threads.

Now you smart parrots would ask:

**Q: How do we prevent this race condition?**

**1. Locks**

We can prevent this by allowing only one person to update the whiteboard at a time!

One common way is to create a lock or mutex. This lock is analogous to a key, and the whiteboard only allows the person holding onto the key to update it.

So if both Bob and Boban tries to access the whiteboard, only one of them will get the lock and be able to update it. 

Lets say Bob accesses the lock to the whiteboard first, Bob will update the whiteboard while Boban waits for the lock.

Once Bob is done, Bob will free up the lock, and Boban accesses the lock to update the whiteboard.

This way, only one person can access the lock!

**Q: What are some other ways to prevent deadlocks?**

**2. Atomic operations**

Atomic operations are operations that are guaranteed to execute without interruption, even if multiple threads are trying to access the same resource at the same time. 

Many programming languages and platforms provide atomic operations for common tasks like incrementing or decrementing a counter.

**3. Use Message Passing**

Avoid sharing data between threads altogether. 

Instead, you can use message passing to communicate between threads in a way that avoids the need for shared resources.

**4. Thread Local Storage**

Thread-local storage (TLS) is a mechanism that allows each thread to have its own private copy of a shared variable. 

This can be useful when you need to maintain state across multiple function calls within a single thread, without the risk of other threads accessing or modifying that state.

**5. Use Immutable Data**

Immutable data is data that cannot be modified once it has been created. By using immutable data structures, you can avoid the need for locks or other synchronization mechanisms, since there is no risk of multiple threads trying to modify the same data at the same time.

**Deadlocks**

Deadlocks happen when 

- two or more threads holds a resource that the other threads need to continue running
- and all the threads are unwilling to release its own resources until it can acquire the other.

**Q: Gimme a specific example!**

Lets say Bob is making a croissant and needs eggs and flour, while Boban is making a cake and needs flour and eggs.

Lets say Bob acquires the lock to the eggs first.

and at the same time, Boban acquires the lock to the flour.

Now, Bob waits for Boban to free up the flour while holding onto the eggs

While Boban waits for Bob to free up the eggs while holding onto the flour.

We call this situation where Bob waits for Boban, and Boban waits for Bob, a circular wait.

Now, we don't get any croissant or cake :')
- this is an exaggerated example where both Bob and Boban don't want to give way to each other!

There we go! A deadlock!

**Q: How do we prevent deadlocks?**

**1. Fixed ordering on all resources**

We can impose a total ordering on all resources, including both the eggs and the flour, and require that all workers (Boban and Bob, we call these processes) acquire them in a specific order.

For example, both Bob and Boban must acquire flour first, before acquiring eggs.

**2. Use timeout and retries**

If Bob / Boban cannot acquire a resource within a certain period of time, they can release any resources they currently holds and try again later. This can help to break deadlocks that are caused by temporary resource contention.

**3. Use Resource Preemption**

Forcibly removing a resource from a process (Bob / Boban) that is holding it, in order to give it to another process that needs it more urgently. 

While this technique can be effective in breaking deadlocks, it can also be dangerous, since it can lead to unexpected behavior and even data corruption if not used carefully.

**4. Deadlock Detection Algorithm**

Periodically examine the resource allocation graph to determine whether a deadlock has occurred. 

If a deadlock is detected, the algorithm can take steps to break the deadlock, such as aborting one of the processes involved.

**5. Deadlock Avoidance Algorithm**

Analyze the resource allocation graph to determine whether a particular resource allocation request will lead to a deadlock. 

If the request would lead to a deadlock, the algorithm can reject the request and force the requesting process to wait until the necessary resources become available.