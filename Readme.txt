core : dossier contenant le simulateur physique, il sera utilisé par les autres dossiers sous forme d'une librairie (voir son .pro)

run : dossier contenant le main, l'interface graphique (mainwindow + viewer)

shaders : dossier contenant vos shaders, les instructions par sommets/facette que opengl lance a la carte graphique

test : ...

Pour compiler : 
qmake -r (-r pour recursive, lance qmake dans chaque sous dossier)
make

Pour voir si tout fonctionne : 
dans core/release une librairie doit être créée
dans run/release, lancer ./run et verifier que le viewer se lance
dans test/release, verifier le hello world


