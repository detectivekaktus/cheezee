# cheezee

![Cheezee preview showing a chessboard position.](https://github.com/detectivekaktus/cheezee/blob/master/imgs/preview1.png)

Cheezee (pronounced as cheese) is an ncurses chess client written for Linux. Play custom positions with FEN notation you can type in or pass as `--fen` argument to the client or play normal game from the standard position.

The FEN position you enter is formatted in the following way: **BOARD WHO_TO_MOVE CASTELING**. For instance you can use **rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq** but not **rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1**.

The client supports all legal moves in chess (including en-passant, casteling) and can understand whether the position is in checkmate or in stalemate.

All the moves played are logged to the right hand side of the board with the standard notation except that the black pieces are annotated with lowercase letters.

## Compilation
In order to compile the program, you need to have a C compiler (either GCC or clang) and the ncurses library installed on your system.

Invoke the following command to compile the executable:
```console
$ make
```

## Contribution
The codebase is a mess which was written with big delays and so it lacks some modern C, good logic and good skills of writing C code.
