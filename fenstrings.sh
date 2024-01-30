if [ "$#" -eq 0 ]; then
    echo "Please pass number for fenstring."
    exit 1
fi

index="$1"
case "$index" in

1)
    fenstring="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
    ;;

# Pawncaptures
2) fenstring="rnbqkbnr/pppppppp/1P6/8/8/2p1p3/PPPPPPPP/RNBQKBNR"
    ;;

# Enpassant
3) fenstring="rnbqkbnr/pppppppp/8/6P1/8/8/PPPPPPPP/RNBQKBNR"
    ;;

# All pieces except Knight
4) fenstring="rnbqkbnr/pppppppp/8/2Q3P1/RBb1K3/8/PPPPPPPP/RNBQKBNR"
    ;;

# For Knights
5) fenstring="rnbqkbnr/pppppppp/8/N3N3/7n/8/PPPPPPPP/RNBQKBNR"
    ;;
esac

./chess "$fenstring"
