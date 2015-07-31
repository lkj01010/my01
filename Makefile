all: src dotasrv

src:
	$(MAKE) --directory=$@ all

dotasrv:
	$(MAKE) --directory=$@ all