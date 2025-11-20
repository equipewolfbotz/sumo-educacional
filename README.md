# Repositório do Sumô Educacional da Wolfbotz
Pasta dedicada ao Projeto de Extensão Sumô Educacional

Passo a passo de como executar o projeto:

## 1 - Vá até o diretório desejado ou crie uma pasta nova para os projetos
  ### No Linux:
    cd nome-da-pasta
    mkdir nome-da-pasta

## 2 - Clonar o repositório
    git clone https://github.com/equipewolfbotz/sumo.git
    cd sumo

## 3 - Gerenciar Branches
  ### 3.1 Verificar a branch atual:

    git branch

  ### 3.2 Trocar de branch

    git switch <nome-da-branch>

  ### 3.3 Receber alterações de uma branch remota
    git pull origin <nome-da-branch>

  ### 3.4 Enviar alterações para a branch remota
    git add .
    git commit -m "Descrição das alterações"
    git push origin <nome-da-branch>
