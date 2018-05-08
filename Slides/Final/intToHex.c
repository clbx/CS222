void intToHex(int number, char hex[]){
	char c = 0;
	int i = 0;
	do{
		c = number%16;
		if(c <= 9 && c >= 0){
			c += '0';
		}
		else{
			c += 'a' -10;
		}
		hex[i] = c;
		i++;
		number /= 16;

	}while(number > 0);
	int j;
	for(j = 0; j < i; j++){
		char temp = hex[i];
		hex[i] = hex[i-j-1];
		hex[i-j-1] = temp;
	}
	hex[i] = '\0';
}
