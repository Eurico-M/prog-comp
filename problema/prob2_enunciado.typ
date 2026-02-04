#set page(
  paper: "a4",
  numbering: "1/1"
)


= Vias de Comunicação

== Editorial

Esta ideia apareceu no fim do semestre, quando o André me perguntou se estava a gostar do trabalho de Compiladores. Eu disse que sim, que era dos trabalhos mais interessantes que eu já tinha feito. Fiquei a pensar noutros trabalhos, em particular um trabalho em Engenharia Civil em que era preciso desenhar um troço de estrada. Ao mesmo tempo, estava a pensar que o problema de Programação Competitiva inventado por mim podia ter algo a ver com grafos. Estas duas ideias deram este resultado.

Apesar de não ter concluído o problema (não escrevi uma resolução ou casos de teste), como já tinha a ideia resolvi pelo menos escrever o enunciado.

== Enunciado

Na construção de estradas, um dos fatores a ter em conta é a quantidade de terra movida. Para minimizar custos, queremos mover a menor quantidade de terra possível.

Na nomenclatura de Engenharia Civil, "escavação" é quando temos de retirar terra do local de construção, e "aterro" é quando temos de introduzir terra.

Uma técnica que pode ser usada para minimizar custos de movimentos de terra é manter um balanço entre escavação e aterro. Assim, a terra escavada pode ser usada em aterro num trecho próximo de estrada, reduzindo assim a quantidade de terra que tem de ser importada/exportada do local de construção.

#image("escavacao-aterro.png")

Esta ideia pode ser aplicada tanto ao corte transversal da estrada como ao corte longitudinal.

Neste exercício estamos apenas a considerar um cenário longitudinal.

Dado um mapa de um local de construção, e dois pontos entre os quais se quer construir uma estrada, queremos saber qual o percurso que minimiza o movimento de terra (i.e. que apresenta a diferença entre escavação e aterro mais próxima de zero).

O mapa representa células quadradas de um determinado local, marcadas com cotas médias em metros ("cota" é a altura em metros acima do nível médio do mar de um determinado ponto geográfico).

#figure(
  table(
    columns: (1cm,) * 3,
    rows: (1cm,) * 3,
    align: center + horizon,
    table.cell(fill: gray)[100], [110], [110],
    [150], [300], [110],
    [100], [ 50], table.cell(fill: gray)[100]
  )
)

Neste exemplo, queremos uma estrada entre o ponto (0,0) e o ponto (2,2).

Assumimos que a estrada começa à cota 100, acaba à cota 100, e não tem nenhuma inclinação (mantém-se à mesma cota durante todo o percurso).

Podemos construir uma estrada que passa no canto superior:

#figure(
  table(
    columns: (1cm,) * 3,
    rows: (1cm,) * 3,
    align: center + horizon,
    table.cell(fill: gray)[100], table.cell(fill: silver)[110], table.cell(fill: silver)[110],
    [150], [300], table.cell(fill: silver)[110],
    [100], [ 50], table.cell(fill: gray)[100]
  )
)

Neste caso, precisaríamos de escavar 30 unidades de terra: a estrada começa à cota 100, na próxima célula à direita temos de escavar 10 unidades, mais 10 unidades na célula do canto superior direito, e por fim 10 unidades na célula abaixo dessa. 
No fim da construção, seria preciso mover esta terra para um local fora do local de construção.

Outra hipótese é construir uma estrada que passa no canto inferior:

#figure(
  table(
    columns: (1cm,) * 3,
    rows: (1cm,) * 3,
    align: center + horizon,
    table.cell(fill: gray)[100], [110], [110],
    table.cell(fill: silver)[150], [300], [110],
    table.cell(fill: silver)[100], table.cell(fill: silver)[ 50], table.cell(fill: gray)[100]
  )
)

Aqui, o movimento de terras no final da construção é zero: temos de escavar 50 unidades na célula (1,0), mas podemos usar essa terra em aterro na célula (2,1).

== Input

Na primeira linha de input estão 2 inteiros, $R$ e $C$, que representam as linhas e colunas, respetivamente, do mapa.

Nas $R$ linhas seguintes estão $C$ inteiros em cada uma, que representam as cotas dos diferentes pontos do mapa (tal como no exemplo).

== Output

O output deve ser um inteiro que representa a quantidade mínima de terra que tem de ser movida, em valor absoluto, de forma a que este valor seja mínimo para o mapa em questão.

Os pontos entre os quais queremos construir a estrada são sempre o canto superior esquerdo e o canto inferior direito.

= Editorial Parte 2

Uma variação deste problema podia envolver uma inclinação da estrada. Por exemplo, introduzir um valor $K$ do qual a estrada pode subir ou descer (em cota).

Assim, para este exemplo:

#figure(
  table(
    columns: (1cm,) * 3,
    rows: (1cm,) * 3,
    align: center + horizon,
    table.cell(fill: gray)[100], [110], [110],
    [150], [300], [110],
    [100], [ 50], table.cell(fill: gray)[100]
  )
)

E com um valor $K = 10$, o percurso ótimo seria:

#figure(
  table(
    columns: (1cm,) * 3,
    rows: (1cm,) * 3,
    align: center + horizon,
    table.cell(fill: gray)[100], table.cell(fill: silver)[110], table.cell(fill: silver)[110],
    [150], [300], table.cell(fill: silver)[110],
    [100], [ 50], table.cell(fill: gray)[100]
  )
)

Já que agora a estrada pode começar na cota 100, subir para a cota 110 (por causa do $K = 10$) e manter-se a esta cota até descer novamente à cota 100. Resultando assim num movimento de terras nulo, já que não é preciso fazer nenhuma escavação.

É claro que a outra solução (canto inferior esquerdo) também apresenta um movimento de terras nulo. Mas o movimento "interno" (dentro do local de construção) é menor no primeiro caso (é igual a zero, enquanto no segundo caso seria, no mínimo, 40).
