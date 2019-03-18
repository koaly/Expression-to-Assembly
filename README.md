# Assembly and Stack Generator
   Using for compile an expression in to assembly language form.

## Uses
### MIPS Assembly Generator (c -> asm)
```bash
    gcc expr_compiler.c
    ./a.out input(.txt) output(.asm)
```
### Stack Assembly Generator (c -> stack)
```bash
    gcc expr_stack_compiler.c
    ./a.out input(.txt) output(.stack)
```

## FYI
```python
    file name
    'a' is result from expression "12 * 3 / (2 + 7) - 5 % 2".
    'b' is result from expression "(20 - 10) * (30 / 4 + 40) % (5 + 6)".
    'c' is result from expression "11 + 22 * 33 % 12 - 44 / 3 - 7".

    file type
    '.txt'      is expression in inorder formula using as 'input'.
    '.asm'      is mips assembly compiled from expr_compiler.c
    '.stack'    is stack assembly compiled from expr_stack_compiler.c
    '.png'      is qtSPIM screen shot of that file name execution.
```

This lab is finished.
