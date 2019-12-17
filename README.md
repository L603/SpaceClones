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
* `sfml`
* `ttf-liberation`

Después debes clonar este repositorio:

``` bash
git clone https://github.com/L603/SpaceClones
```

Y al final compilarlo.

``` bash
cd SpaceClones
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install
```

Si usas `Ubuntu 18.04` tendrás que usar `g++-8`,
para que C++17 funcione.

### Windows(Cross)

Dependencias:

* `git`
* `mingw-w64-cmake`
* `mingw-w64-fontconfig`
* `mingw-w64-sfml`

``` bash
git clone https://github.com/L603/SpaceClones
```

``` bash
cd SpaceClones
mkdir build
cd build
x86_64-w64-mingw32-cmake ..
make -j$(nproc)
```

Después debes copiar los dll's necesarios a la misma carpeta,
moverlo a windows y ejecutarlo.

### MacOS

Instala Linux.
