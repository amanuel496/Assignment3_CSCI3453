
# CPU Scheduler Simulation

This project is a C++ program that simulates various CPU scheduling algorithms, including:

- First-Come, First-Served (FCFS)
- Shortest Remaining Time First (SRTF) - Preemptive
- Round Robin (RR)

## Overview

The simulator models the behavior of different CPU scheduling strategies by processing a set of input tasks, each with specified arrival times, CPU burst durations, and priorities. It provides insights into the performance of each algorithm by calculating metrics such as average turnaround time, waiting time, and response time.

## Features

- **Multi-Platform Support:** Implemented for both Linux and Windows systems.
- **Scheduling Algorithms:** Supports FCFS, SRTF (preemptive), and RR.
- **Sample Input:** Includes a sample process entry file in text format for testing purposes.
- **Comprehensive Metrics:** Calculates and displays performance metrics for each scheduling algorithm.

## Getting Started

### Prerequisites

- **Compiler:** Ensure you have a C++ compiler that supports C++11 or later.
- **Make Utility:** Recommended for building the project (optional).

### Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/amanuel496/Assignment3_CSCI3453.git
   cd Assignment3_CSCI3453
   ```

2. **Build the Project:**

   - **Using Make (if available):**

     ```bash
     make
     ```

   - **Manual Compilation:**

     ```bash
     g++ -std=c++11 main.cpp -o cpu_scheduler
     ```

### Running the Simulator

1. **Prepare Input File:**

   - Create a text file (e.g., `processes.txt`) with the following format for each process:

     ```
     pid arrival_time cpu_burst_time priority
     ```

     Example:

     ```
     1 0 10 2
     2 1 5 1
     3 2 8 3
     ```

2. **Execute the Program:**

   ```bash
   ./cpu_scheduler processes.txt [algorithm] [time_quantum]
   ```

   - **Parameters:**
     - `processes.txt`: Path to the input file containing process information.
     - `algorithm`: Scheduling algorithm to use (`fcfs`, `srtf`, or `rr`).
     - `time_quantum`: (Optional) Time quantum for Round Robin scheduling.

   - **Examples:**
     - FCFS: `./cpu_scheduler processes.txt fcfs`
     - SRTF: `./cpu_scheduler processes.txt srtf`
     - Round Robin with time quantum 4: `./cpu_scheduler processes.txt rr 4`

## Sample Output

Upon execution, the program will display the scheduling order of processes along with calculated metrics. For example:

```
Scheduling Algorithm: FCFS

PID  Arrival  Burst  Completion  Turnaround  Waiting
1    0        10     10          10          0
2    1        5      15          14          9
3    2        8      23          21          13

Average Turnaround Time: X.XX ms
Average Waiting Time: Y.YY ms
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

Special thanks to the resources and references that aided in the development of this simulator.
