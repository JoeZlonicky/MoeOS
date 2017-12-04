.section .init
  /* crtend object file .init section will get placed here */
  popl %ebp
  ret

.section .fini
  /* crtend object file .fini section will get placed here */
  popl %ebp
  ret
