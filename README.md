# Computação Gráfica UM 2024 - Motor Gráfico

Pretende-se implementar um motor gráfico simples que consiga representar várias figuras geométricas tridimensionais, usando a linguagem de programação **[C++](https://cplusplus.com/)**.

O projeto será baseada na interface gráfica **[OpenGL](https://www.opengl.org/)** através da utilização da biblioteca **[GLUT](https://www.opengl.org/resources/libraries/glut/)**.

A implementação será divida em **cinco fases**, sendo a última fase utilizada para a implementação de extras que se considerem interessantes para o bom funcionamento do projeto.

A solução criada deverá, ainda, ser constituída por um **[Gerador de Primitivas](#gerador-de-primitivas)** e um **[Motor Gráfico](#motor-gráfico)**, que deverão, como os nomes indicam, gerar e representar primitivas geométricas, respetivamente, dada uma certa configuração.

---

# Gerador de primitivas

O gerador de primitivas geométricas será responsável pela geração de primitivas e suas propriedades, tal que, o único trabalho que o **[Motor Gráfico](#motor-gráfico)** possa ter neste contexto seja o de representar estas figuras.

## Gerador de figuras (Fase 1)

Numa primeira solução, define-se o simples objetivo de geração única dos vértices necessários para a representação dos modelos geométricos.

Estes vértices deverão ser construídos e armazenados num documento com extensão `.3d` tal que possam ser lidos pelo **[Motor Gráfico](#motor-gráfico)** de forma a gerarem figuras geométricas.

### Primitivas geométricas

Foi definida, portanto, uma lista de primitivas geométricas que se pretendem implementar nesta fase inicial.

- [x] Plano (Plane)
- [x] Cubo (Box)
- [x] Esfera (Sphere)
- [x] Cone (Cone)
- [ ] Círculo (Circle)
- [ ] Cilindro (Cylinder)
- [ ] Torus

Cada uma destas figuras deverá, no ato da sua criação, receber determinados parâmetros que deverão especificar a sua estrutura.

| Primitiva Geométrica | Comprimento      | Raio             | Altura           | Divisões         | Fatias           |Pilhas            |
|----------------------|------------------|------------------|------------------|------------------|------------------|------------------|
| Plano                |:white_check_mark:|:x:               |:x:               |:white_check_mark:|:x:               |:x:               |
| Cubo                 |:white_check_mark:|:x:               |:x:               |:white_check_mark:|:x:               |:x:               |
| Esfera               |:x:               |:white_check_mark:|:x:               |:x:               |:white_check_mark:|:white_check_mark:|
| Cone                 |:x:               |:white_check_mark:|:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|
| Círculo              |:x:               |:white_check_mark:|:x:               |:x:               |:white_check_mark:|:x:               |
| Cilindro             |:x:               |:white_check_mark:|:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|
| Torus                |:white_check_mark:|:white_check_mark:|:x:               |:x:               |:white_check_mark:|:white_check_mark:|

Estas primitivas deverão, então, ser geradas através do comando `generator` fornecendo a este os argumentos necessários (figura pretendida, propriedades da figura e ficheiro de armazenamento).

O comando será dado, portanto, por `$ generator primitiva length divisions ... path/to/file.3d`, como é possível observar nos seguintes exemplos:

- ``` 
  # Gerar um plano de comprimento 1 com 3 divisões
  $ generator plane 1 3 plane.3d 
  ```
- ``` 
  # Gerar um cubo de lado 2 com 3 divisões em cada face
  $ generator box 2 3 box.3d 
  ```
- ``` 
  # Gerar um cone de raio 1, altura 5, dividido em 4 fatias
  # e 3 montes
  $ generator cone 1 5 4 3 cone.3d 
  ```
- ``` 
  # Gerar uma esfera de raio 1, dividida em 10 fatias e
  # 10 montes
  $ generator sphere 1 10 10 sphere.3d 
  ```
- ``` 
  # Gerar um circulo de raio 3, dividida em 10 fatias
  $ generator circle 3 10 circle.3d 
  ```
- ``` 
  # Gerar um cilindro de raio 3 e 6 de altura, dividido em
  # 10 fatias e 2 montes
  $ generator cylinder 3 6 10 2 cylinder.3d 
  ```
- ``` 
  # Gerar um torus de comprimento 1 e 2 de raio, dividido em
  # 10 fatias e 2 montes
  $ generator torus 1 2 10 2 torus.3d 
  ```

---

### Formato do ficheiro .3d

Para armazenar estas estruturas de forma eficaz e íntegra foi definido, ainda, um formato de ficheiro capaz de guardar todos os vértices e faces que constituem uma primitiva.

De forma a ter uma leitura rápida e eficaz, decidiu-se usar uma arquitetura binária, facilitando o armazenamento e leitura das variáveis flutuantes devido a não necessidade de fazer a conversão das mesmas para um formato de texto.

Os valores dos pontos serão armazenados, portanto, de forma contínua, sendo que a cada três valores flutuantes existe um ponto, e a cada três pontos (ou nove valores) existe uma face. O conjunto de pontos guardados nestes ficheiros irá, portanto, definir um conjunto de faces que, por sua vez, definirão uma primitiva.

A quantidade de valores flutuantes será, portanto, sempre múltipla de três.

Esta estrutura pode ser vista, de forma simplificada e considerando os espaços como inexistentes, da seguinte forma:

```
0.0000 0.0000 0.0000 (em binário) | Face1
...Ponto2...                      | Face1
...Ponto3...                      | Face1
...Ponto4...                      | Face2
...Ponto5...                      | Face2
...Ponto6...                      | Face2
...Ponto7...                      | Face3
...                               ...
...
```

Ou seja, por exemplo, um ficheiro que define uma face, seria definido da seguinte forma.

```
0.0000 0.0000 0.0000
1.0000 0.0000 0.0000
0.0000 0.0000 1.0000
(tudo em formato binário)
```

## Gerador de figuras em Bezier Patches (Fase 3)

Para além das primitivas pré-definidas, ainda se pretende que seja possível gerar figuras através de Bezier Patches.

O objetivo destas figuras é representar superfícies curvas através de um conjunto de pontos e um nível de `Tesselation`, que fará o objeto mais curvo quanto maior for.

Assim sendo, o gerador de figuras deverá, agora, aceitar como parâmetros um ficheiro contendo os tais pontos pretendidos para a definição da superfície, e um argumento que indique o nível de `Tesselation` que deverá ser usado para a figura. Como, por exemplo:

``` 
# Gerar uma figura baseada em patches de Bezier
# com nível de Tesselation 16
$ generator patch teapot.patch 16 teapot.3d
```

Os ficheiros que sustentam esta arquitetura de Bezier, deverão, portanto, ser definidos da seguinte forma:

```
2 <- Número de patches
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 # 16 pontos
# indíces dos pontos patch #1
3, 16, 17, 18, 7, 19, 20, 21, 11, 22, 23, 24, 15, 25, 26, 27
# indíces dos pontos patch #2
28 <- Número de pontos de controlo
1.4, 0, 2.4 <- Ponto de controlo 0
1.4, -0.784, 2.4 <- Ponto de controlo 1
0.784, -1.4, 2.4 <- Ponto de controlo 2
0, -1.4, 2.4
1.3375, 0, 2.53125
1.3375, -0.749, 2.53125
0.749, -1.3375, 2.53125
0, -1.3375, 2.53125
1.4375, 0, 2.53125
1.4375, -0.805, 2.53125
0.805, -1.4375, 2.53125
0, -1.4375, 2.53125
1.5, 0, 2.4
1.5, -0.84, 2.4
0.84, -1.5, 2.4
0, -1.5, 2.4
-0.784, -1.4, 2.4
-1.4, -0.784, 2.4
-1.4, 0, 2.4
-0.749, -1.3375, 2.53125
-1.3375, -0.749, 2.53125
-1.3375, 0, 2.53125
-0.805, -1.4375, 2.53125
-1.4375, -0.805, 2.53125
-1.4375, 0, 2.53125
-0.84, -1.5, 2.4 <- Ponto de controlo 26
-1.5, -0.84, 2.4 <- Ponto de controlo 27
```

## Gerador de figuras complementares (Extra)

Devido ao insucesso na implementação de algumas figuras geométricas pretendidas para a fase anterior, pretende-se corrigir essa falha e implementar, agora, as figuras em falta, tal como algumas extra.

Por questões da não necessidade da repetição, as figuras continuarão definidas na primeira fase, sendo aqui indicadas quais foram implementadas e em que fase.

### Fase 2

Foram implementadas (ou pretendia-se implementar) as seguintes primitivas geométricas:

- Cilindro (Cylinder)
- Círculo (Circle)
- Torus

---

# Motor Gráfico

O motor gráfico, em contraste com o gerador de primitivas, apenas possuirá o trabalho de representar as primitivas anteriormente geradas.

Será necessário respeitar as propriedades estabelecidas pelos ficheiros `.3d` gerados, e pelo documento `XML` que estabelece as regras e transformações do cenário.

## Representação de figuras (Fase 1)

Numa primeira fase, apenas será necessária haver preocupação na representação das figuras já estabelecidas pelo **[Gerador de Primitivas](#gerador-de-primitivas)**, assim como da criação da câmera e janela que as vai visualizar.

Dessa forma, deverão ser tidas em conta algumas etiquetas `XML` para a criação de representações nesta primeira etapa.

| Etiqueta | Definição                                     | Lista de propriedades | Etiqueta Mãe |
|----------|-----------------------------------------------|-----------------------|--------------|
|world     | Define o contexto do cenário                  |:x:                    |:x:           |
|window    | Define as propriedades da janela de exibição  | width, height         | world        |
|camera    | Define a uma câmera para visualização         | (sub-etiquetas)       | world        |
|position  | Define a posição da câmera no cenário         | x, y, z               | camera       |
|lookAt    | Define o ponto de "foco" da câmera            | x, y, z               | camera       |
|up        | Define o vetor "up" da câmera                 | x, y, z               | camera       |
|projection| Define as propriedades de projeção da câmera  | fov, near, far        | camera       |
|group     | Define um grupo de representação              |:x:                    | world        |
|models    | Define um grupo de objetos para representação |:x:                    | group        |
|model     | Define um objeto singular para representação  | file                  | models       |

Estas etiquetas deverão, então, definir uma configuração de um cenário, que deverá ser lida pelo motor e representada no ecrã de acordo. Um exemplo de uma configuração com esta hierarquia pode, portanto, ser o seguinte.

```
<world>
    <window width="512" height="512" />
    <camera>
        <position x="3" y="2" z="1" />
        <lookAt x="0" y="0" z="0" />
        <up x="0" y="1" z="0" />
        <projection fov="60" near="1" far="1000" />
    </camera>
    <group>
        <models>
            <model file="plane.3d" />
            <model file="cone.3d" />
        </models>
    </group>
</world>
```

A leitura de uma configuração deverá ser feita numa única vez, sendo que a sua informação deverá ser armazenada em estruturas de dados que consiga criar as representações pretendidas.

Este motor simples terá de originar, portanto, figuras semelhantes às seguintes.

![Representação visual das primitivas](imgs/f1visual.png)

## Transformações de figuras (Fase 2)

Implementado o básico necessário para a representação de modelos no ecrã, pretende-se agora puder mover através de escalas, translações ou rotações estes vários objetos pelo cenário.

Para tal, será necessário que a configuração `XML` aceite novos tipos de etiquetas, as etiquetas de translação.

Estas estruturas deverão estar contidas dentro de um grupo e, portanto, aplicar a todos os objetos contidos nesse mesmo grupo as transformações enunciadas.

Todas as transformações deverão estar, ainda, contidas dentro da secção `transform`, e não se deverá repetir o mesmo tipo de transformação dentro de um mesmo grupo.

Deverá, também, ser possível a criação de grupos dentro de grupos, sendo que um sub-grupo herda as transformações do grupo acima.

Assim sendo, adicionam-se as seguintes propriedades à tabela:
| Etiqueta | Definição                                     | Lista de propriedades | Etiqueta Mãe |
|----------|-----------------------------------------------|-----------------------|--------------|
|world     | Define o contexto do cenário                  | axis                  |:x:           |
|window    | Define as propriedades da janela de exibição  | x, y, name            | world        |
|group     | Define um grupo de representação              |:x:                    | world, group |
|transform | Define um grupo de transformações             |:x:                    | group        |
|translate | Define uma translação de objetos              | x, y, z               | transform    |
|rotate    | Define uma rotação de objetos                 | angle, x, y, z        | transform    |
|scale     | Define uma escala de objetos                  | x, y, z               | transform    |

> IMPORTANTE: A ordem das transformações importa!

Pretende-se obter, portanto, uma maquete do sistema solar, com os planetas, estrelas e luas definidas numa hierarquia de grupos.

## Animação de figuras (Fase 3)

Implementadas e definidas as transformações estáticas, o objetivo é, agora, expandir estas transformações de forma a criar a possibilidade de animar as figuras.

Para tal, pretende-se permitir às translações e rotações que sejam definidas com propriedades de tempo.

Uma translação animada deverá, portanto, ser definida por um conjunto de quatro ou mais pontos que definem uma curva de Catmull-Rom e pelo tempo que uma figura demora a percorrer a curva. Os pontos deverão estar no referencial "atual" (no caso de já terem havido translações no grupo anterior).

Uma rotação animada, em constrate, deverá ser definida como uma rotação normal, diferenciando-se, apenas, no ângulo, que poderá agora ser definido como um intervalo de tempo que a figura demorará a fazer uma rotação completa.

Em notação `XML` realçam-se, então, as segunites mudanças:
| Etiqueta | Definição                                     | Lista de propriedades | Etiqueta Mãe |
|----------|-----------------------------------------------|-----------------------|--------------|
|translate | Define uma translação de objetos              | x, y, z, time, align   | transform    |
|rotate    | Define uma rotação de objetos                 | angle, time, x, y, z   | transform    |
|point     | Define um ponto da curva de Catmull-Rom       | x, y, z                | translate    |

Para além disto, o desenho das figuras deverá ser, agora, implementado por VBO's, constrastando como o modo imediato usado até agora.

Pretende-se, agora, obter uma maquete do sistema solar com um cometa animado através de curvas de Catmull-Rom. O cometa deverá, ainda, ser definido por Bezier patches.

---

# Estrutura da solução

## Fase 1

Definidos os objetivos da fase inicial, é proposta uma solução que baseia a sua estrutura nas hierarquias definidas anteriormente, considerando ambas as hierarquias propostas no **[Gerador](#gerador-de-primitivas)** e no **[Motor](#motor-gráfico)**.

Devido à necessidade de leitura e armazenamento da estruturação dos vértices e das faces definidas para cada primitiva nos seus ficheiros, a estrutura adotada será, de certa forma, semelhante para o **[Gerador](#gerador-de-primitivas)** e para o **[Motor](#motor-gráfico)**, partilhando um ramo idêntico em ambas as arquiteturas.

A implementação será, porém, diferente, já que não existe a necessidade de o **[Gerador](#gerador-de-primitivas)** saber ler ou representar primitivas, tal como não existe a necessidade do **[Motor](#motor-gráfico)** saber escrever ou gerar certos tipos de primitivas.

Desta forma, são propostos os seguintes **Modelos de Domínio**, que tencionam descrevar esta proposta de forma mais detalhada.

### Gerador de Primitivas

```mermaid
graph TD
    Primitive-- tem (*) -->Face
    Face-- tem (3) -->Point
    Plane-- é uma -->Primitive
    Box-- é uma -->Primitive
    Sphere-- é uma -->Primitive
    Cone-- é uma -->Primitive
    Generator-- cria -->Primitive
```

Este modelo representa, portanto de certa forma, o processo da construção de primitivas por parte do gerador.

O gerador irá criar, portanto, uma primitiva, constítuida por faces que são constituídas por pontos, que pode ser ou um plano, ou uma caixa, etc...

O objetivo é implementar o ponto de forma matricial, tal que lhe sejam possível aplicar transformações sem necessidade de um grande poder computacional, reutilizando a mesma matriz no caso de, por exemplo, se querer fazer a mesma transformação em vários pontos ou mesmo numa primitiva inteira.

Assim sendo, e usando esta ideologia de transformações únicas numa primitiva, o processo de construção dos modelos deverá ser baseado neste conceito de criação de sub-primitivas que irão constituir uma primitiva maior.

### Motor Gráfico

```mermaid
graph TD
    Primitive-- tem (*) -->Face
    Face-- tem (3) -->Point
    Group-- tem (*) -->Primitive
    World-- tem -->Window
    World-- tem -->Camera
    World-- tem -->Group
    Engine-- representa -->World
```

Já no lado do **[Motor](#motor-gráfico)**, a estrutura das primitivas é semelhante, porém a implementação não deverá fazer uso do formato matricial ou das transformações anteriormente discutidas.

A leitura das faces e pontos deverá, portanto, ser mais que suficiente para a boa representação das figuras pretendidas.

Ainda existirá um novo conjunto de estruturas, contidas num cenário (mundo), que ajudarão a definir a propriedades da cena.

A câmera deverá conseguir definir o comportamento e as propriedades da própria câmera do cenário, assim como a janela deverá definir a janela que irá ser usada para a representação.

O grupo deverá conter, então, o conjunto de primitivas que se pretende representar.

Todas estas estruturas deverão ser capaz de, dadas estruturas `XML`, lerem e adaptarem os conteúdos dos ficheiros pretendido às suas propriedades, de forma à representação do cenário final apenas necessitar destas estruturas em memória.

## Fase 2

### Motor Gráfico

```mermaid
graph TD
    Primitive-- tem (*) -->Face
    Face-- tem (3) -->Point
    Group-- tem (*) -->Primitive
    Group-- tem (*) -->Group
    Group-- tem (3) -->Transform
    Translate-- é uma -->Transform
    Scale-- é uma -->Transform
    Rotate-- é uma -->Transform
    World-- tem -->Window
    World-- tem -->Camera
    World-- tem -->Group
    Engine-- representa -->World
```
Para a implementação desta fase, o modelo do **[Motor](#motor-gráfico)** foi extendido e, rapidamente, são percétiveis e justificáveis as modificações aplicadas de forma a incluir os requisitos para fase que se pretende implementar.

Um grupo passa, portanto, a ter a possibilidade de ter mais grupos em si própria, utilizando, de certa forma, uma estratégia recursiva para implementar o conceito de sub-grupo.

Para além disso, também foi adicionada a possibilidade de um grupo ter três ou menos transformações. Deverá ser garantido que o tipo destas transformações não se repita, e que todas as tranformações de um grupo sejam, ainda, aplicadas a todos os seus sub-grupos.

Todos os tipos de transformações deverão, também, ser sub-classes de transformação, já que todas partilharão propriedades semelhantes para a sua aplicação e estrutura.

## Fase 3

```mermaid
graph TD
    Primitive-- tem (*) -->Face
    Face-- tem (3) -->Point
    Group-- tem (*) -->Primitive
    Group-- tem (*) -->Group
    Group-- tem (3) -->Transform
    Translate-- é uma -->TransformEstática
    Scale-- é uma -->TransformEstática
    Rotate-- é uma -->TransformEstática
    TranslateAnimada-- é uma -->TransformAnimada
    RotateAnimada-- é uma -->TransformAnimada
    TransformAnimada-- é uma -->Transform
    TransformEstática-- é uma -->Transform
    World-- tem -->Window
    World-- tem -->Camera
    World-- tem -->Group
    Engine-- representa -->World
```

```mermaid
graph TD
    Primitive-- tem (*) -->Face
    Face-- tem (3) -->Point
    Plane-- é uma -->Primitive
    Box-- é uma -->Primitive
    Sphere-- é uma -->Primitive
    Cone-- é uma -->Primitive
    Generator-- cria -->Primitive
    Generator-- cria -->Patch
    Patch-- cria -->Primitive
    Patch-- tem (*) -->Batch
    Patch-- tem (*) -->Point
```

---

# Utilização dos scripts

Foram ainda criados scripts de compilação e execução do projeto que podem ser encontrados na diretoria `scripts`. Estes scripts podem ser utilizados para aplicar a configuração do `CMakeLists.txt` (`configure.sh`) e para a compilação da solução (`build.sh`).

Estes precisam, no entanto, de permissão para serem executados pelo que deverão ser executados da seguinte forma:

```
sudo ./scripts/script.sh
```

ou, para uma solução mais permanente:

```
sudo chmod +x scripts/script.sh
./scripts/script.sh
```

