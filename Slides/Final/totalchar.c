int main(int argc, char** argv){
	int total = 0;
	int i = 0;
	int j = 0;
	
	for(i = 1; i < argc; i++){
		for(j = 0; argv[i][j] != '\0'; j++)
			total++;
	}

}
