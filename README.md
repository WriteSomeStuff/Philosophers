# Philosophers - @Codam
A project to learn about threads with the pthread functions and how to avoid deadlocks.

## How does it work?

```bash
git clone https://github.com/WriteSomeStuff/Philosophers.git
cd Philosophers
make
./philo nr_of_philosophers time_to_die time_to_eat time_to_sleep (optional: nr_of_times_each_philo_must_eat)
```
You should see a file called philo after make succeeded.

example input: ./philo 5 800 200 200 7

◦ nr_of_philosophers: The number of philosophers and also the number of forks.

◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

◦ nr_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
