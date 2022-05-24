#include "header.h"

int empty_3 = 0;


node *insert_list (node *list, char name[], float attack_prob){
    node *atacante, *aux;
    atacante = (node *)malloc(sizeof(node));



    if (list == NULL){
        strcpy(atacante -> name, name);
        atacante -> attack_prob = attack_prob;
        atacante -> next = NULL;
        list = atacante;
    }
    else {
        strcpy(atacante -> name, name);
        atacante -> attack_prob = attack_prob;
        atacante -> next = NULL;
        node *aux = list;
        while(aux -> next != NULL){
            aux = aux -> next;
        }
        aux -> next = atacante;
    }
    return list;
}

//recibe los datos desde el archivo de entrada y los mete en una lista
node *read_file(char *filename, node *list, int category){
    FILE *fp;
    char line [500];
    char name [300];
    char sep[] = ",";
    int column = 0;
    float attack_prob = 0;
    int danger_category = 0;

    fp = fopen(filename,"r");

    if (fp != NULL){
        fgets(line,1000,fp);
        while (!feof(fp)){
            fgets(line, 1000, fp);
            char *token = strtok(line, sep);
            if (token != NULL){
                while (token != NULL){
                    if(column == 0){
                        strcpy(name,token);
                    }
                    if(column == 1){
                        danger_category = atoi(token);
                    }
                    if(column == 2){
                        attack_prob = atof(token);
                    }
                    token = strtok(NULL,sep);
                    column ++ ;
                }
            }
            column = 0;
            if ((danger_category == 2 && attack_prob == 0) || (danger_category == 1 && attack_prob == 0)){
                attack_prob = -1;
            }
            if ((danger_category == 4 && attack_prob == 0) || (danger_category == 5 && attack_prob == 0)){
                attack_prob = 3;
            }
            if (danger_category == category){
                list = insert_list(list, name, attack_prob);
                if (danger_category == 3 && attack_prob != 0 ){
                    empty_3++;
                };
            }
        }
    }
    fclose(fp);
    return list;
}

//se ocupa en read_file y sirve para insertar datos en lista


void swap (node *atacante1, node *atacante2){
    char tmpName[300];
    float tmpProb;

    strcpy(tmpName, atacante1 -> name);
    strcpy(atacante1 -> name, atacante2 -> name);
    strcpy(atacante2 -> name, tmpName);

    tmpProb = atacante1 -> attack_prob;
    atacante1 -> attack_prob = atacante2 ->attack_prob;
    atacante2 -> attack_prob = tmpProb;
}


node *sort_list_name(node *list){
    node* actual = list;
    node *sig;
    while (actual -> next != NULL){
        sig = actual ->next;
        while(sig != NULL){
            if (actual -> attack_prob < sig -> attack_prob){

                swap(actual,sig);


            }
            sig = sig -> next;
        }
        actual = actual -> next;
        sig = actual -> next;
    }
    return list;
}


node *sort_list_prob(node *list){
    node* actual = list;
    node *sig;
    while (actual -> next != NULL){
        sig = actual ->next;
        while(sig != NULL){
            if (actual ->attack_prob < sig -> attack_prob){
                swap(actual,sig);
            }
            sig = sig -> next;
        }
        actual = actual -> next;
        sig = actual -> next;
    }
    return list;
}

node *sort_3(node *list){
    node *tmp1 = list;
    node *tmp2 = NULL;
    int count = 0;
    int mitad = empty_3 / 2;
    tmp1 = list;
    while (tmp1 != NULL){
        if (count < mitad){
            tmp2 = insert_list(tmp2, tmp1 -> name , tmp1 -> attack_prob);
        }
        if (count >= empty_3 ){
            tmp2 = insert_list(tmp2, tmp1 -> name , tmp1 -> attack_prob);
        }
        count++;
        tmp1 = tmp1 -> next;
    }
    tmp1 = list;
    count = 0;
    while (tmp1 != NULL){
        if (count >= mitad && count < empty_3){
            tmp2 = insert_list(tmp2, tmp1 -> name , tmp1 -> attack_prob);
        }
        count++;
        tmp1 = tmp1 -> next;

    }
    return tmp2;
}

//funcion auxiliar ocupada ne ordenamientos

void write_file (char arg[], int n , node *list[]){
    FILE *fp;
    node *aux;
    int count = 0;
    fp = fopen(arg,"w");
    if (fp != NULL){
        for (int i = 5; i > 0; --i){
            aux = list[i];
            while(aux != NULL){
                fprintf(fp, "Nombre: %s\n", aux -> name);
                aux = aux -> next;
                count++;
                if(count == n){
                    i=0;
                    break;
                }
            }
        }
    }
    fclose(fp);
}
