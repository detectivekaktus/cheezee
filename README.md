# cheezee
Cheezee (pronounced as cheese) is an ncurses chess client written for Linux. Play custom positions with FEN notation you can type in or pass as `--fen` argument to the client or play normal game from the standard position.

The client supports all legal moves in chess (including en-passant, casteling) and can understand whether the position is in checkmate or in stalemate.

All the moves played are logged to the right hand side of the board with the standard notation except that the black pieces are annotated with lowercase letters.

## Compilation
In order to compile the program, you need to have a C compiler (either GCC or clang) and the ncurses library installed on your system.

Invoke the following command to compile the executable:
```console
$ make
```

## Contribution
The codebase is a mess which was written with big delays and so it lack some feature, good logic and good skills of writing C code.
