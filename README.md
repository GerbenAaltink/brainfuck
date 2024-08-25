# Brainfuck

My brainfuck interpreter. I had a lot of fun writing this. To often check if my interpreter was wrong or the brainfuck source i used other brainfuck interpreters to test. I found out that there are many (bad) different implementations. Many brainfuck interpreters do not support recursion. Mine does.

## Extra
Syntax like +3 to increment 3 times is not default brainfuck syntax. I implemented it myself to prevent many +'s and -'s.
Also I added support for '!'. This will dump the stack in this format: [0][0][0][0][0]. This will help you debugging.

## Description
```
This is an interpreter for an esoteric programming language. An esoteric programming language is designed to test the boundaries of computer programming language design. This langauge doesn't have any functions beside making the programmer crazy, hence its name. 

there are a bunch of cells horizontally aligned as displayed here: [0][0][0]
you start in the first cell.
you can change value of a cell using + and -.
you can navigate trough cells using < and >.
you can loop code by putting it between []. But: code between [] will only be executed if current cell is non-zero. +[-] is executed since the value is 1. [-] is not executed since there's no value yet.

examples:
 +++ is    [3][0][0]
 +++>++ is [3][2][0]
 +2>+4+ is [2][5][0]
 +>+[-] is [1][0][0] [-] keeps decreasing the current cell until it's zero and that ends the loop.
 +>+<[.>]  print 11, the dot prints the current cell.
 >+9+.     print new line.
 +[-,.[-]+] is like the cat application. comma is asking user for key input.

what is the point? With this information you should be able to do calculations with this language.
See tests.bf
```
