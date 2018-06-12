#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "../include/FUNC.h"

int main(int argc, char** argv){

  //Aqui criamos variaveis para alocarmos os dados do arquivo de entrada


  int lin, col;
  char cel_viva;

  //E algumas para podermos manipula-los depois
  int i, e;
  int count = 0;

  //Abrimos o arquivo de entrada e o de saida.
  std::ifstream entrada;
  entrada.open(argv[1], std::ios::in);

  std::ofstream saida;
  saida.open("saida.txt", std::ios::out);

  //Lemos o tamanho da matrix no arquivo e qual caractere
  //Representa uma celula vida.
  entrada >> lin;
  entrada >> col;
  entrada >> cel_viva;

  //Alocamos dinamicamente uma matrix com os tamanhos lidos
  bool **ecossistema;
  ecossistema = new bool *[lin];
  for(i=0; i<lin; i++){
    ecossistema[i] = new bool[col];
  }

  //Alocamos uma segunda matrix para podermos armazenar uma geração geracao_passada
  //Isso nos ajudará a identificar quando o "ecossistema" ficar estavel.
  bool **ecossistema2;
  ecossistema2 = new bool *[lin];
  for(i=0; i<lin; i++){
    ecossistema2[i] = new bool[col];
  }

  //Agora percorremos o resto dos dados do arquivo de entrada
  //Vendo qual celula está viva e qual está morta
  //E alocamos na nossa primeira matriz

  for(i=0; i<lin; i++){
    for(e=0; e<col; e++){
      char cel;
      entrada >> cel;
      if(cel==cel_viva){
        ecossistema[i][e] = true;
      }
      else{
        ecossistema[i][e] = false;
      }
    }
  }

  //Criamos uma string para podermos receber e trabalhar o comando do usuário
  std::string comando;
  comando = "Go";
  std::cout << "Apos cada geracao digite 'Go' para continuar e 'Stop' para parar" << std::endl;
  //Apos cada geração aumentamos o contador em +1 para podermos ir assimilando nossa progreção
  count++;

  //Nossas saidas devem ser feitas tanto no prompt de comando como no arquivo de saida.
  std::cout << "Geracao "<< count << std::endl;
  saida << "Geracao" << count << std::endl;

  Life Life(lin, col, ecossistema, ecossistema2);
  Life.print(saida, cel_viva);

  std::cout << std::endl;
  saida << std::endl;
  std::cin >> comando;

  while(comando == "Go"){

    count++;

    std::cout << "Geracao "<< count << std::endl;
    saida << "Geracao" << count << std::endl;

    //Progredimos de acordo com a vontade do usuario

    Life.update();
    Life.print(saida, cel_viva);

    std::cout << std::endl;
    saida << std::endl;

    //Mas caso o ecossistema se extinqua o programa se encerra
    if(Life.extinct()==true){

      std::cout << "ECOSSISTEMA EXTINTO" << std::endl;
      saida << "ECOSSISTEMA EXTINTO" << std::endl;
      comando="Stop";

    }
    else{
      std::cin >> comando;
    }
  }


  std::cout << "Parando. . ." << std::endl;

  //Agora que terminamos só precisamos apagar nossas matrixes e fechar nossos arquivos.

  for(i = 0; i <lin; i++){
        delete[] ecossistema[i];
    }
    delete[] ecossistema;
  for(i = 0; i <lin; i++){
        delete[] ecossistema2[i];
    }
    delete[] ecossistema2;

  entrada.close();
  saida.close();

  return 0;

}
