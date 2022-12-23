# ASCII Art Generator


## Description
The project wants to generate ASCII Art from different inputs with C++ by using [OpenCV Library](https://opencv.org/).

![alt text](images/readme.png)

### Features
Accepted input:
- File Image in PNG;
- File GIF in GIF;
- File Video in MP4;


## Installation
### OpenCV
The project was developed in Ubuntu. Following the [install OpenCV](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html) documentation, open a terminal (`shift + alt + t`) and type the following:
```bash
sudo apt update
```

#### Dependence's
```bash
sudo apt install git
sudo apt install -y g++

sudo apt install -y cmake
sudo apt install -y make
```

#### Download Sources
Navegate to the `home/` folder and type:
```bash
git clone https://github.com/opencv/opencv.git
git -C opencv checkout 4.x
```
#### Configure and Build
In the `home/` folder type:
```bash
mkdir -p build && cd build
cmake ../opencv

make -j4
```
`-j4` means that the OpenCV library will be compile using 4 cores. During installation `-j8`, using 8 cores, was tried and it took longer to compile, therefore we recommend to stay with the 4 cores option.

#### Install
Finally type the following command to install the OpenCV library:
```bash
sudo make install
```


## Usage
Lorem Ipsum
```cpp
int main(void) {

    return 0;
};
```
Code structure:

    .
    ├── ...
    ├── main.cpp                # main file
    ├── images                  
    │   ├── ...
    │   └── readme.png          # README.md main image
    └── ...

## Support
Lorem Ipsum
> **Q:** question?
>
> **A:** answer.

## Roadmap
This project had incremental goals:
1. Open a file in:
   - PNG;
   - GIF;
   - MP4;
    
    And converting into an ASCII Art;

2. Use real-time input from the computer's webcam;

3. Save into a `.txt` with:
   - Custom size;
   - *WhatsApp*; 
   - *Telegram*;

## Authors and Acknowledment
- Guilherme TROFINO:
  - [![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/guilherme-trofino/)
  - [![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/tr0fin0)
- Gustavo JODAR:
  - [![Linkedin](https://i.stack.imgur.com/gVE0j.png) LinkedIn](https://www.linkedin.com/in/gustavo-jodar/)
  - [![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/Gustavo-Jodar)

We greatly appreciate our [IN204](https://synapses.ensta-paris.fr/catalogue/2020-2021/ue/3722/IN204-oriente-objet-programmation-et-genie-logiciel?from=D2) teachers at [ENSTA](https://www.ensta-paris.fr/):
- Bruno Monsuez
- Jean-Baptiste Laurent

More information in the [webpage](https://perso.ensta-paris.fr/~bmonsuez/Cours/doku.php?id=in204).

## License
Lorem Ipsum [License](https://choosealicense.com/licenses/)