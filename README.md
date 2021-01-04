Compiler written in cpp

Sample Output (See raw for neat view)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
OPENING: CS4100FinalProjGOODMinimumFA20.txt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Line: 1: unit LastTest;
Line: 2: { Final compiler project test program NO ERRORS INTENDED!  Notify A. Brouillette if errors are found. }
Line: 3:
Line: 4: VAR i,j: integer;
Line: 5: var product, sum: integer;
Line: 6:
Line: 7: begin
Line: 8: for i := 1 to 5 do
Line: 9: { Find summation 5 times }
Line: 10:   begin
Line: 11:   writeln("SUMMATIONS 1 THROUGH 5");
Line: 12:   sum := 0;
Line: 13:   for j := 1 to i do
Line: 14:     begin
Line: 15:     sum := sum + j
Line: 16:     end;
Line: 17:   writeln(sum)
Line: 18:   end;
Line: 19:
Line: 20: { Find 6 factorial }
Line: 21:   product := 1;
Line: 22:   i := 2;
Line: 23:   while i <= 6 do
Line: 24:     begin
Line: 25:     product := product * i;
Line: 26:     writeln("Product now is:");
Line: 27:     writeln(product);
Line: 28:     i := i + 1
Line: 29:     end;
Line: 30:   writeln("6! is:");
Line: 31:   writeln(product);
Line: 32:
Line: 33: { count powers of 2 needed to get over 1000 }
Line: 34: j := 0;
Line: 35: product := 1;
Line: 36: while product <= 1000 do
Line: 37:   begin
Line: 38:   product := product * 2;
Line: 39:   j := j + 1;
Line: 40:   writeln(j);
Line: 41:   if product < 500 then
Line: 42:     writeln("Product < 500")
Line: 43:   else
Line: 44:     writeln("Product >= 500")
Line: 45:   end;
Line: 46: writeln("Iterations = ");
Line: 47: writeln(j);
Line: 48: writeln("Value of product:");
Line: 49: writeln(product);
Line: 50: writeln("Made it to the end.")
Line: 51: end.
Line: 52:

---------------------------------------------------------------------------------------------------------------------------------
Symbol Table
Index & Lexeme                          Kind                                    Type                                    Value
---------------------------------------------------------------------------------------------------------------------------------
[0] NULL                                NULL                                    INT                                     0
[1] PLUS1INDEX                          CONST                                   INT                                     1
[2] MINUS1INDEX                         CONST                                   INT                                     -1
[3] LastTest                            VAR                                     INT                                     0
[4] i                                   DECVAR                                  INT                                     0
[5] j                                   DECVAR                                  INT                                     0
[6] product                             DECVAR                                  INT                                     0
[7] sum                                 DECVAR                                  INT                                     0
[8] 1                                   CONST                                   INT                                     1
[9] 5                                   CONST                                   INT                                     5
[10] TEMP0                              INT                                     INT                                     0
[11] SUMMATIONS 1 THROUGH 5             CONST                                   STRING                                  SUMMATIONS 1 THROUGH 5
[12] 0                                  CONST                                   INT                                     0
[13] 1                                  CONST                                   INT                                     1
[14] TEMP1                              INT                                     INT                                     0
[15] TEMP2                              INT                                     INT                                     0
[16] 1                                  CONST                                   INT                                     1
[17] 2                                  CONST                                   INT                                     2
[18] 6                                  CONST                                   INT                                     6
[19] TEMP3                              INT                                     INT                                     0
[20] TEMP4                              INT                                     INT                                     0
[21] Product now is:                    CONST                                   STRING                                  Product now is:
[22] 1                                  CONST                                   INT                                     1
[23] TEMP5                              INT                                     INT                                     0
[24] 6! is:                             CONST                                   STRING                                  6! is:
[25] 0                                  CONST                                   INT                                     0
[26] 1                                  CONST                                   INT                                     1
[27] 1000                               CONST                                   INT                                     1000
[28] TEMP6                              INT                                     INT                                     0
[29] 2                                  CONST                                   INT                                     2
[30] TEMP7                              INT                                     INT                                     0
[31] 1                                  CONST                                   INT                                     1
[32] TEMP8                              INT                                     INT                                     0
[33] 500                                CONST                                   INT                                     500
[34] TEMP9                              INT                                     INT                                     0
[35] Product < 500                      CONST                                   STRING                                  Product < 500
[36] Product >= 500                     CONST                                   STRING                                  Product >= 500
[37] Iterations =                       CONST                                   STRING                                  Iterations =
[38] Value of product:                  CONST                                   STRING                                  Value of product:
[39] Made it to the end.                CONST                                   STRING                                  Made it to the end.

---------------------------------------------------------------------------------------------------------------------------------
Quad Table
OPCODE                                  OP1                                     OP2                                     OP3
---------------------------------------------------------------------------------------------------------------------------------
MOV_                                    [8]1                                    [0]NULL                                 [4]i
SUB_                                    [4]i                                    [9]5                                    [10]TEMP0
BP__                                    [10]TEMP0                               [0]NULL                                 [15]TEMP2
PRNT                                    [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5
MOV_                                    [12]0                                   [0]NULL                                 [7]sum
MOV_                                    [8]1                                    [0]NULL                                 [5]j
SUB_                                    [5]j                                    [4]i                                    [14]TEMP1
BP__                                    [14]TEMP1                               [0]NULL                                 [12]0
ADD_                                    [7]sum                                  [5]j                                    [15]TEMP2
MOV_                                    [15]TEMP2                               [0]NULL                                 [7]sum
ADD_                                    [5]j                                    [1]PLUS1INDEX                           [5]j
BR__                                    [0]NULL                                 [0]NULL                                 [6]product
PRNT                                    [0]NULL                                 [0]NULL                                 [7]sum
ADD_                                    [4]i                                    [1]PLUS1INDEX                           [4]i
BR__                                    [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
MOV_                                    [8]1                                    [0]NULL                                 [6]product
MOV_                                    [17]2                                   [0]NULL                                 [4]i
SUB_                                    [4]i                                    [18]6                                   [19]TEMP3
BP__                                    [19]TEMP3                               [0]NULL                                 [26]1
MUL_                                    [6]product                              [4]i                                    [20]TEMP4
MOV_                                    [20]TEMP4                               [0]NULL                                 [6]product
PRNT                                    [0]NULL                                 [0]NULL                                 [21]Product now is:
PRNT                                    [0]NULL                                 [0]NULL                                 [6]product
ADD_                                    [4]i                                    [8]1                                    [23]TEMP5
MOV_                                    [23]TEMP5                               [0]NULL                                 [4]i
BR__                                    [0]NULL                                 [0]NULL                                 [17]2
PRNT                                    [0]NULL                                 [0]NULL                                 [24]6! is:
PRNT                                    [0]NULL                                 [0]NULL                                 [6]product
MOV_                                    [12]0                                   [0]NULL                                 [5]j
MOV_                                    [8]1                                    [0]NULL                                 [6]product
SUB_                                    [6]product                              [27]1000                                [28]TEMP6
BP__                                    [28]TEMP6                               [0]NULL                                 43
MUL_                                    [6]product                              [17]2                                   [30]TEMP7
MOV_                                    [30]TEMP7                               [0]NULL                                 [6]product
ADD_                                    [5]j                                    [8]1                                    [32]TEMP8
MOV_                                    [32]TEMP8                               [0]NULL                                 [5]j
PRNT                                    [0]NULL                                 [0]NULL                                 [5]j
SUB_                                    [6]product                              [33]500                                 [34]TEMP9
BNN_                                    [34]TEMP9                               [0]NULL                                 41
PRNT                                    [0]NULL                                 [0]NULL                                 [35]Product < 500
BR__                                    [0]NULL                                 [0]NULL                                 42
PRNT                                    [0]NULL                                 [0]NULL                                 [36]Product >= 500
BR__                                    [0]NULL                                 [0]NULL                                 [30]TEMP7
PRNT                                    [0]NULL                                 [0]NULL                                 [37]Iterations =
PRNT                                    [0]NULL                                 [0]NULL                                 [5]j
PRNT                                    [0]NULL                                 [0]NULL                                 [38]Value of product:
PRNT                                    [0]NULL                                 [0]NULL                                 [6]product
PRNT                                    [0]NULL                                 [0]NULL                                 [39]Made it to the end.

---------------------------------------------------------------------------------------------------------------------------------
Code Generation
PC & OPCODE                             OP1                                     OP2                                     OP3
---------------------------------------------------------------------------------------------------------------------------------
PC 0: MOV_                              [8]1                                    [0]NULL                                 [4]i
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 3: PRNT                              [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5

SUMMATIONS 1 THROUGH 5

PC 4: MOV_                              [12]0                                   [0]NULL                                 [7]sum
PC 5: MOV_                              [8]1                                    [0]NULL                                 [5]j
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 12: PRNT                             [0]NULL                                 [0]NULL                                 [7]sum

1

PC 13: ADD_                             [4]i                                    [1]PLUS1INDEX                           [4]i
PC 14: BR__                             [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 3: PRNT                              [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5

SUMMATIONS 1 THROUGH 5

PC 4: MOV_                              [12]0                                   [0]NULL                                 [7]sum
PC 5: MOV_                              [8]1                                    [0]NULL                                 [5]j
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 12: PRNT                             [0]NULL                                 [0]NULL                                 [7]sum

3

PC 13: ADD_                             [4]i                                    [1]PLUS1INDEX                           [4]i
PC 14: BR__                             [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 3: PRNT                              [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5

SUMMATIONS 1 THROUGH 5

PC 4: MOV_                              [12]0                                   [0]NULL                                 [7]sum
PC 5: MOV_                              [8]1                                    [0]NULL                                 [5]j
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 12: PRNT                             [0]NULL                                 [0]NULL                                 [7]sum

6

PC 13: ADD_                             [4]i                                    [1]PLUS1INDEX                           [4]i
PC 14: BR__                             [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 3: PRNT                              [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5

SUMMATIONS 1 THROUGH 5

PC 4: MOV_                              [12]0                                   [0]NULL                                 [7]sum
PC 5: MOV_                              [8]1                                    [0]NULL                                 [5]j
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 12: PRNT                             [0]NULL                                 [0]NULL                                 [7]sum

10

PC 13: ADD_                             [4]i                                    [1]PLUS1INDEX                           [4]i
PC 14: BR__                             [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 3: PRNT                              [0]NULL                                 [0]NULL                                 [11]SUMMATIONS 1 THROUGH 5

SUMMATIONS 1 THROUGH 5

PC 4: MOV_                              [12]0                                   [0]NULL                                 [7]sum
PC 5: MOV_                              [8]1                                    [0]NULL                                 [5]j
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 8: ADD_                              [7]sum                                  [5]j                                    [15]TEMP2
PC 9: MOV_                              [15]TEMP2                               [0]NULL                                 [7]sum
PC 10: ADD_                             [5]j                                    [1]PLUS1INDEX                           [5]j
PC 11: BR__                             [0]NULL                                 [0]NULL                                 [6]product
PC 6: SUB_                              [5]j                                    [4]i                                    [14]TEMP1
PC 7: BP__                              [14]TEMP1                               [0]NULL                                 [12]0
PC 12: PRNT                             [0]NULL                                 [0]NULL                                 [7]sum

15

PC 13: ADD_                             [4]i                                    [1]PLUS1INDEX                           [4]i
PC 14: BR__                             [0]NULL                                 [0]NULL                                 [1]PLUS1INDEX
PC 1: SUB_                              [4]i                                    [9]5                                    [10]TEMP0
PC 2: BP__                              [10]TEMP0                               [0]NULL                                 [15]TEMP2
PC 15: MOV_                             [8]1                                    [0]NULL                                 [6]product
PC 16: MOV_                             [17]2                                   [0]NULL                                 [4]i
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 19: MUL_                             [6]product                              [4]i                                    [20]TEMP4
PC 20: MOV_                             [20]TEMP4                               [0]NULL                                 [6]product
PC 21: PRNT                             [0]NULL                                 [0]NULL                                 [21]Product now is:

Product now is:

PC 22: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

2

PC 23: ADD_                             [4]i                                    [8]1                                    [23]TEMP5
PC 24: MOV_                             [23]TEMP5                               [0]NULL                                 [4]i
PC 25: BR__                             [0]NULL                                 [0]NULL                                 [17]2
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 19: MUL_                             [6]product                              [4]i                                    [20]TEMP4
PC 20: MOV_                             [20]TEMP4                               [0]NULL                                 [6]product
PC 21: PRNT                             [0]NULL                                 [0]NULL                                 [21]Product now is:

Product now is:

PC 22: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

6

PC 23: ADD_                             [4]i                                    [8]1                                    [23]TEMP5
PC 24: MOV_                             [23]TEMP5                               [0]NULL                                 [4]i
PC 25: BR__                             [0]NULL                                 [0]NULL                                 [17]2
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 19: MUL_                             [6]product                              [4]i                                    [20]TEMP4
PC 20: MOV_                             [20]TEMP4                               [0]NULL                                 [6]product
PC 21: PRNT                             [0]NULL                                 [0]NULL                                 [21]Product now is:

Product now is:

PC 22: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

24

PC 23: ADD_                             [4]i                                    [8]1                                    [23]TEMP5
PC 24: MOV_                             [23]TEMP5                               [0]NULL                                 [4]i
PC 25: BR__                             [0]NULL                                 [0]NULL                                 [17]2
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 19: MUL_                             [6]product                              [4]i                                    [20]TEMP4
PC 20: MOV_                             [20]TEMP4                               [0]NULL                                 [6]product
PC 21: PRNT                             [0]NULL                                 [0]NULL                                 [21]Product now is:

Product now is:

PC 22: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

120

PC 23: ADD_                             [4]i                                    [8]1                                    [23]TEMP5
PC 24: MOV_                             [23]TEMP5                               [0]NULL                                 [4]i
PC 25: BR__                             [0]NULL                                 [0]NULL                                 [17]2
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 19: MUL_                             [6]product                              [4]i                                    [20]TEMP4
PC 20: MOV_                             [20]TEMP4                               [0]NULL                                 [6]product
PC 21: PRNT                             [0]NULL                                 [0]NULL                                 [21]Product now is:

Product now is:

PC 22: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

720

PC 23: ADD_                             [4]i                                    [8]1                                    [23]TEMP5
PC 24: MOV_                             [23]TEMP5                               [0]NULL                                 [4]i
PC 25: BR__                             [0]NULL                                 [0]NULL                                 [17]2
PC 17: SUB_                             [4]i                                    [18]6                                   [19]TEMP3
PC 18: BP__                             [19]TEMP3                               [0]NULL                                 [26]1
PC 26: PRNT                             [0]NULL                                 [0]NULL                                 [24]6! is:

6! is:

PC 27: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

720

PC 28: MOV_                             [12]0                                   [0]NULL                                 [5]j
PC 29: MOV_                             [8]1                                    [0]NULL                                 [6]product
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

1

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

2

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

3

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

4

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

5

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

6

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

7

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

8

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 39: PRNT                             [0]NULL                                 [0]NULL                                 [35]Product < 500

Product < 500

PC 40: BR__, NULL, NULL, 42
PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

9

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 41: PRNT                             [0]NULL                                 [0]NULL                                 [36]Product >= 500

Product >= 500

PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 32: MUL_                             [6]product                              [17]2                                   [30]TEMP7
PC 33: MOV_                             [30]TEMP7                               [0]NULL                                 [6]product
PC 34: ADD_                             [5]j                                    [8]1                                    [32]TEMP8
PC 35: MOV_                             [32]TEMP8                               [0]NULL                                 [5]j
PC 36: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

10

PC 37: SUB_                             [6]product                              [33]500                                 [34]TEMP9
PC 38: BNN_, TEMP9, NULL, 41
PC 41: PRNT                             [0]NULL                                 [0]NULL                                 [36]Product >= 500

Product >= 500

PC 42: BR__                             [0]NULL                                 [0]NULL                                 [30]TEMP7
PC 30: SUB_                             [6]product                              [27]1000                                [28]TEMP6
PC 31: BP__, TEMP6, NULL, 43
PC 43: PRNT                             [0]NULL                                 [0]NULL                                 [37]Iterations =

Iterations =

PC 44: PRNT                             [0]NULL                                 [0]NULL                                 [5]j

10

PC 45: PRNT                             [0]NULL                                 [0]NULL                                 [38]Value of product:

Value of product:

PC 46: PRNT                             [0]NULL                                 [0]NULL                                 [6]product

1024

PC 47: PRNT                             [0]NULL                                 [0]NULL                                 [39]Made it to the end.

Made it to the end.

---------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------
Symbol Table
Index & Lexeme                          Kind                                    Type                                    Value
---------------------------------------------------------------------------------------------------------------------------------
[0] NULL                                NULL                                    INT                                     0
[1] PLUS1INDEX                          CONST                                   INT                                     1
[2] MINUS1INDEX                         CONST                                   INT                                     -1
[3] LastTest                            VAR                                     INT                                     0
[4] i                                   DECVAR                                  INT                                     7
[5] j                                   DECVAR                                  INT                                     10
[6] product                             DECVAR                                  INT                                     1024
[7] sum                                 DECVAR                                  INT                                     15
[8] 1                                   CONST                                   INT                                     1
[9] 5                                   CONST                                   INT                                     5
[10] TEMP0                              INT                                     INT                                     1
[11] SUMMATIONS 1 THROUGH 5             CONST                                   STRING                                  SUMMATIONS 1 THROUGH 5
[12] 0                                  CONST                                   INT                                     0
[13] 1                                  CONST                                   INT                                     1
[14] TEMP1                              INT                                     INT                                     1
[15] TEMP2                              INT                                     INT                                     15
[16] 1                                  CONST                                   INT                                     1
[17] 2                                  CONST                                   INT                                     2
[18] 6                                  CONST                                   INT                                     6
[19] TEMP3                              INT                                     INT                                     1
[20] TEMP4                              INT                                     INT                                     720
[21] Product now is:                    CONST                                   STRING                                  Product now is:
[22] 1                                  CONST                                   INT                                     1
[23] TEMP5                              INT                                     INT                                     7
[24] 6! is:                             CONST                                   STRING                                  6! is:
[25] 0                                  CONST                                   INT                                     0
[26] 1                                  CONST                                   INT                                     1
[27] 1000                               CONST                                   INT                                     1000
[28] TEMP6                              INT                                     INT                                     24
[29] 2                                  CONST                                   INT                                     2
[30] TEMP7                              INT                                     INT                                     1024
[31] 1                                  CONST                                   INT                                     1
[32] TEMP8                              INT                                     INT                                     10
[33] 500                                CONST                                   INT                                     500
[34] TEMP9                              INT                                     INT                                     524
[35] Product < 500                      CONST                                   STRING                                  Product < 500
[36] Product >= 500                     CONST                                   STRING                                  Product >= 500
[37] Iterations =                       CONST                                   STRING                                  Iterations =
[38] Value of product:                  CONST                                   STRING                                  Value of product:
[39] Made it to the end.                CONST                                   STRING                                  Made it to the end.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CLOSING: CS4100FinalProjGOODMinimumFA20.txt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

C:\Users\McCracken\Desktop\Code\Cpp\Compiler\Project1\Debug\Compiler.exe (process 16500) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
