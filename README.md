# KrestikiLanguage

Krestiki Language is a programming language for everyone! (or not)

## Quick start

### Windows
```bat
build.bat
krestiki.exe hello_world.krst --target windows --compile
hello_world.exe
```
To get more information about available options run `krestiki.exe help`


### Linux
```bash
./build.sh
./krestiki hello_world.krst --target linux --compile
./hello_world
```
To get more information about available options run `krestiki help`


### MacOS
```bash
./build.sh
./krestiki hello_world.krst --target macos --compile
./hello_world
```
To get more information about available options run `krestiki help`


## Docs

### Arithmetic operations
| Krestiki Lang | C++ | Example | Description |
|---------------|-----|---------|-------------|
| A | + | 5 A 2 (=7) | - |
| B | - | 5 A 2 (=3) | - |
| C | * | 5 A 2 (=10) | - |
| D | / | 5 A 2 (=2) | - |
| E | % | 5 A 3 (=1) | - |

### Types
- `I` - int64
- `S` - string

### Variables
#### Define a variable:
```
V <var_name> <type> <value>

Example:
V int_variable I 0

String value:
V string S |some string value with @ny sy&mbols ! 23*#( _#$| 
```

#### Update variable value:
```
U <var_name> <new_value_operation>; // semicolon required

Example:
U int_variable 5 A 4;
```
You can update a value only by using some arithmetic operation or function call

### Conditions
There are only 4 types of conditions you can use:
- variable value bigger than zero
- variable value less than zero
- variable value equals to zero
- variable value not equals to zero

```
Examples:
V a I 0

~>a
    // do someting if a > 0
~

~<a
    // do someting if a < 0
~

~=a
    // do someting if a == 0
~

~!a
    // do someting if a != 0
~

```

### Stdin & Stdout (Read & Write)
```
R <var_name> // read from stdin to variable
W <var_name> // write value of variable to stdout
```

### Function Definition
```
F <func_name> <type>(<arg_name> <arg_type> [, <arg2_name> <arg2_type> [, ...]]) <
    // some code
    T <result> // throw (return) value
>

Example:
F sum I(a I, b I) <
    V res I 0
    U res a A b;
    T res
>
```

### Function Call
```
@<func_name>(<args>);

Example:
@sum(45, 60);

V a I 4
V b I 8
V result I 0
@sum(a, b);
```

### Label & Goto
```
:<label_name>

...

G <label_name>

Example:

V a I 0
:input
R a
~<a
W |Value should be greater than zero|
G input
~
V res I 0
U res a C a
W res
```

### Arrays
```
M <array_name> <type> <size>

Example:
M my_array I 40
```

### Built-in constants
| Constant | Value | Description |
|----------|-------|-------------|
| _X1 | \n | newline |

### Built-in functions
| Function Name | Arguments | Description |
|---------------|-----------|-------------|
| _X2 | string S, index I | Returns string which contains symbol from `string` at position `index` |
| _X3 | arr I_Array/S_Array, index I, value I/S | Set `array` value at `index` to `value` |
| _X4 | arr I_Array/S_Array, index I, result I/S | Set `result` to `array` value at `index` |

