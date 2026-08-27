# DSboy - PipboyOS

> A Pip-Boy interface built for NintendoDSi/Raspberry Pi (and other systems), inspired by the iconic wearable computer from the *Fallout* series.

![License](https://img.shields.io/badge/license-MIT-green)

## 📊 About

**DSboy - PipboyOS** aims to bring a functional, real-life recreation of the Pip-Boy from *Fallout* to life using a Raspberry Pi (or compatible single-board computers). The goal is to combine the retro-futuristic aesthetic of the in-game device with real hardware, so you can build and wear your own working Pip-Boy.

## 🧮 Features

- Pip-Boy-style graphical interface (Fallout-inspired UI)
- Designed to run on Raspberry Pi and other compatible systems
- Custom assets for an authentic retro-terminal look

> ℹ️ This section is a starting point — feel free to expand it with the specific tabs/menus (STAT, INV, DATA, MAP, RADIO, etc.) and features your build actually supports.

## 🧱 Repository structure

```
DSBoy-Pipboy/
├── assets/    # Images, fonts, icons and other UI resources
├── source/    # Application source code
├── LICENSE    # MIT License
└── README.md
```

## Requirements

- Raspberry Pi (or another compatible single-board computer)
- [List any specific OS, Python version, or libraries your project depends on]
- [List any hardware components, e.g. display, buttons, enclosure]

## 💾 Installation

```bash
# Clone the repository
git clone https://github.com/cout-magicgnom/DSBoy-Pipboy.git
cd DSBoy-Pipboy

# Run the project
gcc main.c system/inventario.c system/audio.c -o main
cd source
./main

```

## Usage

To use the initial (terminal) version, simply use the numeric keys on the keyboard to navigate through the state machine. The next versions will update the navigation mechanism using the keyboard arrows.
```
 ==========================
  - PIPBOY OS - 1000A 
 ========================== 
 *STATS*   INV   DADOS   MAPA   RADIO


Escolha: 5

 ==========================
  - PIPBOY OS - 1000A 
 ========================== 
 STATS   INV   DADOS   MAPA   *RADIO*
1 - Mr. New Vegas
2 - Big Iron
3 - Blue Moon
4 - Johnny Guitar
5 - Heartaches
0 - Voltar

Escolha:
```
<!-- ## Roadmap

- [ ] Add build/wiring instructions
- [ ] Add screenshots or a demo video
- [ ] Document supported hardware (displays, buttons, enclosures)
- [ ] Add contribution guidelines -->

## Contributing

Contributions, issues and feature requests are welcome! Feel free to check the [issues page](https://github.com/cout-magicgnom/DSBoy-Pipboy/issues) or open a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Disclaimer

This is a fan-made, non-commercial project inspired by the Pip-Boy from the *Fallout* franchise. *Fallout* and *Pip-Boy* are trademarks of Bethesda Softworks / ZeniMax Media. This project is not affiliated with, endorsed by, or sponsored by Bethesda.
