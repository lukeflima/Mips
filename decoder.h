int *decodificador(int *s)
{

    int *registradores, registrador, i;

    registradores = (int*) malloc(32*sizeof(int));
	registrador=16*s[0]+8*s[1]+4*s[2]+2*s[3]+s[4];
	for(i=0;i<32;i++)
	{
		registradores[i]=0;
	}
	registradores[registrador]=1;
    return registradores;
}