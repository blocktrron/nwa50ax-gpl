include include/zld-spec.mk

BASE_DIR=$(shell pwd)

all: $(BASE_DIR)/image/.mrd-generated

$(BASE_DIR)/image/.mrd-generated: gen-mrd.py mrd.json
	./gen-mrd.py mrd.json -d $(BASE_DIR)/image
	touch $@
