template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::calculForcesInteraction(Particule<Dim>* p1, Particule<Dim>* p2) {
    
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    /* Factorisations pour les calculs */
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    /* Définition de toutes les forces d'interaction */
    Vecteur<Dim> fPression = Vecteur<Dim>();
    Vecteur<Dim> fViscosite = Vecteur<Dim>();
    Vecteur<Dim> fSurface = Vecteur<Dim>();
    double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p1->getPosition() - p2->getPosition();
    /* On récupère la vitesse effective des particules, et non celle accumulée */
    double rho;
    Vecteur<Dim> drho;
    restriction(p2->getVitesse(), rho, drho);
    Vecteur<Dim> v2 = p2->getVitesse() * (1 - rho) - 0.5 * pow(p2->getVitesse().norme(), 2)
        * mat->getMasseParticules() * drho;
    
    restriction(p1->getVitesse(), rho, drho);
    Vecteur<Dim> v1 = p1->getVitesse() * (1 - rho) - 0.5 * pow(p1->getVitesse().norme(), 2)
        * mat->getMasseParticules() * drho;
    Vecteur<Dim> v_1_2 = v1 - v2;
    
    /* Renommages */
    double termePressionDensite_1 = p1->getPression() / pow(p1->getMasseVolumique(), 2);
    double masseVolumique_1 = p1->getMasseVolumique();
    double termePressionDensite_2 = p2->getPression() / pow(p2->getMasseVolumique(), 2);
    double masseVolumique_2 = p2->getMasseVolumique();

    /* **Expressions des forces** */

    /* Force de pression */
    fPression -= noyauMonaghan.gradient(x_1_2) * (termePressionDensite_1 + termePressionDensite_2);

    /* Force de viscosité */
    double prodScal = (v_1_2).scalaire(x_1_2);
    if (prodScal < 0) {
        double nu = nu_numerateur / (masseVolumique_1 + masseVolumique_2);
        double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
        fViscosite += noyauMonaghan.gradient(x_1_2) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_1_2.norme(), 2)));
    }

    /* Force de tension de surface */
    double moy_mv = (masseVolumique_1 + masseVolumique_2) / 2;
    colorfield += noyauMonaghan.laplacien(x_1_2) / moy_mv;
    fSurface += noyauMonaghan.gradient(x_1_2) / moy_mv;
    double norme = fSurface.norme();
    if (norme >= mat->getSeuilSurface()) {
        colorfield *= masse;
        fSurface *= -colorfield * mat->getTensionSurface() / norme;
    } else {
        fSurface = Vecteur<Dim>();
    }

    /* Multiplications par les facteurs constants */
    fPression *= masse * moy_mv / 100;
    fViscosite *= masse * moy_mv;
    fSurface *= masse;
    
    return fPression + fViscosite + fSurface;
}

template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::calculForcesInteractionPrec(Particule<Dim>* p1, Particule<Dim>* p2) {
    
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    /* Factorisations pour les calculs */
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    /* Définition de toutes les forces d'interaction */
    Vecteur<Dim> fPression = Vecteur<Dim>();
    Vecteur<Dim> fViscosite = Vecteur<Dim>();
    Vecteur<Dim> fSurface = Vecteur<Dim>();
    double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p1->getPositionPrec() - p2->getPositionPrec();
    /* On récupère la vitesse effective des particules, et non celle accumulée */
    double rho;
    Vecteur<Dim> drho;
    restriction(p2->getVitessePrec(), rho, drho);
    Vecteur<Dim> v2 = p2->getVitessePrec() * (1 - rho) - 0.5 * pow(p2->getVitessePrec().norme(), 2)
        * mat->getMasseParticules() * drho;
    
    restriction(p1->getVitessePrec(), rho, drho);
    Vecteur<Dim> v1 = p1->getVitessePrec() * (1 - rho) - 0.5 * pow(p1->getVitessePrec().norme(), 2)
        * mat->getMasseParticules() * drho;
    Vecteur<Dim> v_1_2 = v1 - v2;
    
    /* Renommages */
    double termePressionDensite_1 = p1->getPressionPrec() / pow(p1->getMasseVolumiquePrec(), 2);
    double masseVolumique_1 = p1->getMasseVolumiquePrec();
    double termePressionDensite_2 = p2->getPressionPrec() / pow(p2->getMasseVolumiquePrec(), 2);
    double masseVolumique_2 = p2->getMasseVolumiquePrec();

    /* **Expressions des forces** */

    /* Force de pression */
    fPression -= noyauMonaghan.gradient(x_1_2) * (termePressionDensite_1 + termePressionDensite_2);

    /* Force de viscosité */
    double prodScal = (v_1_2).scalaire(x_1_2);
    if (prodScal < 0) {
        double nu = nu_numerateur / (masseVolumique_1 + masseVolumique_2);
        double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
        fViscosite += noyauMonaghan.gradient(x_1_2) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_1_2.norme(), 2)));
    }

    /* Force de tension de surface */
    double moy_mv = (masseVolumique_1 + masseVolumique_2) / 2;
    colorfield += noyauMonaghan.laplacien(x_1_2) / moy_mv;
    fSurface += noyauMonaghan.gradient(x_1_2) / moy_mv;
    double norme = fSurface.norme();
    if (norme >= mat->getSeuilSurface()) {
        colorfield *= masse;
        fSurface *= -colorfield * mat->getTensionSurface() / norme;
    } else {
        fSurface = Vecteur<Dim>();
    }

    /* Multiplications par les facteurs constants */
    fPression *= masse * moy_mv / 100;
    fViscosite *= masse * moy_mv;
    fSurface *= masse;
    
    return fPression + fViscosite + fSurface;
}

template <unsigned int Dim>
void Fluide<Dim>::reinsertionTable(Particule<Dim>* part) {
    
    /* Paire d'itérateurs (début et fin) sur les particules de clé hash_key */   
    pair<typename multimap<int, Particule<Dim>*>::iterator, typename multimap<int, Particule<Dim>*>::iterator> part_pit;
    typename multimap<int, Particule<Dim>*>::iterator hash_it;
    Vecteur<Dim> noeud_grille;
    /* On récupère les particules de même clé que la particule courante */
    for (unsigned int i = 1; i <= Dim; i++) {
        noeud_grille(i) = int(floor(part->getPositionPrec()(i)/mat->getRayonNoyau()));
    }
    int hash_key = fonction_hashage(noeud_grille);

    /* On récupère la particule courante */
    hash_it = hash_voisins.find(hash_key);
    while (hash_it->second != part && hash_it != hash_voisins.end()) {
        ++hash_it;
    }
    /* On enlève la particule de la table des voisins */
    hash_voisins.erase(hash_it);

    /* On la réinsère avec sa clé mise à jour avec sa nouvelle position */
    for (unsigned int i = 1; i <= Dim; i++) {
        noeud_grille(i) = int(floor(part->getPosition()(i)/mat->getRayonNoyau()));
    }
    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));
   
}

template <unsigned int Dim>
double Fluide<Dim>::calculCritere(const Vecteur<Dim>& moment) {
    double critere = 0;
    for (unsigned int i = 1; i <= Dim; ++i) {
        critere += moment(i)*moment(i);
    }
    critere /= (2.0*mat->getMasseParticules());
    return critere;
}

template <unsigned int Dim>
void Fluide<Dim>::restriction(const Vecteur<Dim>& moment, double &rho, Vecteur<Dim>& drho) {
    double critere = calculCritere(moment); 

    /* Calcul Rho */
    if(critere <= this->epsilonR) {
        rho = 1.0;
    } else if(critere >= this->epsilonF) {
        rho = 0.0;
    } else if(critere > this->epsilonR && critere < this->epsilonF) {
        double x = (critere - this->epsilonR) / (this->epsilonF - this->epsilonR);
        rho = -6*x*x*x*x*x + 15*x*x*x*x - 10*x*x*x + 1;
    }

    /* Calcul Drho */
    if(rho == 1.0 || rho == 0.0) {
        for (unsigned int i = 1; i <= Dim; ++i) {
            drho(i) = 0.0;
        }
    } else if(rho > 0.0 && rho < 1.0) {
        double x = (critere-this->epsilonR) / (this->epsilonF-this->epsilonR);
        double alpha = (-30*x*x*x*x + 60*x*x*x - 30*x*x);
        alpha /= (mat->getMasseParticules() * (this->epsilonF - this->epsilonR));
        for (unsigned int i = 1; i <= Dim; ++i) {
            drho(i) = alpha*moment(i);
        }
    }
    
}

template<unsigned int Dim>
void Fluide<Dim>::afficher_actives() {
    cout << "Particules actives :" << endl;
    typename list<Particule<Dim>*>::iterator act_it;
    cout << "   ";
    for (act_it = actives.begin(); act_it != actives.end(); ++act_it) {
        cout << (*act_it)->getIndice() << " ";
    }
    cout << endl;
}

template <unsigned int Dim>
bool Fluide<Dim>::voisinsInactifs(Particule<Dim>* part, int nbr_limite) {
    set<Particule<Dim>*> vois = voisinage(*part);
    typename set<Particule<Dim>*>::iterator vois_it = vois.begin();
    int cpt_inactifs = 0;
    while (cpt_inactifs <= nbr_limite && vois_it != vois.end()) {
        if ((*vois_it)->getEtat() == INACTIVE) {
            ++cpt_inactifs;
        }
        ++vois_it;
    }
    return (cpt_inactifs <= nbr_limite);
}


template<unsigned int Dim>
void Fluide<Dim>::integrationForces() {
    set<Particule<Dim>*> vois;
    typename set<Particule<Dim>*>::iterator vois_it;
    typename list<Particule<Dim> *>::iterator part_it;
    NoyauLissageMonaghan<Dim> noyau = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());
    
    if (debutAnim) {
        /* Premier pas de l'animation */

        /* Calcul des masses volumiques et pressions */
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            /* On boucle sur toutes les particules */
            vois = voisinage(*(*part_it));
            double somme = noyau.defaut(Vecteur<Dim>());
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                somme += noyau.defaut((*part_it)->getPosition() - (*vois_it)->getPosition());
            }
            (*part_it)->setMasseVolumique(mat->getMasseParticules() * somme);
            (*part_it)->majPression(mat->getDensiteRepos());
        }

        /* Calcul des forces */
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            /* On boucle sur toutes les particules */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                if ((*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* On ne veut considérer les couples qu'une fois */
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = forces;
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                }
            }
            /* Ajout des forces non interactives */
            (*part_it)->incrForces((*part_it)->getMasseVolumique() * mat->getAccGrav());   // force de gravité
        }
        debutAnim = false;

    } else {
        /* Au milieu de l'algorithme incrémental */

        /*
         * On se base sur les anciennes positions pour enlever les anciennes forces,
         * et les anciennes contributions pour la masse volumique et la pression
         */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinagePrec(*(*part_it));

            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                if ((*vois_it)->getEtat() == INACTIVE
                    /* La particule voisine n'est pas active : il faut quand même
                     * mettre à jour les forces d'interaction entre elles,
                     * et les contributions pour la masse volumique,
                     * mais vois_it ne pourra pas le faire */
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Enlever contributions */
                    double majMasseVolPrec = mat->getMasseParticules() *
                    noyau.defaut((*part_it)->getPositionPrec() - (*vois_it)->getPositionPrec());
                    (*part_it)->decrMasseVolumique(majMasseVolPrec);
                    (*vois_it)->decrMasseVolumique(majMasseVolPrec);

                    /* Enlever interactions */
                    Vecteur<Dim> forcesPrec = matF((*part_it)->getIndice(), (*vois_it)->getIndice());
                    if ((*part_it)->getIndice() > (*vois_it)->getIndice()) {
                        forcesPrec = -forcesPrec;
                    }
                    (*part_it)->decrForces(forcesPrec);
                    (*vois_it)->incrForces(forcesPrec);
                }
            }
        }

        /*
         * On met à jour les positions dans la grille de voxels :
         * on met à jour la hashtable, uniquement pour les particules actives,
         * car les autres n'ont pas modifié leur position
         */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            reinsertionTable(*part_it);
        }

        /*
         * Mise à jour de la densité et de la pression :
         * il faut le faire avant la mise à jour des forces,
         * car leur calcul dépend de la densité et de la pression
         */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur les voisins de la particule */
                if ((*vois_it)->getEtat() == INACTIVE
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Ajouts des contributions à la particule et sa voisine */
                    double majMasseVol = mat->getMasseParticules()
                        * noyau.defaut((*part_it)->getPosition() - (*vois_it)->getPosition());
                    (*part_it)->incrMasseVolumique(majMasseVol);
                    (*vois_it)->incrMasseVolumique(majMasseVol);
                    /*
                     * On met la pression à jour à chaque fois pour les voisins,
                     * pour qu'à la fin elle soit bien correcte, quand toutes
                     * les contributions auront été apportées
                     */
                    (*vois_it)->majPression(mat->getDensiteRepos());
                }
            }
            /*
             * La masse volumique de la particule a fini d'être calculée
             * on peut mettre à jour la pression
             */
            (*part_it)->majPression(mat->getDensiteRepos());
        }    

        /* On ajoute les forces correspondant aux nouvelles positions */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                if ((*vois_it)->getEtat() == INACTIVE
                    /* La particule voisine n'est pas active : il faut quand même
                     * mettre à jour les forces d'interaction entre elles,
                     * mais vois_it ne pourra pas le faire */
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    if ((*part_it)->getIndice() < (*vois_it)->getIndice()) {
                        matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = forces;
                    } else {
                        matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = -forces;
                    }
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                }
            }
        }

    }
}

template<unsigned int Dim>
void Fluide<Dim>::schemaIntegration() {

    /* Mise à jour des forces, et en même temps de la pression et masse volumique */
    integrationForces();

    /* Pour itérer sur les particules */
    typename list<Particule<Dim> *>::iterator part_it;

    /* Réinitialisation de la liste des particules actives */
    actives.clear();

    double rho;
    Vecteur<Dim> drho;
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        /* Mise à jour des vitesses */
        (*part_it)->setVitessePrec((*part_it)->getVitesse());
        (*part_it)->incrVitesse((*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique());

        /* Mise à jour de la liste des particules actives */
        restriction((*part_it)->getVitesse(), rho, drho);
        if (rho == 0) {
            /* Particule complètement active */
            actives.push_back(*part_it);
            (*part_it)->setEtat(ACTIVE);
        } else if (rho < 1) {
            /* Particule en transition */
	    actives.push_back(*part_it);
	    (*part_it)->setEtat(TRANSITION);
        } else {
            /* Particule inactive */
            (*part_it)->setEtat(INACTIVE);
        }

        /* Mise à jour des positions */
        Vecteur<Dim> incr = mat->getPasTemps() * 
            ((*part_it)->getVitesse() * (1 - rho)
             - 0.5 * pow((*part_it)->getVitesse().norme(), 2) * mat->getMasseParticules() * drho
             );
        (*part_it)->setPositionPrec((*part_it)->getPosition());
        (*part_it)->incrPosition(incr); 
        
        /* Détection des collisions */
        if ((*part_it)->getEtat() != INACTIVE) {
            /* Uniquement pour les particules actives */
            Vecteur<Dim> pos = (*part_it)->getPosition();
            Vecteur<Dim> contact;
#if !CASCADE
            contact = collision(pos);
#else
            contact = collisionCascade(pos, mat, 0.5, 0.5, 0.5);
#endif
        
            /* S'il y a collision, on met à jour la position et la vitesse */
            if (contact != pos) {
                pos = contact - pos;
                double dist = pos.norme();
                Vecteur<Dim> normale = pos / dist;
        
                /* Mise à jour de la position */
                (*part_it)->setPosition(contact);
            
                /* Mise à jour de la vitesse */
                double vitesse = (*part_it)->getVitesse().scalaire(normale);
                (*part_it)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse * normale);
                /* Technique plus adaptee dans le cas de la vague, qui consiste a empecher 
                 * Les particules de s'empiler sur un bord */
                // if (normale(3) < 0.001 && (*part_it)->getVitesse()(3) < 0.0) {
                //     (*part_it)->incrVitesse(-3 * vitesse * normale);
                // } else {
                //     (*part_it)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse * normale);
                // }
                
                restriction((*part_it)->getVitesse(), rho, drho);
                /* Mise à jour des particules actives */
                if (rho >= 1) {
                    reinsertionTable(*part_it);
                    actives.remove(*part_it);
                    (*part_it)->setEtat(INACTIVE);
                }
            }
        }
    }
    
    /* On met à jour la coloration des sommets pour le calcul de la surface implicite */
    if (afficheMetaballs) {
        ball->coloration(particules);
    }

}

template<unsigned int Dim>
void Fluide<Dim>::integrationForces_Traces() {
    set<Particule<Dim>*> vois;
    typename set<Particule<Dim>*>::iterator vois_it;
    typename list<Particule<Dim> *>::iterator part_it;
    NoyauLissageMonaghan<Dim> noyau = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());
    
    if (debutAnim) {
        /* Premier pas de l'animation */

        /* Calcul des masses volumiques et pressions */
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            /* On boucle sur toutes les particules */
            vois = voisinage(*(*part_it));
            double somme = noyau.defaut(Vecteur<Dim>());
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                somme += noyau.defaut((*part_it)->getPosition() - (*vois_it)->getPosition());
            }
            (*part_it)->setMasseVolumique(mat->getMasseParticules() * somme);
            (*part_it)->majPression(mat->getDensiteRepos());
        }
        cout << "Calcul masses volumiques et pressions" << endl;
        affiche();

        /* Calcul des forces */
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            /* On boucle sur toutes les particules */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                if ((*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* On ne veut considérer les couples qu'une fois */
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = forces;
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                }
            }
            /* Ajout des forces non interactives */
            (*part_it)->incrForces((*part_it)->getMasseVolumique() * mat->getAccGrav());   // force de gravité
            
            cout << (*part_it)->getIndice() << ". forces début : " << (*part_it)->getForces() << endl;
            
        }
        debutAnim = false;

    } else {
        /* Au milieu de l'algorithme incrémental */
        
        affiche();
        /*
         * On se base sur les anciennes positions pour enlever les anciennes forces,
         * et les anciennes contributions pour la masse volumique
         */
        cout << endl << "********************************************" << endl;
        cout << "Forces enlevées :" << endl;
        matF.afficher();
        cout << endl << "********************************************" << endl;
        
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinagePrec(*(*part_it));
            
            cout << (*part_it)->getIndice() << ". forces précédentes : " << (*part_it)->getForces() << endl;
            
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                
                if ((*vois_it)->getEtat() == INACTIVE
                    /* La particule voisine n'est pas active : il faut quand même
                     * mettre à jour les forces d'interaction entre elles,
                     * et les contributions pour la masse volumique,
                     * mais vois_it ne pourra pas le faire */
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Enlever contributions */
                    double majMasseVolPrec = mat->getMasseParticules() *
                    noyau.defaut((*part_it)->getPositionPrec() - (*vois_it)->getPositionPrec());
                    (*part_it)->decrMasseVolumique(majMasseVolPrec);
                    (*vois_it)->decrMasseVolumique(majMasseVolPrec);

                    /* Enlever interactions */
                    Vecteur<Dim> forcesPrec = matF((*part_it)->getIndice(), (*vois_it)->getIndice());
                    if ((*part_it)->getIndice() > (*vois_it)->getIndice()) {
                        forcesPrec = -forcesPrec;
                    }
                    (*part_it)->decrForces(forcesPrec);
                    (*vois_it)->incrForces(forcesPrec);
                    
                    cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                         << " " << forcesPrec << endl;
                    cout << " => force intermédiaire : " << (*part_it)->getForces() << endl;
                    cout << " => masse volumique enlevée : " << majMasseVolPrec << endl;
                    
                }
            }
            cout << endl;
        }

        cout << "BILAN des forces intermédiaire :" << endl;
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            cout << (*part_it)->getIndice() << " totalforces : " << (*part_it)->getForces() << endl;
        }

        /*
         * On met à jour les positions dans la grille de voxels :
         * on met à jour la hashtable, uniquement pour les particules actives,
         * car les autres n'ont pas modifié leur position
         */
        /* On boucle sur les particules actives */
        afficher_hash();
        cout << "MAJ table hashage" << endl;
        afficher_actives();
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            reinsertionTable(*part_it);
        }
        afficher_hash();

        /*
         * Mise à jour de la densité et de la pression :
         * il faut le faire avant la mise à jour des forces,
         * car leur calcul dépend de la densité et de la pression
         */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur les voisins de la particule */
                if ((*vois_it)->getEtat() == INACTIVE
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Ajouts des contributions à la particule et sa voisine */
                    double majMasseVol = mat->getMasseParticules()
                        * noyau.defaut((*part_it)->getPosition() - (*vois_it)->getPosition());
                    (*part_it)->incrMasseVolumique(majMasseVol);
                    (*vois_it)->incrMasseVolumique(majMasseVol);
                    /*
                     * On met la pression à jour à chaque fois pour les voisins,
                     * pour qu'à la fin elle soit bien correcte, quand toutes
                     * les contributions auront été apportées
                     */
                    (*vois_it)->majPression(mat->getDensiteRepos());
                }
            }
            /*
             * La masse volumique de la particule a fini d'être calculée
             * on peut mettre à jour la pression
             */
            (*part_it)->majPression(mat->getDensiteRepos());
        }    

        /* On ajoute les forces correspondant aux nouvelles positions */
        cout << endl << "********************************************" << endl;
        cout << "Forces ajoutées :" << endl;
        matF.afficher();
        cout << endl << "********************************************" << endl;
        
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            
            cout << (*part_it)->getIndice() << ". forces précédentes : " << (*part_it)->getForces() << endl;
            
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */

                if ((*vois_it)->getEtat() == INACTIVE
                    /* La particule voisine n'est pas active : il faut quand même
                     * mettre à jour les forces d'interaction entre elles,
                     * mais vois_it ne pourra pas le faire */
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    if ((*part_it)->getIndice() < (*vois_it)->getIndice()) {
                        matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = forces;
                    } else {
                        matF((*part_it)->getIndice(), (*vois_it)->getIndice()) = -forces;
                    }
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                    
                    cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                         << " " << forces << endl;
                    cout << " => force intermédiaire : " << (*part_it)->getForces() << endl;
                    
                }
            }
            cout << endl;
        }

        cout << "BILAN des forces :" << endl;
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            cout << (*part_it)->getIndice() << " totalforces : " << (*part_it)->getForces() << endl;
        }

    }
}

template<unsigned int Dim>
void Fluide<Dim>::schemaIntegration_Traces() {

    cout << endl << "|||||||||||||||||||||||||| NOUVEAU PAS ||||||||||||||||||||||||||" << endl;
    
    /* Mise à jour des forces, et en même temps de la pression et masse volumique */
    integrationForces_Traces();

    /* Pour itérer sur les particules */
    typename list<Particule<Dim> *>::iterator part_it;

    /* Réinitialisation de la liste des particules actives */
    actives.clear();
    
    cout << endl << "********************************************" << endl;
    
    double rho;
    Vecteur<Dim> drho;
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
    /* Mise à jour des vitesses */
        (*part_it)->setVitessePrec((*part_it)->getVitesse());
        
        cout << (*part_it)->getIndice() << ".Vitesse " << (*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique() << endl;
        
        (*part_it)->incrVitesse((*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique());

    cout << endl << "********************************************" << endl;
        /* Mise à jour de la liste des particules actives */
        restriction((*part_it)->getVitesse(), rho, drho);
        
        cout << (*part_it)->getIndice() << ". Restriction : " << rho <<  " | " << drho << endl;
        
        if (rho == 0) {
            /* Particule complètement active */
            actives.push_back(*part_it);
            (*part_it)->setEtat(ACTIVE);
        } else if (rho < 1) {
            /* Particule en transition */
            actives.push_back(*part_it);
            (*part_it)->setEtat(TRANSITION);
        } else {
            /* Particule inactive */
	    (*part_it)->setEtat(INACTIVE);
        }
        /* Mise à jour des positions */
        Vecteur<Dim> incr = mat->getPasTemps() * 
            ((*part_it)->getVitesse() * (1 - rho)
             - 0.5 * pow((*part_it)->getVitesse().norme(), 2) * mat->getMasseParticules() * drho
             );
        
        cout << (*part_it)->getIndice() << ". Incr position " << incr << endl;
        
        (*part_it)->setPositionPrec((*part_it)->getPosition());
        (*part_it)->incrPosition(incr); 
        
        /* Détection des collisions */
        if ((*part_it)->getEtat() != INACTIVE) {
            /* Uniquement pour les particules actives */
            Vecteur<Dim> pos = (*part_it)->getPosition();
            Vecteur<Dim> contact;
#if !CASCADE
            contact = collision(pos);
#else
            contact = collisionCascade(pos, mat, 0.5, 0.5, 0.5);
#endif
        
            /* S'il y a collision, on met à jour la position et la vitesse */
            if (contact != pos) {
                pos = contact - pos;
                double dist = pos.norme();
                Vecteur<Dim> normale = pos / dist;
        
                /* Mise à jour de la position */
                cout << (*part_it)->getIndice() << ". maj pos " << contact << endl;
                
                (*part_it)->setPosition(contact);
            
                /* Mise à jour de la vitesse */
                double vitesse = (*part_it)->getVitesse().scalaire(normale);
                
                cout << (*part_it)->getIndice() << ". maj vitesse" << endl;
                
                (*part_it)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse * normale);
                /* Technique plus adaptee dans le cas de la vague, qui consiste a empecher 
                 * Les particules de s'empiler sur un bord */
                // if (normale(3) < 0.001 && (*part_it)->getVitesse()(3) < 0.0) {
                //     (*part_it)->incrVitesse(-3 * vitesse * normale);
                // } else {
                //     (*part_it)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse * normale);
                // }
                restriction((*part_it)->getVitesse(), rho, drho);
                   
                if (rho >= 1) {
                    
                    cout << (*part_it)->getIndice() << ". MAJ actives collision" << endl;
                    
                    reinsertionTable(*part_it);
                    actives.remove(*part_it);
                    (*part_it)->setEtat(INACTIVE);
                }
            }
        }
    }
    
    /* On met à jour la coloration des sommets pour le calcul de la surface implicite */
    if (afficheMetaballs) {
        ball->coloration(particules);
    }
    
    cout << endl << "********************************************" << endl;
    afficher_actives();
    cout << endl << "********************************************" << endl;
    affiche();

}
