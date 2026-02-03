#set page(
  paper: "a4"
)


= T-shirts de Programação Competitiva

== Enunciado

O professor Pedro Ribeiro tem muitas t-shirts de concursos de programação, e quer usar uma t-shirt diferente todas as aulas. 

No entanto, não basta apenas pegar numa t-shirt que ainda não foi usada. Há vários fatores que fazem com que algumas t-shirts só possam ser usadas em certos dias: t-shirts justas só podem ser usadas em dias quentes, camisolas em dias frios. Várias t-shirts têm significados especiais, e o professor gostava de as usar só em determinados dias.

Como a coleção de t-shirts só vai aumentar, e o professor quer aplicar este sistema a um conjunto variado de intervalos de tempo, escreve um programa que, para um número $T$ de t-shirts e $D$ de dias consiga dar ao professor Pedro Ribeiro uma lista ordenada das t-shirts a usar, de acordo com um conjunto de $R$ restrições.

== Input

Na primeira linha estão três inteiros, $T$, $D$ e $R$, que representam o número de t-shirts, dias, e restrições, respetivamente.

As t-shirts são numeradas de 1 a $T$, e os dias de 1 a $D$. 

Nas $R$ linhas seguintes estão representadas as restrições: cada linha tem dois inteiros separados por um espaço. O primeiro número é a t-shirt, o segundo número é o dia em que essa t-shirt tem de ser usada.

Uma t-shirt pode estar associada a vários dias e vice-versa.

*Se uma t-shirt não aparecer em nenhuma restrição, quer dizer que pode ser usada em qualquer dia.*

Por exemplo, o input:

```
5 5 4
1 2
2 3
3 4
4 5
```

quer dizer que temos 5 t-shirts para distribuir por 5 dias, com 4 restrições. A t-shirt 1 tem de ser usada no dia 2, a t-shirt 2 tem de ser usada no dia 3, a t-shirt 3 tem de ser usada no dia 4, a t-shirt 4 tem de ser usada no dia 5. A t-shirt 5 não aparece nas restrições, portanto pode ser usada em qualquer dia.