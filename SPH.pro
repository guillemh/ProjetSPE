#Lance qmake dans les sous-dossiers SUBDIRS
TEMPLATE = subdirs

SUBDIRS =   core \
            test \
            run \
            g3d \
            cascade \
            cascade_complexe \
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
