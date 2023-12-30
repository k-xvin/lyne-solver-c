https://www.kxvin.com/tech/lyne-puzzle-solver/
```
Example Input Board:

A a 2 a b
C B 2 2 2
A 3 c 2 b
c C c c B
```

```
Sample Solutions:

Solution 1
A-a-2-a.b
.../|.|/|
C.B.2-2-2
.\./.\./|
A-3-c-2.b
./.\..|.|
c-C.c-c.B

Solution 2
A-a-2-a.b
.../|.|/|
C.B.2-2-2
.\./.\./|
A-3-c-2.b
./.\..|.|
c-C.c-c.B

Solution 3
A-a-2-a.b
.../|.|/|
C.B.2-2-2
.\./.\./|
A-3-c.2-b
./.\.\.\.
c-C.c-c.B

...

Solution 94
A-a-2-a.b
....|\|/|
C.B-2.2-2
.\./.\./|
A-3-c.2-b
./.\.\.\.
c-C.c-c.B

Total Solutions: 94
Total Moves Explored: 31507
0.013583
```

adjustments from v1
* checks for board solve only when we reach an end terminal, rather than every move
