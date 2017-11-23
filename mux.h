int Mux_2_1(int* a, int s){
	if(s == 0) return a[0];
	else return a[1];
}

int Mux_4_1(int* a,  int *S){
	int y[2];
	y[0] = Mux_2_1(a ,S[0]);
	y[1] = Mux_2_1(&a[2], S[0]);
	return Mux_2_1(y ,S[1]);
}

int Mux_8_1(int *a, int *S){

    int y[2];
    y[0] = Mux_4_1(a, S);
    y[1] = Mux_4_1(&a[4],S);
    return Mux_2_1(y,S[2]);

}
int Mux_32_1(int *a,int *S){

      int y[4], *s1;
      s1 = &S[3];
      y[0] = Mux_8_1(a ,S);
      y[1] = Mux_8_1(&a[8], S);
      y[2] = Mux_8_1(&a[16], S);
      y[3] = Mux_8_1(&a[24], S);
	  return Mux_4_1(y, s1);
}