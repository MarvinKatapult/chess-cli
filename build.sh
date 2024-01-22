gcc -Wall -Wextra src/main.c src/board.c src/square.c src/consoleio.c src/piece.c src/move.c src/logic.c -Iinclude -o chess
if [ "$1" = "-D" ]; 
then
    echo "Generating Doxygen Documentation"
    doxygen
fi
