# Multithreading in C

To test three different multithreading options, three programs simulates a similar situation : a number of philosophers need to eat when there in a limited number of fork. If one don't eat on time, the program must stop.

Each program takes thoses arguments : number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)

The first program uses threads with mutex
The seconde program uses threads with semaphor
The third program uses processes with semaphor

Features:
- Multithreading
- No memory leak

## Installation

Use this command in a terminal in each directory : 

```bash
make
```

(make and clang++ needed)

## Usage

```bash
./philo_one 5 800 200 200
./philo_two 4 310 200 200
./philo_three 5 800 200 200 7
```


#### Author : Alban Kerloc'h
#### Category: Low-level
#### Tag: CPP
