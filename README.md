
# Image Vectorization in C

![Language](https://img.shields.io/badge/Language-C-A8B9CC?logo=c)
![Compiler](https://img.shields.io/badge/Compiler-Clang-blue)
![Build](https://img.shields.io/badge/Build-Make-orange)
![Project](https://img.shields.io/badge/Project-Academic-green)

## Overview

This project implements a bitmap image vectorization
pipeline in C, converting monochrome PBM images into
EPS (Encapsulated PostScript) vector graphics.

The main objective is to extract image contours and
reduce their geometric complexity while preserving
the original shape using contour simplification
algorithms and Bézier curves.

This project was developed as part of the MAP401
course at Université Grenoble Alpes (2024–2025).

## Features

- Reading and manipulation of PBM images.
- Automatic detection and extraction of image contours.
- Management of multiple contours within a single image.
- Vector graphics export in EPS format.
- Polygonal simplification using the Douglas-Peucker algorithm.
- Quadratic Bézier curve approximation.
- Cubic Bézier curve approximation.
- Configurable simplification tolerance.
- Filled and outlined rendering modes.
- Geometric and algorithmic test programs.

## Processing Pipeline

```text
Input image (PBM)
        |
        v
Contour extraction
        |
        v
Geometric simplification
        |
        +-- Line segments (Douglas-Peucker)
        +-- Quadratic Bézier curves
        +-- Cubic Bézier curves
        |
        v
Vector image (EPS)
```

## Technologies

- C programming language
- Clang compiler
- GNU Make
- PBM image format
- EPS / PostScript
- Git and GitHub

## Getting Started

### Prerequisites

- Clang
- Make
- Git
- Linux, macOS or WSL environment

### Installation

Clone the repository:

```bash
git clone https://github.com/AkrBen/MAP401_BENDOUHA_CAILLE.git
cd MAP401_BENDOUHA_CAILLE
```

Compile the project:

```bash
make
```

Remove generated executables and object files:

```bash
make clean
```

## Usage

### Basic vectorization

Convert a PBM image into an EPS file:

```bash
./conversion_en_eps chat.pbm fill
```

Generate an outlined version:

```bash
./conversion_en_eps chat.pbm stroke
```

### Douglas-Peucker simplification

```bash
./test_simplification_douglas_pecker papillon2.pbm 2 fill
```

### Quadratic Bézier approximation

```bash
./test_bezier2 Asterix3.pbm 10 fill
```

### Cubic Bézier approximation

```bash
./test_bezier3 Asterix3.pbm 10 fill
```

The tolerance parameter controls the trade-off between
geometric accuracy and contour complexity.

Higher tolerance values generally produce simpler
vector representations.

Rendering modes:

- `fill`: filled contours.
- `stroke`: outlined contours.

## Experimental Results

The following results illustrate the reduction in
the number of contour segments using the
Douglas-Peucker algorithm.

| Image | Original | d = 1 | d = 2 | Reduction (d = 2) |
|---|---:|---:|---:|---:|
| Elephant | 115564 | 12884 | 3971 | 96.6% |
| Trees | 231284 | 26032 | 12428 | 94.6% |
| Horse | 32002 | 3104 | 1328 | 95.9% |
| Butterfly | 18212 | 1697 | 877 | 95.2% |

These results demonstrate a significant reduction
in geometric complexity.

Detailed results are available in
[resultats-tache6-2.txt](resultats-tache6-2.txt).

## Project Structure

```text
MAP401_BENDOUHA_CAILLE/
├── image.c / image.h
├── geom2d.c / geom2d.h
├── contour.c / contour.h
├── approximation_bezier.c / .h
├── exemple_sequence_point.c / .h
├── conversion_en_eps.c
├── test_*.c
├── resultats-tache*.txt
├── *.pbm
├── *.eps
└── Makefile
```

| Module | Description |
|---|---|
| `image` | Image reading and pixel manipulation |
| `geom2d` | Two-dimensional geometric operations |
| `contour` | Image contour extraction |
| `approximation_bezier` | Bézier curve approximation and simplification |
| `exemple_sequence_point` | Point sequences and data structures |
| `conversion_en_eps` | EPS vector graphics generation |
| `test_*.c` | Functional and geometric tests |

## Technical Skills

- Modular programming in C
- Pointers and dynamic memory allocation
- Linked lists and data structures
- Recursive algorithms
- Digital image processing
- Computational geometry
- Numerical approximation
- Compilation automation with Make
- Software testing and validation

## Authors

- Akram Bendouha
- Daniel Caille

## Academic Context

Université Grenoble Alpes (UGA)  
MAP401 — 2024–2025  
Academic project developed as a team of two.
