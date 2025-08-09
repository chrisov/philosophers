<div align="center">
  <img src="https://www.dieter-schwarz-stiftung.de/files/Projects/Project%20logos/Logo_42HN-min.jpg" alt="Logo"/>
</div>

<br>
<div align="center">
  
  ### 🛠 C (Programming Language)
  ### 🛠 pthread.h (Concurrent Programming)
</div>

<br>

# Philosophers

This project is an implementation of the classic Dining Philosophers problem in C, designed to simulate concurrent 
resource sharing and synchronization among multiple threads. Each philosopher alternates between thinking, eating, 
and sleeping, while competing for limited resources (forks) placed between them. The solution aims to prevent deadlocks 
and starvation, ensuring that all philosophers can eat without violating mutual exclusion constraints.

<div align="center">
  <br><br>
  <img src="https://github.com/chrisov/philosophers/blob/b2665a9bc07ba8c96a78f6830e6fbc5d3536c43c/table.png" alt="Table picture" width="600" height="600"/>
  <br><br>
</div>


## Technical Approach <br>
<p>The project uses threads (pthread) to represent philosophers, with each thread running its own routine. 
Forks are modeled as mutex-protected resources in a circular linked list, ensuring that only one philosopher can hold 
a fork at a time. The core logic carefully manages fork acquisition and release to avoid deadlocks, using a monitor 
thread to detect starvation or death. Shared states, such as meal counts (unsigned int meals_eaten) and simulation status
(bool end), is protected by additional mutexes to guarantee thread safety. Initialization routines set up all data structures,
and cleanup functions ensure proper resource deallocation. The most critical aspect is the synchronization strategy, which balances 
resource contention and fairness, preventing both deadlock and starvation while maintaining high concurrency.</p>

<div align="center"><br>

  ### ./philo [num_of_philo]  [time_to_die]  [time_to_eat]  [time_to_sleep]  [num_of_eat_times] (OPT)
</div><br>

## Philosopher Routine Approach
<p>Each philosopher is represented by a thread running the philo_routine function. The routine begins by initializing 
the philosopher's state. The philosopher then enters a loop that continues until the simulation ends (either due to
a philosopher dying or all philosophers eating the required number of meals).</p>

Within each loop iteration:

<p>The philosopher attempts to pick up both forks (using forks_pickup()). If unsuccessful or if the simulation has ended, the loop breaks.
If both forks are acquired, the philosopher proceeds to eat (eating()), which updates their last meal time and meal count in a thread-safe manner. 
After eating, the philosopher releases the forks. The philosopher then sleeps for a configured duration (sleeping()),
followed by a brief thinking period. The loop includes a short sleep (usleep(100)) to reduce busy-waiting and allow other threads to run.
At the end of the routine, any held forks are released to ensure proper resource cleanup.</p>

## Monitor Thread Approach
<p>The monitor thread is implemented in the monitor_routine() function. Its role is to continuously check the state of all 
philosophers to ensure no one has starved and that the meal requirements are met.</p>

The monitor:

<p>Iterates over all philosophers, checking each one's last meal time and total meals eaten.
If the time since a philosopher's last meal exceeds the allowed time_to_die, the monitor sets the simulation end flag 
and returns the pointer to the philosopher who died. If all philosophers have eaten the required number of meals,
the monitor sets the simulation end flag and returns NULL. The monitor uses mutexes to safely access and update shared state.
The loop includes a short sleep (usleep(100)) after each full pass to avoid excessive CPU usage.
This approach ensures timely detection of starvation and completion, allowing the simulation to terminate gracefully and print the appropriate status.</p>

