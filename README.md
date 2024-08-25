# Brainfuck

My brainfuck interpreter.


## Description
```
there are cells [-1][0][0]
you can change value using + and -
you can navigate trough cells using < and > 
examples:
 +++ is    [2][0][0]
 +++>++ is [2][2][0]
 +2>+4+ is [3][6][0]
 +>+[-] is [0][0][0]
 +>+<[.>]  print 10
 >+9+.     print new line. "." is used for printing
 +[-,.[-]+] is like the cat application. "," is key input "." is print current cell
```
