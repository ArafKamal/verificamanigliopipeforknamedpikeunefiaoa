rm -f fifo_p1_to_p2 fifo_p2_to_p1 processo1 processo2 #
gcc processo1.c -o processo1 #
gcc processo2.c -o processo2 #
./processo2 & #
./processo1 #
wait #
rm -f fifo_p1_to_p2 fifo_p2_to_p1 #
