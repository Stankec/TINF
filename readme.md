# Laboratory exercise for TINF

'Theory of information' or TINF for short is a subject at
[FER](http://www.fer.unizg.hr/en).

## Goal

The exercise consists of three parts:

### 1. Static analysis of the information source

Four information souces are provided `i1`, `i2`, `i3` and `i4`. Each information
source can be individually compiled and run to get an information stream on
STDOUT.

Taska:

1. Draw the propability distribution of symbols and calculate thair entropy.
2. Draw the propability distribution of occurances of symbols 2, 4 and 8 together. Observe the difference betwene each source. Which source is most sutable for compression?
3. Compare your results with the [ZIP compression algorythm](http://www.wikiwand.com/en/Zip_(file_format)) and write your observations in a table.

### 2. Data compression

Data compression is the process of representing data in as little memory space
as possible.

#### 2.1 Huffman's method

The Huffman compression method needs to be implemented.

The coder should open the input fily as binary and map the occurance of each
possible byte and write it to a text file.

The coder uses the generated occurance table and uses it to copress the data.

The algorythm should be implemented in the `huffkoder.c` file.

A decoder alos has to be implemented in the `huffdekoder.c` file.

Expected call:

```BASH
ls -alGh
# Returns uncompressed.dat

huffkoder uncompressed.dat table.txt compressed.dat

ls -alGh
# Returns uncompressed.dat, compressed.dat and table.txt

huffdekoder table.txt compressed.dat re_uncompressed.dat

ls -alGh
# Returns uncompressed.dat, compressed.dat, table.txt and re_uncompressed.dat
```

