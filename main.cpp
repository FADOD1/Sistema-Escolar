#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip> // Para formatação de médias

using namespace std;

// Função para cadastrar alunos
void cadastrarAluno()
{
  ofstream alunosFile("alunos.txt", ios::app);
  string nome, matricula, turma;

  cout << "Nome do aluno: ";
  getline(cin, nome);
  cout << "Matrícula do aluno: ";
  getline(cin, matricula);
  cout << "Turma do aluno: ";
  getline(cin, turma);

  alunosFile << matricula << "," << nome << "," << turma << endl;
  alunosFile.close();

  cout << "Aluno cadastrado com sucesso!" << endl;
}

// Função para cadastrar disciplinas
void cadastrarDisciplina()
{
  ofstream disciplinasFile("disciplinas.txt", ios::app);
  string nome, codigo;

  cout << "Nome da disciplina: ";
  getline(cin, nome);
  cout << "Código da disciplina: ";
  getline(cin, codigo);

  disciplinasFile << codigo << "," << nome << endl;
  disciplinasFile.close();

  cout << "Disciplina cadastrada com sucesso!" << endl;
}

// Função para lançar notas
void lancarNota()
{
  ofstream notasFile("notas.txt", ios::app);
  string matricula, codigoDisciplina;
  float nota;

  cout << "Matrícula do aluno: ";
  getline(cin, matricula);
  cout << "Código da disciplina: ";
  getline(cin, codigoDisciplina);
  cout << "Nota: ";
  cin >> nota;
  cin.ignore(); // Limpar o buffer

  notasFile << matricula << "," << codigoDisciplina << "," << nota << endl;
  notasFile.close();

  cout << "Nota lançada com sucesso!" << endl;
}

// Função para calcular a média de notas de um aluno
void calcularMediaAluno()
{
  ifstream notasFile("notas.txt");
  string matricula, linha;
  float somaNotas = 0, media = 0;
  int quantidadeNotas = 0;

  cout << "Digite a matrícula do aluno: ";
  getline(cin, matricula);

  while (getline(notasFile, linha))
  {
    stringstream ss(linha);
    string matriculaFile, codigoDisciplina;
    float nota;

    getline(ss, matriculaFile, ',');
    getline(ss, codigoDisciplina, ',');
    ss >> nota;

    if (matriculaFile == matricula)
    {
      somaNotas += nota;
      quantidadeNotas++;
    }
  }

  if (quantidadeNotas > 0)
  {
    media = somaNotas / quantidadeNotas;
    cout << "A média do aluno " << matricula << " é: " << fixed << setprecision(2) << media << endl;
  }
  else
  {
    cout << "Nenhuma nota encontrada para o aluno " << matricula << "." << endl;
  }

  notasFile.close();
}

// Função para consultar as notas de um aluno em todas as disciplinas
void consultarNotasAluno()
{
  ifstream notasFile("notas.txt");
  string matricula, linha;

  cout << "Digite a matrícula do aluno: ";
  getline(cin, matricula);

  cout << "Notas do aluno " << matricula << ":" << endl;

  while (getline(notasFile, linha))
  {
    stringstream ss(linha);
    string matriculaFile, codigoDisciplina;
    float nota;

    getline(ss, matriculaFile, ',');
    getline(ss, codigoDisciplina, ',');
    ss >> nota;

    if (matriculaFile == matricula)
    {
      cout << "Disciplina: " << codigoDisciplina << ", Nota: " << nota << endl;
    }
  }

  notasFile.close();
}

// Função para consultar notas de todos os alunos em uma disciplina específica
void consultarNotasDisciplina()
{
  ifstream notasFile("notas.txt");
  string codigoDisciplina, linha;

  cout << "Digite o código da disciplina: ";
  getline(cin, codigoDisciplina);

  cout << "Notas na disciplina " << codigoDisciplina << ":" << endl;

  while (getline(notasFile, linha))
  {
    stringstream ss(linha);
    string matriculaFile, codigoDisciplinaFile;
    float nota;

    getline(ss, matriculaFile, ',');
    getline(ss, codigoDisciplinaFile, ',');
    ss >> nota;

    if (codigoDisciplinaFile == codigoDisciplina)
    {
      cout << "Aluno: " << matriculaFile << ", Nota: " << nota << endl;
    }
  }

  notasFile.close();
}

// Função para gerar um relatório com todas as notas e médias dos alunos
void gerarRelatorio()
{
  ifstream alunosFile("alunos.txt");
  ifstream notasFile("notas.txt");
  ofstream relatorioFile("relatorio.txt");

  string linhaAluno, linhaNota;

  relatorioFile << "Relatório de Notas e Médias" << endl;
  relatorioFile << "=============================" << endl;

  while (getline(alunosFile, linhaAluno))
  {
    stringstream ssAluno(linhaAluno);
    string matricula, nome, turma;

    getline(ssAluno, matricula, ',');
    getline(ssAluno, nome, ',');
    getline(ssAluno, turma, ',');

    relatorioFile << "Aluno: " << nome << " (Matrícula: " << matricula << ", Turma: " << turma << ")" << endl;
    relatorioFile << "Notas:" << endl;

    float somaNotas = 0;
    int quantidadeNotas = 0;

    // Resetar o arquivo de notas para ler desde o início
    notasFile.clear();
    notasFile.seekg(0, ios::beg);

    while (getline(notasFile, linhaNota))
    {
      stringstream ssNota(linhaNota);
      string matriculaNota, codigoDisciplina;
      float nota;

      getline(ssNota, matriculaNota, ',');
      getline(ssNota, codigoDisciplina, ',');
      ssNota >> nota;

      if (matriculaNota == matricula)
      {
        relatorioFile << "Disciplina: " << codigoDisciplina << ", Nota: " << nota << endl;
        somaNotas += nota;
        quantidadeNotas++;
      }
    }

    if (quantidadeNotas > 0)
    {
      float media = somaNotas / quantidadeNotas;
      relatorioFile << "Média geral: " << fixed << setprecision(2) << media << endl;
    }
    else
    {
      relatorioFile << "Nenhuma nota registrada." << endl;
    }

    relatorioFile << "-----------------------------" << endl;
  }

  alunosFile.close();
  notasFile.close();
  relatorioFile.close();

  cout << "Relatório gerado com sucesso!" << endl;
}

// Função principal com menu
int main()
{
  int opcao;

  do
  {
    cout << "\nSistema de Gerenciamento de Notas Escolares" << endl;
    cout << "1. Cadastrar Aluno" << endl;
    cout << "2. Cadastrar Disciplina" << endl;
    cout << "3. Lançar Nota" << endl;
    cout << "4. Calcular Média de um Aluno" << endl;
    cout << "5. Consultar Notas de um Aluno" << endl;
    cout << "6. Consultar Notas por Disciplina" << endl;
    cout << "7. Gerar Relatório" << endl;
    //cout << "8. Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> opcao;
    cin.ignore(); // Limpar o buffer do cin

    switch (opcao)
    {
    case 1:
      cadastrarAluno();
      break;
    case 2:
      cadastrarDisciplina();
      break;
    case 3:
      lancarNota();
      break;
    case 4:
      calcularMediaAluno();
      break;
    case 5:
      consultarNotasAluno();
      break;
    case 6:
      consultarNotasDisciplina();
      break;
    case 7:
      gerarRelatorio();
    case 8:
      cout << "Saindo do sistema...." << endl;
      break;
    default:
      cout << "Opção inválida!" << endl;
    }
  } while (opcao != 0);

  return 0;
}
