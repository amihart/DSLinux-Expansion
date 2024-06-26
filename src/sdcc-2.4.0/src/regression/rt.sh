# test Script

USAGE="Usage: `basename $0` BASENAME"

if [ $# -lt 1 ] ; then
  echo "$USAGE"
  exit 1
fi

# compile
# ../../bin/sdcc -S -mpic14 $1.c
../../bin/sdcc -c -mpic14 -pp16f873 $1.c
#gpasm -c  -I /usr/local/share/gpasm/header $1.asm
#gpasm  $1.asm

# create the executable

gplink --map -c -s 16f877.lkr -o $1.o $1.o
./create_stc $1.cod $1.stc

./simulate $1.stc garbage.log
cat garbage.log
rm garbage.log
