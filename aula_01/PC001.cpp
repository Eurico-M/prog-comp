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
    if (sequence[i] == sequence[i-1]) {
      count++;
      //depois de atualizado, comparar com o máximo encontrado, atualizar se necessário
      if (count > max_count) {
        max_count = count;
      }
    } else {
      count = 1;
    }
  }

  std::cout << max_count << std::endl;

  return 0;
}
