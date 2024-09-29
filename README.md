# Line Visibility Problem

## Overview

The Line Visibility Problem involves determining which line segments are visible from a given point that is not part of any of the segments. This project aims to implement an efficient algorithm in C++ that identifies and colors the visible line segments while considering potential obstructions by other segments.

## Problem Description

Given:
- **N line segments** defined by their endpoints.
- **1 point** (not part of any segment).

### Constraints
- Line segments do not intersect or share endpoints.
- A line segment is considered visible if at least one endpoint is visible from the dot.
- A longer segment may obstruct the visibility of a shorter segment.

### Goal
The objective is to identify and color the segments that are visible from the dot based on their orientation and distance.

## Algorithm

The algorithm uses the following approach:

1. **Sort the Segments**: Sort the segments based on their orientation relative to the dot.
2. **Active Segments Management**: Utilize a Binary Search Tree (BST) to manage active segments during the visibility determination process.
3. **Visibility Check**: Start from the closest segments to the dot, ensuring that these are visible. Then check for obstructions from other segments.

## Current Status

This project is still a work in progress. While the core algorithm has been implemented and is functional, additional features and optimizations are yet to be completed.


### Prerequisites

- Ensure you have a C++ compiler installed
- Have Embarcadero RAD studio installed
- Clone the repository:

```bash
    git clone https://github.com/AldinKajmovic/Line-visibility.git
    cd Line-visibility
```
## Running the Project in RAD Studio

To run the project using RAD Studio, follow these steps:

1. Open **RAD Studio**.
2. Load the project by navigating to `File > Open Project` and selecting your project file.
3. Generate random line segments by using the provided functionality in the application.
4. Add a point (dot) that is not part of any segments.
5. Click the **Run** button to execute the program.

The application will then display the visible segments based on the provided point.
