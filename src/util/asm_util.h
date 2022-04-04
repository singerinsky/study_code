#ifndef E5368C39_4C74_487E_813A_0C28902301B2
#define E5368C39_4C74_487E_813A_0C28902301B2

#define cpu_relax() asm volatile("pause\n": : :"memory")

#endif /* E5368C39_4C74_487E_813A_0C28902301B2 */
