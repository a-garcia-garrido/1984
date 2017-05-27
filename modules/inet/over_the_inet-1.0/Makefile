package = over_the_inet
version = 1.0
tarname = $(package)
distdir = $(tarname)-$(version)

distcheck: $(distdir).tar.gz
	gzip -cd $+ | tar xvf -
	$(MAKE) -C $(distdir) all check clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz ready for distribution."

all clean photo_keeper photo_shooter:
	$(MAKE) -C src $@

dist: $(distdir).tar.gz

$(distdir).tar.gz: FORCE $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $(distdir).tar.gz
	rm -rf $(distdir)

$(distdir):
	mkdir -p $(distdir)/src
	cp Makefile $(distdir)
	cp src/Makefile $(distdir)/src
	cp src/*.cpp src/*.h $(distdir)/src

FORCE:
	rm $(distdir.tar.gz) &> /dev/null
	rm -rf $(distdir) &> /dev/null

.PHONY: all clean FORCE dist distcheck
