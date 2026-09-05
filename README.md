# Privacy Log Cleaner

> **Conteúdo Educativo** - Ferramenta avançada de estudo sobre anti-forensics e limpeza de logs de privacidade no Windows.

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=cplusplus&logoColor=white)](#)
[![Windows](https://img.shields.io/badge/Windows-10/11-0078D4?style=flat-square&logo=windows&logoColor=white)](#)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](#)

## Sobre o Projeto

O **Privacy Log Cleaner** é uma ferramenta C++ desenvolvida para fins de **pesquisa e educação em segurança**, que demonstra como o Windows armazena logs de atividade do usuário e como esses dados podem ser removidos.

### Objetivo Educativo

- Entender a estrutura de diretórios de logs do Windows
- Estudar como o sistema registra atividades do usuário
- Analisar técnicas de anti-forensics
- Compreender a importância da privacidade digital

### ⚠️ Aviso Importante

> Este projeto é exclusivamente para fins educacionais e de pesquisa em segurança. O código aqui presente NÃO deve ser utilizado para atividades ilegais ou maliciosas. O autor não se responsabiliza pelo uso indevido deste material.

## Funcionalidades

### Módulos de Limpeza

| Módulo | Descrição | Arquivos Alvo |
|--------|-----------|---------------|
| **Logs de Execução** | Remove logs de inicialização de aplicativos | `.log`, `.txt`, `.dat`, `.etl`, `.evtx` |
| **Documentos Recentes** | Limpa atalhos e listas de recentes | `.lnk`, `.url` |
| **Logs USB** | Remove registros de dispositivos conectados | Logs de USBSTOR e ConnectedDevices |
| **Logs de Download** | Limpa downloads em andamento e histórico | `.crdownload`, `.part` |

### Segurança Integrada

- **Paths Protegidos**: Nunca acessa `System32`, `Program Files`, etc.
- **Extensões Bloqueadas**: Não remove `.exe`, `.dll`, `.sys`, etc.
- **Verificação de Tamanho**: Arquivos >50MB são ignorados
- **Profundidade Máxima**: Recursão limitada a 3 níveis
- **Log Detalhado**: Cada operação é registrada com timestamp

## Arquitetura

```
PrivacyLogCleaner/
├── promts.txt              # Código principal (845 lines)
├── src/
│   ├── CleanupStats.cpp    # Estatísticas de limpeza
│   ├── Config.cpp          # Configurações globais
│   └── Logger.cpp          # Sistema de logging
├── include/
│   └── ...                 # Headers
├── PrivacyLogCleaner.slnx  # Solução Visual Studio
└── README.md               # Esta documentação
```

## Módulos Detalhados

### 1. AppExecutionLogsModule
- Limpa logs de execução de aplicativos
- Remove dados do Windows Explorer e WER
- Processa diretórios temporários

### 2. RecentFilesModule
- Remove atalhos `.lnk` da pasta Recent
- Limpa lista de documentos recentes do sistema
- Utiliza `SHAddToRecentDocs` para limpar a lista interna

### 3. USBLogsModule
- Identifica registros de dispositivos USB
- Processa logs do ConnectedDevicesPlatform
- Verifica USBSTOR no registro (modo leitura)

### 4. DownloadLogsModule
- Remove downloads incompletos (`.crdownload`, `.part`)
- Limpa histórico de downloads de navegadores
- Processa Chrome, Edge, Brave e Firefox

## Tecnologias

| Tecnologia | Uso |
|------------|-----|
| C++17 | Linguagem principal |
| Windows API | SHGetFolderPath, Registry, CreateFile |
| STL filesystem | Navegação de diretórios |
| STL chrono | Timestamps e logging |
| STL regex | Padronização de nomes de arquivo |

## Como Compilar

```bash
# Requer Visual Studio com C++ Desktop Development
# Abra PrivacyLogCleaner.slnx e compile (x64 Release)
```

## Conceitos Estudados

### Anti-Forensics
- Windows Event Logs (`.evtx`)
- Prefetch files
- Recent documents
- USB device history
- Browser download history

### Windows API
- `SHGetFolderPath` - Obter paths do sistema
- `CreateFile` - Verificar se arquivo está em uso
- `RegOpenKeyEx` - Acessar registro do Windows
- `SHAddToRecentDocs` - Limpar lista de recentes

### Segurança
- Verificação de extensões permitidas/bloqueadas
- Proteção de paths do sistema
- Tratamento de erros e exceções

## Autor

**Rafael Melinsky** - Pesquisador de Segurança

- GitHub: [@melinskyRf](https://github.com/melinskyRf)
- Site: [devmelinsky.site](https://devmelinsky.site)

---

> 📚 **Conteúdo Educativo** - Para aprender sobre anti-forensics e privacidade digital.
