# Módulo 3: Módulos del kernel

## Objetivo
Aprender a crear, compilar, instalar y cargar módulos en el kernel mínimo generado en el capitulo anterior.

---

### 1. Crear un módulo básico: `hello.c`

Primero, crearemos un módulo básico llamado `hello.c`. Este módulo imprimirá un mensaje al cargarse y descargarse del kernel. El código fuente del módulo se encuentra en el archivo [`hello.c`](03-modulos-del-kernel/hello.c).

---

### 2. Crear un Makefile para compilar el módulo

Creamos un archivo `Makefile` para compilar el módulo. El contenido del Makefile se encuentra en [`Makefile`](03-modulos-del-kernel/Makefile).

---

### 3. Recompilar el kernel con soporte para módulos

Para habilitar o deshabilitar el soporte para módulos, recompilaremos el kernel con la opción correspondiente.

**Comandos:**
```bash
make O=$LINUX_BUILD_DIR menuconfig
```

Dentro de "General setup", activa la opción "Enable loadable module support".

![menuconfig-modules](img/menuconfig-modules.png)

Luego, recompila el kernel:
```bash
make O=$LINUX_BUILD_DIR -j$(nproc)
```

---

### 4. Compilar el módulo

Antes de compilar el módulo, prepara el entorno para módulos:
```bash
make O=$LINUX_BUILD_DIR modules_prepare
```

Luego, compila los modulos para generar ```Module.symvers```:
```bash
make O=$LINUX_BUILD_DIR modules
```

Ahora, compila el módulo `hello.c`:
```bash
make -C /path/to/kernel O=$LINUX_BUILD_DIR M=$PWD modules
```
Asegúrate de reemplazar `/path/to/kernel` con la ruta correcta al directorio del kernel.

Esto generará un archivo `hello.ko`, que es el módulo compilado.

---

### 5. Mover el módulo al initramfs

Para que el módulo esté disponible en el sistema mínimo, copia el archivo `hello.ko` al initramfs.

**Comandos:**
```bash
cp hello.ko /home/$USER/initramfs/lib/modules/$(uname-r)
```

Usa ```modules_install``` para instalar el módulo en el initramfs:
```bash
make -C /path/to/kernel O=$LINUX_BUILD_DIR M=$PWD modules_install INSTALL_MOD_PATH=/home/$USER/initramfs
```


Actualiza el initramfs:
```bash
cd /home/$USER/initramfs
find . -print0 | cpio --null --create --verbose --format=newc | gzip --best > ./custom-initramfs.cpio.gz
```

---

### 6. Cargar y descargar el módulo en QEMU

Ejecuta el kernel con el initramfs actualizado:
```bash
qemu-system-x86_64 -kernel $LINUX_BUILD_DIR/arch/x86/boot/bzImage -nographic -append "earlyprintk=serial,ttyS0 console=ttyS0 debug" --initrd $INITRAMFS_DIR
```

Dentro del sistema mínimo, carga el módulo:
```bash
insmod /lib/modules/hello.ko
dmesg | tail -n 20
```

Verifica que el módulo esté cargado:
```bash
lsmod
```

Consulta información sobre el módulo:
```bash
modinfo /lib/modules/hello.ko
```

Descarga el módulo:
```bash
rmmod hello
dmesg | tail -n 20
```

Verifica que se haya descargado:
```bash
lsmod
```

---

### 7. Resumen

En este módulo, aprendiste a crear un módulo básico, compilarlo, instalarlo en el initramfs y cargarlo en el kernel mínimo. Esto te permite extender la funcionalidad del kernel de manera modular.