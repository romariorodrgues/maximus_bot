# 🤖 Robô Maximus - Projeto Arduino Completo

![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow)
![Arduino](https://img.shields.io/badge/Arduino-Mega%202560-blue)
![Licença](https://img.shields.io/badge/Licença-MIT-green)

## 📋 Visão Geral

O **Robô Maximus** é um projeto completo de robótica utilizando Arduino Mega 2560. Ele combina movimento autônomo com controle remoto via Bluetooth, possui sensores para desvio de obstáculos, display expressivo para "olhos" e servo motores para movimentação da cabeça e braços.

### ✨ Características Principais

- 🚗 **Locomoção**: Sistema de lagartas com motores DC
- 🎯 **Navegação Autônoma**: Sensores ultrassônicos para desvio de obstáculos
- 📱 **Controle Remoto**: Via Bluetooth usando smartphone
- 👁️ **Display Expressivo**: LCD 16x2 simulando olhos do robô
- 🦾 **Movimentos Articulados**: Servo motores para cabeça e braços
- 🔋 **Autonomia**: Sistema de bateria com regulagem de tensão

## 🎥 Demonstração

```
┌─────────────────────────────────┐
│          MAXIMUS ONLINE         │
│          AUTO D:25cm            │
└─────────────────────────────────┘
     👁️                    👁️
```

## 📁 Estrutura do Projeto

```
maximus/
├── 📂 src/
│   └── maximus_robot.ino      # Código principal do Arduino
├── 📂 docs/
│   ├── componentes.md         # Lista completa de componentes
│   └── montagem.md           # Instruções de montagem
├── 📂 schematics/
│   └── esquemas.md           # Diagramas elétricos
├── 📂 libraries/
│   └── (bibliotecas customizadas)
└── README.md                 # Este arquivo
```

## 🛠️ Componentes Principais

| Componente | Quantidade | Função |
|------------|------------|--------|
| Arduino Mega 2560 | 1 | Microcontrolador principal |
| Motor DC + Lagartas | 2 | Sistema de locomoção |
| HC-SR04 | 2 | Sensores ultrassônicos |
| Servo SG90 | 3 | Cabeça e braços |
| LCD 16x2 | 1 | Display dos "olhos" |
| HC-05 | 1 | Módulo Bluetooth |
| L298N | 1 | Driver dos motores |
| Bateria LiPo 7.4V | 1 | Alimentação principal |

**💰 Custo Total Estimado**: R$ 850 - R$ 1.400

## 🚀 Início Rápido

### 1. Preparação
```bash
# Clone ou baixe o projeto
git clone https://github.com/seu-usuario/maximus-robot.git
cd maximus-robot
```

### 2. Hardware
- Adquira os componentes da [lista completa](docs/componentes.md)
- Siga as [instruções de montagem](docs/montagem.md)
- Consulte os [esquemas elétricos](schematics/esquemas.md)

### 3. Software
- Instale o Arduino IDE
- Abra o arquivo `src/maximus_robot.ino`
- Configure a placa: Arduino Mega 2560
- Faça o upload do código

### 4. Teste
- Conecte via Serial Monitor (9600 baud)
- Teste comandos básicos: `F`, `B`, `L`, `R`, `S`
- Configure o Bluetooth no smartphone

## 🎮 Comandos de Controle

### Via Serial/Bluetooth
| Comando | Ação |
|---------|------|
| `F` | Mover para frente |
| `B` | Mover para trás |
| `L` | Virar à esquerda |
| `R` | Virar à direita |
| `S` | Parar |
| `A` | Modo autônomo |
| `M` | Modo manual |
| `H` | Mover cabeça |
| `U` | Braços para cima |
| `D` | Braços para baixo |
| `+` | Aumentar velocidade |
| `-` | Diminuir velocidade |

### App Recomendado
- **Android**: Serial Bluetooth Terminal
- **iOS**: Compatible apps via App Store

## 🔧 Configuração Avançada

### Calibração dos Servos
```cpp
// No código Arduino, ajuste se necessário:
int headPosition = 90;        // Posição central da cabeça
int armLeftPosition = 90;     // Posição central do braço esquerdo  
int armRightPosition = 90;    // Posição central do braço direito
```

### Ajuste de Sensibilidade
```cpp
const int SAFE_DISTANCE = 20; // Distância segura em cm
int motorSpeed = 150;         // Velocidade dos motores (0-255)
```

## 📊 Especificações Técnicas

### Performance
- **Velocidade Máxima**: 0.5 m/s
- **Autonomia**: 2-4 horas
- **Alcance Bluetooth**: 10 metros
- **Detecção de Obstáculos**: 2cm - 400cm
- **Peso Total**: ~2kg

### Dimensões
- **Comprimento**: 30cm
- **Largura**: 20cm  
- **Altura**: 25cm

## 🔌 Alimentação

### Sistema Principal
```
Bateria LiPo 7.4V → Regulador LM2596 → Arduino 5V
                  ↓
              Motores DC (via L298N)
```

### Backup
```
Bateria 9V → Arduino VIN (emergência)
```

## 🐛 Troubleshooting

| Problema | Solução |
|----------|---------|
| Motores não funcionam | Verificar bateria e conexões L298N |
| Servo treme | Verificar alimentação 5V estável |
| Bluetooth não conecta | Resetar HC-05 e parear novamente |
| Sensor não detecta | Verificar cabos Trig/Echo |
| Display em branco | Ajustar potenciômetro de contraste |

## 🚀 Próximas Melhorias

- [ ] 📷 Câmera FPV para visão remota
- [ ] 🎤 Reconhecimento de voz
- [ ] 🌈 LEDs RGB para olhos mais expressivos
- [ ] 🦾 Garra funcional nos braços
- [ ] 🗺️ Sistema de mapeamento
- [ ] 🤖 Inteligência artificial básica

## 🤝 Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para:

1. 🍴 Fazer fork do projeto
2. 🌿 Criar uma branch para sua feature
3. 💻 Fazer commit das mudanças
4. 📤 Push para a branch
5. 🔀 Abrir um Pull Request

## 📄 Licença

Este projeto está sob a licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## 📞 Suporte

- **Documentação**: Verifique a pasta `docs/`
- **Issues**: Abra uma issue no GitHub
- **Email**: seu-email@exemplo.com

## 🎯 Status do Projeto

- ✅ Código Arduino funcional
- ✅ Lista de componentes completa
- ✅ Instruções de montagem detalhadas
- ✅ Esquemas elétricos
- 🔄 Testes em andamento
- ⏳ Documentação de troubleshooting

---

**Desenvolvido com ❤️ para a comunidade maker!**

> "Um robô não é apenas metal e circuitos, é a materialização de sonhos e criatividade."
