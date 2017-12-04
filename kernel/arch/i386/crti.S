.section .init
.global _init
.type _init, @function
_init:
  push %ebp
  movl %esp, %ebp
  /* crtbegin object files .init sections will get placed here */

.section .fini
.global _fini
.type _fini, @function
_fini:
  push %ebp
  movl %esp, %ebp
  /* crtbegin object files .fini sections will get placed here */
