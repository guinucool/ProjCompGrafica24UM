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

- [ ] Plano
- [ ] Cubo
- [ ] Esfera
- [ ] Cone
- [ ] Círculo
- [ ] Cilindro

Cada uma destas figuras deverá, no ato da sua criação, receber determinados parâmetros que deverão especificar a sua estrutura.

| Primitiva Geométrica | Comprimento      | Raio             | Divisões         | Fatias           | Pilhas           |
|----------------------|------------------|------------------|------------------|------------------|------------------|
| Plano                | :white_check_mark: |:x:               |:white_check_mark:|:x:               |:x:               |
| Cubo                 |:white_check_mark:|:x:               |:white_check_mark:|:x:               |:x:               |
| Esfera               |:x:               |:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|
| Cone                 |:x:               |:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|
| Círculo              |:x:               |:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|
| Cilindro             |:x:               |:white_check_mark:|:x:               |:white_check_mark:|:white_check_mark:|


---

# Motor Gráfico

`$>generator plane length divisions file.ext`