#include "header.h"
int main (int argc, char *argv[]){
	node *List[5];
	for(int i= 1; i<6; ++i){
		List[i] = NULL;
		List[i] = read_file(argv[1], List[i],i);
	}
	for(int i= 1; i<6; ++i){
		List[i] = sort_list_prob (List[i]);
		List[i] = sort_list_name(List[i]);	
	}
	List[3] = sort_3(List[3]);
	int n = atoi(argv[2]);
	write_file(argv[3], n ,List);
	
	return 0;
}
