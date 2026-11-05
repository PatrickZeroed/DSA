#include <iostream>
#include <stdio.h>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>

const int MAX_OCORRENCIAS = 100;
const int TOTAL_CATEGORIAS = 5;
const std::string CATEGORIAS[TOTAL_CATEGORIAS] = {"Buraco", "Iluminação", "Lixo", "Enchente", "Outros"};

struct ocorrencia
{
    int categoria;
    std::string bairro;
    std::string descricao;
    bool resolvido;
};

int lerCategoria(const std::string &mensagem, int minimo, int maximo)
{
    int valor;

    while (true)
    {
        std::cout << mensagem;
        std::cin >> valor;
        if (valor >= minimo && valor <= maximo)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }

        std::cout << "Valor invalido. Digite entre " << minimo << " e " << maximo << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string paraMinusculo(std::string str)
{
    for (int i = 0; i < (int)str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

int escolherCategoria()
{
    std::cout << "\nCategorias:\n";

    for (int i = 0; i < TOTAL_CATEGORIAS; i++)
    {
        std::cout << i + 1 << ". " << CATEGORIAS[i] << std::endl;
    }

    return lerCategoria("Escolha a categoria (1-5): ", 1, TOTAL_CATEGORIAS) - 1;
}

void exibirOcorrencia(const ocorrencia &o, int numero)
{
    std::cout << numero << ". [" << CATEGORIAS[o.categoria] << "] - Bairro: "
              << o.bairro << " - Descricao: " << o.descricao << " - Situacao: "
              << (o.resolvido ? "Resolvido\n" : "Pendente\n");
}

void cadastrarOcorrencia(ocorrencia ocorrencias[], int &qtd)
{
    if (qtd >= MAX_OCORRENCIAS)
    {
        std::cout << "Limite de ocorrencias atingido!" << std::endl;
        return;
    }

    ocorrencia novaOcorrencia;
    novaOcorrencia.categoria = escolherCategoria();

    do
    {
        std::cout << "Digite o bairro da ocorrencia: ";
        std::getline(std::cin, novaOcorrencia.bairro);
        if (novaOcorrencia.bairro.empty())
        {
            std::cout << "O bairro está vazio, por favor, digite novamente.\n";
        }
    } while (novaOcorrencia.bairro.empty());

    std::cout << "Descricao da ocorrencia: ";
    std::getline(std::cin, novaOcorrencia.descricao);

    novaOcorrencia.resolvido = false;

    ocorrencias[qtd] = novaOcorrencia;
    qtd++;
    std::cout << "Ocorrencia cadastrada com sucesso!\n";
}

void listarOcorrencia(const ocorrencia ocorrencias[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    int categoria = escolherCategoria();
    bool encontrou = false;
    for (int i = 0; i < qtd; i++)
    {
        if (ocorrencias[i].categoria == categoria)
        {
            exibirOcorrencia(ocorrencias[i], i + 1);
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        std::cout << "Nenhuma ocorrencia encontrada para a categoria selecionada.\n";
    }
}

void buscarPorCategoria(const ocorrencia ocorrencias[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    int categoria = escolherCategoria();
    bool encontrou = false;
    for (int i = 0; i < qtd; i++)
    {
        if (ocorrencias[i].categoria == categoria)
        {
            exibirOcorrencia(ocorrencias[i], i + 1);
            encontrou = true;
        }
    }

    if (!encontrou)
    {
        std::cout << "Nenhuma ocorrencia encontrada para a categoria selecionada.\n";
    }
}

void buscarPorBairro(const ocorrencia ocorrencia[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    std::string busca;
    std::cout << "Bairro/Regiao: ";
    std::getline(std::cin, busca);
    busca = paraMinusculo(busca);

    bool encontrou = false;
    for (int i = 0; i < qtd; i++)
    {
        if (paraMinusculo(ocorrencia[i].bairro) == busca)
        {
            exibirOcorrencia(ocorrencia[i], i + 1);
            encontrou = true;
        }
    }
    if (!encontrou)
    {
        std::cout << "Nenhuma ocorrencia encontrada para o bairro/regiao selecionado.\n";
    }
}

void gerarEstatisticas(const ocorrencia ocorrencias[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    int contagemCategorias[TOTAL_CATEGORIAS] = {0};
    int resolvidas = 0;

    for (int i = 0; i < qtd; i++)
    {
        contagemCategorias[ocorrencias[i].categoria]++;
        if (ocorrencias[i].resolvido)
        {
            resolvidas++;
        }
    }

    std::cout << "\nEstatisticas:\n";
    std::cout << "Total de ocorrencias: " << qtd << '\n';

    int indiceMaior = 0;
    for (int i = 0; i < TOTAL_CATEGORIAS; i++)
    {
        double percentual = (double)contagemCategorias[i] / qtd * 100;
        std::cout << CATEGORIAS[i] << ": " << std::fixed << std::setprecision(2) << contagemCategorias[i] << " ocorrencias (" << percentual << "%)\n";
        if (contagemCategorias[i] > contagemCategorias[indiceMaior])
        {
            indiceMaior = i;
        }
    }

    std::cout << "Categoria com mais ocorrencias: " << CATEGORIAS[indiceMaior] << '\n';

    int maiorQtd = 0;
    std::string bairroMaior = "";
    for (int i = 0; i < qtd; i++)
    {
        int contador = 0;
        for (int j = 0; j < qtd; j++)
        {
            if (paraMinusculo(ocorrencias[j].bairro) == paraMinusculo(ocorrencias[i].bairro))
            {
                contador++;
            }
        }
        if (contador > maiorQtd)
        {
            maiorQtd = contador;
            bairroMaior = ocorrencias[i].bairro;
        }
    }

    std::cout << "Bairro/Regiao com mais ocorrencias: " << bairroMaior << " (" << maiorQtd << " ocorrencias)\n";
    std::cout << "Total de ocorrencias resolvidas: " << resolvidas << '\n';
    std::cout << "Total de ocorrencias pendentes: " << qtd - resolvidas << '\n';
}

void marcarComoResolvida(ocorrencia ocorrencias[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    listarOcorrencia(ocorrencias, qtd);
    int numero = lerCategoria("Numero da ocorrencia resolvida: ", 1, qtd);
    ocorrencias[numero - 1].resolvido = true;
    std::cout << "Ocorrencia marcada como resolvida.\n";
}

void ordenarPorBairro(ocorrencia ocorrencias[], int qtd)
{
    if (qtd == 0)
    {
        std::cout << "Nenhuma ocorrencia cadastrada.\n";
        return;
    }

    for (int i = 0; i < qtd - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < qtd; j++)
        {
            if (paraMinusculo(ocorrencias[j].bairro) < paraMinusculo(ocorrencias[menor].bairro))
            {
                menor = j;
            }
        }
        ocorrencia auxiliar = ocorrencias[i];
        ocorrencias[i] = ocorrencias[menor];
        ocorrencias[menor] = auxiliar;
    }
    std::cout << "Ocorrencias ordenadas por bairro/regiao.\n";
    listarOcorrencia(ocorrencias, qtd);
}

int main()
{
    ocorrencia ocorrencias[MAX_OCORRENCIAS];
    int qtd = 0;
    int opcao;

    do
    {
        std::cout << "\nMCPU - Mapa Colaborativo de Problemas Urbanos\n";
        std::cout << "1. Cadastrar ocorrencia\n";
        std::cout << "2. Listar ocorrencias\n";
        std::cout << "3. Buscar por categoria\n";
        std::cout << "4. Buscar por bairro/regiao\n";
        std::cout << "5. Estatisticas\n";
        std::cout << "6. Ordenar por bairro\n";
        std::cout << "7. Marcar ocorrencia como resolvida\n";
        std::cout << "0. Sair\n";
        opcao = lerCategoria("Escolha uma opcao: ", 0, 8);

        switch (opcao)
        {
        case 1:
            cadastrarOcorrencia(ocorrencias, qtd);
            break;
        case 2:
            listarOcorrencia(ocorrencias, qtd);
            break;
        case 3:
            buscarPorCategoria(ocorrencias, qtd);
            break;
        case 4:
            buscarPorBairro(ocorrencias, qtd);
            break;
        case 5:
            gerarEstatisticas(ocorrencias, qtd);
            break;
        case 6:
            ordenarPorBairro(ocorrencias, qtd);
            break;
        case 7:
            marcarComoResolvida(ocorrencias, qtd);
            break;
        case 0:
            std::cout << "Saindo do programa...\n";
            break;
        }

    } while (opcao != 0);

    return 0;
}