#Lance qmake dans les sous-dossiers SUBDIRS
TEMPLATE = subdirs

SUBDIRS =   core \
            test \
            run \
            g3d \
            cascade \
            metaballs \

#Precise les dependances entre les sous-dossiers
test.depends = core
run.depends = core
g3d.depends = core
cascade.depends = core

# Regle pour la génération de la doc via make doc
doc.target = doc
doc.commands = doxygen Doxyfile   
doc.depends = FORCE

QMAKE_EXTRA_TARGETS += doc

# Regle pour l affichage de la doc via make viewdoc 

viewdoc.target = viewdoc
viewdoc.commands = firefox doc/html/index.html   
viewdoc.depends = FORCE

QMAKE_EXTRA_TARGETS += viewdoc

# Regle pour l affichage de la doc via make viewdoc 

realclean.target = realclean
realclean.commands = ./mrproper.sh
realclean.depends = FORCE

QMAKE_EXTRA_TARGETS += realclean

# Regle pour l execution de cascade

cascade.target = cascade
cascade.commands = ./cascade/release/cascade
cascade.depends =

QMAKE_EXTRA_TARGETS += cascade

# Regle pour l execution des tests

test.target = test
test.commands = ./test/release/test
test.depends =

QMAKE_EXTRA_TARGETS += test
