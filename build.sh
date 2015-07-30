# top_path := $(shell pwd | awk -F ' ' {print$1})
top_path :=$(shell pwd)
echo top_path
