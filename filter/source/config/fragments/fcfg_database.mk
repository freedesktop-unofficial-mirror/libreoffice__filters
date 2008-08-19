all_fragments+=database

# -----------------------------------------------
# count = 1
T4_DATABASE = \
    StarBase

# -----------------------------------------------
# count = 1
F4_DATABASE = \
    StarOffice_XML__Base_
    
# -----------------------------------------------
# count = 1
F4_UI_DATABASE = \
    StarOffice_XML__Base__ui

# -----------------------------------------------
# count = 1
L4_DATABASE = \
    org_openoffice_comp_dbflt_DBContentLoader2

# -----------------------------------------------
# count = 1
C4_DATABASE =

# -----------------------------------------------
TYPES_4fcfg_database           = $(foreach,i,$(T4_DATABASE)    types$/$i.xcu                     )
FILTERS_4fcfg_database         = $(foreach,i,$(F4_DATABASE)    filters$/$i.xcu                   )
UI_FILTERS_4fcfg_database      = $(foreach,i,$(F4_UI_DATABASE) $(DIR_LOCFRAG)$/filters$/$i.xcu   )
FRAMELOADERS_4fcfg_database    = $(foreach,i,$(L4_DATABASE)    frameloaders$/$i.xcu              )
CONTENTHANDLERS_4fcfg_database = $(foreach,i,$(C4_DATABASE)    contenthandlers$/$i.xcu           )

# -----------------------------------------------
# needed to get dependencies inside global makefile work!
ALL_4fcfg_database = \
    $(TYPES_4fcfg_database) \
    $(FILTERS_4fcfg_database) \
    $(UI_FILTERS_4fcfg_database) \
    $(FRAMELOADERS_4fcfg_database) \
    $(CONTENTHANDLERS_4fcfg_database)
    
ALL_UI_FILTERS+=$(UI_FILTERS_4fcfg_database)

ALL_PACKAGES+=database
