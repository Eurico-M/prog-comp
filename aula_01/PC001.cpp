#include <iostream>
#include <ostream>
#include <string>

int main() {
  //receber a sequencia de DNA
  std::string sequence;
  std::cin >> sequence;

  //usar um contador
  int count = 1;
  int max_count = 1;
  for (int i = 1; i < int(sequence.length()); i++) {
    // percorrer a sequência, comparando com o caracter anterior
    // se for igual, incrementar contador
    if (sequence[i] == sequence[i-1]) {
      count++;
      //depois de atualizado, comparar com o máximo encontrado, atualizar se necessário
      if (count > max_count) {
        max_count = count;
      }
    // fazer reset do contador se encontrarmos novo caracter
    } else {
      count = 1;
    }
  }

  std::cout << max_count << std::endl;

  return 0;
}
