
include shotgun/config.mk

all: vm exts

vm:
	cd shotgun; $(MAKE) rubinius

exts: vm
	./shotgun/rubinius compile lib/ext/syck

install:
	cd shotgun; $(MAKE) install
	mkdir -p $(RBAPATH)
	mkdir -p $(CODEPATH)
	cp runtime/*.rba runtime/*.rbc $(RBAPATH)/
	mkdir -p $(CODEPATH)/bin
	cp -r lib/* $(CODEPATH)/
	for rb in $(CODEPATH)/*.rb ; do $(BINPATH)/rbx compile $$rb; done	
	for rb in $(CODEPATH)/**/*.rb ; do $(BINPATH)/rbx compile $$rb; done	

clean:
	cd shotgun; $(MAKE) clean

.PHONY: all install clean
