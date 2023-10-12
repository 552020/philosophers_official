#!/bin/bash

# API:
# ./test_philo.sh [number_of_runs] [runtime_in_seconds]

# Default values
DEFAULT_NUM_RUNS=1
DEFAULT_RUNTIME=10

# Get the number of runs and runtime from arguments or use the default values
NUM_RUNS=${1:-$DEFAULT_NUM_RUNS}
RUNTIME=${2:-$DEFAULT_RUNTIME}

# Execute the program the specified number of times
for (( i=1; i<=$NUM_RUNS; i++ )); do
    echo "Run $i:"
    
    # Start the philosopher program in the background and get its PID
    ./philo 5 800 200 200 &
    PHILO_PID=$!
    
    # Let it run for the specified amount of time
    sleep $RUNTIME
    
    # Check if the program is still running after the specified amount of time
    if ps -p $PHILO_PID > /dev/null; then
        echo "Program is still running as expected."
        
        # Kill the program so we can start the next run
        kill $PHILO_PID
    else
        echo "Problem: Program stopped before $RUNTIME seconds."
        exit 1
    fi
    
    echo "--------------------------"
done

echo "All runs completed successfully."

