# Un clon de Space Invaders

<!-- Esta cosa centra el gif-->
<p align="center">

<img width="900" src="https://user-images.githubusercontent.com/39320840/69807595-af888780-11b3-11ea-8aaa-e94eb0491656.gif">

</p>

## Instalación
### Linux
#### Arch Linux
Puedes instalarlo desde el [aur](https://aur.archlinux.org/packages/spaceclones-git/).

#### Otros distros
Primero tienes que instalar las dependencias:
* `cmake`
* `fontconfig`
* `git`
* `grep`
* `sed`
* `sfml`
* `ttf-liberation`

Después debes clonar este repositorio:

``` bash
git clone https://github.com/L603/SpaceClones
```

Y al final compilarlo.

``` bash
cd SpaceClones
cmake .
make
sudo make install
```

Si usas `Ubuntu 18.04` tendrás que usar `g++-8`,
para que C++17 funcione.

### Windows
Instala Linux.
### MacOS
Instala Linux.
