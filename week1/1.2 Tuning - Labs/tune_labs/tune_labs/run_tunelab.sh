#!/bin/bash

CC=${1-"gcc"}
END=15
NPARTS=( 2000 3000 4000 5000 7500 10000 20000 40000 80000 200000 400000 800000 1200000 1600000 3000000 );
LOOPS=( 1000000 500000 300000 100000 100000 10000 10000 10000 10000 10000 1000 1000 1000 1000 1000 );
# NPARTS="2000 3000 4000 5000 7500 10000 20000 40000 80000 200000 400000 800000 1200000 1600000 3000000"
# LOOPS=10000
LOGEXT=$CC.dat

/bin/rm -f aos.$LOGEXT soa.$LOGEXT
# for particles in $NPARTS
# do
#     ./aos.${CC} $LOOPS $particles | grep -v CPU >> aos.$LOGEXT
#     ./soa.${CC} $LOOPS $particles | grep -v CPU >> soa.$LOGEXT
# done

for (( i=0; i<$END; i++ ));
do
    ./aos.${CC} ${LOOPS[$i]} ${NPARTS[$i]} | grep -v CPU >> aos.$LOGEXT
    ./soa.${CC} ${LOOPS[$i]} ${NPARTS[$i]} | grep -v CPU >> soa.$LOGEXT
done

# time to say 'Good bye' ;-)
#
exit 0

