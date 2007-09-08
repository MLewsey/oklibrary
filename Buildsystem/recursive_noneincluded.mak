sub_make_directories := $(dir $(shell cd $(srcdir); find * -mindepth 1 -maxdepth 1 -name "makefile"))

define run_all_makes
  for sm in $(sub_make_directories); do cd $(srcdir)/$${sm}; $(MAKE) $@; if [ $$? != 0 ]; then exit 1; fi; done
endef

define run_all_makes_ignorant
  for sm in $(sub_make_directories); do cd $(srcdir)/$${sm}; $(MAKE) $@ --ignore-errors; done
endef
# run_all_makes_ignorant should be superfluous by now ?!

unexport srcdir

$(normal_goals) $(cleaning_goals) $(test_goals) $(new_test_goals) $(forced_goals) :
	$(run_all_makes)

$(special_goals) :
ifeq ($(MAKELEVEL), 0)
	$(run_all_makes_ignorant)
endif
	$(run_all_makes)

selected_module := $(OKsystem)/Transitional/Variables
# arbitrary choice (this hack will become superfluous with the new master-script)
$(html_goals) :
	make -f$(selected_module)/makefile $@
