# InkClock-ESP

Controle de funções da placa [LilyGo T5 V2.3](https://www.lilygo.cc/products/t5-v2-3-1) \([aliexpress](https://pt.aliexpress.com/item/1005003063164032.html)\) com a tela monocromática __DEPG0213BN__

> [!IMPORTANT]
> Siga as instruções de instalação das dependências no Arduino IDE no \([Github oficial da placa](https://github.com/Xinyuan-LilyGO/LilyGo-T5-Epaper-Series)\) antes de clonar este repositório!

# Funções

## Conexão via rede local

A placa expõe uma api json para troca de informações e acesso de funções

## Texto

Mostra um texto centralizado no display

## Data e hora

Mostra a data e hora em um formato definido pelo usuário, sendo possível sincronização com um servidor NTP

# Funções futuras

- [ ] Configuração automática da fonte: maximiza o texto centralizado
- [ ] Configuração manual da fonte. O texto será "cortado" caso seja maior que as dimensões da tela
- [ ] Nome amigável (como um endereço web) na conexão via API JSON (mdns)
- [ ] API JSON expõe página de configuração com interface gráfica
- [ ] Mostrar uma imagem arbitrária, deve cortar e fazer a conversão no dispositivo
- [x] Configurar o formato de [data e hora](#-data-e-hora)
- [ ] Sincronização de informações sobre bateria
- [ ] Conexão via bluetooth com android, windows, linux, via browser e (talvez) ios

