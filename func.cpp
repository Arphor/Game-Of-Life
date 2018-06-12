#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "../include/FUNC.h"
Life::Life(int nLin, int nCol, bool** aux, bool** aux2){
  //Life nos ajuda a alocar os valores externos com as variaveis internas de nossa classe

  longitude = nLin;
  latitude = nCol;
  set_alive(aux, aux2);

}
void Life::set_alive(bool** matrix, bool** matrix_2){
  //Set_alive faz com que as matrixes internas da classe tomem os valores das matrixes externas.

  geracao_atual = matrix;
  geracao_passada = matrix_2;

}
void Life::update(){
  int entorno;
  int i, e;

  //Criamos uma matrix auxiliar para podermos gerar a geração seguinte

  bool **geracao_seguinte;
  geracao_seguinte = new bool *[longitude];
  for(i=0; i<longitude; i++){
    geracao_seguinte[i] = new bool[latitude];
  }

  //Percorremos cada celula da nossa matrix atual
  //Caso encontremos uma celula viva o entorno aumenta em +1

  for(i=0; i<longitude; i++){
    for(e=0; e<latitude; e++){
      entorno = 0;
      //Comparamos se (i-1)/(e-1)>=0 para sabermos se está dentro dos limites da nossa matrixes
      //A mesma coisa com i+1<longitude e e+1<latitude.
      //Assim evitamos pegar valores lixos e analisarmos celulas que n deveriam existir.

      //As em cima dela com i-1
      if((i-1)>=0){
        //Em cima e da esquerda
        if((e-1)>=0 && geracao_atual[i-1][e-1]==true){
          entorno++;
        }
        //Diretamente em cima
        if(geracao_atual[i-1][e]==true){
          entorno++;
        }
        //Em cima e da direita
        if((e+1)<latitude && geracao_atual[i-1][e+1]==true){
          entorno++;
        }
      }

      //Agora as celulas na mesma "altura" da analisada

      //Da esquerda
      if((e-1)>=0 && geracao_atual[i][e-1]==true){
        entorno++;
      }
      //Da direita
      if((e+1)<latitude && geracao_atual[i][e+1]==true){
        entorno++;
      }

      //Celulas abaixo
      if((i+1)<longitude){
        //E da esquerda
        if((e-1)>=0 && geracao_atual[i+1][e-1]==true){
          entorno++;
        }
        //Diretamente abaixo
        if(geracao_atual[i+1][e]==true){
          entorno++;
        }
        //E da direita
        if((e+1)<latitude && geracao_atual[i+1][e+1]==true){
          entorno++;
        }
      }

      //Agora tendo analisado todas as celulas ao redor, sabemos quantas estão vivas
      //Assim aplicamos as regras do jogo
      if(entorno<2 || entorno>3){
        //Caso tenham menos do que 2 celulas ou mais do que 3 ao seu redor, sempre serão mortas na proxima geração
        //Não importa seu estado atual
        geracao_seguinte[i][e]=false;
      }
      if(entorno ==  3){
        //Caso tenham 3, sempre serão vivas na proxima geração
        geracao_seguinte[i][e]=true;
      }
      if(entorno==2){
        //E caso possuam 2 o seu estado permanece o mesmo da geração atual
        geracao_seguinte[i][e]=geracao_atual[i][e];
      }
    }
  }

  //Agora testamos se o ecossistema esta estavel ou não
  if(stable(geracao_seguinte)==true){
    std::cout << "ECOSSISTEMA ESTAVEL" << std::endl;
    }

    //E alocamos o que era geração atual para a passada e a seguinte para a geracao_atual
    //Já que a matrix geração_seguinte é apenas um auxiliar se será deletada.
  for(i=0; i<longitude; i++){
    for(e=0; e<latitude; e++){
      geracao_passada[i][e]=geracao_atual[i][e];
      geracao_atual[i][e]=geracao_seguinte[i][e];
    }
  }
//Deletamos a matrix auxiliar
  for(i=0; i<longitude; i++){
    delete[] geracao_seguinte[i];
  }
  delete[] geracao_seguinte;
}
void Life::print(std::ostream& os, char c){
//Print percorre toda a matrix analisando se cada celula esta viva ou morta
  int i, e;

  for(i=0; i<longitude; i++){
    for(e=0; e<latitude; e++){
      //Caso esteja viva imprime o caractere informado que representa uma celula viva
      if(geracao_atual[i][e]==true){
        //Tanto no prompt quanto no arquivo de saida
        std::cout << c;
        os << c;
      }
      else{
        //Caso contrário coloca um ponto que para nós irá representar as celulas mortas.
        std::cout << ".";
        os << ".";
      }

      if(e+1 == latitude){
        //Esse if é somente para sabermos quando atingiremos o limite da nossa matrix
        //E assim podermos seguir para a próxima linha.
        std::cout << std::endl;
        os << std::endl;
      }

    }

  }
}
bool Life::stable(bool** matrix){
  //Percorre a matrix para sabermos se está nossa geração demonstra que o ecossistema se apresenta estavel
  int i, e, j, o;

  for(i=0; i<longitude; i++){
    for(e=0; e<latitude; e++){
      //Primeiro compara com a geração imediatamente anterior, se todos os elementos forem iguais, isso irá se repetir na seguinte também
      if(matrix[i][e]!=geracao_atual[i][e]){

        for(j=0; j<longitude; j++){
          for(o=0; o<latitude; o++){

            //Depois compara com a matrix de 2 gerações anteriores para saber se o ecossistema esta estavel
            //E irá se repetir entre 2 composições diferentes
            if(matrix[i][e]!=geracao_passada[i][e]){
              return false;
            }

          }
        }

        return true;

        //Essa função não encerra o programa para o usuario poder continuar rodando e ver se o sistema realmente esta estável

      }

    }
  }

  return true;
}
bool Life::extinct(){

  int i, e;

  for(i=0; i<longitude; i++){
    for(e=0; e<latitude; e++){

      //Simplesmente percorre toda a matrix da geração atual analisando seus elementos
      //Caso todos estejam mortos ele retorna true.

      if(geracao_atual[i][e]==true){
        return false;
      }

    }
  }
  return true;
}
