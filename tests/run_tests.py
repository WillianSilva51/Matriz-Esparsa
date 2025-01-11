import subprocess
import difflib
import logging
import sys
import os
import time  # Importando o módulo time para medir a duração dos testes

# Configuração de logging
logging.basicConfig(filename='tests/log/test_results.log', level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# Cores ANSI
RESET = "\033[0m"
CYAN = "\033[96m"
MAGENTA = "\033[95m"
YELLOW = "\033[93m"
GREEN = "\033[92m"
RED = "\033[91m"
BLUE = "\033[94m"

# Variável para armazenar o último teste executado
last_test = None

def run_test(test_input):
    """Executa o teste e retorna a saída real."""
    try:
        # Lista todos os arquivos na pasta 'bin'
        bin_path = 'bin'
        exe_files = [f for f in os.listdir(bin_path) if f.endswith('.exe')]
        
        # Verifica se há arquivos .exe e usa o primeiro encontrado
        if not exe_files:
            raise FileNotFoundError("Nenhum arquivo .exe encontrado na pasta 'bin'.")
        
        exe_file = exe_files[0]  # Pode escolher outro método para selecionar se houver mais de um
        
        process = subprocess.Popen([os.path.join(bin_path, exe_file)], 
                                   stdin=subprocess.PIPE, 
                                   stdout=subprocess.PIPE, 
                                   stderr=subprocess.PIPE, 
                                   text=True)
        output, _ = process.communicate(test_input)
        return output.strip()
    except Exception as e:
        logging.error(f"Erro ao executar o teste: {e}")
        print(f"Erro ao executar o teste: {e}")
        return ""

def print_diff(expected, actual):
    """Imprime as diferenças entre a saída esperada e a saída real de forma visual."""
    print(MAGENTA + "------------------------------------------------")
    print(RED + "Linhas removidas: vermelho" + RESET)
    print(GREEN + "Linhas adicionadas: verde" + RESET)
    print(BLUE + "Linhas de contexto: azul" + RESET)

    if expected or actual:
        diff = difflib.unified_diff(
            expected.splitlines(keepends=True),
            actual.splitlines(keepends=True),
            fromfile='Esperado',
            tofile='Real',
            lineterm=''
        )

        print("\n" + RED + "Diferenças encontradas:\n" + RESET)

        for line in diff:
            if line.startswith('-'):
                print(RED + line + RESET)  # Linha removida
            elif line.startswith('+'):
                print(GREEN + line + RESET)  # Linha adicionada
            elif line.startswith('@'):
                print(BLUE + line + RESET)  # Linha de contexto
            else:
                print(line, end='')  # Linha não alterada
    else:
        print(RED + "Nenhuma saída esperada ou real para comparar." + RESET)

    print("\n")

def read_test_file(test_file):
    """Lê o arquivo de testes e verifica se existe e está no formato correto."""
    if not os.path.exists(test_file):
        logging.error("Arquivo de testes não encontrado.")
        print(RED + "Arquivo de testes não encontrado." + RESET)
        sys.exit(1)

    with open(test_file, 'r') as f:
        return f.read()

def parse_tests(content):
    """Analisa o conteúdo do arquivo de teste e retorna uma lista de testes com seus nomes."""
    tests = content.split('<<<<<<<< FINISH')
    parsed_tests = []

    for test in tests:
        if not test.strip():
            continue

        lines = test.strip().splitlines()
        insert_line = next((line for line in lines if line.startswith('>>>>>>>> INSERT')), None)

        if insert_line:
            # Extrai o nome do teste após ">>>>>>>> INSERT"
            test_name = insert_line.split(' ')[-1]  
            # Prepara o corpo do teste
            test_body = '\n'.join(lines).strip()
            parsed_tests.append((test_name, test_body))

    return parsed_tests

def generate_report(passed, total):
    """Gera um relatório de resultados dos testes."""
    with open('tests/log/test_report.txt', 'w') as f:
        f.write("========================================\n")
        f.write("           Relatório de Testes         \n")
        f.write("========================================\n")
        f.write(f"Total de testes: {total}\n")
        f.write(f"Testes passados: {passed}\n")
        f.write("========================================\n")
    print(CYAN + "Relatório de testes salvo em 'test_report.txt'" + RESET)

def execute_test(test):
    """Executa um único teste e exibe o resultado."""
    test_name, test_body = test
    sections = test_body.split('======== EXPECT')
    test_input = sections[0].strip().replace('>>>>>>>> INSERT ' + test_name, '').strip()  # Remove o comando e o nome
    expected_output = sections[1].strip() if len(sections) > 1 else ""

    start_time = time.time()  # Marca o tempo de início
    actual_output = run_test(test_input)
    elapsed_time = time.time() - start_time  # Calcula o tempo de execução

    last_test = (test_input, expected_output, actual_output)

    if actual_output == expected_output:
        logging.info("✅ Teste passou: " + test_name + f" (Duracao: {elapsed_time:.2f}s)")
        print(GREEN + "✅ Teste passou!" + RESET)
    else:
        logging.error("❌ Teste falhou: " + test_name + f" (Duracao: {elapsed_time:.2f}s)")
        print(YELLOW + f"Teste executado: {test_name}" + RESET)
        print(GREEN + test_input + RESET + "\n")
        print(RED + "❌ Teste falhou!" + RESET)
        print(BLUE + "Saída esperada:\n" + expected_output + RESET)
        print(RED + "\nSaída real:\n" + actual_output + "\n" + RESET)
        print_diff(expected_output, actual_output)
    return actual_output == expected_output

def run_all_tests(tests):
    """Executa todos os testes fornecidos e retorna o resumo."""    
    total = len(tests)
    passed = 0

    logging.info(f"Iniciando a execucao de {total} testes.")

    for index, test in enumerate(tests):
        print(MAGENTA + "------------------------------------------------")
        print(CYAN + f"Iniciando o teste {index + 1}/{total}..." + RESET)
        print(MAGENTA + "------------------------------------------------" + RESET)
        result = execute_test(test)
        if result:
            passed += 1

    print(CYAN + f"\nTotal de testes: {total}, Testes passados: {passed}" + RESET)
    generate_report(passed, total)
    logging.info(f"Execucao concluida: {passed}/{total} testes passaram.\n")

def run_specific_test(tests):
    """Executa um teste específico com base na escolha do usuário."""    
    test_number = input(YELLOW + "Digite o número do teste que deseja executar: " + RESET)
    if test_number.isdigit() and 1 <= int(test_number) <= len(tests):
        execute_test(tests[int(test_number) - 1])
        logging.info(f"Execucao concluida!\n")
    else:
        print(RED + "Número de teste inválido." + RESET)

def show_help():
    """Mostra as instruções de uso."""    
    print(CYAN + "Instruções de Uso:")
    print("1. Escolha uma opção no menu digitando o número correspondente.")
    print("2. Siga as instruções na tela para executar os testes.")
    print("3. Para sair, escolha a opção de sair no menu.")
    print(RESET)

def show_menu():
    """Mostra o menu de opções ao usuário de forma interativa."""    
    print(CYAN + "Escolha uma opção:")
    print("1. Executar todos os testes")
    print("2. Executar um teste específico")
    print("3. Ajuda")
    print("4. Sair")

def main():
    """Função principal que gerencia a execução dos testes."""    
    print(CYAN + "========================================")
    print("           Iniciando os Testes          ")
    print("========================================\n")

    test_file = input(YELLOW + "Digite o caminho do arquivo de testes (padrão: tests/cases.tio): " + RESET) or 'tests/cases.tio'
    content = read_test_file(test_file)
    tests = parse_tests(content)

    while True:
        show_menu()
        choice = input(YELLOW + "Digite sua escolha: " + RESET)

        if choice == '1':
            run_all_tests(tests)
        elif choice == '2':
            run_specific_test(tests)
        elif choice == '3':
            show_help()
        elif choice == '4':
            print(CYAN + "Saindo do programa..." + RESET)
            break
        else:
            print(RED + "Escolha inválida. Tente novamente." + RESET)

    print(CYAN + "========================================")
    print("          Testes Concluídos            ")
    print("========================================")

if __name__ == "__main__":
    main()
