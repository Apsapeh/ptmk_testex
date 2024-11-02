for i in $(seq 1 10); do
    printf "[%d]: " "$i"
    xmake run ptmk_testex 5 -s
done