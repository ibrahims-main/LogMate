# LogMate

A simple, flexible C++ logging library to log messages at various levels (DEBUG, INFO, WARNING, ERROR, CRITICAL) with support for log rotation, custom formats, and error handling.

## Features

- Multiple log levels: DEBUG, INFO, WARNING, ERROR and CRITICAL.
- Automatic log rotation based on file size.
- Customizable log format with timestamps.
- Thread-safe logging.
- Custom error handling for logging failures.

## Installation

### Prerequisites

Make sure you have the following installed on your system:
- A C++ compiler (e.g., `g++` or `clang++`)
- CMake (optional, if you want to use CMake for building)
- A text editor or IDE (e.g., Visual Studio Code, Code::Blocks, or any other IDE)

### Clone the repository

To use this library, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/ibrahims-main/LogMate.git
```

## Build Instructions

- Copy the Files: Include the `logmate.h` and `logmate.cpp` files in your project.
- Make sure to add your log output file, e.g., `app.log`, or it will be created automatically when the program runs.

## Compiling with LogMate

You can compile your code with the logging library like this:

```bash
g++ -o my_program main.cpp src/logmate.cpp -std=c++11 -pthread
```

## Usage

### Example Code

Here’s a simple example of how to use the `LogMate` library in your project:

```c++
#include <iostream>
#include "logmate.h"

int main() {
    // Initialize logger
    LogMate logger("app.log", LogLevel::DEBUG);  // Logging to "app.log" with DEBUG level

    // Log messages at different levels
    logger.debug("This is a debug message");
    logger.info("Informational message");
    logger.warning("This is a warning!");
    logger.error("Error encountered in processing");
    logger.critical("Critical issue occurred!");

    // Change the log level and log format
    logger.setLogLevel(LogLevel::WARNING);  // Now only WARNING and above will be logged
    logger.setFormat("[%TIME%] [%LEVEL%] - %MESSAGE%");

    // Simulate logging with error handler
    logger.setErrorHandler([](const std::string& errorMessage) {
        std::cerr << "Logging error: " << errorMessage << std::endl;
    });

    logger.info("This message won't be logged due to log level");
    logger.critical("This is a critical log after format and level change!");

    // Log rotation example
    logger.enableLogRotation(1024 * 10);  // Rotate when log file exceeds 10KB

    return 0;
}
```

## Example Output in `app.log`

If you run the above code, `app.log` will contain something like this:

```css
[2024-10-19 10:30:00] [DEBUG] - This is a debug message
[2024-10-19 10:30:01] [INFO] - Informational message
[2024-10-19 10:30:02] [WARNING] - This is a warning!
[2024-10-19 10:30:03] [ERROR] - Error encountered in processing
[2024-10-19 10:30:04] [CRITICAL] - Critical issue occurred!
[2024-10-19 10:30:05] [CRITICAL] - This is a critical log after format and level change!
```

## Customizing the Log

- *Log Level*: You can set the minimum log level using `logger.setLogLevel(LogLevel::LEVEL)`. For example, `LogLevel::WARNING` will only log warnings, errors, and critical messages.

- *Log Format*: Use `logger.setFormat` to customize the format of your logs with placeholders like `%TIME%`, `%LEVEL%`, and `%MESSAGE%.`

- *Log Rotation*: Automatically rotate log files once they reach a specified size using `logger.enableLogRotation(sizeInBytes)`.

## License

This project is licensed under the [MIT License](LICENSE) - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

Happy logging with LogMate!