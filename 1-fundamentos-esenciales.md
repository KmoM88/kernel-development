# Módulo 1: Fundamentos esenciales del kernel de Linux

## Objetivo
Comprender qué es el kernel, cómo se relaciona con el resto del sistema, y conocer su estructura básica.

### 1. ¿Qué es el kernel de Linux?
El kernel es el núcleo del sistema operativo. Es responsable de:
- Gestionar procesos y memoria.
- Interactuar con hardware (a través de drivers).
- Proveer servicios al espacio de usuario (vía syscalls).

**Ejercicio:**  
Abre una terminal y ejecuta:
```bash
uname -r      # Muestra la versión del kernel
cat /proc/version
```

### 2. Espacio de usuario vs espacio del kernel
- **User space**: Donde corren los programas comunes (bash, Firefox, etc).
- **Kernel space**: Donde corre el kernel y sus módulos/drivers.

El sistema cambia de user space a kernel space cuando un proceso hace una syscall.

Ejercicio:
Usa strace para ver cómo un programa entra al kernel:

- Ver qué archivos abre un programa
```bash
strace -e openat cat /etc/passwd
```

- Ver las llamadas de red
```bash
strace -e trace=network curl https://google.com
```
Identificar las llamadas como socket, connect, sendto, recvfrom, etc. Ideal para debug de problemas de red.

- Detectar errores de permisos o archivos faltantes
```bash
strace -e trace=file ls /root
strace bash script.sh
```

- Ver qué procesos se crean
```bash
strace -f ls /home
```

- Tiempo que toma cada syscall
```bash
strace -T ls
strace -t ls
strace -tt ls
```
Muestra cuánto tarda cada llamada al sistema, útil para detectar cuellos de botella.

- Contar cuántas veces se llama cada syscall
```bash
strace -c ls
```

### 3. Arquitectura básica del kernel

Explora los principales componentes:

- `/kernel/` → planificación de procesos
- `/mm/` → administración de memoria
- `/drivers/` → controladores de hardware
- `/fs/` → sistema de archivos
- `/arch/` → código específico por arquitectura

Ejercicio:
Baja el código fuente del kernel:

```bash
git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/
```

Navega las carpetas y usa `tree` o `ls` para explorar.

### 4. Tipos de kernels
- **Monolítico**: Todo el sistema (incluyendo drivers) corre en modo kernel. Ej: Linux.
- **Microkernel**: Solo el núcleo básico corre en kernel space. Ej: Minix, QNX.

### 5. Versión del kernel

Linux tiene versiones:

- **Estables** (ej: 6.1.x)
- **LTS** (Long Term Support) – se mantienen por años
- **RC** (Release Candidate) – candidatas a nuevas versiones

Ejercicio:
Visita [https://www.kernel.org/](https://www.kernel.org/) y anota:

- Última versión estable
- Última versión LTS
- Qué versión tienes instalada con `uname -r`