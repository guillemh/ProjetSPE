
template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::collision(const Vecteur<Dim> & v) {
    Vecteur<Dim> res = Vecteur<Dim>(v);

    if (Dim == 2) {
        if (v(1) < x_min) {
            res(1) = x_min;
        } else if (v(1) > x_max) {
            res(1) = x_max;
        }

        if (v(2) < y_min) {
            res(2) = y_min;
        } else if (v(2) > y_max) {
            res(2) = y_max;
        }
    } else {
        if (v(1) < x_min) {
            res(1) = x_min;
        } else if (v(1) > x_max) {
            res(1) = x_max;
        }

        if (v(2) < y_min) {
            res(2) = y_min;
        } else if (v(2) > y_max) {
            res(2) = y_max;
        }
        if (v(3) < z_min)
            res(3) = z_min;
    }
    
    return res;
}

/*
 * Fonction interne appelée lors de la détection de collisions
 * Elle détecte une collision avec les plans X=x_min, X=x_max, Y=y_min, Y=y_max et Z=z_min
 * Elle renvoie le point de contact s'il y a collision, le Vecteur v sinon
 */
template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::collisionCascade(const Vecteur<Dim> & v,
                                           Materiau<Dim> *mat,
                                           const double bassin_x,
                                           const double bassin_y,
                                           const double bassin_z) {

    Vecteur<Dim> res = Vecteur<Dim>(v);
    double rayon = pow((3 * mat->getRigiditeGaz())/(4 * PI * mat->getPression()), 1.0/3.0);
    rayon += 0.3*rayon;

    if (Dim == 2) {
        
    } else {

        const double v1mr = v(1)-rayon;
        const double v1pr = v(1)+rayon;
        const double v2mr = v(2)-rayon;
        const double v2pr = v(2)+rayon;
        const double v3mr = v(3)-rayon;
        const double v3pr = v(3)+rayon;

        if (v3mr > -0.025 || (v3mr < -0.025 && v3pr > -0.025 && v1pr < bassin_x/2+rayon+0.1)) { // Niveau de la cascade supérieure

            const double bassin_xd2 = bassin_x/2;
            const double bassin_yd2 = bassin_y/2;
	    const double bassin_yd7 = bassin_y/7;
            const double bassin_zd5 = bassin_z/5;            
        
            if (v3mr < bassin_zd5-0.025) { // Niveau du palier
		if (!((v3mr > bassin_zd5+rayon-0.025 || v3mr < bassin_zd5-rayon-0.025) || (v2mr > -2*rayon && v2pr < 2*rayon && v1mr < -bassin_xd2+2*rayon)) && (v2mr < -4*rayon || v2pr > 4*rayon || v1mr > -bassin_x+4*rayon)) // Au dessus du palier, en dehors du sas
		    res(3) = bassin_zd5+rayon-0.025;
            }        

            if (v1mr < -bassin_xd2) {  // Derrière le bassin
                res(1) = -bassin_xd2+rayon;            
	    } else if (v1pr > bassin_xd2 && (((v2mr < -bassin_yd7 || v2pr > bassin_yd7 || v3pr > bassin_zd5-0.025) && v1pr < bassin_xd2+rayon))) { // Devant le bassin, en dehors du trou de la face avant            
                res(1) = bassin_xd2-rayon;   
	    } else if (v1pr > bassin_xd2) { // Tunnel de la face avant
		if (v2mr < -bassin_yd7)
		    res(2) = -bassin_yd7+rayon;
		else if (v2pr > bassin_yd7)
		    res(2) = bassin_yd7-rayon;
		if (v3mr < -0.025 && v3pr > -0.025)
		    res(3) = rayon-0.025;
            }
            
            if (v2mr < -bassin_yd2 && !(v1mr > bassin_xd2)) { // A gauche du bassin
                res(2) = -bassin_yd2+rayon;

            } else if (v2pr > bassin_yd2 && v1mr < bassin_xd2) { // A droite du bassin
                res(2) = bassin_yd2-rayon;
            }

            if (v3mr < -0.025 && v3pr > -0.025 && v1pr > -bassin_xd2 && v1mr < bassin_xd2)  // Fond du bassin
                res(3) = rayon-0.025;

        } else if (v3mr > -1.0 || (v3mr <= -1.0 && v3pr >= -1.0)) { // Niveau du bassin intermédiaire

            const double bassin_xd2 = bassin_x/2;
            const double bassin_yd3 = bassin_y/3;

            if (v3mr < -1.0 && v3pr > -1.0 && v1pr > bassin_xd2 && v1mr < 2*bassin_x && v2mr < bassin_yd3 && v2pr > -bassin_yd3) // Fond du bassin
                res(3) = -1.0+rayon;

            if (v1pr > 2*bassin_x) { // Devant le bassin 
		//if (v3mr < -1.0+bassin_z/7 && v1pr < 2*bassin_x+rayon)  // Sous le niveau de la paroi
                if (v3mr < -1.0+bassin_z/7 && v1pr <= 2*bassin_x+rayon)  // Sous le niveau de la paroi
		    res(1) = 2*bassin_x-rayon;
		else if ( !(v3mr > -1.0+bassin_z/7) && v1pr >= 2*bassin_x+rayon && v1pr <= 2*bassin_x+rayon+0.1) // Au dessus du niveau de la paroi
		    res(3) = -1.0+bassin_z/7+rayon;
		 
	    } else if (v1mr < bassin_xd2) { // Derrière le bassin
		if (v3mr < -1.0+bassin_z/3 && v1mr > bassin_xd2-rayon) // Sous la paroi
		    res(1) = bassin_xd2+rayon;
		else if (v3mr < -1.0+bassin_z/3 && v3pr > -1.0+bassin_z/3 && v1mr < bassin_xd2-rayon && v1pr > bassin_xd2+rayon-0.1)  // Au dessus du niveau de la paroi
		    res(3) = -1.0+bassin_z/3+rayon;
	    }
	    
	    if (v2pr > bassin_yd3) { // A droite du bassin
		if (v3mr < -1.0+bassin_z/3 && v2pr < bassin_yd3+rayon) // Sous la paroi
		    res(2) = bassin_yd3-rayon;
		else if ((v3mr) < -1.0+bassin_z/3 && v3pr > -1.0+bassin_z/3 && (v2pr>bassin_yd3+rayon) && (v2mr<bassin_yd3-rayon+0.1)) // Au dessus de la paroi
		    res(3) = -1.0+bassin_z/3+rayon;
		
	    } else if (v2mr < -bassin_yd3) { // A gauche du bassin
		if (v3mr < -1.0+bassin_z/3 && v2mr > -bassin_yd3-rayon) // Sous la paroi
		    res(2) = -bassin_yd3+rayon;
		else if (v3mr < -1.0+bassin_z/3 && v3pr > -1.0+bassin_z/3 && (v2mr) < -bassin_yd3-rayon && v2pr > -bassin_yd3+rayon-0.1) // Au dessus de la paroi
		    res(3) = -1.0+bassin_z/3+rayon;
	    }
	    
	} else if (v3mr > -2.0 || (v3mr < -2.0 && v3pr > -2.0)) { // Niveau du bassin inférieur 1
	    
	    const double bassin_xf2 = 2*bassin_x;
	    const double bassin_xf4 = 4*bassin_x;
	    const double bassin_yd2 = bassin_y/2;
	    
	    if (v3mr < -2.0 && v3pr > -2.0 && v1pr > bassin_xf2 && v1mr < bassin_xf4 && (v2mr) < bassin_yd2 && v2pr > -bassin_yd2) // Fond du bassin
		res(3) = -2.0+rayon;
	    
	    if (v1pr > bassin_xf4) { // Devant le bassin
		if (v3mr < -2.0+bassin_z/5 && v1pr < bassin_xf4+rayon) // Sous le niveau de la paroi
		    res(1) = bassin_xf4-rayon;
		else if (v3mr < -2.0+bassin_z/5 && v3pr > -2.0+bassin_z/5 && v1pr > bassin_xf4+rayon && v1mr < bassin_xf4-rayon+0.1) //  Au dessus du niveau de la paroi
		    res(3) = -2.0+bassin_z/5+rayon;
		
	    } else if (v1mr < bassin_xf2) { // Derriere le bassin
		if (v3mr < -2.0+bassin_z/5 && v1mr > bassin_xf2-rayon) // Sous le niveau de la paroi
		    res(1) = bassin_xf2+rayon;
		else if (v3mr < -2.0+bassin_z/5 && v3pr > -2.0+bassin_z/5 && v1mr < bassin_xf2-rayon && v1pr > bassin_xf2+rayon-0.1)
		    res(3) = -2.0+bassin_z/5+rayon;
	    }
	    
	    if (v2pr > bassin_yd2) { // A droite du bassin
		if (v3mr < -2.0+bassin_z/5 && v2pr < bassin_yd2+rayon) // Sous la paroi
		    res(2) = bassin_yd2-rayon;
		
		else if ((v3mr) < (-2.0+bassin_z/5) && (v3pr) > (-2.0+bassin_z/5) && (v2pr) > (bassin_yd2+rayon) && (v2mr) < (bassin_yd2-rayon+0.1)) // Au dessus de la paroi
		    res(3) = -2.0+bassin_z/5+rayon;

	    } else if (v2mr < -bassin_yd2) { // A gauche du bassin
		if (v3mr < -2.0+bassin_z/5 && v2mr > -bassin_yd2-rayon) // Sous la paroi
		    res(2) = -bassin_yd2+rayon;
		else if (v3mr < -2.0+bassin_z/5 && v3pr > -2.0+bassin_z/5 && (v2mr) < -bassin_yd2-rayon && v2pr > -bassin_yd2+rayon-0.1) // Au dessus de la paroi
		    res(3) = -2.0+bassin_z/5+rayon;
	    }
	    
	} else if (v3mr > -3.0 || (v3mr < -3.0 && v3pr > -3.0)) { // Niveau du bassin inférieur 2
	    
	    const double bassin_xf6 = 6*bassin_x;
	    
	    if (v3mr < -3.0 && v3pr > -3.0) // Fond du bassin
		res(3) = -3.0+rayon;
	    
	    if (v1pr > bassin_xf6) { // Devant le bassin
		if (v3mr < -3.0+bassin_z/5 && v1pr < bassin_xf6+rayon) { // Sous le niveau de la paroi
		    res(1) = bassin_xf6-rayon;
		} else if (v3mr < -3.0+bassin_z/5 && v3pr > -3.0+bassin_z/5 && v1pr > bassin_xf6+rayon && v1mr < bassin_xf6-rayon+0.1) { //  Au dessus du niveau de la paroi
		    res(3) = -3.0+bassin_z/5+rayon;
		}	
	    } else if (v1mr < bassin_x) { // Derrière le bassin 
		if (v3mr < -3.0+bassin_z && v1mr > bassin_x-rayon) // Sous le niveau de la paroi
		    res(1) = bassin_x+rayon;
		else if (v3mr < -3.0+bassin_z/5 && v3pr > -3.0+bassin_z/5 && v1mr < bassin_x-rayon && v1pr > bassin_x+rayon-0.1) // Au dessus de la paroi
		    res(3) = -3.0+bassin_z/5+rayon;		  
	    }
	    
	    if (v2pr > bassin_y) { // A droite du bassin
		if (v3mr < -3.0+bassin_z/5 && v2pr < bassin_y+rayon) // Sous la paroi
		    res(2) = bassin_y-rayon;
		else if (v3mr < -3.0+bassin_z/5 && v3pr > -3.0+bassin_z/5 && v2pr > bassin_y+rayon && v2mr < bassin_y-rayon+0.1) // Au dessus de la paroi
		    res(3) = -3.0+bassin_z/5+rayon;
		
	    } else if (v2mr < -bassin_y) { // A gauche du bassin
		if (v3mr < -3.0+bassin_z/5 && v2mr > -bassin_y-rayon) // Sous la paroi
		    res(2) = -bassin_y+rayon;
		else if (v3mr < -3.0+bassin_z/5 && v3pr > -3.0+bassin_z/5 && v2mr < -bassin_y-rayon && v2pr > -bassin_y+rayon-0.1) // Au dessus de la paroi
		    res(3) = -3.0+bassin_z/5+rayon;	  
	    } 
	} 
    }    
    return res;
}
