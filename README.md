# Word Transformation Graph
## Project Overview
This project implements a solution to the word transformation problem, where the goal is to transform one word into another through a series of valid transformations. A valid transformation is a one-character substitution, one-character insertion, or one-character deletion. The application reads a list of valid words from a text file and determines if one word can be transformed into another, then prints the series of transformations needed.
## Features
- **Word Checking:** Verify if a direct transformation between two words is possible through substitution, insertion, or deletion.
- **Path Finding:** Determine the shortest sequence of valid transformations from a start word to an end word.
- **Transformation Output:** For each valid transformation, the specific change is detailed (change, insert, delete) alongside the position in the word.
## Prerequisites
To compile and run this project, you need:
- A C++ compiler that supports C++11 or later (GCC, Clang, MSVC).
- Access to a command line interface for running the compiled application.
Setup
1. **Clone the Repository**
   ```
   git clone https://github.com/yourusername/wordgraph.git
   cd wordgraph
   ```
2. **Compiling the Project**
   Navigate to the project directory where `main.cpp` is located and compile using a C++ compiler:
   ```
   g++ -o wordgraph main.cpp
   ```
3. **Prepare the Word List**
   Ensure you have a file named `words.txt` in the same directory as your executable. This file should contain a list of valid words, one per line.
## Usage
Run the program from the command line:
```
./wordgraph
```
Follow the prompts in the command line interface. Enter two words when prompted, and the program will output the transformation sequence or an error message if no transformation is possible.

### Example
Input:
```
enter the words: can pale
```
Output:
```
can
man (change c at position 1 to m)
mane (insert e after position 3)
male (change n at position 3 to l)
pale (change m at position 1 to l)
```
To exit the program, use `*` as the first word.
## Contributing
Contributions are welcome! For major changes, please open an issue first to discuss what you would like to change.
## License
[MIT](https://choosealicense.com/licenses/mit/)
