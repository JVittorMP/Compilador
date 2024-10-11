# Compilador

### Compilador para um subconjunto da linguagem Java implementado em C++.

O compilador em questão foi implementado utilizando a solução de software
para geração de analisadores léxicos *FLEX (Fast Lexical Analyser)*.

O problema do compilador foi modelado através de algumas ténicas,
dentre elas o uso de *Análise Sintática Recursiva Descendente*, a qual permitiu
simplificar o processo de análise e construção da *Árvore de Análise Sintática*
(SAT), além da construção de uma *Árvore Sintática Abstrata* (AST) a partir da SAT,
o que simplificou a estrutura do código e facilitou as etapas de Análise Semântica
e Geração de Código ao apresenta-lo de maneira transparente.

### Análise Léxica com Flex

O pacote do FLEX pode ser instalado em distribuições Unix através do comando:

    sudo apt-get install flex

A sintaxe para o arquivo de geração do analisador léxico está contida na seguinte
página WEB:
<a href="https://westes.github.io/flex/manual/index.html#SEC_Contents" target="_blank">Lexical Analysis With Flex</a>.
Essa regras de correspondência devem ser implementadas no arquivo **lexer.l**, o qual deve ser compilado
através do seguinte comando:

    flex lexer.l

A execução da instrução supracitada é responsável pela geração do arquivo **lex.yy.c**,
que conterá o módulo do analisador léxico (inicialmente atribuído à assinatura da função
**::yylex**) que devolve uma lista contendo os tokens identificados a partir de uma
entrada armazenada em arquivo.

Essa sequência de tokens será utilizada durante todo o processo de compilação
em diferentes formas de acordo com as etapas de análise sintática e semântica.