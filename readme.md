# Laboratory exercise for TINF

'Theory of information' or TINF for short is a subject at
[FER](http://www.fer.unizg.hr/en).

## Goal

The exercise consists of three parts:

### 1. Static analysis of the information source

Four information souces are provided `i1`, `i2`, `i3` and `i4`. Each information
source can be individually compiled and run to get an information stream on
STDOUT.

Tasks:

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

Task:

1. What's the time complexity of assigning codes to a set of N symbols. If N = 256 what's the complexity of of compressing a file of M bytes?

#### 2.2 LZW method

It's necessary to implement the LZW compression algorythm.

The coder reads th einput file byte by btye and builds a dictionary.
Set the symbol limit to 65536. The coder's output hav to be 16-bit numbers
(unsigned short / uint16_t). The source code must be in the `lzwkoder.c` file.
A decoder also has to be implemented in the `lzwdekoder.c` file.

Example call:

```BASH
lwzkoder uncompressed.dat compressed.dat

lzwdekoder compressed.dat uncompressed.dat
```

Task:

1. What's the time complexity of compressing a file of N bytes using the LWZ algorythm?

#### 2.3 Comparison

Compare the two methods and compare your results with the first assignemnt and note and observations.

### 3. Data protection

In real data communication applications we don't want any errors to occure in
the data being transmitted therefore we implement data protection algorythms.

#### 3.1 Linear binary block code [16, 8, 5]

A matrix for generating linear binary block code is given

```
0001000100110011
0010001001011100
0100010011000011
1000100010101100
1100110111010111
1001101111101101
0011011110111011
0110111001111110
```

Convert it to it's standard form and determin the according parity matrix.

Implement a coder and decoder for the given [16, 8, 5] code. It should be
implemented in the `linbinkoder.c` file and `linbindekoder.c` file respectively.

Example call:

```BASH
linbinkoder unprotected.dat protected.dat

linbindekoder protected.dat unprotected.dat
```

#### 3.2 Binary simmetric channel

A program that simulates a binary simmetric channel needs to be implemented.

The program reads each bit from the input file and applies the given error
value to it. It should be implemented in the `binsimkanal.c` file.

Example call:

```BASH
# binsimkanal {input file} {error value} {output file}
binsimkanal input.dat 0.01 output.dat
```

#### 3.3 Data transfer using the binary simmetric channel

Compile and run the `prikazipiksele` program. It will display the intensity of
each pixel of a given black and white image.

for our example, run: `prikazipiksele pikseli 512 512`

Run the given image through the binary simmetric channel program while varing
the error factor e = 0.1, 0.2, 0.3 and display the image after it has been
transmittet through the channel. Then do the same process again but protect the
transmitted image first.

Task:

1. How much did the size vary? Did data protection prevent the data getting coruppted?
