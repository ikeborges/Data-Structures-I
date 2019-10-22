#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int existe_em(int numero, int *vetor, int tamanho_vetor);
void gerar_vetor_treino(int *vetor_treino, int *vetor_teste);
int **receber_imagem(int numero_imagem, char classe[], int *tamanho_imagem);
double *calcular_ilbp(int **imagem, int *tamanho_imagem);
int calcular_decimal(int *b);
int menor_binario(int *b);
double menor_valor(double *vetor, int tam);
double maior_valor(double *vetor, int tam);
double *concatenar(double *vetor1, double *vetor2);
double *normaliza_vetor(double *vetor, int tam);
double *calcular_media(double **matriz);
double distancia_euclidiana(double *vetor1, double *vetor2);
double *calcular_glcm(int **imagem, int *tamanho_imagem);
double calcular_contraste(int **matriz);
double calcular_energia(int **matriz);
double calcular_homogeneidade(int **matriz);

int main(int argc, char const *argv[])
{
    int treino_grama[25] = {0}, teste_grama[25] = {0}, treino_asfalto[25] = {0}, teste_asfalto[25] = {0}, **imagem, tamanho_imagem;
    double *ilbp, *glcm, *descritor_normalizado, *descritor_imagem, **descritores_grama, *descritor_grama, **descritores_asfalto, *descritor_asfalto, distancia_grama, distancia_asfalto, acertos = 0, falsa_aceitacao = 0, falsa_rejeicao = 0;

    srand(time(NULL));
    gerar_vetor_treino(treino_grama, teste_grama);
    printf("Vetor treino e teste da classe GRAMA montado\n");
    gerar_vetor_treino(treino_asfalto, teste_asfalto);
    printf("Vetor treino e teste da classe ASFALTO montado\n");

    descritores_grama = (double **)malloc(25*sizeof(double *));
    if(descritores_grama == NULL){printf("Erro ao alocar descritores da classe GRAMA\n");exit(1);}

    printf("\n\nCLASSE GRAMA\n\n");
    // Calcula descritores para cada item de treino em grama
    for(int i = 0; i < 25; i++){
        imagem = receber_imagem(treino_grama[i], "grass", &tamanho_imagem);
        printf("Imagem %d recebida\n", i + 1);
        ilbp = calcular_ilbp(imagem, &tamanho_imagem);
        glcm = calcular_glcm(imagem, &tamanho_imagem);

        descritor_imagem = concatenar(ilbp, glcm);

        descritor_normalizado = normaliza_vetor(descritor_imagem, 536);
        descritores_grama[i] = (double *)malloc(536*sizeof(double));
        if(descritores_grama[i] == NULL){printf("Erro ao alocar descritor %d da classe GRAMA\n", i);exit(1);}
        descritores_grama[i] = descritor_normalizado;

        printf("------------\n");
        for(int j = 0; j < tamanho_imagem; j++)
            free(imagem[j]);
        free(imagem);
        free(descritor_imagem);
        free(glcm);
    }

    descritor_grama = calcular_media(descritores_grama);
    printf("\n=================================\n");

    descritores_asfalto = (double **)malloc(25*sizeof(double *));
    if(descritores_asfalto == NULL){
        printf("Erro ao alocar descritores da classe ASFALTO\n");
        for(int i=0;i<25;i++)
            free(descritores_grama[i]);
        free(descritores_grama);
        exit(1);
    }

    printf("\nCLASSE ASFALTO\n");
    // Calcula descritores para cada item de treino em asfalto
    for(int i = 0; i < 25; i++){
        imagem = receber_imagem(treino_asfalto[i], "asphalt", &tamanho_imagem);
        printf("Imagem %d recebida\n", i + 1);
        ilbp = calcular_ilbp(imagem, &tamanho_imagem);
        glcm = calcular_glcm(imagem, &tamanho_imagem);

        descritor_imagem = concatenar(ilbp, glcm);

        descritor_normalizado = normaliza_vetor(descritor_imagem, 536);
        descritores_asfalto[i] = (double *)malloc(536*sizeof(double));
        if(descritores_asfalto[i] == NULL){printf("Erro ao alocar descritor %d da classe ASFALTO\n", i);exit(1);}
        descritores_asfalto[i] = descritor_normalizado;

        printf("------------\n");
        for(int j = 0; j < tamanho_imagem; j++)
            free(imagem[j]);
        free(imagem);
        free(descritor_imagem);
        free(glcm);
    }

    descritor_asfalto = calcular_media(descritores_asfalto);
    printf("===================================\n");
    printf("===================================\n");

    printf("Testando sistema...\n\n\n");
    
    // Testando GRAMA
    for(int i = 0; i < 25; i++){
        imagem = receber_imagem(teste_grama[i], "grass", &tamanho_imagem);
        printf("Imagem %d recebida\n", i + 1);
        ilbp = calcular_ilbp(imagem, &tamanho_imagem);
        glcm = calcular_glcm(imagem, &tamanho_imagem);

        descritor_imagem = concatenar(ilbp, glcm);
        descritor_normalizado = normaliza_vetor(descritor_imagem, 536);

        distancia_grama = distancia_euclidiana(descritor_normalizado, descritor_grama);
        distancia_asfalto = distancia_euclidiana(descritor_normalizado, descritor_asfalto);

        if(distancia_grama < distancia_asfalto)
            acertos++;
        else
            falsa_rejeicao++;        

        printf("------------\n");
        for(int j = 0; j < tamanho_imagem; j++)
            free(imagem[j]);
        free(imagem);
        free(descritor_imagem);
        free(glcm);
    }

    // Testando ASFALTO
    for(int i = 0; i < 25; i++){
        imagem = receber_imagem(teste_asfalto[i], "asphalt", &tamanho_imagem);
        printf("Imagem %d recebida\n", i + 26);
        ilbp = calcular_ilbp(imagem, &tamanho_imagem);
        glcm = calcular_glcm(imagem, &tamanho_imagem);

        descritor_imagem = concatenar(ilbp, glcm);
        descritor_normalizado = normaliza_vetor(descritor_imagem, 536);

        distancia_grama = distancia_euclidiana(descritor_normalizado, descritor_grama);
        distancia_asfalto = distancia_euclidiana(descritor_normalizado, descritor_asfalto);

        if(distancia_grama < distancia_asfalto)
            falsa_aceitacao++;
        else
            acertos++;     

        printf("------------\n");
        for(int j = 0; j < tamanho_imagem; j++)
            free(imagem[j]);
        free(imagem);
        free(descritor_imagem);
        free(glcm);
    }

    printf("Sistema testado com sucesso!\n");
    printf("Gerando resultados...\n");
    printf("\n=============== Resultados ===============\n");

    printf("Taxa de acerto: %.2lf%%\n", (double)(acertos/50.0)*100);
    printf("Taxa de falsa aceitação: %.2lf%%\n", (double)(falsa_aceitacao/50.0)*100.0);
    printf("Taxa de falsa rejeição: %.2lf%%\n", (double)(falsa_rejeicao/50.0)*100.0);

    printf("\n================ Grupos utilizados ==============\n\n");

    printf("-------------- Treinamento --------------\n");
    printf("Grama:\n");
    for(int i = 0; i < 25; i++)
        printf("%d ", treino_grama[i]);
    printf("\n");

    printf("Asfalto:\n");
    for(int i = 0; i < 25; i++)
        printf("%d ", treino_asfalto[i]);
    printf("\n\n");

    printf("-------------- Testes --------------\n");
    printf("Grama:\n");
    for(int i = 0; i < 25; i++)
        printf("%d ", teste_grama[i]);
    printf("\n");

    printf("Asfalto:\n");
    for(int i = 0; i < 25; i++)
        printf("%d ", teste_asfalto[i]);
    printf("\n");


    for(int i = 0; i < 25; i++){
        free(descritores_grama[i]);
        free(descritores_asfalto[i]);
    }
    free(descritores_grama);
    free(descritores_asfalto);
    free(descritor_grama);
    free(descritor_asfalto);

    return 0;
}

int existe_em(int numero, int *vetor, int tamanho_vetor){
    int existe = 0;
    for(int i = 0; i < tamanho_vetor; i++){
        if(*(vetor + i) == numero)
            return existe = 1;
    }
    
    return existe;
}

void gerar_vetor_treino(int *vetor_treino, int *vetor_teste){
    int i = 0, j = 0;

    // Popula vetor de treino
    while(i < 25) {
        int numero = rand() % 50 + 1;
        if(!existe_em(numero, vetor_treino, 25))
        {
            *(vetor_treino + i) = numero;
            i++;
        }
    }
        
    int n = 1;
    // Vai iterando de um em um e checando se existe no vetor de treino, caso não exista, o adiciona ao vetor de teste
    while(j < 25) {
        if(!existe_em(n, vetor_treino, 25)){
            *(vetor_teste + j) = n;
            j++;
        }
        n++;
    }
}

int **receber_imagem(int numero_imagem, char classe[], int *tamanho_imagem){
    int **imagem, numero, linha, coluna;
    char nome_arquivo[50], caractere;
    sprintf(nome_arquivo, "%s%s%c%s%c%.2d%s", "DataSet/", classe, '/', classe, '_', numero_imagem, ".txt");

    FILE *fp;

    fp = fopen(nome_arquivo, "r");
    if(fp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    imagem = (int**)malloc(sizeof(int*));
    if(imagem == NULL) {
        printf("Erro ao alocar memória para linha 0\n");
        exit(1);
    }

    imagem[0] = (int*)malloc(sizeof(int));
    if(imagem[0] == NULL){
        printf("Erro ao alocar memório para coluna 0\n");
        free(imagem);
        exit(1);
    }

    linha = 0;
    coluna = 0;

    while(!feof(fp)){
        fscanf(fp, "%d%c", &numero, &caractere);
        imagem[linha][coluna] = numero;

        if(caractere == '\n'){
            linha++;
            imagem = (int**)realloc(imagem, (linha + 1)*sizeof(int*));

            if(imagem == NULL){
                printf("Erro ao alocar memória para linha %d\n", linha + 1);
                for(int i = 0; i < linha; i++)
                    free(imagem[i]);                
                free(imagem);
                exit(1);
            }

            imagem[linha] = (int*)malloc(sizeof(int));
            
            if(imagem[linha] == NULL){
                printf("Erro ao alocar memória para coluna %d\n", coluna + 1);
                for(int i = 0; i < linha; i++)
                    free(imagem[i]);                
                free(imagem);
                exit(1);
            }
            coluna = 0;
            continue;
        }

        coluna++;
        imagem[linha] = (int*)realloc(imagem[linha], (coluna + 1)*sizeof(int));

        if(imagem[linha] == NULL){
            printf("Erro ao alocar memória para coluna %d\n", coluna + 1);
            for(int i = 0; i < linha; i++)
                free(imagem[i]);                
            free(imagem);
            exit(1);
        }
    }
    
    fclose(fp);

    *tamanho_imagem = linha - 1;
    return imagem;
}

double *calcular_ilbp(int **imagem, int *tamanho_imagem){
    int p[9], b[9], ilbp;
    double media, *vetor_ilbp;

    vetor_ilbp = (double *)calloc(512, sizeof(double));
    if(vetor_ilbp == NULL){
        printf("Erro ao alocar memória para vetor ILBP");
        exit(1);
    }

    printf("Calculando ILBP...\n");

    for(int i = 1; i < *tamanho_imagem - 1; i++){
        for(int j = 1; j < *tamanho_imagem - 1; j++){
            p[0] = imagem[i-1][j-1];
            p[1] = imagem[i-1][j];
            p[2] = imagem[i-1][j+1];
            p[3] = imagem[i][j-1];
            p[4] = imagem[i][j];
            p[5] = imagem[i][j+1];
            p[6] = imagem[i+1][j-1];
            p[7] = imagem[i+1][j];
            p[8] = imagem[i+1][j+1];

            media = (p[0] + p[1] + p[2] + p[3] + p[4] + p[5] + p[6] + p[7] + p[8])/9.0;

            for(int k = 0; k < 9; k++){
                if(p[k] > media)
                    b[k] = 1;
                else
                    b[k] = 0;
            }

            ilbp = menor_binario(b);
            vetor_ilbp[ilbp] += 1;
        }
    }
    printf("ILBP calculado com sucesso!\n");
    return vetor_ilbp;
}

int calcular_decimal(int *b){
    int numero_decimal = 1*b[8] + 2*b[7] + 4*b[6] + 8*b[5] + 16*b[4] + 32*b[3] + 64*b[2] + 128*b[1] + 256*b[0];
    return numero_decimal;
}

int menor_binario(int *b){
    int decimal, menor_binario, aux0, aux1, aux2, aux3, aux4, aux5, aux6, aux7;

    decimal = calcular_decimal(b);
    menor_binario = decimal;
    
    for(int i = 0; i < 9; i++){
        aux0 = b[0];
        b[0] = b[8];
        aux1 = b[1];
        b[1] = aux0;
        aux2 = b[2];
        b[2] = aux1;
        aux3 = b[3];
        b[3] = aux2;
        aux4 = b[4];
        b[4] = aux3;
        aux5 = b[5];
        b[5] = aux4;
        aux6 = b[6];
        b[6] = aux5;
        aux7 = b[7];
        b[7] = aux6;
        b[8] = aux7;

        decimal = calcular_decimal(b);
        if(decimal < menor_binario)
            menor_binario = decimal;
    }

    return menor_binario;
}

double menor_valor(double *vetor, int tam){
    double menor = vetor[0];
    for(int i = 1; i < tam; i++){
        if(vetor[i] < menor)
            menor = vetor[i];
    }

    return menor;
}

double maior_valor(double *vetor, int tam){
    double maior = vetor[0];
    for(int i = 1; i < tam; i++){
        if(vetor[i] > maior)
            maior = vetor[i];
    }

    return maior;
}

double *concatenar(double *vetor1, double *vetor2){
    printf("Concatenando vetores...\n");

    double *vetor;

    vetor = vetor1;

    vetor = (double *)realloc(vetor, 536*sizeof(double));
    if(vetor == NULL){printf("Erro ao alocar descritor da imagem\n");exit(1);}

    for(int i = 0; i < 24; i++)
        vetor[512 + i] = vetor2[i];

    printf("Vetores concatenados com sucesso!\n");
    return vetor;
}

double *normaliza_vetor(double *vetor, int tam){
    printf("Normalizando vetor...\n");

    double *vetor_normalizado;
    double xmin = menor_valor(vetor, tam);
    double xmax = maior_valor(vetor, tam);

    vetor_normalizado = (double *)malloc(tam*sizeof(double));

    for(int i = 0; i < tam; i++)
        vetor_normalizado[i] = (vetor[i] - xmin)/(xmax - xmin);

    printf("Vetor normalizado com sucesso!\n");

    return vetor_normalizado;
}

double *calcular_media(double **matriz){
    double *resultado;
    resultado = (double *)calloc(536, sizeof(double));
    if(resultado == NULL){printf("Erro ao alocar vetor médio\n"); exit(1);}

    for(int j = 0; j < 536; j++){
        for(int i = 0; i < 25; i++)
            resultado[j] += (double)matriz[i][j]/25.0;
    }

    return resultado;
}

double distancia_euclidiana(double *vetor1, double *vetor2){
    double soma = 0, distancia;

    for(int i = 0; i < 536; i++)
        soma += pow((vetor1[i] - vetor2[i]), 2);
    
    distancia = sqrt(soma);
    return distancia;
}

double *calcular_glcm(int **imagem, int *tamanho_imagem){
    int **norte, **nordeste, **leste, **sudeste, **sul, **sudoeste, **oeste, **noroeste;
    double *resultado;

    printf("Calculando GLCM...\n");

    // Aloca memória para vetor resultado
    resultado = (double *)calloc(24, sizeof(double));
    if(resultado == NULL){printf("Erro ao alocar memória para vetor resultado");exit(1);}

    // Aloca memória para vetores glcm
    norte = (int **)calloc(256, sizeof(int *));
    if(norte == NULL){printf("Erro ao alocar memória para linhas vetor direção norte");exit(1);}
    for(int i = 0; i < 256; i++){
        norte[i] = (int *)calloc(256, sizeof(int));
        if(norte[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção norte");free(norte);exit(1);}
    }

    nordeste = (int **)calloc(256, sizeof(int *));
    if(nordeste == NULL){printf("Erro ao alocar memória para linhas vetor direção nordeste");exit(1);}
    for(int i = 0; i < 256; i++){
        nordeste[i] = (int *)calloc(256, sizeof(int));
        if(nordeste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção nordeste");free(nordeste);exit(1);}
    }

    leste = (int **)calloc(256, sizeof(int *));
    if(leste == NULL){printf("Erro ao alocar memória para linhas vetor direção leste");exit(1);}
    for(int i = 0; i < 256; i++){
        leste[i] = (int *)calloc(256, sizeof(int));
        if(leste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção leste");free(leste);exit(1);}
    }

    sudeste = (int **)calloc(256, sizeof(int *));
    if(sudeste == NULL){printf("Erro ao alocar memória para linhas vetor direção sudeste");exit(1);}
    for(int i = 0; i < 256; i++){
        sudeste[i] = (int *)calloc(256, sizeof(int));
        if(sudeste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção sudeste");free(sudeste);exit(1);}
    }

    sul = (int **)calloc(256, sizeof(int *));
    if(sul == NULL){printf("Erro ao alocar memória para linhas vetor direção sul");exit(1);}
    for(int i = 0; i < 256; i++){
        sul[i] = (int *)calloc(256, sizeof(int));
        if(sul[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção sul");free(sul);exit(1);}
    }

    sudoeste = (int **)calloc(256, sizeof(int *));
    if(sudoeste == NULL){printf("Erro ao alocar memória para linhas vetor direção sudoeste");exit(1);}
    for(int i = 0; i < 256; i++){
        sudoeste[i] = (int *)calloc(256, sizeof(int));
        if(sudoeste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção sudoeste");free(sudoeste);exit(1);}
    }

    oeste = (int **)calloc(256, sizeof(int *));
    if(oeste == NULL){printf("Erro ao alocar memória para linhas vetor direção oeste");exit(1);}
    for(int i = 0; i < 256; i++){
        oeste[i] = (int *)calloc(256, sizeof(int));
        if(oeste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção oeste");free(oeste);exit(1);}
    }

    noroeste = (int **)calloc(256, sizeof(int *));
    if(noroeste == NULL){printf("Erro ao alocar memória para linhas vetor direção noroeste");exit(1);}
    for(int i = 0; i < 256; i++){
        noroeste[i] = (int *)calloc(256, sizeof(int));
        if(noroeste[i] == NULL){printf("Erro ao alocar memória para colunas vetor direção noroeste");free(noroeste);exit(1);}
    }

    for(int i = 1; i < *tamanho_imagem - 1; i++){
        for(int j = 1; j < *tamanho_imagem - 1; j++){
            int ponto_central = imagem[i][j];

            // Norte
            int valor_norte = imagem[i-1][j];
            norte[ponto_central][valor_norte]++;

            // Nordeste
            int valor_nordeste = imagem[i-1][j+1];
            nordeste[ponto_central][valor_nordeste]++;

            // Leste
            int valor_leste = imagem[i][j+1];
            leste[ponto_central][valor_leste]++;

            // Sudeste
            int valor_sudeste = imagem[i+1][j+1];
            sudeste[ponto_central][valor_sudeste]++;

            // Sul
            int valor_sul = imagem[i+1][j];
            sul[ponto_central][valor_sul]++;

            // Sudoeste
            int valor_sudoeste = imagem[i+1][j-1];
            sudoeste[ponto_central][valor_sudoeste]++;

            // Oeste
            int valor_oeste = imagem[i][j-1];
            oeste[ponto_central][valor_oeste]++;

            // Noroeste
            int valor_noroeste = imagem[i-1][j-1];
            noroeste[ponto_central][valor_noroeste]++;
        }
    }

    resultado[0] = calcular_contraste(norte);
    resultado[1] = calcular_energia(norte);
    resultado[2] = calcular_homogeneidade(norte);

    resultado[3] = calcular_contraste(nordeste);
    resultado[4] = calcular_energia(nordeste);
    resultado[5] = calcular_homogeneidade(nordeste);

    resultado[6] = calcular_contraste(leste);
    resultado[7] = calcular_energia(leste);
    resultado[8] = calcular_homogeneidade(leste);

    resultado[9] = calcular_contraste(sudeste);
    resultado[10] = calcular_energia(sudeste);
    resultado[11] = calcular_homogeneidade(sudeste);

    resultado[12] = calcular_contraste(sul);
    resultado[13] = calcular_energia(sul);
    resultado[14] = calcular_homogeneidade(sul);

    resultado[15] = calcular_contraste(sudoeste);
    resultado[16] = calcular_energia(sudoeste);
    resultado[17] = calcular_homogeneidade(sudoeste);

    resultado[18] = calcular_contraste(oeste);
    resultado[19] = calcular_energia(oeste);
    resultado[20] = calcular_homogeneidade(oeste);

    resultado[21] = calcular_contraste(noroeste);
    resultado[22] = calcular_energia(noroeste);
    resultado[23] = calcular_homogeneidade(noroeste);

    for(int i = 0; i < 256; i++)
        free(norte[i]);
    free(norte);

    for(int i = 0; i < 256; i++)
        free(nordeste[i]);
    free(nordeste);

    for(int i = 0; i < 256; i++)
            free(leste[i]);
    free(leste);

    for(int i = 0; i < 256; i++)
        free(sudeste[i]);
    free(sudeste);

    for(int i = 0; i < 256; i++)
        free(sul[i]);
    free(sul);

    for(int i = 0; i < 256; i++)
        free(sudoeste[i]);
    free(sudoeste);

    for(int i = 0; i < 256; i++)
        free(oeste[i]);
    free(oeste);

    for(int i = 0; i < 256; i++)
        free(noroeste[i]);
    free(noroeste);

    printf("GLCM calculado com sucesso!\n");

    return resultado;
}

double calcular_contraste(int **matriz){
    double soma = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++)
            soma += pow(i - j, 2)*matriz[i][j];
    }

    return soma;
}

double calcular_energia(int **matriz){
    double soma = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++)
            soma += pow(matriz[i][j], 2);
    }

    return soma;
}

double calcular_homogeneidade(int **matriz){
    double soma = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 256; j++)
            soma += (matriz[i][j])/(1 + sqrt(pow(i-j, 2)));
    }

    return soma;
}
