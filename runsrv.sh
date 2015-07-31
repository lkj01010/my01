# top_path := $(shell pwd | awk -F ' ' {print$1})
echo "run dotasrv"
./dotasrv/dotasrv
