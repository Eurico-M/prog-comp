#include <iostream>
#include <string>

int main() {
  int cases;
  std::cin >> cases;
  for (int i = 0; i < cases; i++) {
    int n, x;
    std::cin >> n >> x;
    //std::cout << "n=" << n << " x=" << x << std::endl;

    std::string res = "YES";
    bool button_pressed = false;
    for (int j = 0; j < n; j++) {
      int door;
      std::cin >> door;

      //std::cout << "J=" << j << " x=" << x << std::endl;

      //se encontrar uma porta mas já não tiver mais tempo disponível no botão, impossivel
      if (door == 1 && x < 1) {
        res = "NO";
        //std::cout << "j=" << j << std::endl;
      //se encontrar uma porta, premir botao e reduzir 1s ao tempo disponivel
      } else if (door == 1) {
        button_pressed = true;
        x--;
      //se nao tiver porta, mas o botao já tiver sido premido, reduzir tempo na mesma
      } else if (button_pressed) {
        x--;
      }
    }

    std::cout << res << std::endl;
  }

  return 0;
}
