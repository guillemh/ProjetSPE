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

    while (lookup[tmp] > x)
	tmp--;

    if (lookup[tmp] < x)
	tmp++;

    return lookup[tmp];
}

template <unsigned int Dim>
int Premier<Dim>::calculPremier(int x) const 
{
    while(!estPremier(x)){
	x++;
    }
    return x;
}

template <unsigned int Dim>
bool Premier<Dim>::estPremier(const int x) const 
{

    if (x < 2)
	return false;
    for (int i = 2; i < x; i++) {	
	 if (x % i == 0) 
	     return false;	 
    }
    return true;
}



