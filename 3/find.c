// Return 'some' index of a character found
int indexOf(char* str,char ch, int size){
    int index = -1;
    for(int i =0; i < size; i++){
        if(str[i]==ch){
            index =i;
        }
    }
    return -1;
}

// vs a faster early exit

int indexOf(char* str,char ch, int size){
    for(int i =0; i < size; i++){
        if(str[i]==ch){
            return i;
        }
    }

    return -1;
}

