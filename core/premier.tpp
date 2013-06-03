/* ** Constructeurs ** */
template<unsigned int Dim>
Premier<Dim>::Premier(){}

template<unsigned int Dim>
Premier<Dim>::~Premier(){}


/* ** Methodes ** */
template <unsigned int Dim>
int Premier<Dim>::getPremier(int x) const 
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



