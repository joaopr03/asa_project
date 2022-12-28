<h2 align="center"> INSTITUTO SUPERIOR TÉCNICO </h2>
<h1 align="center"> Análise e Síntese de Algoritmos <br> <i> 2022/2023 </i> </h1>
<h2 align="center"> 1º Projecto </h2>
<h3 align="center"> <i>Data enunciado: 25 de novembro de 2022 <br>
Data Limite de Entrega: 13 de dezembro de 2022 (18h00)</i> </h3>
<br>
<h2 align="left"> <b> Descrição do Problema </b> </h2>
<p align="left"> 
  Pretende-se ladrilhar, ou seja cobrir com ladrilhos, uma dada área definida sobre um retângulo,
  delimitada por um caminho em escada, tal como ilustrado na Figura 1. A área a ladrilhar é
  definida sobre uma grelha unitária, com n linhas e m colunas. Os ladrilhos a utilizar são sempre
  quadrados com dimensões do lado múltiplas da unidade, ou seja: 1 × 1, 2 × 2, etc. Considerando que pode utilizar um número arbitrário de ladrilhos quadrados das várias dimensões,
  existem diversas configurações possíveis dos ladrilhos que permitem cobrir totalmente a área
  em questão.
  No exemplo ilustrado na Figura 1, existem 4 configurações possíveis para ladrilhar a área em
  questão. Uma configuração apenas utliza ladrilhos com dimensão 1×1, sendo que as restantes
  três utilizam ladrilhos com dimensões 1×1 e 2×2.
</p>
<br>
<div align="center">
  <img      src="https://cdn.discordapp.com/attachments/1052333643231674451/1057451840930857010/D8RtLh6s9PKpAAAAABJRU5ErkJggg.png"  alt="Figura 1">
</div>
<br>
<p align="left">
  <b> Objectivo </b> : Dadas as dimensões n e m, bem como a especificação do caminho em escada que
  delimita a área a ladrilhar, pretende-se determinar o <b> número de configurações distintas </b> de
  ladrilhos que permitem ladrilhar a referida área.
  Tal como ilustrado na Figura 2, a especificação do caminho em escada será efetuada através de
  uma sequência de n valores inteiros ci
  , para i = 1,2,...,n, que indicam o índice da coluna pela
  qual passa o caminho na i-ésima linha. Note que 0 ≤ ci ≤ m, para i = 1,2,...,n. Note também
  que ci ≥ ci−1, para i = 2,3,...,n. A Figura 3 ilustra todos os caminhos em escada possíveis
  para n = 3 e m = 3.
</p>

<h2 align="left"> <b> Input </b> </h2>
<p align="left">
  O ficheiro de entrada contendo a informação relativa ao problema a resolver, é definido da
  seguinte forma:
</p>

- uma linha contendo apenas um valor inteiro <i>n</i>, que indica o número de linhas da grelha
unitária utilizada para descrever a área a ladrilhar;

- uma linha contendo apenas um valor inteiro <i>m</i>, que indica o número de colunas da grelha
unitária utilizada para descrever a área a ladrilhar;

- <i>n</i> linhas, em que cada linha contém apenas um valor inteiro <i>c</i>, que indica o índice da
coluna pela qual o caminho em escada passa na i-ésima linha.

<h2 align="left"> <b> Output </b> </h2>
<p align="left">
  O programa deverá escrever no output uma linha contendo um único valor inteiro, que corresponderá ao número de configurações distintas de ladrilhos que permitem ladrilhar a área em
  questão. Considere que, para o caso em que o caminho em escada é definido por <i>c</i> = 0, para
  <i>i</i> = 1,2,...,n, o número de configurações é 0.
</p>
<br>
<div align="center">
  <img src="https://cdn.discordapp.com/attachments/1052333643231674451/1057452763530940477/image.png" alt="Figura 2">
</div>
<br>
<h2 align="left"> <b> Exemplos </b> </h2>
<h3 align="left"> <b> Input </b> </h3>
<p align="left"> 4 <br> 5 <br> 0 <br> 2 <br> 3 <br> 5 <br> </p>
<h3 align="left"> <b> Output </b> </h3>
<p> 4 </p>
<br>
<h3 align="left"> <b> Input </b> </h3>
<p align="left"> 3 <br> 4 <br> 4 <br> 4 <br> 4 <br> </p>
<h3 align="left"> <b> Output </b> </h3>
<p> 13 </p>
