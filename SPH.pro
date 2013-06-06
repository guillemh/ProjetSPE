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

