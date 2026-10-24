boolean BarPUSH(BARALHO *baralho, int x){
    if (baralho != NULL){
        CARTA *carta = (CARTA *)malloc(sizeof(CARTA));
        carta->proximo = NULL;
        carta->num = x;
        if (baralho->inicio == NULL){
            baralho->inicio = carta;
        }
        else{
            CARTA *aux = baralho->inicio;
            while (aux->proximo != NULL){
                aux = aux->proximo;
            }
            aux->proximo = carta;
        }
        baralho->tam++;
        return TRUE;
    }
    return FALSE;
}

int BarPOP(BARALHO *baralho){
    if (baralho != NULL && baralho->inicio != NULL){
        int x = 0;
        CARTA *aux = baralho->inicio;
        CARTA *aux2 = NULL;
        
        while (aux->proximo != NULL){
            aux2 = aux;
            aux = aux->proximo;
        }
        x = aux->num;
        if (aux == baralho->inicio){
            baralho->inicio = NULL;
        }
        else{
            aux2->proximo = NULL;
        }
        free(aux);
        baralho->tam--;
        return x;
    }
    return FALSE;
}