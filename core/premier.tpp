/* ** Constructeurs ** */
template<unsigned int Dim>
Premier<Dim>::~Premier(){}


/* ** Methodes ** */
template <unsigned int Dim>
int Premier<Dim>::getPremier(const int x) const 
{
    int tmp;
    if (x < NUM_LOOKUP-1) {
	tmp = x;
    } else if (x <= 99991) {
	tmp = NUM_LOOKUP-1;
    } else {
	return calculPremier(x);
    }

    int cpt = 0;

    while (lookup[tmp] > x) {
	tmp--;
	cpt ++;
    }

    //cout << "Nombre d'acces a la table : " << cpt << endl;

    if (lookup[tmp] < x)
	tmp++;

    return lookup[tmp];
}

template <unsigned int Dim>
int Premier<Dim>::calculPremier(int x) const 
{

    if (x <= 2)
	return 2;
    if (!(x&1))
	++x;
    for(; !estPremier(x);x+=2)
	;
    return x;
}

template <unsigned int Dim>
bool Premier<Dim>::estPremier(const int x) const 
{    
    int q ;
    for (int i = 3; true; i++) {
	q = x/i;
	if (q < i)
	    return true;
	if (x == q*i) 
	    return false;	 
    }
    return true;
}



