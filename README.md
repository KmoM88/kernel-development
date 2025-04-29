# Kernel Development
Guía de introducción al desarrollo sobre el kernel de Linux

Este proyecto tiene como objetivo ser una guía introductoria para aprender y explorar el desarrollo sobre el kernel de Linux. A continuación, se presenta el índice de los temas que se abordarán:

## Índice

1. **[Fundamentos esenciales](./1-fundamentos-esenciales.md)** 
   - ¿Qué es el kernel de Linux y cómo se estructura?  
   - Monolítico vs microkernel  
   - Kernel space vs user space  
   - Arquitectura básica del kernel:  
     - Planificación de procesos  
     - Gestión de memoria  
     - Sistemas de archivos  
     - Controladores de dispositivos (drivers)  

2. **[Entorno de desarrollo](./2-entorno-de-desarrollo.md)**
   - Preparar un entorno seguro (máquina virtual o Raspberry Pi)  
   - Descargar y compilar el kernel  
   - Obtener el código: [git.kernel.org](https://git.kernel.org)  
   - Compilar y bootear con tu kernel  
   - Introducción al Makefile del kernel  
   - Herramientas útiles:  
     - `gcc`, `make`, `gdb`, `qemu`, `cscope`, `ctags`  

3. **Primeros pasos prácticos**  
   - Leer código fuente del kernel (por ejemplo, `/kernel/sched/`, `/mm/`, `/drivers/`)  
   - Crear un módulo del kernel simple  
     - `hello_world.ko`  
     - Uso de `insmod`, `rmmod`, `dmesg`  
   - Comunicación entre kernel y user space (`printk`, `/proc`, `/sys`)  

4. **Desarrollo de módulos**  
   - Hooks y puntos de extensión del kernel  
   - Acceso a memoria y estructuras del kernel  
   - Controladores de dispositivos (drivers):  
     - Character device drivers  
     - Bloque vs carácter  
     - Ejemplo: leer/escribir desde user space a un driver  

5. **Depuración y testing**  
   - Uso de `printk`, `dmesg`, `gdb`, `ftrace`, `perf`  
   - Verificación de errores (`checkpatch.pl`, `sparse`, `smatch`)  
   - Pruebas en `qemu` o máquinas virtuales  
   - Uso de `kprobes`, `eBPF` y tracing  

6. **Internals y subsistemas del kernel**  
   - El scheduler (`kernel/sched/`)  
   - Gestión de memoria (`mm/`)  
   - System calls (`arch/`, `kernel/sys.c`)  
   - Sysfs y Procfs  
   - Locks, semáforos, y concurrencia  
   - Interrupts y manejo de hardware  

7. **Contribuir al kernel (nivel avanzado)**  
   - Estilo de código del kernel ([Documentation/process](https://www.kernel.org/doc/html/latest/process/index.html))  
   - Uso de `git` para parches (`git format-patch`, `git send-email`)  
   - Herramientas para contribuir (`scripts/checkpatch.pl`)  
   - Suscribirte a listas de correo  
   - Enviar tu primer parche  

8. **Casos de estudio y proyectos**  
   - Crear tu propio sistema de archivos  
   - Hacer un scheduler básico  
   - Implementar una syscall propia (en laboratorio)  
   - Portar el kernel a una arquitectura pequeña (ej: ARM, Raspberry)  

¡Bienvenido al mundo del desarrollo del kernel de Linux!
