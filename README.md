# <img alt="Logo" height="25" src="assets/logo.png" width="25"/> StreamDeckDeeJ - Arduino

Module embarqué spécialisé pour le **Raspberry Pi Pico 2020**, recevant et exécutant les commandes de l’application desktop [StreamDeck-DeeJ-App](https://github.com/lachaux-remi/StreamDeckDeeJ-App) via USB natif et protocole série optimisé.

---

## ⚙️ Prérequis

- **Raspberry Pi Pico 2020**.
- **Arduino IDE**.

---

## 🚀 Installation et déploiement

1. **Clonage du dépôt**
   ```bash
   git clone https://github.com/lachaux-remi/StreamDeckDeeJ-Arduino.git
   ```
2. **Préparation de l'Arduino IDE**
   - Dans **Tools > Board**, installe et sélectionne **Raspberry Pi Pico/RP2040/RP2350**.
   - Dans **Tools > USB Stack**, choisis **Adafruit TinyUSB**.
   - Installe les bibliothèques suivantes via **Tools > Manage Libraries** :
     - **Adafruit NeoPixel**
     - **IRremote**

3) **Export du binaire compilé**

   - Dans l’IDE Arduino, va dans **Sketch > Export Compiled Binary**.
   - Le fichier `*.uf2` généré se trouve dans le dossier du sketch (voir la console pour le chemin exact).

4) **Téléversement du binaire sur le Pico**

   - Déconnecte et reconnecte le Pico tout en maintenant le bouton **BOOTSEL** enfoncé pour entrer en mode bootloader.
   - Le Pico apparaît comme un lecteur USB nommé `RPI-RP2`.
   - Copie le fichier `*.uf2` sur ce lecteur pour flasher le firmware.

---

## 📖 Usage

1. Branche le Pico 2020 via USB.
2. Lance l’application **StreamDeck-DeeJ-App**.
3. Sélectionne le port série du Pico 2020.
4. Vérifie les actions depuis l’interface pour valider le déploiement.

---

## 📝 Licence

Distribué sous licence MIT. Voir [LICENSE](./LICENSE) pour les détails.

---

## 👤 Auteur

**Rémi Lachaux** – mainteneur principal ([lachaux-remi](https://github.com/lachaux-remi))

