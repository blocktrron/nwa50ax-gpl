imgaddr=0x83000000
fileaddr=0x8b000000

erase()
{
	start_addr=$1
	size="$(printf '0x%x\n' $2)"
	script=$3
	printf "nmbm nmbm0 erase $start_addr $size " >> $script
}

write()
{
	start_addr=$1
	size="$(printf '0x%x\n' $2)"
	script=$3
	printf "nmbm nmbm0 write $fileaddr $start_addr $size " >> $script
}
