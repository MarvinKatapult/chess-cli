gcc -Wall src/main.c src/board.c src/square.c src/consoleio.c src/piece.c src/move.c -Iinclude -o chess
if [ "$1" = "-D" ]; 
then
    echo "Generating Doxygen Documentation"
    doxygen
fi
