# VideoProcessor Library

A thread-safe C++ library for simulating video processing operations.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [API Usage](#api-usage)
- [Output Example](#output-example)
- [Future Enhancements](#future-enhancements)
- [Author](#author)

## Overview

The `VideoProcessor` class provides a thread-safe API for simulating video processing tasks like resizing, cropping, and changing colors. For demonstration purposes, the library performs a simple sleep operation to simulate video frame processing.

## Features

- **Thread-Safe Video Processing**: Allows multiple threads to invoke the `processVideo()` function, but only one thread can operate on a particular video operation at any given time.
  
- **Progress Tracking**: Displays live progress updates during the processing of each video operation.
  
- **Cancellation Support**: An ongoing operation can be canceled without affecting other operations.

## Installation

The project comes with a Makefile for easy compilation. Simply run:

`make` (Add jproc+1 for faster executions for heavy makes)

This will produce an executable named VideoProcessor.

## Running the Program
After building the project, you can run it with:

`./VideoProcessor`

## API Usage
- **bool processVideo(Operation& o)**:
Initiates the processing of a video for the operation specified in the argument. If the operation is already in progress, this function returns false.

- **void cancel(Operation &o)**:
Cancels an ongoing operation. If the operation does not exist, no action is taken.

- **void cleanup(Operation &o)**:
Cleans up the resources or state related to an operation. It removes the operation from the internal tracking.

## Output Example
Here is a sample output when running the program:

`Started processing video for operation: 1`

`Started processing video for operation: 2`

`Operation 1 progress:   81/5000 ms`

`Cancelled operation: 1`

`Operation 2 progress: 4999/5000 ms`

`Finished processing video for operation: 2`

## Future Enhancements
- Add more video operations like resize, crop, change colors, etc.
- Implement a logging mechanism instead of standard output.

## Author
[prathams99 - Prathamesh Sahasrabuddhe]

